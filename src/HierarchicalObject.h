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
 *  HierarchicalObject.h, created by Marek Bereza on 08/01/2014.
 */
#pragma once

#include "ClassRegistry.h"

// you subclass this to be part of the menu
class HierarchicalObject: public TypedObject {
public:

	string name;
	
	vector<HierarchicalObject*> children;
	HierarchicalObject *parent;
	
	bool expanded;
	
	
	
	HierarchicalObject(string name = "");
	virtual ~HierarchicalObject() {}
	
	void addChild(HierarchicalObject *child);
	
	void addChildAtFront(HierarchicalObject *child);
	bool addChildAfter(HierarchicalObject *obj, HierarchicalObject *after);
	bool removeFromParent();
	
	bool removeChild(HierarchicalObject *child);
};


