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
	vector<ofVec2f> texCoords;
	vector<ofVec2f> vertices;
	
	bool shiftDown;
	bool invert;
	int selected;
	int over;
	float brightness;
	QuadObject() {
		brightness = 1;
		selected = -1;
		invert = false;	
		over = -1;
		texCoords.resize(4);
		texCoords[0].set(0,0);
		texCoords[1].set(1,0);
		texCoords[2].set(1,1);
		texCoords[3].set(0,1);
	
		vertices.resize(4);
		vertices[0].set(0,0);
		vertices[1].set(100,0);
		vertices[2].set(100,100);
		vertices[3].set(0,100);
		
		shiftDown = false;
		name = "Quad";
	}
		
	
	
	virtual void parameterize(xmlgui::SimpleGui &gui) {
		
		gui.addSlider("brightness", brightness, 0, 1);
		gui.addToggle("invert", invert);
		
		float xx;
		
		
		
		for(int i = 0; i < vertices.size(); i++) {
			xmlgui::Control *g = gui.addFloatField("v["+ofToString(i)+"].x", vertices[i].x);
			if(i==0) xx = g->x;
			align2(xx,
				   g,
				   gui.addFloatField("v["+ofToString(i)+"].y", vertices[i].y)
				   );
		}
		
		gui.addHR()->x = xx;
		
		for(int i = 0; i < texCoords.size(); i++) {
			align2(xx,
				   gui.addFloatField("tc["+ofToString(i)+"].x", texCoords[i].x),
				   gui.addFloatField("tc["+ofToString(i)+"].y", texCoords[i].y)
				   );
		}
		
		
		
				 
		 
		 
		 
	}
	
	
	void drawTextured() {
		ofVboMesh mesh;
		for(int i = 0; i < vertices.size(); i++) {
			
			int ii = i;
			if(ii==3) ii = 2;
			else if(ii==2) ii = 3;
			mesh.addVertex(vertices[ii]);
			mesh.addTexCoord(texCoords[ii]);
		}
		mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
		mesh.draw();
	}
	
	void drawVertices() {
		ofVboMesh mesh;
		for(int i = 0; i < vertices.size(); i++) {
			
			int ii = i;
			if(ii==3) ii = 2;
			else if(ii==2) ii = 3;
			mesh.addVertex(vertices[ii]);
		}
		mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
		mesh.draw();
	}
	
	void draw() {

		ofSetColor(255);
		ofDrawBitmapString(name, vertices[0]);
		ofNoFill();
		
		ofBeginShape();
		for(int i = 0; i < vertices.size(); i++) {
			ofVertex(vertices[i].x, vertices[i].y);
		}
		ofEndShape(true);
		
		for(int i = 0; i < vertices.size(); i++) {
			if(i==selected) {
				ofSetColor(255, 0, 0);
			} else if(i==over) {
				ofSetColor(0, 255, 0);
			} else {
				ofSetColor(255);
			}
			ofCircle(vertices[i], 4);
		}
		ofSetColor(255);
		ofFill();
	}
	const int MIN_DIST_SQR = 64;
	bool mouseMoved(ofMouseEventArgs &m) {
		
		for(int i = 0; i < vertices.size(); i++) {
			if(vertices[i].distanceSquared(ofVec2f(m.x,m.y))<MIN_DIST_SQR) {
				over = i;
				return true;
			}
			
		}
		over = -1;
		return false;
	}
	
	bool mousePressed(ofMouseEventArgs &m) {
		for(int i = 0; i < vertices.size(); i++) {
			if(vertices[i].distanceSquared(ofVec2f(m.x,m.y))<MIN_DIST_SQR) {
				selected = i;
				
				return true;
			}
			
		}
		selected = -1;
		return false;
	}
	
	bool mouseDragged(ofMouseEventArgs &m) {
		if(selected!=-1) {
			vertices[selected].set(m.x, m.y);
		}
		
	}
	
	bool mouseReleased(ofMouseEventArgs &m) {

		//selected = -1;
	}
	
	void keyReleased(ofKeyEventArgs &k) {
		if(k.key==OF_KEY_SHIFT) {
			shiftDown = false;
		}
	}
	
	void keyPressed(ofKeyEventArgs &k) {
		if(selected<0) return;
		
		int key = k.key;
		
		float increment = 1;

		if(key==OF_KEY_SHIFT) {
			shiftDown = true;
		}
		
		if(shiftDown) {
			increment = 10;
		}

		if(key==OF_KEY_UP) {
			vertices[selected].y -= increment;
		} else if(key==OF_KEY_DOWN) {
			vertices[selected].y += increment;
		} else if(key==OF_KEY_LEFT) {
			vertices[selected].x -= increment;
		} else if(key==OF_KEY_RIGHT) {
			vertices[selected].x += increment;
		}
	}
	
};


