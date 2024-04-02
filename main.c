/**
 * @file main.c
 * @author Sotiris Rafail Meletiou AM941797
 * @author Michalis Fykiris AK767066
 * @brief  entry point.
 * @version 4
 * 
 * @copyright Copyright (C) 1992-1993 Jean-loup Gailly
* This is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public
* License, see the file COPYING
 */

#include "FunctionsDecler.h"
void CopyrightClaim(void)
{
    printf("\n+++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("Copyright (C) 1992-1993 Jean-loup Gailly \n\
    This is free software; you can redistribute it and/or \n\
    modify it under the terms of the GNU General Public\n\
    License, see the file COPYING\n");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++\n");

}

void funcCAll(int argc, char *argv[])
{   //listing function call
    if (strcmp(argv[1], "-list") == 0)
        if (argc > 2)
        {
            int fileNum = 1;
            if (argc > 3)
                fileNum = argc - 2;
            listing(fileNum, argv);
        }
        else
        {
            printf("\nYou need atleast (1) wav file\n\n");
            CopyrightClaim();
            exit(EXIT_FAILURE);
        }
    //Stereo to Mono convertion function call
    else if (strcmp(argv[1], "-mono") == 0)
        if (argc > 2)
        {
            int fileNum = 1;
            if (argc > 3)
                fileNum = argc - 2;
            StereoToMono(fileNum, argv);
        }
        else
        {
            printf("\nYou need atleast (1) wav file\n");
            CopyrightClaim();
            exit(EXIT_FAILURE);
        }
    //Mixing function call
    else if (strcmp(argv[1], "-mix") == 0)
        if (argc == 4){
            MixTwoTracks(argv);
         } else
        {
            printf("\nYou need (2) wav files\n");
            CopyrightClaim();
            exit(EXIT_FAILURE);
        }
    //Choppin function call
    else if (strcmp(argv[1], "-chop") == 0)
        if (argc == 5){
            ChopTracks(argv);
        }  else
        {
            printf("\nYou need (1) wav file , starting sec and ending sec\n");
            CopyrightClaim();
            exit(EXIT_FAILURE);
        }
    //Reversing function call
    else if (strcmp(argv[1], "-reverse") == 0)
        if (argc > 2)
        {
            int fileNum = 1;
            if (argc > 3)
                fileNum = argc - 2;
            ReversedTrack(fileNum,argv);
        }
        else
        {
            printf("\nYou need atleast (1) wav file\n");
            CopyrightClaim();
            exit(EXIT_FAILURE);
        }
    //Encoding function call
    else if (strcmp(argv[1], "-encodeText") == 0)
        if (argc == 4){
            Encrypt(argv);
      } else
        {
            printf("\nYou need (1) wav file and a message\n");
            CopyrightClaim();
            exit(EXIT_FAILURE);
        }
    //Decoding function call
    else if (strcmp(argv[1], "-decodeText") == 0)
        if (argc == 5){
            Decrypt(argv);
         } else
        {
            printf("\nYou need (1) wav file,length of message and outputfile");
            CopyrightClaim();
            exit(EXIT_FAILURE);
        }
    //Slow Motion function call
    else if (strcmp(argv[1],"-slow")==0)
         if (argc > 2)
        {
            int fileNum = 1;
            if (argc > 3)
                fileNum = argc - 2;
            SlowMotion(fileNum, argv);
        }
        else
        {
            printf("\nYou need atleast (1) wav file\n");
            CopyrightClaim();
            exit(EXIT_FAILURE);
        }
    else
    {
        printf("\nFunction does not exist\n");
        printf("**********************************************\n");
        printf("Please choose one of the following\n");
        printf("Listing Wav : -list\n");
        printf("Convert stereo to mono  : -mono \n");
        printf("Mix : -mix\n");
        printf("Chop : -chop\n");
        printf("Reverse a wav file : -reverse\n");
        printf("Encrypt a secret message in wav : -encodeText\n");
        printf("Decrypt a message : -decodeText\n");
        printf("Slow Motion : -slow\n");
        CopyrightClaim();
        exit(EXIT_FAILURE);
    }
}
 

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: \n");
        printf("./wavengine -list <wav> {<wav2.....wavN}\n");
        printf("./wavengine -mono <wav> {<wav2.....wavN}\n");
        printf("./wavengine -mix <wav> <wav2>\n");
        printf("./wavengine -chop <wav> <startSec> <endSec>\n");
        printf("./wavengine -reverse <wav> {<wav2.....wavN}\n");
        printf("./wavengine -encodeText <wav> <inputTXT>\n");
        printf("./wavengine -decodeText <wav> <msgLength> <outputTXT>\n");
        printf("./wavengine -slow <wav> {<wav2.....wavN}\n");
        exit(EXIT_FAILURE);
    }
        
    funcCAll(argc, argv);
    return 0;
}
