/**
 *  DMXManager.cpp
 *
 *  Created by Marek Bereza on 30/05/2014.
 */

#include "DMXManager.h"


DMXManager &DMXManager::getInstance() {
	DMXManager *instance = NULL;
	if(instance==NULL) {
		instance = new DMXManager();
	}
	return *instance;
}


DMXManager::DMXManager() {
	dmx.connect(0, NUM_DMX_CHANNELS);
	ofAddListener(ofEvents().update, this, &DMXManager::update);
}


void DMXManager::addSender(DMXSender *sender) {
	senders.push_back(sender);
}


void DMXManager::removeSender(DMXSender *sender) {
	for(int i = 0; i < senders.size(); i++) {
		if(senders[i]==sender) {
			senders.erase(senders.begin() + i);
			return;
		}
	}
	ofLogError() << "Can't find the sender to delete";

}



void  DMXManager::update(ofEventArgs &e) {
	for(int i = 0; i < senders.size(); i++) {
		
	}
}