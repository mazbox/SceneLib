/**
 *  Frameset.cpp
 *
 *  Created by Marek Bereza on 11/03/2014.
 */

#include "Frameset.h"
void Frameset::setup(float x, float y, float width, float height) {
	resize(x, y, width, height);
	ofAddListener(ofEvents().mouseMoved,	this,	&Frameset::mouseMoved);
	ofAddListener(ofEvents().mousePressed,	this,	&Frameset::mousePressed);
	ofAddListener(ofEvents().mouseDragged,	this,	&Frameset::mouseDragged);
	ofAddListener(ofEvents().mouseReleased, this,	&Frameset::mouseReleased);
}

void Frameset::draw() {
	Frame::draw();
}

bool Frameset::mouseMoved(ofMouseEventArgs &m) {
	return false;
}

bool Frameset::mousePressed(ofMouseEventArgs &m) {
	return false;
}


bool Frameset::mouseDragged(ofMouseEventArgs &m) {
	return false;
}


bool Frameset::mouseReleased(ofMouseEventArgs &m) {
	selections.clear();
	return false;
}

