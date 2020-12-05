#include "Audio.h"


Audio::Audio()
{
}

void Audio::setAudioFile(const char* file)
{
    if(avformat_open_input(&container, file, NULL, NULL) < 0)
    {
        std::cout << "Could not open: " << file << "\n";
        exit(1);
    }

    if(avformat_find_stream_info(container, NULL) < 0)
    {
        std::cout << "Could not find file info: " << file << "\n";
        exit(1);
    }
}