/**
 *  HierarchicalObject.cpp
 *
 *  Created by Marek Bereza on 08/01/2014.
 */

#include "HierarchicalObject.h"




HierarchicalObject::HierarchicalObject(string name) {
	this->name = name;
	this->type = "object";
	this->expanded = false;
	parent = NULL;
}


void HierarchicalObject::addChild(HierarchicalObject *child) {
	children.push_back(child);
	child->parent = this;
}

void HierarchicalObject::addChildAtFront(HierarchicalObject *child) {
	children.insert(children.begin(), child);
	child->parent = this;
}
bool HierarchicalObject::addChildAfter(HierarchicalObject *obj, HierarchicalObject *after) {
	for(int i = 0; i < children.size(); i++) {
		if(children[i]==after) {
			obj->parent = this;
			children.insert(children.begin() + i + 1, obj);
			return true;
		}
	}
	return false;
}

bool HierarchicalObject::removeFromParent() {
	if(parent==NULL) return true;
	return parent->removeChild(this);
}

bool HierarchicalObject::removeChild(HierarchicalObject *child) {
	for(int i = 0; i < children.size(); i++) {
		if(children[i]==child) {
			child->parent = NULL;
			children.erase(children.begin() + i);
			return true;
		}
	}
	return false;
}


