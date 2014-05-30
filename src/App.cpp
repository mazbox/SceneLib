/**
 *  App.cpp
 *
 *  Created by Marek Bereza on 29/10/2013.
 */

#include "App.h"
#include "ScreenLayoutMode.h"
#include "RenderClientPreviewMode.h"
#include "UI.h"

App *App::instance = NULL;

App::App() {

	currModeId = 0;
	ofAddListener(ofEvents().mouseMoved, this, &App::mouseMoved, 300);
	ofAddListener(ofEvents().mousePressed, this, &App::mousePressed, 300);
	ofAddListener(ofEvents().mouseReleased, this, &App::mouseReleased, 300);
	ofAddListener(ofEvents().mouseDragged, this, &App::mouseDragged, 300);
	ofAddListener(ofEvents().keyPressed, this, &App::keyPressed, 300);
	ofAddListener(ofEvents().keyReleased, this, &App::keyReleased, 300);
}


App *App::getInstance() {
	if(instance==NULL) {
		instance = new App();
	}
	
	return instance;
}

void App::addRenderClientMode(RenderClientMode *mode) {
	renderClientMode = mode;
	// TODO: this should only allow one for now.
	addMode(mode);
	RenderClientPreviewMode *previewMode = new RenderClientPreviewMode();
	previewMode->setup(mode);
	addMode(previewMode);
	screenLayout->setRenderClientMode(mode);
}

void App::addMode(Mode *mode) {
	modes.push_back(mode);
}


void App::setup(Scene *scene) {
	this->scene = scene;
	screenLayout = new ScreenLayoutMode(scene);
	addMode(screenLayout);
	UI::getInstance()->setup(scene);
}

Mode *App::getCurrMode() {
	return modes[currModeId];
}

void App::draw() {
	screenLayout->sendAnyScreenPositionChanges();
	
	getCurrMode()->drawMode();
}

void App::nextMode() {
	currModeId = (currModeId + 1) % modes.size();
}
void App::setToRenderMode() {
	while(modes[currModeId]!=renderClientMode) {
		nextMode();
	}
}
void App::prevMode() {
	currModeId--;
	if(currModeId<0) currModeId += modes.size();
}

void App::update(ofEventArgs &evt) {
	ofSetWindowTitle(App::getInstance()->getCurrMode()->getName());
}

void App::mouseMoved(ofMouseEventArgs &m) {
	return getCurrMode()->mouseMoved(m);
}

bool App::mousePressed(ofMouseEventArgs &m) {
	return getCurrMode()->mousePressed(m);
}

bool App::mouseDragged(ofMouseEventArgs &m) {
	return getCurrMode()->mouseDragged(m);
}

bool App::mouseReleased(ofMouseEventArgs &m) {
	return getCurrMode()->mouseReleased(m);
}

bool App::keyPressed(ofKeyEventArgs &k) {
	return getCurrMode()->keyPressed(k);
}
bool App::keyReleased(ofKeyEventArgs &k) {
	return getCurrMode()->keyReleased(k);
}