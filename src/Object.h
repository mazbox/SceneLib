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
 *  Object.h, created by Marek Bereza on 10/10/2013.
 */

#include "IndexedObject.h"
#include "ofxXmlGui.h"

#pragma once

#include "ClassRegistry.h"


class Object: public IndexedObject {
public:
	static ClassRegistry registry;
	static void registerTypes();
	
	static void registerClass(TypedObjectConstructor constructor, string type);

	
	
	static Object *create(string type);
	ofVec3f position;
	ofVec3f rotation;
	ofVec3f scale;
	bool selected;
	ofFloatColor color;
	bool locked;
	bool expandedInSceneList;
	bool enabled;
	static Object *draggers;
	static void init();
	
	Object();
	virtual ~Object() {}
	void pos(float x, float y, float z);
	
	
	
	// feel free to add gui listeners to this gui in your object
	virtual void parameterize(xmlgui::SimpleGui &gui) {
		
	}
	

	// callback for if you want to take an action
	// on anything that gets set by parameterize
	// when loading from a file (i.e. loading an asset)
	virtual void loadedSettings() {
		
	}
	
	Object *clone();
	
	

	
	
	void load(string path);
	void save(string path);
	
	void clearChildren();

	
	string serialize();
	void deserialize(string serialized);
	
	
	
	
	void drawWithChildren(bool forPicker = false);
	
	virtual void draw() {};

	void parameterizeIncludingGeneric(xmlgui::SimpleGui &gui);
	
	
protected:
	void align2(float xx, xmlgui::Control *a, xmlgui::Control *b);
	void align3(float xx, xmlgui::Control *a, xmlgui::Control *b, xmlgui::Control *c);
	
	
private:
	void parameterizeIncludingGenericAndHidden(xmlgui::SimpleGui &gui);
	
	
	void save(ofxXmlSettings &xml, int pos);
	void loadChildren(ofxXmlSettings &xml);
	

};
