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
 *  Description: 
 *				 
 *  Frameset.h, created by Marek Bereza on 11/03/2014.
 */

#pragma once

#include "Frame.h"

class Frameset: public Frame {
public:
	class Selection {
	public:
		ofRectangle *rect;
		enum SelectionType {
			LEFT,
			RIGHT,
			TOP,
			BOTTOM
		};
		
		SelectionType type;
		Selection(ofRectangle &rect, SelectionType type) {
			this->rect = &rect;
			this->type = type;
		}
		void draw() {
		}
		
	};
	
	
	void setup(float x, float y, float width, float height);
	
	bool mouseMoved(ofMouseEventArgs &m);
	bool mousePressed(ofMouseEventArgs &m);
	bool mouseDragged(ofMouseEventArgs &m);
	bool mouseReleased(ofMouseEventArgs &m);

	
	vector<Selection> selections;
	void draw();
	
	
};

