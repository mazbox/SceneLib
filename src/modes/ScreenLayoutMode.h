/**     ___           ___           ___                         ___           ___     
 *     /__/\         /  /\         /  /\         _____         /  /\         /__/|    
 *    |  |::\       /  /::\       /  /::|       /  /::\       /  /::\       |  |:|    
 *    |  |:|:\     /  /:/\:\     /  /:/:|      /  /:/\:\     /  /:/\:\      |  |:|    
 *  __|__|:|\:\   /  /:/~/::\   /  /:/|:|__   /  /:/~/::\   /  /:/  \:\   __|__|:|    
 * /__/::::| \:\ /__/:/ /:/\:\ /__/:/ |:| /\ /__/:/ /:/\:| /__/:/ \__\:\ /__/::::\____
 * \  \:\~~\__\/ \  \:\/:/__\/ \__\/  |:|/:/ \  \:\/:/~/:/ \  \:\ /  /:/    ~\~~\::::/
 *  \  \:\        \  \::/          |  |:/:/   \  \::/ /:/   \  \:\  /:/      |~~|:|~~ 
 *   \  \:\        \  \:\          |  |::/     \  \:\/:/     \  \:\/:/       |  |:|   
 *    \  \:\        \  \:\         |  |:/       \  \::/       \  \::/        |  |:|   
 *     \__\/         \__\/         |__|/         \__\/         \__\/         |__|/   
 *
 *  Description: 
 *				 
 *  ScreenLayout.h, created by Marek Bereza on 24/10/2013.
 */

#pragma once

#include "ofMain.h"

#include "Mode.h"

#include "ScreenObject.h"
#include "ScreenCanvasObject.h"
#include "UI.h"
#include "ofxMPEClient.h"


class ScreenLayoutMode: public Mode {
public:
	
	ScreenCanvasObject *canvas;
	vector<ScreenObject*> screens;
	RenderClientMode *renderClient;
	
	bool shiftDown;
	bool altDown;
	
	string getName() {
		return "Screen Layout";
	}
	
	UID selectedScreenUid;
	
	
	int lastSelectedScreenUid;
	string lastSelectedScreenString;
	
	Scene *scene;
	ofVec2f pMouse;
	bool scalingScreen;

	
	ScreenLayoutMode(Scene *scene) {
		lastSelectedScreenUid = -1;
		scalingScreen = false;
		selectedScreenUid = -1;
		enabled = false;
		load(scene);
		shiftDown = false;
		altDown = false;

	}
	
	
	void load(Scene *scene) {
		this->scene = scene;
		
		vector<HierarchicalObject*> outObjects;
		IndexedObject::getObjectsOfType(outObjects, "screen canvas");
		if(outObjects.size()>0) {

			this->canvas = (ScreenCanvasObject*) outObjects[0];
		} else {
			ofLogError() << "There are no screen canvases in the scene, ScreenLayoutMode will crash";
		}

	}

	

	void setRenderClientMode(RenderClientMode *mode) {
		renderClient = mode;
	}
	
	
	void sendAnyScreenPositionChanges() {
		if(IndexedObject::uidExists(selectedScreenUid)
		   && selectedScreenUid == lastSelectedScreenUid) {
			Object *obbr = (Object*)IndexedObject::get(selectedScreenUid);
			string serializedGui = obbr->serialize();
			if(serializedGui != lastSelectedScreenString) {
				ofxMPEClient::getInstance()->broadcast(
													   "screen: "+serializedGui
				);
				lastSelectedScreenString = serializedGui;
			}
			
		}
		
		
	}
	
	void reloadScreens() {
		// re-get the screens every frame incase they change
		vector<HierarchicalObject *> outObjects;
		scene->getObjectsOfType(outObjects, "screen");
		// use these
		screens.clear();
		
		
		for(int i = 0; i < outObjects.size(); i++) {
			screens.push_back((ScreenObject*)outObjects[i]);
		}
	}
	
	void drawMode() {
		
		
		reloadScreens();
		
		
		
		renderClient->draw();
		
		glPushMatrix();
		glScalef((float)ofGetWidth()/canvas->width, (float)ofGetHeight()/canvas->height, 1);
		for(int i = 0; i < screens.size(); i++) {
			screens[i]->drawFrame(UI::getInstance()->isSelected(screens[i]));
			
		}
		glPopMatrix();
	}
	
	
	
	bool mousePressed(ofMouseEventArgs &mm) {

		ofVec2f m(mm.x, mm.y);
		m /= ofVec2f((float)ofGetWidth()/canvas->width, (float)ofGetHeight()/canvas->height);
		for(int i = 0; i < screens.size(); i++) {
			if(screens[i]->sourceRect.inside(m)) {
				UI::getInstance()->setSelectedObject(screens[i]);
				if(ABS(screens[i]->sourceRect.getRight()-m.x)<canvas->width*10.f/ofGetWidth()
				   
				   &&
				   ABS(screens[i]->sourceRect.getBottom()- m.y)<canvas->height*10.f/ofGetHeight()
				   ) {
					scalingScreen = true;
				} else {
					scalingScreen = false;
				}
				selectedScreenUid = screens[i]->uid;;
				lastSelectedScreenUid = selectedScreenUid;
				lastSelectedScreenString = screens[i]->serialize();
				
				pMouse = m;
				return true;
			}
		}
		
		lastSelectedScreenUid = -1;
		lastSelectedScreenString = "";
		selectedScreenUid = -1;
		UI::getInstance()->setSelectedObject(NULL);
		return false;
	}
	
	bool keyReleased(ofKeyEventArgs &k) {
		int key = k.key;
		if(key==OF_KEY_SHIFT || key==OF_KEY_LEFT_SHIFT || key==OF_KEY_RIGHT_SHIFT) {
			shiftDown = false;
			return false;
		}
		
		if(key==OF_KEY_ALT || key==OF_KEY_LEFT_ALT || key==OF_KEY_RIGHT_ALT) {
			altDown = false;
			return false;
		}
		return false;
	}
	bool keyPressed(ofKeyEventArgs &k) {

#ifdef TARGET_OSX
		shiftDown = CGEventSourceFlagsState(kCGEventSourceStateHIDSystemState) & kCGEventFlagMaskShift;
		altDown =   CGEventSourceFlagsState(kCGEventSourceStateHIDSystemState) & kCGEventFlagMaskAlternate;;
#endif

		int key = k.key;
		if(key==OF_KEY_SHIFT || key==OF_KEY_LEFT_SHIFT || key==OF_KEY_RIGHT_SHIFT) {
			shiftDown = true;
			return false;
		}
		
		if(key==OF_KEY_ALT || key==OF_KEY_LEFT_ALT || key==OF_KEY_RIGHT_ALT) {
			altDown = true;
			return false;
		}
		
		
		float dx = 0;
		float dy = 0;
		if(k.key==OF_KEY_LEFT) {
			dx = -1;
		} else if(k.key==OF_KEY_RIGHT) {
			dx = 1;
		} else if(k.key==OF_KEY_UP) {
			dy = -1;
		} else if(k.key==OF_KEY_DOWN) {
			dy = 1;
		}
		
		if(shiftDown) {
			dx *= 10;
			dy *= 10;
		}
		

		
		float increment = 1; // 1mm
		
		dx *= increment;
		dy *= increment;
		

		
		if(IndexedObject::uidExists(selectedScreenUid)) {
			ScreenObject *screen = (ScreenObject*) IndexedObject::get(selectedScreenUid);
			if(altDown) {
				screen->sourceRect.height += dx;
				screen->sourceRect.height += dy;
			} else {
				screen->sourceRect.x += dx;
				screen->sourceRect.y += dy;
			}
			return true;
		}
		return false;
	}
	
	bool mouseDragged(ofMouseEventArgs &mm) {
		ofVec2f m(mm.x, mm.y);
		m /= ofVec2f((float)ofGetWidth()/canvas->width, (float)ofGetHeight()/canvas->height);

		if(IndexedObject::uidExists(selectedScreenUid)) {
			ofVec2f delta = m - pMouse;

			ScreenObject *screen = (ScreenObject*) IndexedObject::get(selectedScreenUid);
			if(scalingScreen) {
				screen->sourceRect.width  += delta.x;
				screen->sourceRect.height += delta.y;
			} else {
				screen->sourceRect.x += delta.x;
				screen->sourceRect.y += delta.y;
			}
			pMouse = m;
			return true;
		}
		return false;
	}
	
	bool mouseReleased(ofMouseEventArgs &m) {
		//selectedScreen = NULL;
		//lastSelectedScreenUid = -1;
		return false;
	}
	
	void fromMPEServer(const string &inp) {

		if(lastSelectedScreenUid!=-1) return;

		
		// have to do this to stop an infinite loop
		lastSelectedScreenString = inp;
		ofxXmlSettings xml;
		xml.loadFromBuffer(inp);
		xml.pushTag("object");
		int numSettings = xml.getNumTags("setting");
		int uid = -1;
		for(int i = 0; i < numSettings; i++) {
			if(xml.getAttribute("setting", "id", "", i)=="uid") {
				uid = xml.getAttribute("setting", "value", 0, i);
				//printf("UID: %d\n", uid);
			}
		}
		
		
		
		if(uid==-1) {
			ofLogError("ScreenLayoutMode") << "Can't find UID";
			return;
		}
		
		reloadScreens();
		
		// now update the actual screen
		for(int i = 0; i < screens.size(); i++) {
			if(screens[i]->uid==uid) {
				//printf("Found a screen to deserialize into\n");
				screens[i]->deserialize(inp);
				return;
//				break;
				
			//} else {
			//	printf("%d != %d\n", screens[i]->uid, uid);
			}
		}
		//printf("Hit the bottom\n");
	}
	
	
	
private:
	bool enabled;
};