/**
 *  Objects.cpp
 *
 *  Created by Marek Bereza on 11/10/2013.
 */

#include "Object.h"
#include "CubeObject.h"
#include "PlaneObject.h"
//#include "OBJModelObject.h"
#include "ScreenObject.h"
#include "DraggerObjects.h"
#include "ScreenCanvasObject.h"
#include "QuadObject.h"

ClassRegistry Object::registry;
void Object::registerTypes() {
	registry.registerClass(TypedObjectInstantiator<QuadObject>, "quad");
	registry.registerClass(TypedObjectInstantiator<Object>, "object");
	registry.registerClass(TypedObjectInstantiator<Object>, "object");
	registry.registerClass(TypedObjectInstantiator<Object>, "group");
	registry.registerClass(TypedObjectInstantiator<CubeObject>, "cube");
	registry.registerClass(TypedObjectInstantiator<ScreenObject>, "screen");
	//registry.registerClass(TypedObjectInstantiator<OBJModelObject>, "obj model");
	registry.registerClass(TypedObjectInstantiator<PlaneObject>, "plane");
	registry.registerClass(TypedObjectInstantiator<ScreenCanvasObject>, "screen canvas");
}

Object *Object::create(string type) {
	Object *o = (Object*)registry.create(type);
	return o;
}



Object *Object::draggers;

void Object::init() {
	registerTypes();
	draggers = Object::create("object");
	draggers->addChild(new DraggerObject(AXIS_X));
	draggers->addChild(new DraggerObject(AXIS_Y));
	draggers->addChild(new DraggerObject(AXIS_Z));
}