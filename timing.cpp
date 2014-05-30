/**
 *  timing.cpp
 *
 *  Created by Marek Bereza on 01/11/2013.
 */

#include "timing.h"
namespace scene {
	namespace timing {
		int frameNo = 0;
		float fps = 30.f;
		void setFrame(int frame) {
			frameNo = frame;
		}
		float getElapsedTime() {
			return frameNo/fps;
		}
	};
};