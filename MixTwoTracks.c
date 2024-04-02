/**
 * @file MixTwoTracks.c
 * @author Sotiris Rafail Meletiou AM941797
 * @author Michalis Fykiris AK767066
 * @brief mix two wavs toghether
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
void MixTwoTracks(char *argv[])
{    
    //if one of the files is not wav terminates program
     if(checkExtension(2,argv)==0||checkExtension(3,argv)==0){
        printf("Please give another file\n");
        exit(EXIT_FAILURE);
     }

    FILE *wav1 = fopen(argv[2], "rb");
    checkFile(wav1,argv,2);

    FILE *wav2 = fopen(argv[3], "rb");
    checkFile(wav2,argv,3);

    //Read Header 1
    Header header=readHead(header,wav1);
    //checks if file1 is pcm format 
    isPCM(header.fmt.subchunk1_size,header.fmt.audio_format,argv,2);
     
    //Read Header 2
    Header header2=readHead(header2,wav2);
    //checks if file2 is pcm format
    isPCM(header.fmt.subchunk1_size,header.fmt.audio_format,argv,3);
     

    //checks if both files are stereo and have the same bits per sample so the can be mixed
    if ((header.fmt.num_channels != 2 || header2.fmt.num_channels != 2) ||
        (header.fmt.bits_per_sample != header2.fmt.bits_per_sample))
    {
        if (header.fmt.num_channels != 2)
            printf("%s is not Stereo\n", argv[2]);

        if (header2.fmt.num_channels != 2)
            printf("%s is not Stereo\n", argv[3]);

        if (header.fmt.bits_per_sample != header2.fmt.bits_per_sample)
            printf("Files does not have the same bits per sample\n");

        exit(EXIT_FAILURE);
    }

    //create name for new file
    printf("Creating new file...\n");
    char *copy = malloc(strlen(argv[2]) - 4);
    memcpy(copy, argv[2], strlen(argv[2]) - 4);
    char *name = malloc(5 + strlen(argv[2]) + strlen(argv[3]));
    strcpy(name, "mix-"); 
    strcat(name, copy);
    strcat(name, "-"); 
    strcat(name, argv[3]);

    FILE *new = fopen(name, "wb");
    checkFile(new,NULL,-1);

    float Sec_F1 = getSeconds(header.fmt.byte_rate, header.data.subchunk2_size);//get length of first file
    float Sec_F2 = getSeconds(header2.fmt.byte_rate, header2.data.subchunk2_size);//get length of second file

    //reading data in size of a channel 
    size_t channel_size = (size_t)(header.fmt.bits_per_sample / 8);
    char *data = (char *)malloc(channel_size);
    char *data2 = (char *)malloc(channel_size);
    int i;
    
    printf("Mixing %s and %s together...\n",argv[2],argv[3]);
    if (Sec_F1 < Sec_F2)//if first file smaller than the second we choose the first
    {
        fwrite(&header, sizeof(Header), 1, new);//writes the header of the first file
        //all the bytes of the file minus the header by step of number of channels
        for (i = 0; i < header.riff.chunk_size - sizeof(Header) + 8; i += header.fmt.num_channels)
        {   
            if (fread(data2, channel_size, 1, wav2));//reads left channel of second file
            fwrite(data2, channel_size, 1, new);//adds it as left channel of the new file
            if (fread(data2, channel_size, 1, wav2));//reads right channel of second file and discards it

            if (fread(data, channel_size, 1, wav1));//reads left channel of first file
            if (fread(data, channel_size, 1, wav1));//reads right channel of first file discarding the left
            fwrite(data, channel_size, 1, new);//writes the right channel of first file in the new file
        }
    }
    else//if the second is smaller we choose the second and do the same as above
    {
        fwrite(&header2, sizeof(Header), 1, new);//writes the header of the second file  
        for (i = 0; i < (header2.riff.chunk_size - sizeof(Header) + 8); i += header2.fmt.num_channels)
        {
            if (fread(data2, channel_size, 1, wav2)) ;
            fwrite(data2, channel_size, 1, new);
            if (fread(data2, channel_size, 1, wav2)) ;
            if (fread(data, channel_size, 1, wav1)) ;
            if (fread(data, channel_size, 1, wav1));
            fwrite(data, channel_size, 1, new);
        }
    }
    //free everything
    fclose(wav1);wav1=NULL;
    fclose(wav2);wav2=NULL;
    fclose(new);new=NULL;
    free(copy);copy = NULL;
    free(name);name = NULL; 
    free(data);data = NULL;
    free(data2);data2 =NULL;
    printf("Done...\n");
}

/* gcc -DDMix -o mixTest MixTwoTracks.c headInit.c
   ./mixTest -mix <wav> */
#ifdef DMix
int main(int argc, char *argv[])
{
   MixTwoTracks(argv);
   return 0;
}
#endif