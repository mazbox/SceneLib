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
 *  Header.h, created by Marek Bereza on 10/10/2013.
 */
#pragma once

#include "ofMain.h"
#include "HierarchicalObject.h"
#include <stdint.h>
typedef int UID;

class IndexedObject: public HierarchicalObject {
public:
	IndexedObject();
	
	virtual ~IndexedObject();
	
	// this is a session id (persistent only to current instance of app)
	int id;
	
	// this is a persistent id that persists when re-opening the app.
	UID uid;
	static void printObjects();
	static int uidCounter;
	static int idCounter;
	
	ofColor getIndexColor();
	

	static int getIndexForColor(const ofColor &col);
	static IndexedObject *getObjectForColor(const ofColor &col);
	
	static bool uidExists(const UID &uid);
	
	static IndexedObject *get(const UID &uid);
	
	// this is for looking up when picking
	static map<int,IndexedObject*> objs;
	
	// this is for looking up pointer references
	static map<int, IndexedObject*> uidMap;
	
	// this MUST be called after loading a file.
	// it creates the map from uid's to objects,
	// and also finds the highest uid number
	// which it needs to know to increment uids.
	static void rebuildUIDMap();
	
	static void getObjectsOfType(vector<HierarchicalObject*> &outObjects, const string &typeToList);
};