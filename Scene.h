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
 *  Scene.h, created by Marek Bereza on 10/10/2013.
 */

#pragma once


#include "Object.h"
#include "SelectionListener.h"



class Scene {

public:
	Object *root;
	
	Scene() {
		Object::init();
		root = Object::create("object");
		root->name = "root";
		
	}
	
	void addSelectionListener(SelectionListener *listener) {
		listeners.push_back(listener);
	}
	
	vector<SelectionListener*> listeners;
	
	Object *getRoot() {
		return root;
	}
	
	void add(Object *object) {
		root->addChild(object);
		

	}
	
	void drawForPicker() {
		root->drawWithChildren(true);
	}
	
	
	void draw() {
		root->drawWithChildren(false);
	}
	
	void save(string path) {
		root->save(path);
	}
	
	void load(string path) {
		root->load(path);
	}

	IndexedObject *getObjectByUid(UID uid) {
		return IndexedObject::get(uid);
	}
	
	void getObjectsOfType(vector<HierarchicalObject*> &outObjects, const string &typeToList) {
		root->getObjectsOfType(outObjects, typeToList);
	}
	
	void objectClicked(Object *obj) {
		
		deselect(root);
		if(obj==NULL) {
			selection.clear();
			
			for(int i = 0; i < listeners.size(); i++) {
				listeners[i]->objectsDeselected();
			}
			return;
		}
		
		
		

		selection.clear();
		selection.push_back(obj);
		obj->selected = true;
		for(int i = 0; i < listeners.size(); i++) {
			listeners[i]->objectSelected(obj);
		}
	}
	
	void deselect(Object *parent) {
		parent->selected = false;
		for(int i = 0; i < parent->children.size(); i++) {
			Object *obj = (Object*) parent->children[i];
			deselect(obj);
		}
	}
	
	vector<Object*> selection;

};