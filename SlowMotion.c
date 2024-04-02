/**
 * @file SlowMotion.c
* @author Sotiris Rafail Meletiou AM941797
* @author Michalis Fykiris AK767066
 * @brief convert wav to slow motion
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

void SlowMotion(int fileNum, char *argv[])
{
    static int f = 2;

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

    header.fmt.num_channels = 1;//makes wav into mono
    header.fmt.byte_rate /= 2;//halves the byte rate
    header.fmt.block_align /= 2;//halves the block alligmemt
    
    printf("Creating new file...\n");
    char *name = malloc(6 + strlen(argv[f]));
    strcpy(name, "slow-");
    strcat(name, argv[f]);

    FILE *new = fopen(name, "wb");
    checkFile(new,NULL,-1);

    fwrite(&header, sizeof(Header), 1, new);
    
    printf("Converting %s to Slow motion...\n",argv[f]);
    unsigned int sample;  int i;
    //to say the truth this function was an accident we tried to do the StereoToMono and we made this
    for (i = 0; i < header.riff.chunk_size - sizeof(Header) + 8; i += sizeof(unsigned int))
    {
        if (fread(&sample, sizeof(unsigned int), 1, wav));//reads every bit
        sample = (sample & ((0xffffffff)));//and compairs it with this mask
        fwrite(&sample, sizeof(unsigned int), 1, new);//and writes of the result of the operator &
    }
    
    //free everything
    fclose(wav);wav=NULL;
    fclose(new);new=NULL;
    free(name);name = NULL;
    printf("Done...\n");
    if (fileNum != 1)
    {
        f++;
        SlowMotion(--fileNum, argv);
    }
}


/* gcc -DDSlow -o slowTest SlowMotion.c headInit.c
   ./slowTest -slow <wav> */
#ifdef DSlow
int main(int argc, char *argv[])
{
   SlowMotion(1,argv);
   return 0;
}
#endif