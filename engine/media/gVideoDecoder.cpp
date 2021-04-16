/*
 * gVideoDecoder.cpp
 *
 *  Created on: 11 Apr 2021
 *      Author: FranticDreamer
 */

#include "gVideoDecoder.h"
#include "gUtils.h"

#include "stb/stb_image.h"

gVideoDecoder::gVideoDecoder() {
	videoindex = 0;
	y_size = 0;
	ret, got_picture = 0;
	frame_cnt = 0;
}

gVideoDecoder::~gVideoDecoder() {
	// Free Memory
	for (auto &attack : pFrameVector)
	{
		delete attack;
	}
	av_packet_unref(packet);
	sws_freeContext(img_convert_ctx);
	av_frame_free(&pFrameBGR);
	av_frame_free(&pFrame);
	avcodec_close(pCodecCtx);
	avformat_close_input(&pFormatCtx);
}

int gVideoDecoder::decodeVideo(std::string filefullpath) {
	//FFmpeg libraries mostly work with C strings.
	//So, we use this as a small -but big in long term- impact on performance.
	const char *filepath = filefullpath.c_str();

	// Open the network video stream
	avformat_network_init();
	// Initialize AVFormatContext, or initialize with NULL
	pFormatCtx = avformat_alloc_context();

	// Open the input data stream
	if (avformat_open_input(&pFormatCtx, filepath, NULL, NULL) != 0)
	{
		gLogi("gVideo") << "Can't open input stream." << std::endl;
		return -1;
	}
	// Get data flow information
	if (avformat_find_stream_info(pFormatCtx, NULL) < 0)
	{
		gLogi("gVideo") << "Can't find stram information." << std::endl;
		return -1;
	}
	// Find the video stream part of the input stream
	videoindex = -1 ;
	for (int i = 0; i < pFormatCtx->nb_streams; i++)
	{
		if (pFormatCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
		{
			videoindex = i;
			break;
		}
	}
	if (videoindex == -1)
	{
		gLogi("gVideo") << "Can't find a video stream." << std::endl;
		avformat_close_input(&pFormatCtx);
		return -1;
	}
	// Look for a decoder
	pCodecCtx = pFormatCtx->streams[videoindex]->codec;
	//avcodec_parameters_to_context(pCodecCtx, pFormatCtx->streams[videoindex]->codecpar);
	pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
	if (pCodec == NULL)
	{
		gLogi("gVideo") << "Can't find Codec." << std::endl;
		avformat_close_input(&pFormatCtx);
		return -1;
	}
	// Open the decoder
	if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0)
	{
		gLogi("gVideo") << "Can't open the selected Codec." << std::endl;
		return -1;
	}

	gLogi("gVideo") << "Time of this video: " << pFormatCtx->duration << " us." << std::endl;

	// Allocate space to save frame data
	pFrame = av_frame_alloc ();
	pFrameBGR = av_frame_alloc ();

	// Set image size
	int size = av_image_get_buffer_size (AV_PIX_FMT_BGR24, pCodecCtx->width, pCodecCtx->height, 1);
	out_buffer = (uint8_t *)av_malloc(size);
	av_image_fill_arrays (pFrameBGR->data, pFrameBGR->linesize, out_buffer, AV_PIX_FMT_BGR24, pCodecCtx->width, pCodecCtx->height, 1);
	packet = (AVPacket *)av_malloc(sizeof(AVPacket));

	// Format conversion
	img_convert_ctx = sws_getContext(pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt,
		pCodecCtx->width, pCodecCtx->height, AV_PIX_FMT_BGR24, SWS_BICUBIC, NULL, NULL, NULL);

	while (av_read_frame(pFormatCtx, packet) >= 0) {
			if (packet->stream_index == videoindex) {
				// Decoding
				ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture, packet);
				if (ret < 0) {
					std::cout << "Decode Error." << std::endl;
					return -1;
				}
				if (got_picture) {
					sws_scale(img_convert_ctx, (const uint8_t* const*)pFrame->data, pFrame->linesize, 0, pCodecCtx->height,
						pFrameBGR->data, pFrameBGR->linesize);

					std::cout << "Decode frame index: " << frame_cnt << std::endl;
					frame_cnt++;

					// Display image
					pFrameVector.push_back(pFrameBGR);
				}
			}
			av_free_packet (packet);
		}
		sws_freeContext(img_convert_ctx);
		av_frame_free(&pFrameBGR);
		av_frame_free(&pFrame);
		avcodec_close(pCodecCtx);
		avformat_close_input(&pFormatCtx);
	gLogi("gVideo") << "Done saving frames" << std::endl;
	return 0;
}

AVFrame* gVideoDecoder::getVideoFrame(int frame_cnt){
	return pFrameVector.at(frame_cnt);
}
