/**
 * @file Decrypt.c
 * @author Sotiris Rafail Meletiou AM941797
 * @author Michalis Fykiris AK767066
 * @brief extract hidden message from an encoded-wav
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
#define system_key 1000

void Decrypt(char *argv[])
{
    //check if its the correct format for a file
    char *copy = malloc(strlen(argv[2]));
    memcpy(copy, argv[2], 8);
    copy[9] = '\0';
    if (strcmp(copy, "encoded-"))
    {
        printf("ERROR : This file does not contain encrypted message\n");
        printf("Please enter a file starting with \"encoded-\" \n");
        free(copy);
        exit(EXIT_FAILURE);
    }
    free(copy);

    FILE *wav = fopen(argv[2], "rb");
    checkFile(wav,argv,2);

    //Read Header
    Header header=readHead(header,wav);
    
    int msgLen = atoi(argv[3]);         //read encrypted msgs length
    FILE *output = fopen(argv[4], "w"); //open output file for the decrypted msg
    
    //char data[header.data.subchunk2_size];
    char *data = (char *)malloc(header.data.subchunk2_size + 1);
    data[header.data.subchunk2_size + 1] = '\0';
    if(fread(data,header.data.subchunk2_size,1,wav));
    fclose(wav);wav=NULL;

    printf("Decrypting %s file...\n",argv[2]);
    char *msgInBinary=malloc(msgLen*8+1);//creates and allocates memory for the binary string 
    int* permut=createPermutationFunction(header.data.subchunk2_size,system_key);

    int i;
    for (i=0;i<8*msgLen+1;i++){//take the length of the binary string that was given
      if(data[permut[i]] & 1)//checks the premut at i and compares it with 1 so we can take back the altered bits
        msgInBinary[i]='1';//if the last bit is 1 we add 1 in the binary string
      else
        msgInBinary[i]='0'; //else we add 0
}     //at the end we will have a string by 1s and 0s to be translate to decimal and the to Ascii

   printf("Extracting hidden message...\n");
   msgInBinary[msgLen*8+1]='\0';

   char *msgInText=malloc(msgLen+1);//creates and allocates memory for the decrepted msg
   int binaryLen=msgLen*8;//length of binary string

    binaryToText(msgInBinary,binaryLen,msgInText,msgLen);//converts binary string to decimal and then to ASCII
    msgInText[msgLen+1]='\0';
    printf("Message extracted successfully at %s \n",argv[4]);
    
    fwrite(msgInText,msgLen,1,output);//writes decrypted txt in output file

    //free everything 
    free(data);data= NULL;
    free(msgInBinary);msgInBinary=NULL;
    free(permut);permut=NULL;
    free(msgInText);msgInText=NULL;
    fclose(output);
}

/* gcc -DDDecod -o decTest Decrypt.c headInit.c StenographyFuncs.c
   ./decTest -decodeText <wav> <msglen> <outputtxt> */
#ifdef DDecod
int main(int argc, char *argv[])
{
   Decrypt(argv);
   return 0;
}
#endif