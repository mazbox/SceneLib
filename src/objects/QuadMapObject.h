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
 *  QuadMapObject.h, created by Marek Bereza on 03/06/2014.
 */

#pragma once
#include "Object.h"
#include "QuadObject.h"
#include "ImageSource.h"
class QuadMapObject: public Object {
public:
	float width;
	float height;
	bool doTestPattern;
	ImageSource *imageSource;
	ofImage testPattern;
	QuadMapObject() {
		imageSource = NULL;
		
		name = "QuadMap";
		
		width = 1024;
		height = 768;
	}
	
	virtual void parameterize(xmlgui::SimpleGui &gui) {
		gui.addFloatField("width", width);
		gui.addFloatField("height", height);
		gui.addToggle("do test pattern", doTestPattern);
	}
	
	int getNumQuads() {
		int count = 0;
		for(int i = 0; i < children.size(); i++) {
			if(children[i]->type=="quad") {
				count++;
			}
		}
		return count;
	}
	
	QuadObject *getQuad(int pos) {
		int p = 0;
		for(int i = 0; i < children.size(); i++) {
			if(children[i]->type=="quad") {
				if(p==pos) return (QuadObject*)children[i];
				p++;
			}
		}
		ofLogError() << "QuadObject index out of range";
		return NULL;
	}
	void render(ofVec2f origin) {
		render(ofRectangle(origin.x, origin.y, width, height));
	}
	
	
	void setImageSource(ImageSource *imageSource) {
		this->imageSource = imageSource;
	}
	
	
	void bindTexture() {
		if(doTestPattern) {
			if(!testPattern.isAllocated()) {
				testPattern.loadImage("testPattern.png");
			}
			testPattern.bind();
		} else {
			if(imageSource!=NULL) {
				imageSource->getTexture().bind();
			}
		}
	}
	
	void unbindTexture() {
		if(doTestPattern) {
			testPattern.unbind();
		} else {
			if(imageSource!=NULL) {
				imageSource->getTexture().unbind();
			}
		}
	}
	
	void render(ofRectangle r) {
		glPushMatrix();
		glTranslatef(r.x, r.y, 0);

		

		glScalef(r.width/width, r.height/height, 1);
		ofSetColor(0);
		ofRect(0, 0, width, height);
		
		int numQuads = getNumQuads();
		
		for(int i = 0; i < numQuads; i++) {
			
			
			
			QuadObject *q = getQuad(i);
			
			ofSetColor(255*q->brightness);
			
			bindTexture();
			getQuad(i)->drawTextured();
			unbindTexture();
			
		}
		
		
		
		
		glPopMatrix();
	}
	
};
