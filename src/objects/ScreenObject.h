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
 *  ScreenObject.h, created by Marek Bereza on 11/10/2013.
 */

#pragma once

#include "Object.h"
#include "ObjectList.h"

class ScreenObject: public Object {
public:
	float width;
	float height;
	int resolutionX;
	int resolutionY;
	
	// number of clockwise rotations
	int orientation;
	
	ofRectangle sourceRect;
	
	
	
	
	
	ScreenObject() {
		name = "Screen";
		width = 1;
		height = 9.f/16.f;
		resolutionX = 1920;
		resolutionY = 1080;
		canvasUid = 0;
		orientation = 0;
	}
	
	
	void drawFrame(bool isSelected = false) {
		ofNoFill();
		if(isSelected) {
			ofSetHexColor(0x00FF00);
		} else {
			ofSetHexColor(0x990099);
		}
		
		ofRect(sourceRect);
		if(orientation==0 || orientation==1) {
			ofLine(sourceRect.getCenter(), (sourceRect.getTopRight() + sourceRect.getBottomRight())/2);
		}
		
		
		if(orientation==1 || orientation==2) {
			ofLine(sourceRect.getCenter(), (sourceRect.getBottomRight() + sourceRect.getBottomLeft())/2);
		}
		if(orientation==2 || orientation==3) {
			ofLine(sourceRect.getCenter(), (sourceRect.getBottomLeft() + sourceRect.getTopLeft())/2);
		}
		
		if(orientation==3 || orientation==0) {
			ofLine(sourceRect.getCenter(), (sourceRect.getTopLeft() + sourceRect.getTopRight())/2);
		}
		
		
		char info[1024];
		sprintf(info, "%s\n%dx%d\nUID: %d\n", name.c_str(), resolutionX, resolutionY, uid);
		
		string screenInfo(info);
		
		ofDrawBitmapString(screenInfo,
						   
						   
						   sourceRect.x, sourceRect.y + sourceRect.height/2);
	}
	
	
	ObjectList *canvasList;
	int canvasUid;
	
	virtual void parameterize(xmlgui::SimpleGui &gui) {
		gui.addFloatField("width", width);
		float w = gui.addFloatField("height", height)->width;
		
		xmlgui::Control *cc = gui.addIntField("resolutionX", resolutionX);
		cc->width/=2;
		xmlgui::Control *c = gui.addIntField("resolutionY", resolutionY);
		
		gui.addFloatField("source.x", sourceRect.x);
		gui.addFloatField("source.y", sourceRect.y);
		gui.addFloatField("source.width", sourceRect.width);
		gui.addFloatField("source.height", sourceRect.height);
		gui.addSegmented("orientation", orientation, "0|90 CW|180|90 CCW");
		
		
		c->width/=2;
		c->x += c->width;
		c->y = cc->y;
		
		// this was crashing
		//canvasList = new ObjectList("canvas", "canvas", canvasUid, "screen canvas");
		
		//gui.addChild(canvasList);
		//canvasList->x = cc->x;
		//canvasList->width = w;
	}
	
	void draw() {
		glBegin(GL_QUADS);
		glNormal3f(0, 0, 1);
		glTexCoord2f(0, 0);
		glVertex2f(-width/2, -height/2);
		glTexCoord2f(1, 0);
		glVertex2f(width/2, -height/2);
		glTexCoord2f(1, 1);
		glVertex2f(width/2, height/2);
		glTexCoord2f(0, 1);
		glVertex2f(-width/2, height/2);
		glEnd();
	}

};
