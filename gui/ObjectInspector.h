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
 *  Inspector.h, created by Marek Bereza on 10/10/2013.
 */


#pragma once

#include "ofxXmlGui.h"
#include "Object.h"
#include "SelectionListener.h"

class ObjectInspector: public SelectionListener {
public:
	
	void setup() {
		
	}
	
	
	void objectSelected(Object *obj) {
		setFocus(obj);
	}
	void setEnabled(bool enabled) {
		gui.setEnabled(enabled);
	}
	
	void setFocus(Object *object) {
		gui.clear();
		if(object!=NULL) {
			object->parameterizeIncludingGeneric(gui);
		}
		
	}
	
	xmlgui::SimpleGui gui;
};