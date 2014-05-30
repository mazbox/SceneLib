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
 *  ObjectList.h, created by Marek Bereza on 16/10/2013.
 */
#include "ofMain.h"
#include "xmlgui/controls/LabeledControl.h"

class ObjectList: public xmlgui::LabeledControl {
public:
	string typeToList;
	ObjectList(string id, string name, int &value, string type) {
		width = 70;
		height = 70;
		this->value = &value;
		this->id = id;
		this->name = name;
		this->typeToList = type;
	}
	vector<HierarchicalObject*> objs;
	
	void draw() {
		const int itemHeight = 16;
		IndexedObject::getObjectsOfType(objs, typeToList);
		
		ofNoFill();
		ofSetColor(255);
		ofRect(*this);
		
		ofFill();
		ofSetColor(50);
		ofRect(*this);
		ofSetColor(255);
		for(int i = 0; i < objs.size(); i++) {
			float yy = y + (i + 1) * itemHeight;
			xmlgui::Resources::drawString(this, objs[i]->name, x + 3, yy - 5);
			ofLine(x, y + (i + 1) * itemHeight, x + width, yy);
		}
		drawLabel();
	}
};

