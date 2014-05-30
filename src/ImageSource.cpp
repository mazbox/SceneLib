/**
 *  ImageSource.cpp
 *
 *  Created by Marek Bereza on 30/05/2014.
 */

#include "ImageSource.h"


ofTexture &ImageSource::getTexture() {
	if(lastFrameRendered!=ofGetFrameNum()) {
		render();
	}
	return getTextureReference();
}

ImageSource::ImageSource() {
	lastFrameRendered = -1;
}