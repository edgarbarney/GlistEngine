/*
 * gVideoDecoder.h
 *
 *  Created on: 11 Apr 2021
 *      Author: FranticDreamer
 */

#ifndef MEDIA_GVIDEODECODER_H_
#define MEDIA_GVIDEODECODER_H_

#ifdef __cplusplus
extern "C"
{
	#include <libavcodec/avcodec.h>
	#include <libavutil/imgutils.h>
    #include <libavformat/avformat.h>
    #include <libswscale/swscale.h>
    #include <libswresample/swresample.h>
}
#endif

#include <vector>

#include "gImage.h"

class gVideoDecoder
{
public:
	gVideoDecoder();
	~gVideoDecoder();


	int decodeVideo(std::string filefullpath);
	AVFrame* getVideoFrame(int frame_cnt);
	std::vector <AVFrame*> pFrameVector; // We should contain all frames within RAM for now.

private:
	AVFormatContext	*pFormatCtx;
	AVCodecContext	*pCodecCtx;
	AVCodec			*pCodec;
	AVFrame			*pFrame, *pFrameBGR;
	AVPacket 		*packet;
	uint8_t 		*out_buffer;
	int	videoindex;
	int y_size;
	int ret, got_picture;
	struct SwsContext *img_convert_ctx;
	int frame_cnt;
};

#endif /* MEDIA_gVideoDecoder_H_ */
