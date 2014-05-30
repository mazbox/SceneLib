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
 *  Description: This takes a renderer (i.e. your program) and a scene, and draws the bits of the
 *				 scene that need rendering (i.e. the screens you've specified in your client.xml)
 *				 
 *  TODO: this thinks that all screen objects belong to the main screencanvas, this might not be true
 *  TODO: needs to pick which screens to draw with depending on client.xml
 *  TODO: MPE Goes in here probably.
 *  TODO: get rid of the 2 fbos and just use one. The reason there was 2 is that I had trouble programming
 *        a rotatable opengl view.
 *
 *  RenderClient, created by Marek Bereza on 29/10/2013.
 */

#pragma once

#include "Mode.h"

#include "ScreenCanvasRenderer.h"
#include "ScreenCanvasObject.h"
#include "ScreenObject.h"
#include "Scene.h"
#include "ofxMPEClient.h"

class RenderClientMode: public Mode {
public:
	
	string getName() {
		return "Render Client";
	}

	
	
	ScreenCanvasRenderer *renderer;
	ScreenCanvasObject *canvas;
	Scene *scene;
	vector<ScreenObject*> screens;
	
	void setup(ScreenCanvasRenderer *renderer, Scene *scene);
	
	

	bool thisClientRenders(ScreenObject *screen);
	
	ofFbo screenFbo;

	ofVboMesh quadMesh;
	ofShader fxaa;
	bool fxaaEnabled;
	void drawMode();	
	void draw();
	
	void drawTestScreen();
private:
	void checkFboIsBigEnough();
	int fboChannelInfo;
};
