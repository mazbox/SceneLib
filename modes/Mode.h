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
 *  Description: This represents a mode in the app. So there might be a texturing mode, a layout 
 *				 mode etc. You might have custom modes for your app.
 * 
 *				 
 *  Mode.h, created by Marek Bereza on 29/10/2013.
 */

#pragma once

#include "ofMain.h"
#include "UI.h"

class Mode {
public:
	virtual string getName() = 0;
	virtual void drawMode() = 0;
	virtual void mouseMoved (ofMouseEventArgs &m) {}
	virtual bool mousePressed (ofMouseEventArgs &m) {}
	virtual bool mouseDragged (ofMouseEventArgs &m) {}
	virtual bool mouseReleased(ofMouseEventArgs &m) {}
	virtual bool keyPressed(ofKeyEventArgs &k) {}
	virtual bool keyReleased(ofKeyEventArgs &k) {}
};

