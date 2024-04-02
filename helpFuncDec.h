/**
* @file libDecl.h
* @author Sotiris Rafail Meletiou AM941797
* @author Michalis Fykiris AK767066
* @brief getting extra info and checking of formats. 
* @version 4

* @copyright Copyright (C) 1992-1993 Jean-loup Gailly
* This is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public
* License, see the file COPYING
 * 
 */
#ifndef HELPFUNCDEC_H
#define HELPFUNCDEC_H
#include "WavStructs.h"

/**
 * @brief File Size .
 * get the size in mb
 * @param inFile 
 * @return int 
 */
int getFileSize(FILE *fp);

/**
 * @brief Get Seconds .
 * gets the size of a wav in seconds (float)
 * @param ByteRate form header
 * @param subchunk2size from header
 * @return int time
 */
float getSeconds(dword ByteRate, dword subchunk2size);

/**
 * @brief Checks if pcm.
 * checks if a wav is pcm format
 * (subchunk1size=16 && Audioformat =1)
 * @param subchunk 
 * @param Af 
 * @return int 
 */
void isPCM(dword subchunk,word Af,char *argv[],int f);

/**
 * @brief Check for .wav.
 * checks if a file has .wav extension
 * @param f 
 * @param argv 
 * @return int 
 */
int checkExtension(int f ,char *argv[]);

/**
 * @brief file checker.
 * checks if file opened successfully
 * @param fp file
 * @param argv 
 * @param f index of file 
 */
void checkFile(FILE *fp,char *argv[],int f);

/**
 * @brief print Copyright.
 * printing copyright claim at incorrect input
 */
void CopyrightClaim(void);

/**
 * @brief Turn binary numbers to Decimals.
 * so the binaryToText function can turn the decimal number
 * to ASCII characters
 * @param binary binary string
 * @param length 
 * @return unsigned long length of binary string
 */
unsigned long binaryToDecimal(char *binary, int length);

/**
 * @brief Turn binary to text.
 * it takes the binary string and its length
 * 
 * @param binary 
 * @param binaryLength 
 * @param text 
 * @param symbolCount 
 */
void binaryToText(char *binary, int binaryLength, char *text, int symbolCount);
#endif