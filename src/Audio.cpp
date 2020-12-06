#include "Audio.h"


Audio::Audio()
{
    packet = av_packet_alloc();
    decoded_frame = av_frame_alloc();

    ao_initialize();


    codec = avcodec_find_decoder(AV_CODEC_ID_MP2);
    if(!codec)
    {
        std::cout << "Decoder not found\n";
        exit(0);
    }

    parser = av_parser_init(codec->id);
    if(!parser)
    {
        std::cout << "Parser not found\n";
        exit(0);
    }

    codecContext = avcodec_alloc_context3(codec);
    if(avcodec_open2(codecContext, codec, NULL ) < 0)
    {
        std::cout << "Cannot open Codec\n";
        exit(0);
    }

}

void Audio::setAudioFile(const char* fileName)
{

    f_size = std::filesystem::file_size(fileName);

    file = fopen(fileName, "rb");

    if(!file)
    {
        std::cout << "Could not open " << fileName << "\n";
        exit(0);
    }

}

void Audio::setAudioDevice()
{
    outputFormat.bits = 16;
    outputFormat.channels = 2;
    outputFormat.rate= 44100;
    outputFormat.byte_format = AO_FMT_NATIVE;
    outputFormat.matrix = 0;

    int driver = ao_default_driver_id();
    outputDevice = ao_open_live(driver, &outputFormat, NULL);

    isPlaying = true;
}

void Audio::start()
{
    fileDecode = std::thread(&Audio::play, this);
}

void Audio::stop()
{
    isPlaying = false;
    if(fileDecode.joinable())
        fileDecode.join();
}

void Audio::play()
{
    int ret;
    uint8_t *data;
    size_t size;  
    uint8_t* buffer  = (uint8_t*)malloc(sizeof(char)*f_size);

    data = buffer;

    if((size = fread(data, 1, f_size, file)) < 0){
        isPlaying = false;
        return;
    }
    
    while(size > 0){
        ret = av_parser_parse2(parser, codecContext, 
                            &packet->data, &packet->size,
                            data, size,
                            AV_NOPTS_VALUE,
                            AV_NOPTS_VALUE, 0 );
        data += ret;           
        size -= ret;
        if(packet->size)
            this->decode();
    }
    free(buffer);
}

Audio::~Audio()
{

    fclose(file);
    avcodec_free_context(&codecContext);    
    av_parser_close(parser);
    av_frame_free(&decoded_frame);
    av_packet_free(&packet);

    ao_close(outputDevice);
    ao_shutdown();
}

void Audio::decode()
{
    int16_t *buf;
    int ret, i;
    int size;

    ret = avcodec_send_packet(codecContext, packet);

    if( ret < 0)
    {
        //std::cout << "Error decoding packet\n";
    }

    while(ret >= 0 && isPlaying)
    {
        ret = avcodec_receive_frame(codecContext, decoded_frame);
        if(ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
            return;

        size = sizeof(*buf) * 2  * decoded_frame->nb_samples;
        buf = (int16_t*)av_malloc(size);
        for (i = 0; i < decoded_frame->nb_samples; i++) {
            buf[2 * i]     = ((int16_t*)decoded_frame->data[0])[i];
            buf[2 * i + 1] = ((int16_t*)decoded_frame->data[1])[i];
        }

        this->writeToDevice((char*)&buf[0], size);
        av_freep(&buf);
    }
}

void Audio::writeToDevice(char* buf, size_t size)
{
    ao_play(outputDevice, buf, size);
}