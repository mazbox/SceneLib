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
#include "ofxXmlSettings.h"


//--------------------------------------------------------------
class ofxMPEClient : public ofThread {
private:
	ofxMPEClient();
	
  public:
    static ofxMPEClient *getInstance();
	


    //must call this before calling setup and it will work offline
    void  useSimulationMode(int framesPerSecond); //will work offline

    void setup(string clientXmlFile, string computerName);
    //TODO: simple non-xml based setup method
    //void setup(string hostname, int clientId, int port, bool mainThreadOnly = true);

    void  done(); //done drawing

    void  start();
    void  stop();

//    void  draw();

    int   getPort() { return serverPort; }
    int   getID()   { return id; }

    //we need this incase the server launches after the clients
    void setDoesRetry(bool doRetry);


    void setClientName(string name){ clientName = name; }

    int   getFrameCount() { return frameCount; }
    float getFPS()        { return fps; }
    
    bool isConnected();
   

    void  broadcast(string _msg);
    bool  areAllConnected() { return allConnected; }

	string getName() { return clientName; }
	
	bool doesRenderScreen(int uid);
	void getScreenUids(vector<int> &uids);
  protected:
    void setDefaults();

	bool verbose;
	string delimiter;
	
    void draw(ofEventArgs& e);
    void retryConnectionLoop(ofEventArgs& e);

    void threadedFunction();

    void loadIniFile(string _fileString, string computerName);



    void read(string _serverInput);
    void send(string _msg);

    void reset();

    string       serverName;
    int          serverPort;
    ofxTCPClient tcpClient;

    /** The id is used for communication with the server, to let it know which
     *  client is speaking and how to order the screens. */
    int id;
	
    /** The total number of screens. */
    int numClients;
    float lastHeartbeatTime;
    

    string outgoingMessage;


    bool isAttemptingToConnect;
    float lastConnectionAttempt;

    string clientName;

    bool triggerFrame;
    bool shouldReset;


    //simulation mode
    bool simulationMode;
    float lastFrameTime;
    int simulatedFPS;

    int   frameCount;
    float fps;
    long  lastMs;

    /** True if all the other clients are connected. */
    bool allConnected;
	bool connected;
	
    bool bMessageAvailable;

    vector<string> dataMessage;
    float heartbeatInterval;
    float timeOfNextHeartbeat;

    string lastmsg; //used to ignore duplicates
	vector<int> screenUids;
};
