/**
 * @file StereoToMono.c
 * @author Sotiris Rafail Meletiou AM941797
 * @author Michalis Fykiris AK767066
 * @brief convert stereo wavs to mono 
 * @version 4
 * 
 * @copyright Copyright (C) 1992-1993 Jean-loup Gailly
* This is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public
* License, see the file COPYING
 * 
 */
#include "FunctionsDecler.h"
#include "helpFuncDec.h"

void StereoToMono(int fileNum, char *argv[])
{
    static int f = 2;//index for file (starts from 2 cuz 0 
                     //is the name of the exe and 1 the function name)

    while(checkExtension(f,argv)==0){
        if(fileNum!=1){
        f++;
       --fileNum;
      }else if(fileNum==1)
        exit(EXIT_FAILURE);
    }

    FILE *wav = fopen(argv[f], "rb");
    checkFile(wav,argv,f);

    //Read Header
    Header header=readHead(header,wav);

    isPCM(header.fmt.subchunk1_size,header.fmt.audio_format,argv,f);

    header.fmt.num_channels = 1; //change number of channels from stereo to mono
    header.data.subchunk2_size /= 2;//halves size cuz we remove the entire right channel 
    header.riff.chunk_size = header.data.subchunk2_size + 36;//changes to the new chunk size
    header.fmt.byte_rate /= 2; //halves the byte rate
    header.fmt.block_align /= 2; //halves the blocks 

    //create name for new file
    printf("Creating new file...\n");
    char *name = malloc(6 + strlen(argv[f]));
    strcpy(name, "mono-");
    strcat(name, argv[f]);
    
    FILE *new = fopen(name, "wb");
    checkFile(new,NULL,-1);

    fwrite(&header, sizeof(Header), 1, new);//writes the new header to the new wav file

    printf("Converting %s to Mono...\n",argv[f]);

    size_t channel_size = (size_t)(header.fmt.bits_per_sample / 8);//finds the size of each channel
    char *data = (char *)malloc(channel_size);//makes a table that reads bytes as channel size
    int i;      
    for (i = 0; i < header.riff.chunk_size - sizeof(Header) + 8; i += header.fmt.num_channels)
    {//in length from begging to filesize minus the header with step of the size of channels
        if (fread(data, channel_size, 1, wav)); //reads left channel
        fwrite(data, channel_size, 1, new);//writes it on the new file
        if (fread(data, channel_size, 1, wav));//reads right channel and discards it
    }

    fclose(wav);wav = NULL;
    fclose(new);new=NULL;
    free(name);name = NULL;
    free(data);data = NULL;

    printf("Done...\n");
    if (fileNum != 1)
    {
        f++;
        StereoToMono(--fileNum, argv);
    }
}

/* gcc -DDMono -o monoTest StereoToMono.c headInit.c
   ./monoTest -mono <wav> */
#ifdef DMono
int main(int argc, char *argv[])
{
   StereoToMono(1,argv);
   return 0;
}
#endif