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
 *  DraggerObjects.h, created by Marek Bereza on 14/10/2013.
 */

#pragma once

#include "Object.h"
#include "constants.h"



class DraggerObject: public Object {
public:
	
	float width, height;
	int orientation;
	
	
	
	DraggerObject(int orientation = 0) {
		width = 1;
		height = 0.1;
		this->orientation = orientation;
	}
	void draw() {

		glPushMatrix();
		if(orientation==AXIS_X) {
			ofSetColor(255, 0, 1);
		} else if(orientation==AXIS_Y) {
			ofSetColor(0, 255, 1);
			glRotatef(90, 0, 0, 1);
		} else {
			ofSetColor(0, 0, 255);
			glRotatef(90, 0, 1, 0);
		}
		ofRect(0, -height/2, width, height);
		glPopMatrix();
	}
};
