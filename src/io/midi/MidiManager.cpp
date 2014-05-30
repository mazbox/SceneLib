/**
 *  MidiManager.cpp
 *
 *  Created by Marek Bereza on 30/05/2014.
 */

#include "MidiManager.h"



MIDIManager &MIDIManager::getInstance() {
	MIDIManager *instance = NULL;
	if(instance==NULL) {
		instance = new MIDIManager();
	}
	return *instance;
}


MIDIManager::MIDIManager() {
	midiIn.listPorts();
	midiIn.openPort();
	midiIn.addListener(this);
}





void MIDIManager::newMidiMessage(ofxMidiMessage& msg) {
	for(int i = 0; i < receivers.size(); i++) {
		receivers[i]->newMidiMessage(msg);
	}
}

void MIDIManager::addReceiver(MIDIReceiver *receiver) {
	receivers.push_back(receiver);
}

void MIDIManager::removeReceiver(MIDIReceiver *receiver) {
	for(int i = 0; i < receivers.size(); i++) {
		if(receivers[i]==receiver) {
			receivers.erase(receivers.begin()+i);
		}
	}
	ofLogError() << "Error: can't erase receiver because it's not there!!";
}


