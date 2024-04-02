/**
 * @file ReverseTrack.c
 * @author Sotiris Rafail Meletiou AM941797
 * @author Michalis Fykiris AK767066
 * @brief reverse wav 
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

void ReversedTrack(int fileNum, char *argv[])
{
    static int f = 2;//index of files
    //check for .wav extension
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

    //check for pcm format
    isPCM(header.fmt.subchunk1_size,header.fmt.audio_format,argv,f);

    //create name for new file
    char *name = malloc(9 + strlen(argv[f]));
    strcpy(name, "reverse-");
    strcat(name, argv[f]);
    
    printf("Creating new file...\n");
    FILE *new = fopen(name, "wb");
    checkFile(new,NULL,-1);

    fwrite(&header, sizeof(Header), 1, new);//writes the new header to the new wav

    int bytes_per_sample = header.fmt.bits_per_sample / 8;
    //total samples per channel
    int samps_per_chan = header.data.subchunk2_size / bytes_per_sample;
    //total samples for entire file
    int TotalSamps = (samps_per_chan - 1) * header.fmt.num_channels;

    //stores all the data after the header    
    char *data = (char *)malloc(header.data.subchunk2_size + 1);
    data[header.data.subchunk2_size + 1] = '\0';
    //reads all the data after the header
    if (fread(data, header.data.subchunk2_size, 1, wav)) ;
    fclose(wav);wav = NULL;

    printf("Reversing %s...\n", argv[f]);
    int i, j; short temp;
    //reverse the array with all the data we read from the wav 
    for (i = 0; i < samps_per_chan / 2; i++)
        for (j = 0; j < header.fmt.num_channels; j++)
        {
            temp = data[i * header.fmt.num_channels + j];
            data[i * header.fmt.num_channels + j] = data[TotalSamps - i * header.fmt.num_channels + j];
            data[TotalSamps - i * header.fmt.num_channels + j] = temp;
        }
    fwrite(data, header.data.subchunk2_size, 1, new);//writes the reversed array to the new wav
   
    fclose(new);new=NULL;
    free(data);data = NULL;
    free(name);name = NULL;

    printf("Done...\n");
    if (fileNum != 1)
    {
        f++;
        ReversedTrack(--fileNum, argv);
    }
}

/* gcc -DDRev -o revTest ReverseTrack.c headInit.c
   ./revTest -rev <wav> */
#ifdef DRev
int main(int argc, char *argv[])
{
   ReversedTrack(1,argv);
   return 0;
}
#endif