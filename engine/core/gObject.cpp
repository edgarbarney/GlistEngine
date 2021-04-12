/*
 * gObject.cpp
 *
 *  Created on: May 16, 2020
 *      Author: noyan
 */

#include "gObject.h"
#include <unistd.h>

const int gObject::LOGLEVEL_SILENT = 0;
const int gObject::LOGLEVEL_INFO = 1;
const int gObject::LOGLEVEL_DEBUG = 2;
const int gObject::LOGLEVEL_WARNING = 3;
const int gObject::LOGLEVEL_ERROR = 4;

std::string gObject::exepath;

int gObject::renderpassnum = 1;
int gObject::renderpassno = 0;


gObject::gObject() {
	char temp[256];
	exepath = getcwd(temp, sizeof(temp));
	exepath += "/";
	for (int i = 0; i < exepath.size(); i++) {
	    if (exepath[i] == '\\') {
	    	exepath[i] = '/';
	    }
	}
//	std::replace(0, 1, "", "");
}

gObject::~gObject() {
}

std::string gObject::gGetAppDir() {
	return exepath;
}

std::string gObject::gGetAssetsDir() {
	return exepath + "assets/";
}

std::string gObject::gGetFilesDir() {
	return exepath + "assets/files/";
}

std::string gObject::gGetImagesDir() {
	return exepath + "assets/images/";
}

std::string gObject::gGetVideosDir() {
	return exepath + "assets/videos/";
}

std::string gObject::gGetFontsDir() {
	return exepath + "assets/fonts/";
}

std::string gObject::gGetModelsDir() {
	return exepath + "assets/models/";
}

std::string gObject::gGetTexturesDir() {
	return exepath + "assets/textures/";
}

std::string gObject::gGetShadersDir() {
	return exepath + "assets/shaders/";
}

std::string gObject::gGetSoundsDir() {
	return exepath + "assets/sounds/";
}


void gObject::logi(std::string tag, std::string message) {
	if(!gIsLoggingEnabled()) return;
	gLogi(tag) << message;
}

void gObject::logi(std::string message) {
	if(!gIsLoggingEnabled()) return;
	gLogi(abi::__cxa_demangle(typeid(*this).name(), 0, 0, 0)) << message;
}

void gObject::logd(std::string tag, std::string message) {
	if(!gIsLoggingEnabled()) return;
	gLogd(tag) << message;
}

void gObject::logd(std::string message) {
	if(!gIsLoggingEnabled()) return;
	gLogd(abi::__cxa_demangle(typeid(*this).name(), 0, 0, 0)) << message;
}

void gObject::logw(std::string tag, std::string message) {
	if(!gIsLoggingEnabled()) return;
	gLogw(tag) << message;
}

void gObject::logw(std::string message) {
	if(!gIsLoggingEnabled()) return;
	gLogw(abi::__cxa_demangle(typeid(*this).name(), 0, 0, 0)) << message;
}

void gObject::loge(std::string tag, std::string message) {
	if(!gIsLoggingEnabled()) return;
	gLoge(tag) << message;
}

void gObject::loge(std::string message) {
	if(!gIsLoggingEnabled()) return;
	gLoge(abi::__cxa_demangle(typeid(*this).name(), 0, 0, 0)) << message;
}

