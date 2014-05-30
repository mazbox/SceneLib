/**
 *  ContextMenuLevel.cpp
 *
 *  Created by Marek Bereza on 08/11/2013.
 */

#include "ContextMenuLevel.h"

#include "ContextMenuItem.h"
#ifdef USING_XMLGUI
#include "xmlgui/framework/Resources.h"
#endif
ContextMenuLevel::ContextMenuLevel() {
	width = CONTEXT_MENU_WIDTH;
	isShowing = false;
	
}
void ContextMenuLevel::draw() {
	ofSetHexColor(0xBBBBBB);
	ofRect(*this);
	ofNoFill();
	glColor4f(0.1, 0.1, 0.1, 0.3);
	ofRect(*this);
	ofFill();
	for(int i = 0; i < children.size(); i++) {
		ofRectangle r(children[i]->x+1, children[i]->y+1, children[i]->width-2, children[i]->height-2);
		if(children[i]==selectedChild) {
			ofSetColor(255, 255, 100);
			ofRect(r);
		}
		glColor4f(0.1, 0.1, 0.1, 0.3);
		ofNoFill();
		
		ofLine(children[i]->x, children[i]->y, children[i]->x+children[i]->width, children[i]->y);
		//ofRect(r);
		ofFill();
		ofSetHexColor(0);
		#ifdef USING_XMLGUI
		xmlgui::Resources::drawString
		#else
		ofDrawBitmapString
		#endif
		(children[i]->text, children[i]->x + 3, children[i]->y + CONTEXT_MENU_ITEM_HEIGHT-5);
		
		if(children[i]->child!=NULL) {
#ifdef USING_XMLGUI
			xmlgui::Resources::drawString
#else
			ofDrawBitmapString
#endif
			(">", children[i]->x + CONTEXT_MENU_WIDTH - 10, children[i]->y + CONTEXT_MENU_ITEM_HEIGHT-5);
			if(children[i]->child->isShowing) {
				children[i]->child->draw();
			}
		}
	}
}

void ContextMenuLevel::closeChildren() {
	for(int i = 0; i < children.size(); i++) {
		if(children[i]->child!=NULL) {
			children[i]->child->isShowing = false;
			//children[i]->child->selectedChild = NULL;
		}
	}
}

ContextMenuItem *ContextMenuLevel::recursiveFindSelected(float x, float y) {
	selectedChild = NULL;
	for(int i = 0; i < children.size(); i++) {
		if(children[i]->inside(x, y)) {
			if(children[i]->child!=NULL) {
				children[i]->child->isShowing = true;
				children[i]->child->closeChildren();
				children[i]->child->selectedChild = NULL;
			}
			selectedChild = children[i];
			
		} else if(children[i]->child!=NULL) {
			ContextMenuItem *result = children[i]->child->recursiveFindSelected(x, y);
			if(result==NULL) {
				children[i]->child->isShowing = false;
			} else {
				return result;
			}
		}
	}
	return selectedChild;
}


void ContextMenuLevel::mouseMoved(float x, float y) {
	selectedChild = recursiveFindSelected(x, y);
}

void ContextMenuLevel::addItem(string name, string command) {
	children.push_back(new ContextMenuItem(name, command));
	height += CONTEXT_MENU_ITEM_HEIGHT;
}
void ContextMenuLevel::addItem(string name, ContextMenuLevel *submenu) {
	children.push_back(new ContextMenuItem(name, submenu));
	height += CONTEXT_MENU_ITEM_HEIGHT;
}

void ContextMenuLevel::calculateLayouts(ofVec2f m) {
	x = m.x;
	y = m.y;
	for(int i = 0; i < children.size(); i++) {
		children[i]->x = x;
		children[i]->y = y + i*CONTEXT_MENU_ITEM_HEIGHT;
		children[i]->width = CONTEXT_MENU_WIDTH+1;
		children[i]->height = CONTEXT_MENU_ITEM_HEIGHT+1;
		if(children[i]->child!=NULL) {
			children[i]->child->calculateLayouts(ofVec2f(x+CONTEXT_MENU_WIDTH, y + i*CONTEXT_MENU_ITEM_HEIGHT));
		}
	}
}
