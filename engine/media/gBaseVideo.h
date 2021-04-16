/*
 * gBaseVideo.h
 *
 *  Created on: 10 Apr 2021
 *      Author: FranticDreamer
 */

#ifndef MEDIA_GBASEVIDEO_H_
#define MEDIA_GBASEVIDEO_H_

#include "gNode.h"
#include "gImage.h"
#include "gFbo.h"
#include "gVideoDecoder.h"

class gBaseVideo: public gNode {
public:
	gBaseVideo();
	~gBaseVideo();
	
	// Should we use boolean or short or even byte???
	int load(std::string fullPath);
	int loadVideo(std::string fullPath);

	void play(int w, int h);
	void stop();
	void close();
	void draw(int x, int y);
	
	// Should we use long int???
	void seekMilisec(int position);
	void seekFrame(int position);
	int getDuration();
	int getPosition();

	// No Setter-Getter. Makes us gain some CPU time
	float audioVolume; //Preserved for audio
	bool isLooping;
	bool isPaused;
	AVFrame* currentframe; // Feed to gImage TEMPORARILY!!!

private:
	std::string getDirName(const std::string& fname);
	std::string getFileName(const std::string& fname);

	std::string videodir, directory, path; // We'll work with videodir, mostly.
	std::string codec, extension;
	gVideoDecoder* decoder;
	gFbo* fbo;
};

#endif /* MEDIA_gBaseVideo_H_ */
