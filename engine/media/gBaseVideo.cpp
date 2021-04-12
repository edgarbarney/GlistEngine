/*
 * gBaseVideo.cpp
 *
 *  Created on: 10 Apr 2021
 *      Author: FranticDreamer
 */

#include "gBaseVideo.h"

gBaseVideo::gBaseVideo() {
	audioVolume = 10; //Preserved for audio
	isLooping = false;
	isPaused = false;
	decoder = new gVideoDecoder;
	//currentFrame.load("engineassets/nullvideo.jpg");

}

gBaseVideo::~gBaseVideo() {
	delete decoder;
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
	videoDir = fullPath;
	directory = getDirName(videoDir);
	path = getFileName(videoDir);

	return decoder->decodeVideo(videoDir);
}

int gBaseVideo::loadVideo(std::string fullPath) {
	return load(gGetVideosDir() + fullPath);
}


void gBaseVideo::play() {
	decoder->decodeVideo(videoDir);
}

void gBaseVideo::stop() {

}

void gBaseVideo::close() {

}

void gBaseVideo::draw(int x, int y) {
	currentFrame = *(decoder->getVideoFrame(1));
	currentFrame.draw(x, y);
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
