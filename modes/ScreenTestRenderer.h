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
 *  ScreenTestMode.h, created by Marek Bereza on 05/11/2013.
 */

#pragma once
#include "ScreenCanvasRenderer.h"

class ScreenTestRenderer: public ScreenCanvasRenderer {
public:
	ofTrueTypeFont *font;
	ofImage testPattern;
	ScreenTestRenderer() {
		font = NULL;

	}
	void render(const float &canvasWidth, const float &canvasHeight, ScreenObject *screen) {
		if(font==NULL) {
			font = new ofTrueTypeFont();
			font->loadFont("res/Arial.ttf", 10);
			testPattern.loadImage("test-pattern.png");
		}
		ofClear(0, 0, 0, 0);
		ofSetColor(255);
		TexQuad tq(ofRectangle(0, 0, canvasWidth, canvasHeight));
		testPattern.bind();
		
//		testPattern.draw(0, 0, canvasWidth, canvasHeight);
		tq.draw();
		
		testPattern.unbind();

		ofSetColor(100);
		ofVboMesh mesh;
		for(float f = 0; f < 1; f+= 0.01) {
			mesh.addVertex(ofVec2f(0, f));
			mesh.addVertex(ofVec2f(1, f));
		}
		
		for(float f = 0; f < 1; f+= 0.005) {
			mesh.addVertex(ofVec2f(f, 0));
			mesh.addVertex(ofVec2f(f, 1));
		}
		mesh.setMode(OF_PRIMITIVE_LINES);
		mesh.draw();
		
		ofFill();
		glPushMatrix();
		glTranslatef(screen->sourceRect.x, screen->sourceRect.y + screen->sourceRect.height/2, 0);
		glScalef(100, 100, 1); // don't know if this does anything
		ofDrawBitmapString(screen->name, 0, 0);
		glPopMatrix();
	}

};
