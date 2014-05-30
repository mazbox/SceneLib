/**
 *  IndexedObject.cpp
 *
 *  Created by Marek Bereza on 10/10/2013.
 */

#include "IndexedObject.h"
#include "Object.h"
int IndexedObject::uidCounter = 1;
int IndexedObject::idCounter = 1;

map<int, IndexedObject*> IndexedObject::objs;
map<int, IndexedObject*> IndexedObject::uidMap;



void IndexedObject::rebuildUIDMap() {
	uidMap.clear();
	map<int,IndexedObject*> ::iterator it;
	uidCounter = 0;
	for(it = objs.begin(); it != objs.end(); it++) {
		IndexedObject *obj = (*it).second;
		if(obj->uid==0) obj->uid = ++uidCounter;
		
		if(uidCounter<obj->uid) {
			uidCounter = obj->uid;
		}
		if(uidMap.find(obj->uid)!=uidMap.end()) {
			ofLogError() << "There is more than one object with uid " << obj->uid;
		}
		uidMap[obj->uid] = obj;
	}
}

int IndexedObject::getIndexForColor(const ofColor &col) {
	if(col.b==0) return -1;
	return col.r + col.g * 256;
}


IndexedObject *IndexedObject::getObjectForColor(const ofColor &col) {
	int i = getIndexForColor(col);
	if(objs.find(i)==objs.end()) return NULL;
	return objs[i];
}


IndexedObject::IndexedObject() {
	id = ++idCounter;
	uid = ++uidCounter;
	//printf("My id is %d\n", id);
	objs[id] = this;
	rebuildUIDMap();
	//printf("Objects size: %d\n", objs.size());
}

IndexedObject::~IndexedObject() {
	{
		map<int,IndexedObject*>::iterator it;
		for(it = objs.begin(); it != objs.end(); it++) {
			if((*it).second==this) {
				objs.erase(it);
				break;
			}
		}
	}
	
	{
	
		map<int, IndexedObject*>::iterator it;
		
		for(it = uidMap.begin(); it != uidMap.end(); it++) {
			if((*it).second==this) {
				uidMap.erase(it);
				break;
			}
		}
	}
	//printf("Deleting an object: %s (%s)\n", name.c_str(), type.c_str());
}



ofColor IndexedObject::getIndexColor() {
	
	return ofColor(id%256, id/256, 1);
}

void IndexedObject::getObjectsOfType(vector<HierarchicalObject*> &outObjects, const string &typeToList) {
	outObjects.clear();
	map<int,IndexedObject*>::iterator it;
	for(it = objs.begin(); it != objs.end(); it++) {
		IndexedObject *obj = (*it).second;
		if(obj==NULL) {
			ofLogError() << "Blaaahdee 'ell, it's NULL!\n";
		}
		
		if(obj->type==typeToList) {
			outObjects.push_back((*it).second);
		}
	}
}

bool IndexedObject::uidExists(const UID &uid) {
	return uidMap.find(uid)!=uidMap.end();
}

IndexedObject *IndexedObject::get(const UID &uid) {
	return uidMap[uid];
}




void IndexedObject::printObjects() {
	map<int,IndexedObject*>::iterator it;
	for(it = objs.begin(); it != objs.end(); it++) {
		printf("%s - name: %s   uid: %d\n", (*it).second->type.c_str(), (*it).second->name.c_str(), (*it).second->uid);
	}
}


