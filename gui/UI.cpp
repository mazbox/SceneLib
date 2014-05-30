/**
 *  UI.cpp
 *
 *  Created by Marek Bereza on 04/11/2013.
 */

#include "UI.h"

	
UI *UI::getInstance() {
	static UI *instance = NULL;
	if(instance==NULL) {
		instance = new UI();
	}
	return instance;
}

void UI::setup(Scene *scene) {
	sceneList = new SceneList(scene, this);
	grabAxis = -1;
	this->scene = scene;
	shiftDown = false;
	inspector.setup();
	setupMenu();
	enabled = false;
	
	
	
}

bool UI::isEnabled() {
	return enabled;
}

void UI::toggle() {
	setEnabled(!isEnabled());
}

void UI::setEnabled(bool enabled) {
	if(this->enabled==enabled) {
		return;
	}
	this->enabled = enabled;
	
	if(this->enabled) {
		ofAddListener(ofEvents().keyPressed, this, &UI::keyPressed, 600);
		
		ofAddListener(ofEvents().keyReleased, this, &UI::keyReleased, 600);
		ofAddListener(ofEvents().mouseDragged, this, &UI::mouseDragged);
		ofAddListener(ofEvents().mousePressed, this, &UI::mousePressed);
		ofAddListener(ofEvents().mouseReleased, this, &UI::mouseReleased);
		
		
	} else {
		ofRemoveListener(ofEvents().keyPressed, this, &UI::keyPressed);
		
		ofRemoveListener(ofEvents().keyReleased, this, &UI::keyReleased);
		ofRemoveListener(ofEvents().mouseDragged, this, &UI::mouseDragged);
		ofRemoveListener(ofEvents().mousePressed, this, &UI::mousePressed);
		ofRemoveListener(ofEvents().mouseReleased, this, &UI::mouseReleased);
		
	}
	
	menu.setEnabled(this->enabled);
	sceneList->setEnabled(this->enabled);
	inspector.setEnabled(this->enabled);
}

void UI::setupMenu() {
	menu.addListener(this);
	
	ContextMenuLevel *adder = new ContextMenuLevel();
	vector<string> types = Object::registry.getClassNames();
	for(int i = 0; i < types.size(); i++) {
		adder->addItem(types[i], "add " + types[i]);
	}
	menu.addItem("add", adder);
	menu.addItem("duplicate");
	menu.addItem("group");
}



void UI::keyPressed(ofKeyEventArgs &k) {
	if(k.key==OF_KEY_BACKSPACE) {
		for(int i = 0; i < selectedObjects.size(); i++) {
			Object *selectedObject = selectedObjects[i];
			if(selectedObject!=NULL && selectedObject->parent!=NULL) {
				// TODO: undo
				if(selectedObject->parent->removeChild(selectedObject)) {
					delete selectedObject;
					selectedObject = NULL;
					setFocus(NULL);
				} else {
					ofLogError() << "UI: Can't find parent of object to delete!";
				}
			}
			selectedObjects.clear();
		}
	} else if(k.key==OF_KEY_LEFT_SHIFT || k.key==OF_KEY_RIGHT_SHIFT) {
		shiftDown = true;
		
	} else if(k.key=='g') {
		groupSelectedItems();
	}
}

void UI::groupSelectedItems() {
	if(selectedObjects.size()>0) {
		Object *group = Object::create("group");
		
		for(int i = 0; i < selectedObjects.size(); i++) {
			if(i==0) {
				selectedObjects[i]->parent->addChild(group);
			}
			
			selectedObjects[i]->parent->removeChild(selectedObjects[i]);
			group->addChild(selectedObjects[i]);
		}
		
	}
}

void UI::keyReleased(ofKeyEventArgs &k) {
	if(k.key==OF_KEY_LEFT_SHIFT || k.key==OF_KEY_RIGHT_SHIFT) {
		shiftDown = false;
	}
}

void UI::axisGrabbed(int axis, bool shouldDuplicate) {
	if(shouldDuplicate && selectedObjects.size()==1) {
		Object *sel = selectedObjects[0]->clone();
		setSelectedObject(sel);
	}
	grabAxis = axis;
	prevMouse.set(ofGetMouseX(), ofGetMouseY());
}

void UI::mousePressed(ofMouseEventArgs &m) {
}
void UI::mouseReleased(ofMouseEventArgs &m) {
	grabAxis = -1;
}

void UI::mouseDragged(ofMouseEventArgs &m) {
	
	if(m.button!=0) return;
	if(grabAxis<0) return;
	ofVec2f p(m.x, m.y);
	p -= prevMouse;
	
	float increment = 0.01;
	if(shiftDown) increment *= 10;
	
	if(selectedObjects.size()!=1) return;
	Object *selectedObject = selectedObjects[0];
	if(selectedObject!=NULL) {
		
		if(grabAxis==AXIS_X) {
			selectedObject->position.x += p.y*increment;
		} else if(grabAxis==AXIS_Y) {
			selectedObject->position.y -= p.y*increment;
		} else if(grabAxis==AXIS_Z) {
			selectedObject->position.z += p.y*increment;
		}
	}
	prevMouse.set(m.x, m.y);
}



void UI::contextMenuItemSelected(ContextMenuItem *item) {
	printf("Command: %s\n", item->command.c_str());
	if(item->command.find("add ")==0) {
		addObject(item->command.substr(4));
	} else if(item->command=="duplicate") {
		
		
		if(selectedObjects.size()!=1) return;
		Object *selectedObject = selectedObjects[0];
		
		if(selectedObject!=NULL && selectedObject->parent!=NULL) {
			printf("doing clone\n");
			Object *obj = selectedObject->clone();
			selectedObject->parent->addChild(obj);
		}
	} else if(item->command=="group") {
		groupSelectedItems();
	}
	
}

void UI::addObject(string type) {
	
	Object *o = Object::create(type);
	if(o!=NULL) {
		scene->add(o);
	} else {
		ofLogError() << "Couldn't create "<< type;
	}
	
}

void UI::addSelectedObject(Object *object) {
	if(object==NULL) return;
	for(int i = 0; i < selectedObjects.size(); i++) {
		if(selectedObjects[i]==object) {
			selectedObjects[i]->selected = true;
			ofLogWarning() << "Not adding duplicate selection";
			return;
		}
	}
	object->selected = true;
	
	selectedObjects.push_back(object);
	
}


void UI::setSelectedObject(Object *object) {
	for(int i = 0; i < selectedObjects.size(); i++) {
		selectedObjects[i]->selected = false;
	}
	selectedObjects.clear();
	
	addSelectedObject(object);
	//printf("%s\n", object->serialize().c_str());
	if(selectedObjects.size()==1) {
		setFocus(object);
	} else {
		//printf("Num selected: %d\n", selectedObjects.size());
		setFocus(NULL);
	}
}

bool UI::isSelected(Object *object) {
	for(int i = 0; i < selectedObjects.size(); i++) {
		if(selectedObjects[i]==object) {
			return true;
		}
	}
	return false;
}


void UI::setFocus(Object *object) {
	inspector.setFocus(object);
}
