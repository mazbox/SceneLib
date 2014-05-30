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
 *  Registry.h, created by Marek Bereza on 18/03/2013.
 */

#pragma once

#include "ofMain.h"

class TypedObject {
public:
	string type;
};

typedef TypedObject* (*TypedObjectConstructor)();

template<class T>
TypedObject *TypedObjectInstantiator() {
	return new T();
}


class ClassRegistry: public vector<string> {
public:
	
	TypedObject *create(string type) {
		TypedObjectConstructor c = registry[type];
		
		if(registry.find(type)!=registry.end()) {
			TypedObject *cc = c();
			cc->type = type;
			return cc;
		} else {
			return NULL;
		}
	}

	vector<string> getClassNames() {
		vector<string> names;
		map<string,TypedObjectConstructor>::iterator it = registry.begin();
		for(; it != registry.end(); it++) {
			names.push_back((*it).first);
		}
		return names;
	}
	
	map<string,TypedObjectConstructor> registry;
	
	void registerClass(TypedObjectConstructor constructor, string type) {
		registry[type] = constructor;
		push_back(type);
	}

};
