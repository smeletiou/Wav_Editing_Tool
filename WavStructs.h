/**
* @file libDecl.h
* @author Sotiris Rafail Meletiou AM941797
* @author Michalis Fykiris AK767066
* @brief  Structs for Header of wav and reads of them.
* @version 4

* @copyright Copyright (C) 1992-1993 Jean-loup Gailly
* This is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public
* License, see the file COPYING 
 * 
 */

#ifndef WAVSTRUCTS_H
#define WAVSTRUCTS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char byte;
typedef unsigned short int word;
typedef unsigned int dword;

/**
 * @brief Riff_Chunk.
 *the riff part of the wav header.
 */
typedef struct RIFF_CHUNK
{
   byte chunk_id[4];
   dword chunk_size;
   byte format[4];
} __attribute__((packed)) RIFF;

/**
 * @brief Fmt_Sub_Chunk.
 *the fmt part of the wav header.
 */
typedef struct FMT_SUB_CHUNK
{
   byte subchunk1_id[4];
   dword subchunk1_size;
   word audio_format;
   word num_channels;
   dword sample_rate;
   dword byte_rate;
   word block_align;
   word bits_per_sample;
} __attribute__((packed)) FMT;

/**
 * @brief Data_Sub_Chunk.
 * the data part of the wav header.
 */
typedef struct DATA_SUB_CHUNK
{
   byte subchunk2_id[4];
   dword subchunk2_size;
} __attribute__((packed)) DATA;

/**
 * @brief Entire header.
 * combines the 3 parts of the header.
 */
typedef struct wavHeader
{
  RIFF riff;
  FMT fmt;
  DATA data;
}__attribute__((packed)) Header;

/**
 * @brief Reads Riff.
 * reads the riff part of a wav
 * and saves it
 * @param wav 
 * @return RIFF 
 */
RIFF readRIFF(FILE *wav);

/**
 * @brief reads FMT.
 * reads the fmt part of a wav
 * and saves it
 * @param wav 
 * @return FMT 
 */
FMT readFMT(FILE *wav);

/**
 * @brief Reads Data.
 * reads the data part of a wav
 * (Subchunk2) and saves it 
 * @param wav 
 * @return DATA 
 */
DATA readDATA(FILE *wav);

/**
 * @brief Reads Head.
 * reads all part of the header 
 * @param header variable to save all the parts
 * @param wav file
 * @return Header the entire header
 */
Header readHead(Header header,FILE *wav);

#endif