#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofBackground(0);

	lastFrameTime = ofGetElapsedTimef();

	client.setup("mpe_client_settings.xml", true); //false means you can use backthread
	client.start();
	
	ofxMPERegisterEvents(this);
}

//--------------------------------------------------------------
void testApp::update(){
}

//--------------------------------------------------------------
void testApp::draw(){
	//don't use this
}

//--------------------------------------------------------------
void testApp::mpeFrameEvent(ofxMPEEventArgs& event)
{
	ofDrawBitmapString( ofToString(event.frame), 10, 10);
	
	/*
	float now = ofGetElapsedTimef();
	cout << "fps would be " << 1./(now - lastFrameTime) << endl;
	lastFrameTime = now;
	*/
}

//--------------------------------------------------------------
void testApp::mpeMessageEvent(ofxMPEEventArgs& event){
	//received a message from the server
}


void testApp::mpeResetEvent(ofxMPEEventArgs& event){
	//triggered if the server goes down, another client goes offline, or a reset was manually triggered in the server code
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}