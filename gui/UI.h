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
 *  UI.h, created by Marek Bereza on 10/10/2013.
 */
#pragma once

#include "Inspector.h"
#include "ContextMenu.h"
#include "Scene.h"
#include "HierarchicalList.h"

#include "constants.h"
class UI: public ContextMenuListener {
private:
	UI() {}
public:
	
	static UI *getInstance();
	
	void setup(Scene *scene);
	
	
	bool isEnabled();
	void toggle();
	void setEnabled(bool enabled);
	
	
	void setupMenu();
	

	
	void mousePressed(ofMouseEventArgs &m);
	void mouseReleased(ofMouseEventArgs &m);
	void mouseDragged(ofMouseEventArgs &m);
	void keyPressed(ofKeyEventArgs &k);
	void keyReleased(ofKeyEventArgs &k);

	void axisGrabbed(int axis, bool shouldDuplicate = false);
	void contextMenuItemSelected(ContextMenuItem *item);
	
	
	void addObject(string type);
	
	// selection
	void addSelectedObject(Object *object);
	void setSelectedObject(Object *object);
	
	void groupSelectedItems();
	
	
	bool isSelected(Object *object);
	
private:
	
	void setFocus(Object *object);
	
	vector<Object*> selectedObjects;
	Inspector inspector;
	ContextMenu menu;
	Scene *scene;
	HierarchicalList *sceneList;
	ofVec2f prevMouse;
	int grabAxis;
	bool shiftDown;
	bool enabled;
};