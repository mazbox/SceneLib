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

#pragma once

#include "ofMain.h"
#include "ofxNetwork.h"


typedef struct
{
	string name;
	int id;
	int tcpServerIndex;
	bool asynchronous;
	bool receiveMessages;
	bool ready;
	bool disconnected;
} Connection;

class ofxMPEServer : public ofThread
{
  public:
	ofxMPEServer();


	void setup(string setupFile);
	void setup(int framerate = 30,
			   int port = 9001,
			   int numClients = 1,
			   bool verbose = false);
	
	void reset(); //sends a reset signal to all clients and reset frame count
	void close();
	void printClientStatus();
	string getClientStatusString();
	void exit(ofEventArgs& args);
	float getCurrFrameRate() {
		return currFrameRate;
	}
	
	
	float getCurrFrameRateRaw() {
		return currFrameRateRaw;
	}
	void setPaused(bool paused);
	bool getPaused();
	
	
  protected:
	bool paused;
	void doTriggerFrame();
	void processIncomingMessages();
	void checkForDeadConnections();
	void triggerFrameIfAllReady();
	
	
	ofxTCPServer server;
	void threadedFunction();
	
	string delimiter;
	float lastFrameTriggeredTime;
	bool shouldWaitForAllClients;
	bool allconnected;

	int framerate;

	int numConnectedClients;
	int numRequiredClients;
	
	int currentFrame;
	bool shouldTriggerFrame;
	bool verbose;

	map<int, Connection> connections;
	bool newMessage;
	string currentMessage;
	float timeOfNextHeartbeat;
	
	float heartBeatInterval;

	float currFrameRate;
	float currFrameRateRaw;
	bool mustSendRandomSeed;
	
};
