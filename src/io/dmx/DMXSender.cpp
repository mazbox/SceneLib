/**
 *  DMXSender.cpp
 *
 *  Created by Marek Bereza on 30/05/2014.
 */

#include "DMXSender.h"
#include "DMXManager.h"


DMXSender::DMXSender() {
	DMXManager::getInstance().addSender(this);
}

DMXSender::~DMXSender() {
	DMXManager::getInstance().removeSender(this);
}