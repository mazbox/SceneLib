/**
 *  openFrameworks version of the popular synchronization system Most Pixels Ever by Dan Shiffman
 *  original repo: https://github.com/shiffman/Most-Pixels-Ever
 *  our fork: https://github.com/FlightPhase/Most-Pixels-Ever
 *
 *  I affectionately refer to as "Most Pickles Ever" since it's gotten me out of the most pickles. ever!
 *
 *  Standing on the shoulders of the original creators:
 *  Dan Shiffman with Jeremy Rotsztain, Elie Zananiri, Chris Kairalla.
 *  Extended by James George on 5/17/11 @ Flightphase for the National Maritime Museum
 *
 *  Still need to convert the original examples to the new format
 *
 *  There is a drawback that this is not compatible with the Java MPE jar, the connections must go OF client to OF Server
 *
 */

#include "ofxMPEServer.h"
#include "ofxXmlSettings.h"

ofxMPEServer::ofxMPEServer()
{
	paused = false;
	allconnected = false;
	mustSendRandomSeed = false;
	framerate = 30;
	numRequiredClients = 0;
	currentFrame = 0;
	shouldTriggerFrame = false;

	newMessage = false;
	verbose = false;
	delimiter = "|";
	
	//TODO: heart beats
	timeOfNextHeartbeat = ofGetElapsedTimef();
	heartBeatInterval = 2.0;

}


void ofxMPEServer::setup(string settingsFile)
{

	ofxXmlSettings xml;
	if(!xml.loadFile(settingsFile)){
		ofLog(OF_LOG_ERROR, "MPE Server -- Couldn't load settings file: " + settingsFile);
		return;
	}
	xml.pushTag("clients");
	int numClients = xml.getNumTags("client");
	xml.popTag();
	setup(
		  
		  xml.getAttribute("clients", "fps", 0, 0),
		  xml.getAttribute("clients", "port", 9001, 0),
		  numClients,
		  false);
	
	//server.setMessageDelimiter("\n");
	ofAddListener(ofEvents().exit, this, &ofxMPEServer::exit);
}

void ofxMPEServer::setup(int fps, int port, int numClients, bool verbose)
{

	close(); // in case of double set up

	//make sure vsync is OFF
	//make sure framerate is fast as it can go

	this->verbose = verbose;
	//TODO: support
	shouldWaitForAllClients = true;
	
	while(!server.setup(port, false)){
		ofLog(OF_LOG_ERROR, "MPE Serever :: Setup failed - will keep trying\n");
		ofSleepMillis(1000);
	}
	
	numRequiredClients = numClients;
	framerate = fps;

	shouldTriggerFrame = false;
	allconnected = false;
	lastFrameTriggeredTime = 0;
	currentFrame = 0;

	startThread(true, false);

	cout << "Setting up server with FPS " << fps << " on port " << port << " with clients " << numClients << endl;
}

void ofxMPEServer::reset()
{
	ofLogNotice() << "Sending reset!!";
	//client already connected, must have reset...
	allconnected = false;
	currentFrame = 0;
	currentMessage = "";
	shouldTriggerFrame = false;
	server.sendToAll("R");
}







void ofxMPEServer::doTriggerFrame() {
	float now = ofGetElapsedTimef();
	float elapsed = (now - lastFrameTriggeredTime);
	
	
	if(elapsed >= 1.0/framerate){
		
		//				cout << "triggered frame with framerate error of " << fabs( elapsed - 1.0/framerate)  << endl;
		currFrameRateRaw = 1.f/elapsed;
		if(currFrameRate==0) {
			currFrameRate = currFrameRateRaw;
		}
		currFrameRate = currFrameRate * 0.95 + currFrameRateRaw * 0.05;
		
		if(mustSendRandomSeed) {
			int randomSeed = (int)ofRandom(0, 10000);
			ofLogNotice() << "Sending random seed " << randomSeed;
			server.sendToAll("T|random: " +ofToString(randomSeed));
			mustSendRandomSeed = false;
		}
		
		
		string message = "G"+delimiter+ofToString(currentFrame);
		if (currentMessage != ""){
			message += currentMessage;
			currentMessage = "";
		}
		//	cout << "Sending " << message << endl;
		//TODO: per-client messaging
		server.sendToAll(message);
		
		
		map<int, Connection>::iterator it;
		for(it = connections.begin(); it != connections.end(); it++){
			it->second.ready = false;
		}
		
		shouldTriggerFrame = false;
		lastFrameTriggeredTime = now;
	}
}








void ofxMPEServer::threadedFunction()
{
	while(isThreadRunning()){
		while(paused) {
			ofSleepMillis(10);
		}
		
		
		if(shouldTriggerFrame){
			doTriggerFrame();
		} else {
			
			
			

			checkForDeadConnections();

			processIncomingMessages();
			
			
			

			//if we are still waiting for everyone to be connected check to see if we are all here...
			if(!allconnected){
				numConnectedClients = 0;
				map<int, Connection>::iterator it;				
				for(it = connections.begin(); it != connections.end(); it++){
					Connection& connection = it->second;
					if( !connection.disconnected ){
						numConnectedClients++;
					}
				}
				
				
				//we are all here! trigger the first frame
				if(numConnectedClients == numRequiredClients){
					allconnected = true;
					shouldTriggerFrame = true;
					mustSendRandomSeed = true;
					cout << "All clients connected!" << endl;
					
				}
			}
			//All connected and going, see if we are ready for the next frame
			else {
				triggerFrameIfAllReady();
			}
			
		}
		ofSleepMillis(1);
	}//end while
}


void ofxMPEServer::checkForDeadConnections() {
	map<int, Connection>::iterator it;
	for(it = connections.begin(); it != connections.end(); it++){
		Connection& connection = it->second;
		if(!connection.disconnected && !server.isClientConnected(connection.tcpServerIndex)){
			cout << "LOST CONNECTION TO CLIENT " << connection.id << endl;
			connection.disconnected = true;
		}
	}
}


void ofxMPEServer::processIncomingMessages() {
	for(int i = 0; i < server.getLastID(); i++){
		if(!server.isClientConnected(i)){
			continue;
		}
		
		string response = server.receive(i);
		if(response == ""){
			continue;
		}
		
		
		vector<string> splitResponse = ofSplitString(response, delimiter, true,true);
		if(splitResponse[0].length() != 1){
			ofLogError() << "MostPixelsEver response code is not valid " << splitResponse[0];
			continue;
		}
		//cout << "received a response " << response << endl;
		string messageCode = splitResponse[0];
		if(splitResponse[0] == "S"){
			if(splitResponse.size() < 2){
				ofLogError() << "MostPixelsEver Wrong number of arguments for synchronous connection. Format is S|ID#|Name. Actual Response [" << response << "]";
				continue;
			}
			
			Connection c;
			c.id = ofToInt(splitResponse[1]);
			
			if(allconnected && connections.find(c.id) != connections.end() &&
			   connections[c.id].disconnected &&
			   currentFrame != 0)
			{
				
				reset();
			}
			
			c.name = splitResponse.size() > 2 ? splitResponse[2] : "no-name";
			c.receiveMessages = true;
			c.ready = false;
			c.disconnected = false;
			c.tcpServerIndex = i;
			
			connections[c.id] = c;
			
			printClientStatus();
		}
		
		else if(splitResponse[0] == "T"){
			//TODO: per-client messages
			currentMessage += delimiter + splitResponse[1];
			
		}
		else if(splitResponse[0] == "D"){
			
			
			if(!allconnected){
				continue;
			}
			
			if(splitResponse.size() < 3){
				ofLogError() << "MostPixelsEver Wrong number of arguments for Done. Format is D|ID#|Frame# .  " << response;
				return;
			}
			
			int clientID = ofToInt(splitResponse[1]);
			int frameNumber = ofToInt(splitResponse[2]);
			//					cout << "Received DONE signal from client " << clientID << " client frame num " <<  frameNumber << " server frame num " << currentFrame << endl;
			if(frameNumber == currentFrame){
				//TODO: validate client id
				connections[clientID].ready = true;
			}
		}
	}
}


void ofxMPEServer::triggerFrameIfAllReady() {
	bool allready = true;
	map<int, Connection>::iterator it;
	for(it = connections.begin(); it != connections.end(); it++){
		Connection& connection = it->second;
		if(!connection.ready){
			allready = false;
			break;
		}
	}
	
	//all clients reported in, next frame!
	if(allready){
		//					cout << "All clients Ready!" << endl;
		shouldTriggerFrame = true;
		currentFrame++;
	}
}




























string ofxMPEServer::getClientStatusString() {
	string out = "";
	out += ofToString(numConnectedClients) + " / " + ofToString(numRequiredClients) + " client";
	if(numRequiredClients!=1) out += "s";
	out += " connected.\n";
	
	map<int, Connection>::iterator it;
	for(it = connections.begin(); it != connections.end(); it++){
		string connectedStr = "";
		if(it->second.disconnected) {
			connectedStr = " (disconnected)";
		}
		out += 
		"id: " + ofToString(it->second.id) + " - "
		+ it->second.name + connectedStr+"\n";
	}
	out += "\n";
	out += "Desired FPS: " + ofToString(framerate) + "\n";
	out += "Actual  FPS: " + ofToString(currFrameRateRaw) + "\n";
	out += "Current Frame: " + ofToString(currentFrame);
	return out;
}











void ofxMPEServer::printClientStatus() {
	ofLogNotice() << getClientStatusString();
}

void ofxMPEServer::exit(ofEventArgs& args){
	close();
}



void ofxMPEServer::close()
{
	if(isThreadRunning()){
		
		cout << " closing MPE Server " << endl;
		
		//if(server.isConnected()){
		cout << "shutting down server" << endl;
		server.close();

		
		connections.clear();
		waitForThread(true);
		
	}

}

void ofxMPEServer::setPaused(bool paused) {
	this->paused = paused;
}

bool ofxMPEServer::getPaused() {
	return paused;
}