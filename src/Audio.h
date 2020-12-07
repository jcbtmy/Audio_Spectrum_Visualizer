#ifndef AUDIO_H
#define AUDIO_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <filesystem>
#include <fftw3.h>

extern "C"{
    #include <libavcodec/avcodec.h>
    #include <libavformat/avformat.h>
    #include <libavutil/avutil.h>
    #include <ao/ao.h>
}


class Audio{

    private:

        double *frequencies;
        bool updated;

        fftw_plan plan;
        fftw_complex *in, *out;
        bool planSet;

        std::thread fileDecode;
        std::thread fftwExec;

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
        void createPlan(size_t alloc_size);
        void updateFrequencies(size_t N);
        double* getFrequencies();
        float applyWindow(uint16_t input, int tite, size_t N);

        bool isPlaying;


};




#endif