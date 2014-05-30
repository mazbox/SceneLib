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
 *  ContextMenuLevel.h, created by Marek Bereza on 08/11/2013.
 */

#pragma once

#include "ofMain.h"

#define USING_XMLGUI

#define CONTEXT_MENU_ITEM_HEIGHT 20
#define CONTEXT_MENU_WIDTH 100

class ContextMenuItem;

class ContextMenuLevel: public ofRectangle {
public:
	ContextMenuLevel();
	void draw();
	void addItem(string name, ContextMenuLevel *submenu = NULL);
	void addItem(string name, string command);
	vector<ContextMenuItem*> children;
	void calculateLayouts(ofVec2f m);
	bool isShowing;
	void mouseMoved(float x, float y);
	ContextMenuItem *selectedChild;
	ContextMenuItem *recursiveFindSelected(float x, float y);
	void closeChildren();
};

