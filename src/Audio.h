#ifndef AUDIO_H
#define AUDIO_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <filesystem>


extern "C"{
    #include <libavcodec/avcodec.h>
    #include <libavformat/avformat.h>
    #include <libavutil/avutil.h>
    #include <ao/ao.h>
}


class Audio{

    private:

        std::thread fileDecode;

        FILE* file;
        size_t f_size;
        AVCodecContext* codecContext;
        AVCodec* codec;
        AVCodecParserContext* parser;

        AVFrame* decoded_frame;
        AVPacket* packet;

        ao_device* outputDevice;
        ao_sample_format outputFormat;

    public:

        Audio();
        ~Audio();
        void setAudioFile(const char* fileName);
        void setAudioDevice();
        void playFrame();
        void decode();
        void play();
        void writeToDevice(char* buf, size_t size);
        void start();
        void stop();

        bool isPlaying;


};




#endif