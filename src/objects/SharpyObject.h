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
 *  Sharpy.h, created by Marek Bereza on 29/05/2014.
 */

#pragma once

#include "Object.h"

#include "ofxDmx.h"
#include "ofxXmlGui.h"

/*
  1: colour wheel
  2: stop / strobe
  3: dimmer
  4: static gobo change
  5: prism insertion
  6: prism rotation
  7: effects movement
  8: frost
  9: focus
 10: pan
 11: pan fine
 12: tilt
 13: tilt fine
 14: function
 15: reset
 16: lamp control (with option "Lamp DMX")
 */

class SharpyObject: public Object {
public:

	
	enum {
		COLOUR_WHEEL = 0,
		STOP_STROBE,
		DIMMER,
		GOBO,
		PRISM_INSERTION,
		PRISM_ROTATION,
		EFFECTS_MOTION,
		FROST,
		FOCUS,
		PAN,
		PAN_FINE,
		TILT,
		TILT_FINE,
		FUNCTION,
		RESET,
		LAMP_CONTROL,
		NUM_PARAMS
	};
	
	SharpyObject() {
		name = "Sharpy";
		this->startingChannel = 1;
		objectInSpace = true;
		memset(data, 0, NUM_PARAMS*sizeof(int));
	}
	
	int data[NUM_PARAMS];
	int startingChannel;
	
	
	
	void setPanTilt(int pan, int tilt) {
		data[PAN] = pan;
		data[TILT] = tilt;
	}
	
	

	void parameterize(xmlgui::SimpleGui &gui) {
		gui.addTitle(name);
		
		gui.addSlider("Pan", data[PAN], 0, 255);
		gui.addSlider("Tilt", data[TILT], 0, 255);
		
		gui.addSlider("Focus", data[FOCUS], 0, 255);
		
		gui.addSlider("Dimmer", data[DIMMER], 0, 255);
		gui.addSlider("Gobo", data[GOBO], 0, 255);
		
		gui.addSlider("Pan Fine", data[PAN_FINE], 0, 255);
		gui.addSlider("Tilt Fine", data[TILT_FINE], 0, 255);
		
		
		gui.addSlider("Colour Wheel",data[COLOUR_WHEEL], 0, 255);
		gui.addSlider("Stop Strobe", data[STOP_STROBE], 0, 255);
		
		gui.addSlider("Prism Insertion", data[PRISM_INSERTION], 0, 255);
		gui.addSlider("Prism Rotation", data[PRISM_ROTATION], 0, 255);
		gui.addSlider("Effects Motion", data[EFFECTS_MOTION], 0, 255);
		gui.addSlider("Frost", data[FROST], 0, 255);
		gui.addSlider("Lamp Control", data[LAMP_CONTROL], 0, 255);
		
		
	}
	
	void update(ofxDmx &dmx) {
		for(int i = 0; i < NUM_PARAMS; i++) {
			dmx.setLevel(startingChannel + i, data[i]);
		}
	}
	
	
};
