/**
 * @file Encrypt.c
 * @author Sotiris Rafail Meletiou AM941797
 * @author Michalis Fykiris AK767066
 * @brief hid secret message in wav 
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

void Encrypt(char *argv[])
{
     if(checkExtension(2,argv)==0){
        printf("Please give another file\n");
        exit(EXIT_FAILURE);
     }

    FILE *wav = fopen(argv[2], "rb");
    checkFile(wav,argv,2);

    //Read Header
    Header header=readHead(header,wav);

    FILE *msg = fopen(argv[3], "r");
    checkFile(msg,argv,3);//check if msg.txt opened successfully

    int len=getFileSize(msg);//get size of message

    //create name for new file
    char *name = malloc(9 + strlen(argv[2]));
    strcpy(name, "encoded-");
    strcat(name, argv[2]);

    FILE *new = fopen(name, "wb");
    checkFile(new,NULL,-1);//check if file opened successful

    fwrite(&header, sizeof(Header), 1, new);//writes the new header to the new wav
   
    //char data[header.data.subchunk2_size];//saves wav data after the header 
    char *data = (char *)malloc(header.data.subchunk2_size + 1);
    data[header.data.subchunk2_size + 1] = '\0';
    if(fread(data,header.data.subchunk2_size,1,wav));//reads that data
    
    char *Encrypt_msg=(char*)malloc(len+1);//msg to be encrypted
    Encrypt_msg[len+1]='\0';
    if(fgets(Encrypt_msg, len+1, msg));//reads msg from file
    printf("Encrypting %s...\n",argv[2]);
    //creates a premutation to encrypt the msg
    int* permut=createPermutationFunction(header.data.subchunk2_size,system_key);
   
   /*
   Για κάθε i από 0 στο (1 + strlen(m)) × 8 
  - υπολόγισε  u = getBit(m, i) 
  - υπολόγισε x = permutation[i], το οποίο είναι το x-οστό byte των samples 
  - διέγραψε το bit μικρότερου βάρους του x-οστού byte του πίνακα των samples 
  - αντικατέστησε αυτό το bit που διαγράφτηκε με την τιμή u. 
  */
   printf("Hidding message between bytes...\n");
   int i,u;
   for (i=0;i<8*(strlen(Encrypt_msg)+1);i++){
     u=getBit(Encrypt_msg,i);
     if(u==1)//if bit is 1 set it to 1
        data[permut[i]]=data[permut[i]] | u;
     else //else set it to 0
        data[permut[i]]=data[permut[i]] & u; 
}
    
    //saves the tampered encrypted data to new wav
    fwrite(data,header.data.subchunk2_size,1,new);
    printf("Message hid successfully...\n");
    printf("Message length : %d \n",len);//length that you gonna need to decrypt the msg
    
    //free everything
    free(data);data = NULL;
    free(name);name=NULL;
    free(Encrypt_msg);Encrypt_msg=NULL;
    free(permut);permut=NULL; 
    fclose(wav);wav=NULL;
    fclose(msg);msg=NULL;
    fclose(new);new=NULL;
}

/* gcc -DDEncod -o encTest Encrypt.c headInit.c StenographyFuncs.c
   ./encTest -encodeText <wav> <txt> */
#ifdef DEncod
int main(int argc, char *argv[])
{
   Encrypt(argv);
   return 0;
}
#endif