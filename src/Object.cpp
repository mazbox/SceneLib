/**
 *  Object.cpp
 *
 *  Created by Marek Bereza on 05/11/2013.
 */

#include "Object.h"


Object::Object() {
	expandedInSceneList = true;
	locked = false;
	name = "Object";
	type = "object";
	selected = false;
	enabled = true;
	scale.set(1, 1, 1);
}
void Object::pos(float x, float y, float z) {
	position.set(x, y, z);
	
}

void Object::registerClass(TypedObjectConstructor constructor, string type) {
	registry.registerClass(constructor, type);
}

void Object::align3(float xx, xmlgui::Control *a, xmlgui::Control *b, xmlgui::Control *c) {
	a->x = b->x = c->x = xx;
	int pad = 5;
	float w = a->width;
	float w3 = w/3;
	w3 -= pad;
	
	
	a->width = b->width = c->width = w3;
	b->y = c->y = a->y;
	b->x += w3 + pad;
	c->x += 2*(w3 + pad);
}
float ffff = 0;

void Object::parameterizeIncludingGeneric(xmlgui::SimpleGui &gui) {
	gui.setAutoLayout(false);
	gui.addTextField("name", name);
	gui.addToggle("enabled", enabled);
	// this align3 business is a bit ugly but it makes a nicer
	// and more compact layout to work with.
	float xx = gui.addToggle("locked", locked)->x;
	align3(xx,
		   gui.addFloatField("pos.x", position.x),
		   gui.addFloatField("pos.y", position.y),
		   gui.addFloatField("pos.z", position.z)
		   );
	
	align3(xx,
		   gui.addFloatField("scale.x", scale.x),
		   gui.addFloatField("scale.y", scale.y),
		   gui.addFloatField("scale.z", scale.z)
		   );
	
	align3(xx,
		   gui.addFloatField("rot.x", rotation.x),
		   gui.addFloatField("rot.y", rotation.y),
		   gui.addFloatField("rot.z", rotation.z)
		   );
	
	
	gui.addColorPicker("colour", color)->x = xx;
	
	parameterize(gui);
}



void Object::parameterizeIncludingGenericAndHidden(xmlgui::SimpleGui &gui) {
	parameterizeIncludingGeneric(gui);
	// this doesn't work
	gui.addToggle("expandedInSceneList", expandedInSceneList);
	gui.addIntField("uid", uid);
}



Object *Object::clone() {
	printf("Hit clone funciton\n");
	Object *obj = Object::create(type);
	xmlgui::SimpleGui gui;
	parameterizeIncludingGeneric(gui);
	ofxXmlSettings xml;
	xml.addTag("object");
	
	printf("doing this\n");
	
	
	gui.saveSettings(xml);
	gui.clear();
	obj->parameterizeIncludingGenericAndHidden(gui);
	gui.loadSettings(xml);
	obj->loadedSettings();
	return obj;
}

void Object::save(ofxXmlSettings &xml, int pos) {
	
	xml.addTag("object");
	xml.addAttribute("object", "type", type, pos);
	
	
	
	xml.pushTag("object", pos);
	xmlgui::SimpleGui gui;
	this->parameterizeIncludingGenericAndHidden(gui);
	gui.saveSettings(xml);
	
	for(int i = 0; i < children.size(); i++) {
		((Object*)children[i])->save(xml, i);
	}
	xml.popTag();
	
	
}



string Object::serialize() {
	string outStr;
	ofxXmlSettings xml;
	save(xml, 0);
	xml.copyXmlToString(outStr);
	return outStr;
}

void Object::deserialize(string serialized) {
	ofxXmlSettings xml;
	xml.loadFromBuffer(serialized);
	xmlgui::SimpleGui gui;
	parameterizeIncludingGenericAndHidden(gui);
	xml.pushTag("object");
	gui.loadSettings(xml);
}




void Object::load(string path) {
	clearChildren();
	ofxXmlSettings xml;
	xml.loadFile(path);
	int numRoots = xml.getNumTags("object");
	if(numRoots!=1) {
		ofLogError() << "Scene has more than one root";
		return;
	}
	xml.pushTag("object", 0);
	
	loadChildren(xml);
	xml.popTag();
	
	
}




void Object::loadChildren(ofxXmlSettings &xml) {
	int numChildren = xml.getNumTags("object");
	for(int i = 0; i < numChildren; i++) {
		string type = xml.getAttribute("object", "type", "", i);
		Object *obj = Object::create(type);
		if(obj!=NULL) {
			xml.pushTag("object", i);
			xmlgui::SimpleGui gui;
			obj->parameterizeIncludingGenericAndHidden(gui);
			
			gui.loadSettings(xml);
			
			addChild(obj);
			
			obj->loadChildren(xml);
			obj->loadedSettings();
			xml.popTag();
		}
	}
}


void Object::save(string path) {
	ofxXmlSettings xml;
	save(xml, 0);
	xml.saveFile(path);
}




void Object::drawWithChildren(bool forPicker) {
	if(!enabled) return;
	if(forPicker && locked) return;
	glPushMatrix();
	
	glRotatef(rotation.x, 1, 0, 0);
	glRotatef(rotation.y, 0, 1, 0);
	glRotatef(rotation.z, 0, 0, 1);
	glTranslatef(position.x, position.y, position.z);
	glScalef(scale.x, scale.y, scale.z);
	
	for(int i = 0; i < children.size(); i++) {
		((Object*)children[i])->drawWithChildren(forPicker);
	}
	if(forPicker) ofSetColor(getIndexColor());
	else {
		if(selected) {
			
			ofSetColor(255, 200, 100);
		} else {
			ofSetColor(color);
		}
	}
	draw();
	
	if(selected) {
		ofDisableDepthTest();
		draggers->drawWithChildren();
		ofEnableDepthTest();
	}
	glPopMatrix();
}





void Object::clearChildren() {
	// TODO: This is a memory leak - we need to delete object when clearing them
	// but for some reason I'm getting a "pointer being freed was not allocated" error 
	//printf("Clearing\n");
	for(int i = 0; i < children.size(); i++) {
		printf("Deleting a %s\n", children[i]->name.c_str());
		delete children[i];
	}
	children.clear();
}


