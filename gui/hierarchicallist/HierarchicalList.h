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
 *  SceneList.h, created by Marek Bereza on 14/10/2013.
 */

#pragma once

#include "ofMain.h"

#include "HierarchicalObject.h"
#include "Scene.h"
#include "SceneView.h"
#include "Frame.h"




class HierarchicalListItem {
public:
	HierarchicalListItem(HierarchicalObject *obj, int depth = 0) { this->obj = obj; this->depth = depth; }
	HierarchicalObject *obj;
	int depth;
};


class HierarchicalList: public SceneView {
public:
	
	vector<HierarchicalListItem> items;
	void buildItemList(HierarchicalObject *parent, int depth = 0);

	HierarchicalListItem *itemBeingDragged;
	HierarchicalListItem *lastItemPressed;
	
	ofVec2f itemDraggedMouseOffset;
	int itemHeight;
	int dropPos;
	ofVec2f mousePressLocation;
	HierarchicalList();
	void draw(ofEventArgs &args);
	
	void setEnabled(bool enabled);
	
	bool mousePressed(ofMouseEventArgs &m);
	bool mouseReleased(ofMouseEventArgs &m);
	bool mouseDragged(ofMouseEventArgs &m);
	void keyReleased(ofKeyEventArgs &k);
	void keyPressed(ofKeyEventArgs &k);
	void drawItem(HierarchicalListItem *item, ofRectangle &r);

	bool altPressed;
	bool shiftPressed;
	
	bool enabled;


};