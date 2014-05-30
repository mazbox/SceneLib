
#include "HierarchicalList.h"
#include "ofxXmlGui.h"




HierarchicalList::HierarchicalList() {
	itemHeight = 20;
	enabled = false;
	shiftPressed = false;
	altPressed = false;
	itemBeingDragged = NULL;
	lastItemPressed = NULL;
	dropPos = -1;
	x = 0;
	y = 0;
	width = 100;
	height = 200;
}




void HierarchicalList::setEnabled(bool enabled) {
	if(this->enabled==enabled) {
		return;
	}
	this->enabled = enabled;
	if(this->enabled) {
		ofAddListener(ofEvents().draw, this, &HierarchicalList::draw);
		ofAddListener(ofEvents().mousePressed, this, &HierarchicalList::mousePressed);
		ofAddListener(ofEvents().mouseDragged, this, &HierarchicalList::mouseDragged);
		ofAddListener(ofEvents().mouseReleased, this, &HierarchicalList::mouseReleased);
		ofAddListener(ofEvents().keyPressed, this, &HierarchicalList::keyPressed);
		ofAddListener(ofEvents().keyReleased, this, &HierarchicalList::keyReleased);
	} else {
		ofRemoveListener(ofEvents().draw, this, &HierarchicalList::draw);
		ofRemoveListener(ofEvents().mousePressed, this, &HierarchicalList::mousePressed);
		ofRemoveListener(ofEvents().mouseDragged, this, &HierarchicalList::mouseDragged);
		ofRemoveListener(ofEvents().mouseReleased, this, &HierarchicalList::mouseReleased);
		ofRemoveListener(ofEvents().keyPressed, this, &HierarchicalList::keyPressed);
		ofRemoveListener(ofEvents().keyReleased, this, &HierarchicalList::keyReleased);
	}
}

void HierarchicalList::keyPressed(ofKeyEventArgs &k) {
	if(k.key==OF_KEY_LEFT_SHIFT || k.key==OF_KEY_RIGHT_SHIFT) {
		shiftPressed = true;
	} else if(k.key==OF_KEY_LEFT_ALT || k.key==OF_KEY_RIGHT_ALT) {
		altPressed = true;
	}
}

void HierarchicalList::keyReleased(ofKeyEventArgs &k) {
	if(k.key==OF_KEY_LEFT_SHIFT || k.key==OF_KEY_RIGHT_SHIFT) {
		shiftPressed = false;
	} else if(k.key==OF_KEY_LEFT_ALT || k.key==OF_KEY_RIGHT_ALT) {
		altPressed = false;
	} else if(k.key=='w') {
		
	}
}

void HierarchicalList::buildItemList(HierarchicalObject *parent, int depth) {
	if(parent==root) {
		items.clear();
		root->expanded = true;
	}

	if(!parent->expanded) return;
	for(int i = 0; i < parent->children.size(); i++) {
		items.push_back(HierarchicalListItem(parent->children[i], depth));

		// if this is the root, expand it.
		buildItemList(parent->children[i], depth+1);
	}
}


void HierarchicalList::draw(ofEventArgs &args) {

	glEnable(GL_SCISSOR_TEST);
	glScissor(x, ofGetHeight()-(y+height), width, height);
	


	buildItemList(root);
	//width = 220;
	//height = items.size() * itemHeight;
	//x = ofGetWidth() - width;
	//y = 0;
	
	ofFill();
	glColor4f(0, 0, 0, 0.4);
	ofRect(*this);
	
	
	int pos = 0;
	
	
	for(int i = 0; i < items.size(); i++) {
		if(&items[i]!=itemBeingDragged) {
			
			ofRectangle r;
			r.set(x, y + itemHeight*pos, width, itemHeight);
			if(pos%2==0) {
				glColor4f(0.1, 0.1, 0.1, 0.8);
				ofRect( r );
			} else {
				
			}
			
			drawItem(&items[i], r);
			
			pos++;
		}
	}
	 
	
	if(itemBeingDragged!=NULL) {
		ofRectangle r(ofGetMouseX() - itemDraggedMouseOffset.x, ofGetMouseY() - itemDraggedMouseOffset.y, width, itemHeight);
		glColor4f(0.1, 0.1, 0.1, 0.8);
		ofRect(r);
		drawItem(itemBeingDragged, r);
		ofLine(x, dropPos*itemHeight+1, x+width, dropPos*itemHeight+1);
		
	}
	glDisable(GL_SCISSOR_TEST);
}

void HierarchicalList::drawItem(HierarchicalListItem *item, ofRectangle &r) {
	if(((Object*)item->obj)->selected) {
		ofSetColor(255, 200, 100);
	} else if(!((Object*)item->obj)->enabled) {
		ofSetColor(120);
	} else {
		ofSetColor(255);
	}
	
	string str = item->obj->name;
	if(item->obj->children.size()>0) {
		if(item->obj->expanded)  {
			str = "v " + str;
		} else {
			str = "> " + str;
		}
	} else {
		str = "  " + str;
	}
	xmlgui::Resources::drawString
	//ofDrawBitmapString
	(str, r.x+3+8*item->depth, r.y + r.height - 5);
	xmlgui::Resources::drawString
	//ofDrawBitmapString
	(item->obj->type, r.x + r.width * 2 / 3, r.y + r.height - 5);
}



bool HierarchicalList::mousePressed(ofMouseEventArgs &m) {
	if(inside(m.x, m.y)) {
		int i = m.y/itemHeight;
		if(i<items.size()) {
			lastItemPressed = &items[i];
			itemDraggedMouseOffset.set(m.x - this->x, m.y - i*itemHeight);
			mousePressLocation.set(m.x, m.y);
			if(items[i].obj->children.size()>0 && m.x - x < 20) {
				items[i].obj->expanded ^= true;
			} else {
				scene->objectClicked((Object*)items[i].obj);
			}
			return true;
		}
		
	}
	return false;
}

bool HierarchicalList::mouseReleased(ofMouseEventArgs &m) {
	if(itemBeingDragged!=NULL) {
		if(!itemBeingDragged->obj->removeFromParent()) {
			ofLogError() << "Couldn't remove "<<itemBeingDragged->obj->name<<" from parent";
			return false;
		}
		int dp = dropPos;
		bool found = false;
		for(int i = 0; i < dropPos; i++) {
			if(items[i].obj==itemBeingDragged->obj) {
			
				found = true;
				break;
			}
			
		}
		if(!found) {
			dp--;
		}
		if(dp==-1) {
			root->addChildAtFront(itemBeingDragged->obj);
		} else if(items[dp].obj->expanded) {
			items[dp].obj->addChildAtFront(itemBeingDragged->obj);
		} else {
//			ofLogNotice() << "Adding child '"<<itemBeingDragged->obj->name <<"' to '"<<items[dp].obj->parent->name <<"' - after "<<items[dp].obj->name<<"!";
			if(!items[dp].obj->parent->addChildAfter(itemBeingDragged->obj, items[dp].obj)) {
			
				ofLogError() << "Couldn't add child to '"<<items[dp].obj->parent->name <<"'!";
			}
		}
		itemBeingDragged = NULL;
		lastItemPressed = NULL;
		return true;
	}
	
	
	return false;
}





bool HierarchicalList::mouseDragged(ofMouseEventArgs &m) {
	if(itemBeingDragged!=NULL || (mousePressLocation.distance(ofVec2f(m.x, m.y))>4 && inside(m.x, m.y))) {
		itemBeingDragged = lastItemPressed;
		dropPos = m.y/itemHeight;
		dropPos = ofClamp(dropPos, 0, items.size()-1);
		return true;
	}
	return false;
}

