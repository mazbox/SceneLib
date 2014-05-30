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
 *  OBJModelObject.h, created by Marek Bereza on 11/10/2013.
 */

#pragma once

#include "Object.h"
#include "ofxOBJModel.h"

class OBJModelObject: public Object, public xmlgui::Listener {
public:
	ofxOBJModel model;
	
	xmlgui::Control *fileControl;
	string filePath;
	
	OBJModelObject() {
		name = "obj";
	}
	
	virtual void parameterize(xmlgui::SimpleGui &gui) {
		fileControl = gui.addFileField("file", filePath);
		gui.addListener(this);
	}
	
	void loadedSettings() {

		if(filePath!="") {
			model.load(filePath);
		}
	}
	
	void controlChanged(xmlgui::Event *evt) {
		if(evt->type==xmlgui::Event::TOUCH_UP && evt->control==fileControl) {
			model.load(filePath);
		}
	}
	
	void draw() {
		model.draw();
	}
};