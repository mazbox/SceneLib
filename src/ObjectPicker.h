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
 *  Picker.h, created by Marek Bereza on 10/10/2013.
 */

#pragma once

#include "Camera.h"
#include "Scene.h"
#include "UI.h"


class ObjectPicker {
public:
	Scene *scene;
	Camera *camera;
	UI *ui;
	
	
	
	int lastEventType;
	bool mustCheckSelection;
	ofVec2f clickPos;
	
	enum {
		MOUSE_DOWN = 0,
		MOUSE_UP = 1
	};
	bool shiftPressed;
	bool altPressed;
	
	
	void setup(Camera *camera, Scene *scene, UI *ui) {
		this->ui = ui;
		this->scene = scene;
		this->camera = camera;
		ofAddListener(ofEvents().mousePressed, this, &ObjectPicker::mousePressed);
		ofAddListener(ofEvents().mouseReleased, this, &ObjectPicker::mouseReleased);
		ofAddListener(ofEvents().keyPressed, this, &ObjectPicker::keyPressed);
		ofAddListener(ofEvents().keyReleased, this, &ObjectPicker::keyReleased);
		ofAddListener(ofEvents().update, this, &ObjectPicker::update);
		mustCheckSelection = false;
		lastEventType = 0;
		altPressed = false;
		shiftPressed = false;
	}
	
	
	
	void update(ofEventArgs &e) {
		if(mustCheckSelection) {
			ofEnableDepthTest();
			ofClear(0, 0, 0, 0);
			camera->begin();
			scene->drawForPicker();
			camera->end();
			ofColor c;
			ofDisableDepthTest();
			glReadPixels(
						 clickPos.x,
						 ofGetHeight() - clickPos.y,
						 1,1,GL_RGB, GL_UNSIGNED_BYTE, &c);
			printf("%u %u %u\n", c.r, c.g, c.b);
			
			
			
			if(c.r==255 && c.g==0 && c.b==1) {
				ui->axisGrabbed(AXIS_X, altPressed);
			} else if(c.r==0 && c.g==255 && c.b==1) {
				ui->axisGrabbed(AXIS_Y, altPressed);
			} else if(c.r==0 && c.g==0 && c.b==255) {
				ui->axisGrabbed(AXIS_Z, altPressed);
			} else {
			
				
				IndexedObject *obj = IndexedObject::getObjectForColor(c);
				
				if(shiftPressed) {
					ui->addSelectedObject((Object*)obj);
				} else {
					ui->setSelectedObject((Object*)obj);
					
				}
			}
				
			
				
			mustCheckSelection = false;
		}
		
		
	}
	
	
	void mousePressed(ofMouseEventArgs &m) {
		if(m.button!=0) return;
		clickPos.set(m.x, m.y);
		lastEventType = MOUSE_DOWN;
		mustCheckSelection = true;
	}
	
	void mouseReleased(ofMouseEventArgs &m) {
		if(m.button!=0) return;
		clickPos.set(m.x, m.y);
		lastEventType = MOUSE_UP;
		mustCheckSelection = true;
	}
	
	void keyPressed(ofKeyEventArgs &k) {
		if(k.key==OF_KEY_LEFT_SHIFT || k.key==OF_KEY_RIGHT_SHIFT) {
			shiftPressed = true;
		} else if(k.key==OF_KEY_LEFT_ALT || k.key==OF_KEY_RIGHT_ALT) {
			altPressed = true;
		}
	}
	
	void keyReleased(ofKeyEventArgs &k) {
		if(k.key==OF_KEY_LEFT_SHIFT || k.key==OF_KEY_RIGHT_SHIFT) {
			shiftPressed = false;
		} else if(k.key==OF_KEY_LEFT_ALT || k.key==OF_KEY_RIGHT_ALT) {
			altPressed = false;
		}
	}
	
	void draw() {
		camera->begin();
		scene->drawForPicker();
		camera->end();
	}
	
	
	
};