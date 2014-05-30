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
 *  Frame.h, created by Marek Bereza on 11/03/2014.
 */

#pragma once

#include "ofMain.h"

class Frame: public ofRectangle {
public:
	
	Frame();

	// left/right or top/bottom frames
	vector<Frame*> children;
	
	// if false, left/right otherwise top/bottom
	bool vertical;
	
	
	virtual void draw();
	
	void drawChildren();
	
	void addChild(Frame *child);
	
	void respaceEvenly();
	
	
	bool loadLayout(string path);
	
	bool saveLayout(string path);
	
	
	void resize(float x, float y, float width, float height);
	
	void resize(ofRectangle &r);
	
	

};

class ColourFrame: public Frame {
public:
	
	int colour;
	
	ColourFrame(int colour): Frame() {
		this->colour = colour;
	}
	
	virtual void draw() {
		//printf("Drawing %f %f %f %f\n", x, y, width, height);
		ofSetHexColor(colour);
		ofRect(*this);
	}
};

class RectFrame: public Frame {
public:
	ofRectangle *rect;
	RectFrame(ofRectangle &r): Frame() {
		rect = &r;
	}
		
	virtual void draw() {
		// doesn't draw anything, just updates the rectangle
		rect->set(x, y, width, height);
	}
};

