#include "Audio.h"


Audio::Audio()
{
    //allocate packets, framse, find decoders, etc
    packet = av_packet_alloc();
    decoded_frame = av_frame_alloc();

    ao_initialize();


    codec = avcodec_find_decoder(AV_CODEC_ID_MP2);
    if(!codec)
    {
        std::cout << "Decoder not found\n";
        exit(EXIT_FAILURE);
    }

    parser = av_parser_init(codec->id);
    if(!parser)
    {
        std::cout << "Parser not found\n";
        exit(EXIT_FAILURE);
    }

    codecContext = avcodec_alloc_context3(codec);
    if(avcodec_open2(codecContext, codec, NULL ) < 0)
    {
        std::cout << "Cannot open Codec\n";
        exit(EXIT_FAILURE);
    }
    planSet = false;
    
}

Audio::~Audio()
{
    //cleanup
    delete[] frequencies;
    fftw_destroy_plan(plan);
    fftw_free(in);
    fftw_free(out);

    fclose(file);
    avcodec_free_context(&codecContext);    
    av_parser_close(parser);
    av_frame_free(&decoded_frame);
    av_packet_free(&packet);

    ao_close(outputDevice);
    ao_shutdown();
}

void Audio::setAudioFile(const char* fileName)
{

    //check if audio file is there, if so, how big is it

    file = fopen(fileName, "rb");
    if(!file)
    {
        std::cout << "Could not open " << fileName << "\n";
        exit(EXIT_FAILURE);
    }
    if(fseek(file, 0, SEEK_END) < 0)
    {
        std::cout << "Could not seek file end\n";
        exit(EXIT_FAILURE);
    }
    if((f_size = ftell(file)) < 0)
    {
        std::cout << "Failed to tell\n";
        exit(EXIT_FAILURE);
    }
    fseek(file, 0, SEEK_SET);

}

void Audio::setAudioDevice()
{
    //setup output device format and 
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
        free(buffer);
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



void Audio::decode()
{
    const int REAL = 0;
    const int IMAG = 1;
    int16_t *buf;
    int ret, i;
    int size, N = 0;

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


        N = decoded_frame->nb_samples;
        size = sizeof(*buf) * 2  * N ;
        buf = (int16_t*)av_malloc(size);

        if(!planSet)
        {
            this->createPlan(N);
        }

        for (i = 0 ; i < N; i++) {  
            
            uint16_t  left = ((int16_t*)decoded_frame->data[0])[i];
        
            in[i][REAL] = this->applyWindow(left, i, N);
            in[i][IMAG] = 0;

            buf[2 * i]     = ((int16_t*)decoded_frame->data[0])[i];
            buf[2 * i + 1] = ((int16_t*)decoded_frame->data[1])[i];
        }
        this->updateFrequencies(N);
        this->writeToDevice((char*)&buf[0], size);
        av_freep(&buf);
    }
}

void Audio::writeToDevice(char* buf, size_t size)
{
    ao_play(outputDevice, buf, size);
}

void Audio::createPlan(size_t alloc_size)
{
    in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * alloc_size);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * alloc_size);
    plan = fftw_plan_dft_1d(decoded_frame->nb_samples,in, out,FFTW_FORWARD, FFTW_ESTIMATE);
    planSet = true;
}


float* Audio::getFrequencies()
{
    if(updated)
    {
        updated = false;
        return frequencies;
    }
    return nullptr;
}

void Audio::updateFrequencies(size_t N)
{

   if(N == 0)
        return;

   double imag, real, magnitude, max = 0.0;
   int step = (int)ceil(((float)(N /2 )/ (float)bin_size));

   fftw_execute (plan);
   

   for(int i = 0, k = 0; i < (N / 2); i++)
   {    
        real = out[i][0];
        imag  = out[i][1];
        magnitude = sqrt((imag * imag)+(real * real));
        max = (magnitude > max) ? magnitude : max;
        
        if(i != 0 && i % step == 0 )
        {
            frequencies[k] = (max > 50.0f) ? 1.0f : (float)(max)/50.0f;
            k++;
            max = 0.0;
        }
        
   }

   updated = true;
   return;
}

float Audio::applyWindow(uint16_t input, int tite, size_t N)
{
    
    double window_modifier = (0.5 * (1 - cos(2 * M_PI * tite / (N - 1))));
    double value = (double) window_modifier * ((input)/32768.0f);

    if(value > 1.0)
    {
        value = 1.0;
    }
    else if(value < -1.0)
    {
        value = -1.0;
    }

    return value;
}

void Audio::setBinSize(int size)
{
    bin_size = size;
    frequencies = new float[size];
}