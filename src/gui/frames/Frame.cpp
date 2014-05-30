/**
 *  Frame.cpp
 *
 *  Created by Marek Bereza on 11/03/2014.
 */

#include "Frame.h"


Frame::Frame() {
	vertical = false;
}

void Frame::draw() {
	drawChildren();
}

void Frame::drawChildren() {
	for(int i =0 ; i < children.size(); i++) {
		children[i]->draw();
	}
}
void Frame::addChild(Frame *child) {
	children.push_back(child);
	respaceEvenly();
}

void Frame::respaceEvenly() {
	for(int i = 0; i < children.size(); i++) {
		if(vertical) {
			children[i]->x = x;
			children[i]->y = (float)i* height/children.size();
			children[i]->width = width;
			children[i]->height = height/children.size();
		} else {
			children[i]->x = (float)i*width/children.size();
			children[i]->y = y;
			children[i]->width = width/children.size();
			children[i]->height = height;
		}
	}
}



bool Frame::loadLayout(string path) {
	
}

bool Frame::saveLayout(string path) {
	
}


void Frame::resize(float x, float y, float width, float height) {
	set(x, y, width, height);
	respaceEvenly();
	
}

void Frame::resize(ofRectangle &r) {
	resize(r.x, r.y, r.width, r.height);
}
