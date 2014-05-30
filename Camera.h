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
 *  Camera.h, created by Marek Bereza on 10/10/2013.
 */

#pragma once
#include "Object.h"
#include <sstream>

// largely based on Elliot Woods' ofxGrabCam

class Camera: public ofCamera {
public:
	bool interactionEnabled;
	
	Camera(): ofCamera() {
		interactionEnabled = false;
		enableInteraction();
		setNearClip(0.001);
	}
	
	// shift pans
	// alt zooms
	// mouse wheel zooms
	bool shiftDown = false;
	bool altDown = false;
	
	//--------------------------------------------------------------
	void keyPressed(ofKeyEventArgs &e){
		if(e.key==OF_KEY_LEFT_SHIFT || e.key==OF_KEY_RIGHT_SHIFT) {
			shiftDown = true;
		} else if(e.key==OF_KEY_RIGHT_ALT || e.key==OF_KEY_LEFT_ALT) {
			altDown = true;
		}
		
	}
	
	//--------------------------------------------------------------
	void keyReleased(ofKeyEventArgs &e){
		if(e.key==OF_KEY_LEFT_SHIFT || e.key==OF_KEY_RIGHT_SHIFT) {
			shiftDown = false;
		} else if(e.key==OF_KEY_RIGHT_ALT || e.key==OF_KEY_LEFT_ALT) {
			altDown = false;
		}
	}
	


	
	
	void enableInteraction() {
		
		if(interactionEnabled) return;

		ofAddListener(ofEvents().mousePressed, this, &Camera::mousePressed);
		ofAddListener(ofEvents().mouseDragged, this, &Camera::mouseDragged);
		ofAddListener(ofEvents().keyPressed, this, &Camera::keyPressed);
		ofAddListener(ofEvents().keyReleased, this, &Camera::keyReleased);

		interactionEnabled = true;
	}
	
	void disableInteraction() {
		if(!interactionEnabled) return;
		ofRemoveListener(ofEvents().mousePressed, this, &Camera::mousePressed);
		ofRemoveListener(ofEvents().mouseDragged, this, &Camera::mouseDragged);
		ofRemoveListener(ofEvents().keyPressed, this, &Camera::keyPressed);
		ofRemoveListener(ofEvents().keyReleased, this, &Camera::keyReleased);
	
		interactionEnabled = false;
	}
	
	
	ofVec2f mouseP;
	
	ofQuaternion rotation;
	//
	bool		fixUpwards;
	float		trackballRadius = 0.1;
	//--------------------------------------------------------------
	void mouseDragged(ofMouseEventArgs &m){
		if(m.button==0) {
			return;
		} else {
			float dx = (m.x - mouseP.x) / ofGetViewportWidth();
			float dy = (m.y - mouseP.y) / ofGetViewportHeight();
			mouseP.set(m.x, m.y);
			
			ofVec3f p = getPosition();
			ofVec3f uy = getUpDir();
			ofVec3f ux = getSideDir();
			float ar = float(ofGetViewportWidth()) / float(ofGetViewportHeight());
			
			// centre
			ofVec3f w = ofVec3f();
			
			if(shiftDown) {
				//pan
				float d = (p - w).length();
				//ofCamera::getFov() doesn't exist!!
				move(dx * -ux * d * ar);
				move(dy * uy * d);
			} else if(altDown) {
				move(2 * (w - p) * -dy);
			} else {
				
				
				ofVec3f arcEnd(dx, -dy, -trackballRadius);
				arcEnd.normalize();
				ofQuaternion orientation = getGlobalOrientation();
				rotation.makeRotate(orientation * ofVec3f(0.0f, 0.0f, -1.0f), orientation * arcEnd);
				
				//if (fixUpwards) {
				ofQuaternion rotToUp;
				ofVec3f sideDir = getSideDir() * rotation;
				rotToUp.makeRotate(sideDir, sideDir * ofVec3f(1.0f, 0, 1.0f));
				rotation *= rotToUp;
				//}
				setOrientation(getGlobalOrientation() * rotation);
				ofCamera::setPosition((p - w) * rotation + w);
				
			}
		}
		
		
	}
	
	
	void mouseScrolled(float x, float y) {
		ofVec3f p = getPosition();
		
		// centre
		ofVec3f w = ofVec3f();
		move(0.2 * (w - p) * -y);
	}
	
	
	//--------------------------------------------------------------
	void mousePressed(ofMouseEventArgs &m) {
		mouseP.set(m.x, m.y);
	}
	
	void save(string xmlPath) {
		ofxXmlSettings xml;
		

		
		const ofMatrix4x4 &mat = getLocalTransformMatrix();
		xml.addTag("camera");
		for(int i = 0; i < 16; i++) {
			xml.addAttribute("camera", "mat"+ofToString(i), mat.getPtr()[i], 0);
		}
		xml.saveFile(xmlPath);
	}
	
	void load(string xmlPath) {
		ofxXmlSettings xml;
		xml.loadFile(xmlPath);
		ofMatrix4x4 mat;
		for(int i = 0; i < 16; i++) {
			mat.getPtr()[i] = xml.getAttribute("camera", "mat" + ofToString(i), mat.getPtr()[i], 0);
		}
		
		
		setTransformMatrix(mat);

		
	}
	
	

};