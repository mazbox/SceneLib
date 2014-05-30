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
 *  TODO: get rid of setToRenderMode() and RenderClientMode *renderClientMode, and addRenderClientMode
 *  App.h, created by Marek Bereza on 29/10/2013.
 */

#pragma once

#include "ofMain.h"
#include "Mode.h"
#include "Scene.h"
#include "RenderClientMode.h"
#include "ScreenLayoutMode.h"


class App {

private:
	App();
	static App *instance;
	Scene *scene;
	int currModeId;
	
public:
	ScreenLayoutMode *screenLayout;
	void setToRenderMode();
	
	
	static App *getInstance();
	void update(ofEventArgs &evt);
	void mouseMoved(ofMouseEventArgs &m);
	bool mousePressed(ofMouseEventArgs &m);
	bool mouseDragged(ofMouseEventArgs &m);
	bool mouseReleased(ofMouseEventArgs &m);
	bool keyPressed(ofKeyEventArgs &k);
	bool keyReleased(ofKeyEventArgs &k);
	
	Mode *getCurrMode();
	void addRenderClientMode(RenderClientMode *mode);
	void setup(Scene *scene);
	
	vector<Mode*> modes;
	
	void draw();
	void nextMode();
	void prevMode();
	void addMode(Mode *mode);

	RenderClientMode *renderClientMode;
};
