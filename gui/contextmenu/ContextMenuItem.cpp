/**
 *  ContextMenuItem.cpp
 *
 *  Created by Marek Bereza on 08/11/2013.
 */

#include "ContextMenuItem.h"




ContextMenuItem::ContextMenuItem(string name, string command) {
	this->text = name;
	this->command = command;
	enabled = true;
	this->child = NULL;
}

ContextMenuItem::ContextMenuItem(string name, ContextMenuLevel *child) {
	this->text = name;
	this->child = child;
	command = name;
	enabled = true;
}
