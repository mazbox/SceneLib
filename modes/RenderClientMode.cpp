/**
 *  ClientRenderer.cpp
 *
 *  Created by Marek Bereza on 29/10/2013.
 */

#include "RenderClientMode.h"

void RenderClientMode::setup(ScreenCanvasRenderer *renderer, Scene *scene) {
	this->renderer = renderer;
	this->scene = scene;
	//fxaa.load("../shader/v002.FXAA.vert", "../shader/v002.FXAA.frag");
	fxaaEnabled = false;
	vector<HierarchicalObject *> outObjects;
	
	
	scene->getObjectsOfType(outObjects, "screen canvas");
	if(outObjects.size()!=1) {
		ofLogError() << "There were not exactly 1 screen canvases in the scene!";
		return;
	}
	
	canvas = (ScreenCanvasObject*) outObjects[0];
	
	
	//scene->getObjectsOfType(outObjects, "screen");
	// use these
/*	for(int i = 0; i < outObjects.size(); i++) {
		screens.push_back((ScreenObject*)outObjects[i]);
	}*/
	IndexedObject::printObjects();
	vector<UID> screenUids;
	
	ofxMPEClient::getInstance()->getScreenUids(screenUids);
	
	for(int i = 0; i < screenUids.size(); i++) {
		screens.push_back((ScreenObject*)scene->getObjectByUid(screenUids[i]));
		printf("Gonna render to %d\n", screenUids[i]);
	}
	
	
	fboChannelInfo = GL_RGBA;//GL_RGBA16;
	screenFbo.allocate(128, 128, fboChannelInfo);
}




void RenderClientMode::draw() {
	ofRectangle r;
	
	r.width = canvas->width;
	r.height = canvas->height;
		

	glPushMatrix();
	
	
	glScalef((float)ofGetWidth()/canvas->width, (float)ofGetHeight()/canvas->height, 1);
	//glScalef((float)ofGetWidth(), (float)ofGetHeight(), 1);
	ScreenObject screen;
	screen.sourceRect = r;
	
	renderer->render(canvas->width, canvas->height, &screen);
	
	
	glPopMatrix();
}

bool RenderClientMode::thisClientRenders(ScreenObject *screen) {
	return ofxMPEClient::getInstance()->doesRenderScreen(screen->uid);

}

void RenderClientMode::checkFboIsBigEnough() {
	// use these
	/*	for(int i = 0; i < outObjects.size(); i++) {
	 screens.push_back((ScreenObject*)outObjects[i]);
	 }*/
	vector<UID> screenUids;
	
	ofxMPEClient::getInstance()->getScreenUids(screenUids);
	screens.clear();
	for(int i = 0; i < screenUids.size(); i++) {
		screens.push_back((ScreenObject*)scene->getObjectByUid(screenUids[i]));

	}

	
	
	
	float maxW = screenFbo.getWidth();
	float maxH = screenFbo.getHeight();
	
	for(int i =0 ; i < screens.size(); i++) {
		//printf("%d\n", i);
		if(maxW<screens[i]->resolutionX) maxW = screens[i]->resolutionX;
		if(maxH<screens[i]->resolutionY) maxH = screens[i]->resolutionY;
		
		
	}
	
	// TODO: get actual max texture size instead of 4096
	maxW = ofClamp(maxW, 0, 4096);
	maxH = ofClamp(maxH, 0, 4096);
	
	maxW = maxH = MAX(maxW, maxH);
	
	
	if(maxW!=screenFbo.getWidth() || maxH!=screenFbo.getHeight()) {
		screenFbo.allocate(maxW, maxH, fboChannelInfo);
		printf("Bumping res to %.0f %.0f\n", maxW, maxH);
	}
}


void RenderClientMode::drawMode() {
	
	
	
	
	ofRectangle r;
	
	r.x = 0;
	r.y = 0; 


	checkFboIsBigEnough();

	
	for(int i =0 ; i < screens.size(); i++) {
		//
		//if(!thisClientRenders(screens[i])) continue;
		r.width = screens[i]->resolutionX;
		r.height = screens[i]->resolutionY;
		

		
		screenFbo.begin();
		


		
		float resX = screens[i]->resolutionX;
		float resY = screens[i]->resolutionY;
		if(screens[i]->orientation%2==1) { // we're portrait, so swap dims
			float tmp = resX;
			resX = resY;
			resY = tmp;
		}
		
		glEnable(GL_SCISSOR_TEST);
		//ofPushView();
		//ofViewport(ofRectangle(0, 0, resX, screenFbo.getHeight()));
		glScissor(0, 0, resX, resY);
		ofClear(0,0,0,0);
		glPushMatrix();

		glScalef(resX/screens[i]->sourceRect.width, resY/screens[i]->sourceRect.height, 1);
				
		glTranslatef(-screens[i]->sourceRect.x, -screens[i]->sourceRect.y, 0);
		
		renderer->render(canvas->width, canvas->height, screens[i]);
		
		glPopMatrix();

		glDisable(GL_SCISSOR_TEST);
		
		screenFbo.end();
		
		ofSetColor(255);
		
		float tcX = resX/(float)screenFbo.getWidth();
		float tcY = resY/(float)screenFbo.getHeight();
		
		deque<ofVec2f> tc;
		quadMesh.clear();
		
		tc.push_back(ofVec2f(0, 0));
		tc.push_back(ofVec2f(tcX, 0));
		tc.push_back(ofVec2f(tcX, tcY));
		tc.push_back(ofVec2f(0, tcY));
		
		for(int k = 0; k < screens[i]->orientation; k++) {
			ofVec2f v = tc.front();
			tc.pop_front();
			tc.push_back(v);
			
			/*
			ofVec2f v = tc.back();
			tc.pop_back();
			tc.push_front(v);*/
		}
		vector<ofVec2f> v;
		v.push_back(ofVec2f(r.x, r.y));
		v.push_back(ofVec2f(r.x+r.width, r.y));
		v.push_back(ofVec2f(r.x+r.width, r.y+r.height));
		v.push_back(ofVec2f(r.x, r.y+r.height));
		
		
		
		for(int k = 0; k < tc.size(); k++) {
			quadMesh.addTexCoord(tc[k]);
			quadMesh.addVertex(v[k]);
			
		}
		quadMesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
		
		
		//if(fxaaEnabled) fxaa.begin();
		screenFbo.getTextureReference(0).bind();
		quadMesh.draw();

		screenFbo.getTextureReference(0).unbind();
		//if(fxaaEnabled) {
		//	fxaa.end();
		//}
		
		r.x += r.width;

	}
	
	
	
}

void RenderClientMode::drawTestScreen() {
	
}

