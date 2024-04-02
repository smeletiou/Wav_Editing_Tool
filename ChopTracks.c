/**
 * @file ChopTracks.c
 * @author Sotiris Rafail Meletiou AM941797
 * @author Michalis Fykiris AK767066
 * @brief chop tracks to given time space
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

void ChopTracks(char *argv[])
{    //check if it is a .wav
     if(checkExtension(2,argv)==0){
        printf("Please give another file\n");
        exit(EXIT_FAILURE);
     }

    FILE *wav = fopen(argv[2], "rb");
    checkFile(wav,argv,2);

    //Read Header
    Header header=readHead(header,wav); 
    //check if its pcm format
    isPCM(header.fmt.subchunk1_size,header.fmt.audio_format,argv,2);

    float FromSec = atof(argv[3]);//staring point
    float ToSec = atof(argv[4]);//ending point
      
      //check if starting point is out of bounds 
      if(FromSec>getSeconds(header.fmt.byte_rate,header.data.subchunk2_size)||FromSec<0){
         printf("Your starting point its out of length\n");
         printf("File is %f seconds\n",getSeconds(header.fmt.byte_rate,header.data.subchunk2_size));
         exit(EXIT_FAILURE);
      //checks if ending point is out of bounds
      }else if(ToSec>getSeconds(header.fmt.byte_rate,header.data.subchunk2_size)){
         printf("Your ending point its out of length\n");
         printf("File is %f seconds\n",getSeconds(header.fmt.byte_rate,header.data.subchunk2_size));
         exit(EXIT_FAILURE);
      //checks if starting point is not after the eneding point 
      }else if(FromSec>ToSec){
          printf("starting point cant be after the ending point\n");
          exit(EXIT_FAILURE);
      }
    //create name for new file
    printf("Creating new file...\n");
    char *name = malloc(9 + strlen(argv[2]));
    strcpy(name, "chopped-");
    strcat(name, argv[2]);
    
    //finds in which block the given starting point is 
    int From=(FromSec*header.fmt.byte_rate)/header.fmt.block_align;
    //finds in which block the given ending point is
    int To=(ToSec*header.fmt.byte_rate)/header.fmt.block_align;
    //calculates the new blocks required for the new file
    //by subtracting the two points to find it
    dword NewBlocks=To-From;
    
    //calculates the new size that its gonna take for the new file
    //by multiply the number of required blocks with block align 
    header.data.subchunk2_size=NewBlocks*header.fmt.block_align;
    header.riff.chunk_size=header.data.subchunk2_size+36;
    
    FILE *new = fopen(name, "wb");
    checkFile(new,NULL,-1);

    fwrite(&header, sizeof(Header), 1, new);
    
    printf("Chopping %s from %f to %f...\n",argv[2],FromSec,ToSec);
    int i;int data;
    //reads till the given ending point 
    for ( i = 0; i < To; i++){
        //the bytes before the given staring point are discarded
        if(i<From){
          if(fread(&data,sizeof(int),1,wav));
        }else{//and it only reads the bytes from the starting point to the ending point
          if(fread(&data,sizeof(int),1,wav));
          fwrite(&data,sizeof(int),1,new);//and writes the to the new file
        }
    }
    
    printf("Done...\n");
    free(name);name=NULL;
    fclose(wav);wav=NULL;
    fclose(new);new=NULL;
}


/* gcc -DDChop -o chopTest ChopTracks.c headInit.c
   ./chopTest -chop <wav> <startPoint> <endPoint> */
#ifdef DChop
int main(int argc, char *argv[])
{
   ChopTracks(argv);
   return 0;
}
#endif