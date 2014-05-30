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
 *  ContextMenu.h, created by Marek Bereza on 11/10/2013.
 */

#pragma once

#include "ofMain.h"

#include "ContextMenuListener.h"
#include "ContextMenuLevel.h"




class ContextMenu {
public:
	bool enabled;
	vector<ContextMenuListener*> listeners;
	
	ContextMenu() {
		enabled = false;
		root = new ContextMenuLevel();
		hasMoved = false;
		isShowing = false;
	}
	
	void addListener(ContextMenuListener *listener) {
		this->listeners.push_back(listener);
	}
	
	void setEnabled(bool enabled) {
		if(this->enabled==enabled) {
			return;
		}
		
		this->enabled = enabled;
		if(this->enabled) {
			ofAddListener(ofEvents().mouseMoved, this, &ContextMenu::mouseMoved);
			ofAddListener(ofEvents().mousePressed, this, &ContextMenu::mousePressed);
			ofAddListener(ofEvents().mouseDragged, this, &ContextMenu::mouseDragged);
			ofAddListener(ofEvents().mouseReleased, this, &ContextMenu::mouseReleased);
			ofAddListener(ofEvents().draw, this, &ContextMenu::draw);
		} else {
			ofRemoveListener(ofEvents().mouseMoved, this, &ContextMenu::mouseMoved);
			ofRemoveListener(ofEvents().mousePressed, this, &ContextMenu::mousePressed);
			ofRemoveListener(ofEvents().mouseDragged, this, &ContextMenu::mouseDragged);
			ofRemoveListener(ofEvents().mouseReleased, this, &ContextMenu::mouseReleased);
			ofRemoveListener(ofEvents().draw, this, &ContextMenu::draw);
		}
	}
	
	bool hasMoved;
	bool isShowing;
	
	
	void addItem(string name, ContextMenuLevel *submenu = NULL) {
		root->addItem(name, submenu);
	}
	
	
	void addItem(string name, string command) {
		root->addItem(name, command);
	}
	
	
	void mouseMoved(ofMouseEventArgs &args) {
		if(isShowing) {
			root->mouseMoved(args.x, args.y);
		}
	}
	bool mousePressed(ofMouseEventArgs &args) {
		bool cancelBubble = false;
		if(isShowing && args.button==0) {
			ContextMenuItem *item = root->recursiveFindSelected(args.x, args.y);
			if(item!=NULL) {
				for(int i = 0; i < listeners.size(); i++) {
					listeners[i]->contextMenuItemSelected(item);
				}
			}
			hide();
			cancelBubble = true;
		}
		hasMoved = false;
		//if(cancelBubble) {
		//	printf("ContextMenu canceled bubble\n");
		//}
		return cancelBubble;

	}
	
	void mouseDragged(ofMouseEventArgs &args) {
		hasMoved = true;
	}
	
	bool mouseReleased(ofMouseEventArgs &args) {

		if(args.button==0) {
			return false;
		}
		if(!hasMoved) {
			show(ofVec2f(args.x, args.y));
		} else {
			hide();
			
		}
		return true;
	}
	
	void hide() {
		isShowing = false;
	}
	void show(ofVec2f m) {
		isShowing = true;
		root->calculateLayouts(ofVec2f(m.x, m.y));
		root->closeChildren();
		root->selectedChild = NULL;
	}

	
	void draw(ofEventArgs &args) {
		if(isShowing) {
			root->draw();
		}
	}
	
	
	ContextMenuLevel *root;

};