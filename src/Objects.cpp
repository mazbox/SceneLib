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
#include "SharpyObject.h"
ClassRegistry Object::registry;
void Object::registerTypes() {
	registerClass(TypedObjectInstantiator<QuadObject>, "quad");
	registerClass(TypedObjectInstantiator<Object>, "object");
	registerClass(TypedObjectInstantiator<Object>, "object");
	registerClass(TypedObjectInstantiator<Object>, "group");
	registerClass(TypedObjectInstantiator<CubeObject>, "cube");
	registerClass(TypedObjectInstantiator<ScreenObject>, "screen");
	//registry.registerClass(TypedObjectInstantiator<OBJModelObject>, "obj model");
	registerClass(TypedObjectInstantiator<PlaneObject>, "plane");
	registerClass(TypedObjectInstantiator<ScreenCanvasObject>, "screen canvas");
	registerClass(TypedObjectInstantiator<SharpyObject>, "sharpy");
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