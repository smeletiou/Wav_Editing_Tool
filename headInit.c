/**
* @file headInit.c
* @author Sotiris Rafail Meletiou AM941797
* @author Michalis Fykiris AK767066
* @brief Functions for reading every info of a file 
* @version 4
*
* @copyright Copyright (C) 1992-1993 Jean-loup Gailly
* This is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public
* License, see the file COPYING
 */
#include "helpFuncDec.h"

RIFF readRIFF(FILE *wav)
{
    RIFF riff;
    if (fread(&riff, sizeof(RIFF), 1, wav) == 0)
    {
        printf("read of riff failed\n");
        exit(EXIT_FAILURE);
    }
    return riff;
}

FMT readFMT(FILE *wav)
{
    FMT fmt;
    if (fread(&fmt, sizeof(FMT), 1, wav) == 0)
    {
        printf("read of fmt failed\n");
        exit(EXIT_FAILURE);
    }
    return fmt;
}

DATA readDATA(FILE *wav)
{
    DATA data;
    if (fread(&data, sizeof(DATA), 1, wav) == 0)
    {
        printf("read of data failed\n");
        exit(EXIT_FAILURE);
    }
    return data;
}

Header readHead(Header header, FILE *wav)
{
    header.riff = readRIFF(wav); // reads Riff part
    header.fmt = readFMT(wav);   // reads FMT part
    header.data = readDATA(wav); // reads Data part
    return header;
}

int getFileSize(FILE *fp)
{
    int fileSize = 0;
    fseek(fp, 0, SEEK_END);
    fileSize = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    return fileSize;
}

float getSeconds(dword ByteRate, dword subchunk2size)
{
    return ((float)subchunk2size / (float)ByteRate);
}

void isPCM(dword subchunk, word Af, char *argv[], int f)
{
    if (subchunk != 16 || Af != 1)
    {
        printf("File %s is not PCM format \n", argv[f]);
        printf("Please give another one\n");
        exit(EXIT_FAILURE);
    }
}

int checkExtension(int f, char *argv[])
{
    char *str = argv[f];
    char *ext;
    ext = strstr(str, ".wav");//check if .wav exist in the str
    if (!ext)
    {
        printf("File %s is not a .wav **IGNORED**\n", argv[f]);
        return 0;
    }
    return 1;
}

void checkFile(FILE *fp, char *argv[], int f)
{
    if (f != -1)//for files from the argv
    {
        if (fp == NULL)
        {
            printf("Error : File %s failed\n", argv[f]);
            exit(EXIT_FAILURE);
        }
    }
    else //for the new files that are created 
    {
        if (fp == NULL)
        {
            printf("ERROR: New file failled to open...\n");
            exit(EXIT_FAILURE);
        }
    }
}


/* gcc -DDeInit -o testHead headInit.c   
   ./testHead <wav file> */
#ifdef DeInit
int main(int argc, char *argv[])
{
    FILE *fp = fopen(argv[1], "rb"); //open file

    checkFile(fp, argv, 1); //check if file opened
    printf("File check successful\n");

    checkExtension(1, argv); //check if it ends to a .wav
    printf("Extension check successful\n");

    int len = getFileSize(fp); //get size
    printf("Size %d successful\n", len);

    Header head = readHead(head, fp); //read head

    isPCM(head.fmt.subchunk1_size, head.fmt.audio_format, argv, 1); //check if is pcm
    printf("PCM check successful\n");

    //get length of file in seconds
    printf("%f seconds\n", getSeconds(head.fmt.byte_rate, head.data.subchunk2_size));
    fclose(fp);
    return 0;
}
#endif