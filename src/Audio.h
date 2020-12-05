#ifndef AUDIO_H
#define AUDIO_H

#include <iostream>

extern "C"{
    #include <libavcodec/avcodec.h>
    #include <libavformat/avformat.h>
    #include <libavutil/avutil.h>
    #include <ao/ao.h>
}


class Audio{

    public:

        AVFormatContext *container = 0;
        bool endOfStream;

        Audio();
        void setAudioFile(const char* file);
        void 

};




#endif