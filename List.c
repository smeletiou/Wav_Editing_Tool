/**
 * @file List.c
 * @author Sotiris Rafail Meletiou AM941797
 * @author Michalis Fykiris AK767066
 * @brief show header of wav
 * @version 0.1
 * 
* @copyright Copyright (C) 1992-1993 Jean-loup Gailly
* This is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public
* License, see the file COPYING
 * 
 */
#include "FunctionsDecler.h"
#include "helpFuncDec.h"

void listing(int fileNum, char *argv[])
{
    static int f = 2;//index for file (starts from 2 cuz 0 
                     //is the name of the exe and 1 the function name)

    while(checkExtension(f,argv)==0){//check files for .wav extension
        if(fileNum!=1){//if the are more than one files as input
        f++; //moves the index to the next file
       --fileNum; //decreases the amount of files left
        printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n");
      }else if(fileNum==1)//if the final file is not a wav ends process
        exit(EXIT_FAILURE);
    }

    //reads wav
    FILE *wav = fopen(argv[f], "rb");
    checkFile(wav,argv,f);

    //finds size of entire file in bytes
    int len = getFileSize(wav);

    //Read Header
    Header header=readHead(header,wav);
    fclose(wav);wav=NULL;

    printf("==================\n");
    printf("%s\n", argv[f]);
    printf("==================");
    printf("\nRIFF_CHUNK_HEADER\n");
    printf("==================\n");
    printf("ChunkID \t:  %c%c%c%c\n", header.riff.chunk_id[0], header.riff.chunk_id[1], header.riff.chunk_id[2], header.riff.chunk_id[3]);
    printf("ChunkSize \t:  %d  (File_Size : %d)\n", header.riff.chunk_size, len);
    printf("Format \t\t:  %c%c%c%c\n", header.riff.format[0], header.riff.format[1], header.riff.format[2], header.riff.format[3]);

    printf("\nFMT_SUBCHUNK_HEADER\n");
    printf("==================\n");
    printf("Subchunk1ID \t:  %c%c%c%c\n", header.fmt.subchunk1_id[0], header.fmt.subchunk1_id[1], header.fmt.subchunk1_id[2], header.fmt.subchunk1_id[3]);
    printf("Subchunk1Size \t:  %d\n", header.fmt.subchunk1_size);
    printf("AudioFormat \t:  %d\n", header.fmt.audio_format);
    printf("NumChannels \t:  %d\n", header.fmt.num_channels); //Number of channels (mono=1/sterio=2)
    printf("sampleRate \t:  %d\n", header.fmt.sample_rate);   //Sampling frequency of the wav file
    printf("ByteRate \t:  %d\n", header.fmt.byte_rate);       //Number of bytes per second
    printf("BlockAlign \t:  %d\n", header.fmt.block_align);
    printf("BitsPerSample \t:  %d\n", header.fmt.bits_per_sample); //Number of bits used per sample

    printf("\nDATA_SUBCHUNK_HEADER\n");
    printf("====================\n");
    printf("Subchunk2ID \t:  %c%c%c%c\n", header.data.subchunk2_id[0], header.data.subchunk2_id[1], header.data.subchunk2_id[2], header.data.subchunk2_id[3]);
    printf("Subchunk2Size \t:  %d\n", header.data.subchunk2_size);
    printf("\n");
    printf("Time of wav : %f\n", getSeconds(header.fmt.byte_rate, header.data.subchunk2_size));
    
    //recursion for more files 
    if (fileNum != 1)
    {
        printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n");
        f++;
        listing(--fileNum, argv);
    }
}

/*gcc -DDList -o listTest List.c headInit.c 
  ./listTest -list <wav>   */
#ifdef DList
int main(int argc, char *argv[])
{
    listing(1,argv);
    return 0;
}
#endif