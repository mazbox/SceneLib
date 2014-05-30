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

#include "ofxMPEClient.h"
#include "ofxMPEEvents.h"

//--------------------------------------------------------------
ofxMPEClient::ofxMPEClient() {
    setDefaults();
}

//--------------------------------------------------------------
void ofxMPEClient::setDefaults(){
	verbose = true;

	delimiter = "|";
	
	id = 0;

	
	triggerFrame = false;
	
	lastConnectionAttempt = 0;
	isAttemptingToConnect = false;
	simulationMode = false;
	
	frameCount = 0;
	fps        = 0.0f;
	lastMs     = 0;
	connected = false;
	
	allConnected = false;
	lastHeartbeatTime = 0.0;
	
	outgoingMessage = "";
	
	lastmsg = "";
	
	clientName = "noname";
}

//--------------------------------------------------------------
void ofxMPEClient::setup(string _fileString, string computerName) {


    fps = 0;
    loadIniFile(_fileString, computerName);
    frameCount = 0;
    shouldReset = false;
    heartbeatInterval = 0;
    timeOfNextHeartbeat = ofGetElapsedTimef();
}


//--------------------------------------------------------------
void ofxMPEClient::useSimulationMode(int framesPerSecond) {
    simulatedFPS = framesPerSecond;
    simulationMode = true;
    lastFrameTime = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void ofxMPEClient::start() {

    ofAddListener(ofEvents().draw, this, &ofxMPEClient::draw);

    if (!simulationMode && !tcpClient.setup(serverName, serverPort)) {
        ofLogError("MPE") << "TCP failed to connect to port " << ofToString(serverPort);
        lastConnectionAttempt = ofGetElapsedTimef();
        ofAddListener(ofEvents().update, this, &ofxMPEClient::retryConnectionLoop);

    }
    else{
		connected = true;
        startThread(true, false);  // blocking, verbose
        ofLogNotice() << "TCP connection bound on port " << ofToString(serverPort);
    }
}

//--------------------------------------------------------------
void ofxMPEClient::retryConnectionLoop(ofEventArgs& e)
{
    float now = ofGetElapsedTimef();
    if(now - lastConnectionAttempt > 1.0){ //retry every second
        if(tcpClient.setup(serverName, serverPort)) {
			ofLogNotice("MPE") << "Managed to connect!";
			connected = true;
            ofRemoveListener(ofEvents().update, this, &ofxMPEClient::retryConnectionLoop);
            startThread(true, false);  // blocking, verbose
        } else {
			ofLogNotice("MPE") << "Couldn't connect, will retry in 1 second";
		}
        lastConnectionAttempt = now;
    }
}
bool isNumeric(string a) {
	if(a.size()==0) return false;
	for(int i = 0; i < a.size(); i++) {
		if(a[i]<'0' || a[i]>'9') return false;
	}
	return true;
}

//--------------------------------------------------------------
void ofxMPEClient::draw(ofEventArgs& e)
{

	lock();

	for(int i = 0; i < dataMessage.size(); i++){
		ofxMPEEventArgs e;
		e.message = dataMessage[i];
		e.frame = getFrameCount();
		if(!isNumeric(e.message)) {
			printf("GOT MESSAGE: %s\n", e.message.c_str());
			if(e.message.find("T|random: ")==-1) {
				ofNotifyEvent(ofxMPEEvents.mpeMessage, e);
			} else {
				printf("GOT RANDOM SEED!!\n");
				ofSeedRandom(ofToInt(e.message.substr(10)));
			}
		}
	}
	dataMessage.clear();
	
	
	if(shouldReset){
		reset();
	}
	unlock();
	
	while(connected && !triggerFrame) {
		ofSleepMillis(1);
	}

	if(triggerFrame){
		triggerFrame = false;
		
		ofxMPEEventArgs e;
		e.message = "";
		e.frame = frameCount;
		ofBackground(0,0,0);
		if(connected) ofNotifyEvent(ofxMPEEvents.mpeFrame, e);

	
		done();
	}
}

//--------------------------------------------------------------
// Loads the settings from the Client XML file.
//--------------------------------------------------------------
void ofxMPEClient::loadIniFile(string _fileString, string computerName) {
    ofLogNotice("MPE") << "Loading settings from file " <<  _fileString;
    
    ofxXmlSettings xmlReader;
    if (!xmlReader.loadFile(_fileString)){
        ofLogError("MPE") << "ERROR loading XML file!";
        return;
    }
	
	
	clientName = computerName;
	serverName = xmlReader.getAttribute("clients", "server", "127.0.0.1", 0);
	serverPort = xmlReader.getAttribute("clients", "port", 9001);
	
	xmlReader.pushTag("clients");
	
	screenUids.clear();
	numClients = xmlReader.getNumTags("client");
	for(int i = 0; i < numClients; i++) {
		if(xmlReader.getAttribute("client", "host", "", i)==computerName) {
			id = xmlReader.getAttribute("client", "id", 0, i);
			xmlReader.pushTag("client", i);
			int numScreens = xmlReader.getNumTags("screen");
			printf("This client had %d screens\n", numScreens);
			for(int j = 0; j < numScreens; j++) {
				screenUids.push_back(xmlReader.getAttribute("screen", "uid", 0, j));
			}
			
			break;
		}
	}
 
	ofLogNotice("MPE") << "SERVER IS " << serverName << "  PORT is " << serverPort;
}


//--------------------------------------------------------------
bool ofxMPEClient::isConnected()
{
    return tcpClient.isConnected();
}



void ofxMPEClient::getScreenUids(vector<int> &uids) {
	//set<int>::iterator it;
	//for(it = screenUids.begin(); it != screenUids.end(); it++) {
	for(int i = 0; i < screenUids.size(); i++) {
		uids.push_back(screenUids[i]);
	}
}
//--------------------------------------------------------------
void ofxMPEClient::threadedFunction() {
    

    

	// let the server know that this client is ready to start
	send("S" + delimiter + ofToString(id) + delimiter + clientName);

    

    while(isThreadRunning()) {

        if(simulationMode){
            
            float now = ofGetElapsedTimef();
            if(now - lastFrameTime > 1./simulatedFPS){
				triggerFrame = true;
                lastFrameTime = now;
            }

            ofSleepMillis(5);
            continue;
        }


        if(!tcpClient.isConnected()){
            //we lost connection, start the retry loop and kill the thread
            lastConnectionAttempt = ofGetElapsedTimef();
            ofAddListener(ofEvents().update, this, &ofxMPEClient::retryConnectionLoop);
            // waitForThread(true);

			shouldReset = true;
           

			ofLogError("MPE") << "lost connection to server";
            connected = false;
			
            //break the loop because we'll need to restart
            return;
        }

        if (lock()) {
            string msg = tcpClient.receive();
            if (msg.length() > 0 && lastmsg != msg) {
                read(msg);
                lastmsg = msg;
            }
			unlock();
        }
        ofSleepMillis(1);
    }
}

//--------------------------------------------------------------
// Reads and parses a message from the server.
//--------------------------------------------------------------
void ofxMPEClient::read(string _serverInput) {
  //  ofLogNotice("MPE") << "Receiving: " << _serverInput;

    char c = _serverInput.at(0);
    if(c == 'R'){
        if(frameCount != 0){
            //we received a reset signal
			shouldReset = true;
           
            ofLogNotice("MPE") << "Received frame reset";
        }
    }
    else if (c == 'G') {
        if (!allConnected) {
            ofLogNotice() << "all clients connected!";
            allConnected = true;
        }
        
        lastHeartbeatTime = ofGetElapsedTimef();
        
        // split into frame message and data message
        vector<string> info = ofSplitString(_serverInput, delimiter);
        int fc = ofToInt( info[1] );
		//ofLogNotice() << "frameCount is " << fc << " and our current frame is " << frameCount;
        if (fc == frameCount) {
            
            // calculate new framerate
            float nowms = ofGetElapsedTimeMillis();
            float ms = nowms - lastMs;
            fps += ((1000.f / ms) - fps)*.2;
            lastMs = nowms;
            
			//cout << "trigger frame " << frameCount << endl;
			triggerFrame = true;
        }

         //JG switched to after done event
        if (info.size() > 1) {
            // there is a message here with the frame event
            info.erase(info.begin());

            for(int i = 0; i < info.size(); i++){
				dataMessage.push_back( info[i] );
			}
        }
    }
}

void ofxMPEClient::reset() {
    ofxMPEEventArgs e;
    e.message = "reset";
    e.frame = frameCount;
    ofNotifyEvent(ofxMPEEvents.mpeReset, e);
    allConnected = false;
    
    shouldReset = false;
    frameCount = 0;
}


//--------------------------------------------------------------
// Send a message to the server.
//--------------------------------------------------------------
void ofxMPEClient::send(string _msg) {

    //_msg += "\n";
    if(!simulationMode){
     //   ofLogNotice() << "Sending: " << _msg;
        tcpClient.send(_msg);
    }
}

//--------------------------------------------------------------
// Format a broadcast message and send it.
// Do not use a colon ':' in your message!!!
//--------------------------------------------------------------
void ofxMPEClient::broadcast(string _msg) {
    if(!simulationMode){

        outgoingMessage += delimiter + _msg;
       // cout << "outgoing message is now " << outgoingMessage << endl;
		
    }
}

//--------------------------------------------------------------
// Sends a "Done" command to the server. This must be called at
// the end of the draw loop.
//--------------------------------------------------------------
//TODO: if done has already been called, dont call it again
void ofxMPEClient::done() {
	if(!simulationMode) {
		string msg = "D" + delimiter + ofToString(id) + delimiter + ofToString(frameCount);
		send(msg);
		if(outgoingMessage!="") {
			send("T" + outgoingMessage);
			//printf("T%s\n", outgoingMessage.c_str());
			outgoingMessage = "";
		}
	}
	frameCount++;
}

//--------------------------------------------------------------
// Stops the client thread.  You don't really need to do this ever.
//--------------------------------------------------------------
void ofxMPEClient::stop() {
    stopThread();
	ofRemoveListener(ofEvents().draw, this, &ofxMPEClient::draw);
    
}

bool ofxMPEClient::doesRenderScreen(int uid) {
	if(simulationMode) {
		if(screenUids.size()==0) {
			ofLogNotice() << "ofxMPEClient running in simulation mode. Simulating using screen uid " << uid;
			screenUids.push_back(uid);
		}
	}
	for(int i = 0; i < screenUids.size(); i++) {
		if(screenUids[i]==uid) return true;
	}
	return false;	
}




ofxMPEClient *ofxMPEClient::getInstance() {
	static ofxMPEClient *instance = NULL;
	if(instance==NULL) {
		instance = new ofxMPEClient();
	}
	return instance;
}