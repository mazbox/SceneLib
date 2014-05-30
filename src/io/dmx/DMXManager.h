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
 *  Description: Do not use this class directly - subclass the DMXSender class
 *				 
 *  DMXManager.h, created by Marek Bereza on 30/05/2014.
 */

#pragma once
#include "ofMain.h"
#include "ofxDmx.h"
#include "DMXSender.h"


#define NUM_DMX_CHANNELS 128

class DMXManager {
public:
	static DMXManager &getInstance();

	void addSender(DMXSender *sender);
	void removeSender(DMXSender *sender);
private:
	
	
	DMXManager();
	
	vector<DMXSender*> senders;
	
	
	ofxDmx dmx;
	void update(ofEventArgs &e);
};
