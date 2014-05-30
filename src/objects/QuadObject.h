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
	ofVec2f texCoords[4];
	ofVec2f vertices[4];
	
	int pos;
	float slider;
	QuadObject() {
		
		texCoords[0].set(0,0);
		texCoords[1].set(1,0);
		texCoords[2].set(1,1);
		texCoords[3].set(0,1);
		
		vertices[0].set(0,0);
		vertices[1].set(100,0);
		vertices[2].set(100,100);
		vertices[3].set(0,100);
		
		// register with the global quad list
		quads.push_back(this);
		
		slider = 0.5;
		pos = 0;
		name = "Quad";
		glutSetCursor(GLUT_CURSOR_FULL_CROSSHAIR);
		ofAddListener(ofEvents().mousePressed, this, &QuadObject::mousePressed);
		ofAddListener(ofEvents().mouseDragged, this, &QuadObject::mouseDragged);
		ofAddListener(ofEvents().mouseReleased, this, &QuadObject::mouseReleased);
	}
		
	~QuadObject() {
		for(int i = 0; i < quads.size(); i++) {
			if(quads[i]==this) {
				quads.erase(quads.begin() + i);
			}
				
		}
	}

	
	virtual void parameterize(xmlgui::SimpleGui &gui) {
		float xx;
		
		
		
		for(int i = 0; i < 4; i++) {
			xmlgui::Control *g = gui.addFloatField("v["+ofToString(i)+"].x", vertices[i].x);
			if(i==0) xx = g->x;
			align2(xx,
				   g,
				   gui.addFloatField("v["+ofToString(i)+"].y", vertices[i].y)
				   );
		}
		
		gui.addHR()->x = xx;
		
		for(int i = 0; i < 4; i++) {
			align2(xx,
				   gui.addFloatField("tc["+ofToString(i)+"].x", texCoords[i].x),
				   gui.addFloatField("tc["+ofToString(i)+"].y", texCoords[i].y)
				   );
		}
		
		
		
				 
		 
		 
		 
	}
	
	
	void draw() {

		ofNoFill();
		
		ofBeginShape();
		for(int i = 0; i < pos; i++) {
			ofVertex(vertices[i].x, vertices[i].y);
		}
		ofEndShape();
		
		for(int i = 0; i < pos; i++) {
			ofCircle(vertices[i], 4);
		}
		
		ofFill();
	}
	
	bool mousePressed(ofMouseEventArgs &m) {
		if(pos<=3) pos++;
		if(pos<=3) {
			vertices[pos].set(m.x, m.y);
		}
	}
	
	bool mouseDragged(ofMouseEventArgs &m) {
		if(pos<=3) {
			vertices[pos].set(m.x, m.y);
		}
	}
	
	bool mouseReleased(ofMouseEventArgs &m) {
		if(pos>=3) {
			glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
		}
	}
	static vector<QuadObject*> quads;
	
};


