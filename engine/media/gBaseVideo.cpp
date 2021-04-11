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
}

gBaseVideo::~gBaseVideo() {
}

int gBaseVideo::load(std::string fullPath) {
	return 0;
}

void gBaseVideo::play(){

}

void gBaseVideo::stop(){

}

void gBaseVideo::close(){

}

void seekMilisec(int position){

}

void seekFrame(int position){

}

int getDuration(){
	return 0;
}

int getPosition(){
	return 0;
}
