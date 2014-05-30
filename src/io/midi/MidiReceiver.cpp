/**
 *  MidiReceiver.cpp
 *
 *  Created by Marek Bereza on 30/05/2014.
 */

#include "MIDIReceiver.h"
#include "MIDIManager.h"

MIDIReceiver::MIDIReceiver() {
	MIDIManager::getInstance().addReceiver(this);
}

MIDIReceiver::~MIDIReceiver() {
	MIDIManager::getInstance().removeReceiver(this);
}