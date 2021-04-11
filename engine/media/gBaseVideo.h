/*
 * gBaseVideo.h
 *
 *  Created on: 10 Apr 2021
 *      Author: FranticDreamer
 */

#ifndef MEDIA_GBASEVIDEO_H_
#define MEDIA_GBASEVIDEO_H_

#include "gNode.h"
#include "gVideoDecoder.h"

class gBaseVideo: public gNode {
public:
	gBaseVideo();
	~gBaseVideo();

	int load(std::string fullPath); // Should we use boolean???
	
	void play();
	void stop();
	void close();
	
	void seekMilisec(int position);
	void seekFrame(int position);  // Should we use long int???
	int getDuration();
	int getPosition();

	float audioVolume; //Preserved for audio
	bool isLooping;
	bool isPaused;

private:

};

#endif /* MEDIA_gBaseVideo_H_ */
