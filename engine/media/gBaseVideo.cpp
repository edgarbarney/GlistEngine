/*
 * gBaseVideo.cpp
 *
 *  Created on: 10 Apr 2021
 *      Author: FranticDreamer
 */

#include "gBaseVideo.h"

#if defined(WIN32) || defined(LINUX)
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif

gBaseVideo::gBaseVideo() {
	audioVolume = 10; //Preserved for audio
	isLooping = false;
	isPaused = false;
	decoder = new gVideoDecoder;
	fbo = new gFbo;
	//currentFrame.load("engineassets/nullvideo.jpg");
}

gBaseVideo::~gBaseVideo() {
	delete decoder;
	delete fbo;
}

std::string gBaseVideo::getDirName(const std::string& fname) {
     size_t pos = fname.find_last_of("\\/");
     return (std::string::npos == pos)
         ? ""
         : fname.substr(0, pos);
}

std::string gBaseVideo::getFileName(const std::string& fname) {
     size_t pos = fname.find_last_of("\\/");
     return (std::string::npos == pos)
         ? ""
         : fname.substr(pos + 1, fname.size());
}

int gBaseVideo::load(std::string fullPath) {
	videodir = fullPath;
	directory = getDirName(videodir);
	path = getFileName(videodir);

	return decoder->decodeVideo(videodir);
}

int gBaseVideo::loadVideo(std::string fullPath) {
	return load(gGetVideosDir() + fullPath);
}


void gBaseVideo::play(int w, int h) {
	//decoder->decodeVideo(videodir);
	fbo->allocate(w, h, false);
}

void gBaseVideo::stop() {

}

void gBaseVideo::close() {

}

void gBaseVideo::draw(int x, int y) {
	currentframe = decoder->getVideoFrame(5);

	unsigned int texture = -1;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_BGR, currentframe->width, currentframe->height, 0, GL_BGR, GL_UNSIGNED_BYTE, currentframe->data[0]);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexImage2D(GL_TEXTURE_2D, 0, 0, currentframe->width, currentframe->height, 0, GL_BGR, GL_UNSIGNED_BYTE, currentframe->data[0]);

	fbo->bind();

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

	fbo->unbind();

	fbo->draw(x, y);
}

void seekMilisec(int position) {

}

void seekFrame(int position) {

}

int getDuration() {
	return 0;
}

int getPosition() {
	return 0;
}
