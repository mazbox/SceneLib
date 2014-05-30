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
 *  QuadObject.h, created by Marek Bereza on 09/01/2014.
 */




#pragma once
#include "Object.h"

#ifdef TARGET_WIN32
#define GLUT_BUILDING_LIB
#include "glut.h"
#endif
#ifdef TARGET_OSX
#include <OpenGL/OpenGL.h>
#include "../../../libs/glut/lib/osx/GLUT.framework/Versions/A/Headers/glut.h"
#include <Carbon/Carbon.h>
#endif
#ifdef TARGET_LINUX
#include <GL/glut.h>
#include "ofIcon.h"
#include "ofImage.h"
#include <X11/Xatom.h>
#endif

class QuadObject: public Object {
public:
	ofVec2f quad[4];
	
	int pos;
	float slider;
	QuadObject() {
		slider = 0.5;
		pos = 0;
		name = "Quad";
		glutSetCursor(GLUT_CURSOR_FULL_CROSSHAIR);
		ofAddListener(ofEvents().mousePressed, this, &QuadObject::mousePressed);
		ofAddListener(ofEvents().mouseDragged, this, &QuadObject::mouseDragged);
		ofAddListener(ofEvents().mouseReleased, this, &QuadObject::mouseReleased);
	}
	

	
	virtual void parameterize(xmlgui::SimpleGui &gui) {
			printf("sdfkjsdfk\n");
		gui.addSlider("slider", slider, 0, 1);
	}
	
	
	void draw() {

		ofNoFill();
		
		ofBeginShape();
		for(int i = 0; i < pos; i++) {
			ofVertex(quad[i].x, quad[i].y);
		}
		ofEndShape();
		
		for(int i = 0; i < pos; i++) {
			ofCircle(quad[i], 4);
		}
		
		ofFill();
	}
	
	bool mousePressed(ofMouseEventArgs &m) {
		if(pos<=3) pos++;
		if(pos<=3) {
			quad[pos].set(m.x, m.y);
		}
	}
	
	bool mouseDragged(ofMouseEventArgs &m) {
		if(pos<=3) {
			quad[pos].set(m.x, m.y);
		}
	}
	
	bool mouseReleased(ofMouseEventArgs &m) {
		if(pos>=3) {
			glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
		}
	}
	
	
};


