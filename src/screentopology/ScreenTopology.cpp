/**
 *  ScreenTopology.cpp
 *
 *  The platform independent part of screen topology
 *
 *  Created by Marek Bereza on 03/06/2014.
 */

#include "ScreenTopology.h"


ofRectangle ScreenTopology::getControlScreen() {
	ofRectangle firstScreen = getScreenRect(0);
	
	// we're not fullscreen so just make the first screen the control screen
	if(firstScreen.getWidth()>ofGetWidth()) {
		ofRectangle(0, 0, ofGetWidth(), ofGetHeight());
	} else {
		return firstScreen;
	}
}

ofRectangle ScreenTopology::getOutputScreen() {
	int numScreens = getNumScreens();
	
	// if there's more than one screen, add up all the other
	// screens to output one big screen.
	if(numScreens>1) {
		ofRectangle r = getScreenRect(1);
		for(int i = 2; i < numScreens; i++) {
			r.growToInclude(getScreenRect(i));
		}
		
		return r;
	} else {
		return ofRectangle();
	}
}