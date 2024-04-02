/**
* @file FunctionsDecler.h
* @author Sotiris Rafail Meletiou AM941797
* @author Michalis Fykiris AK767066
* @brief Declerations for the 8 functions
* @version 4
* 
* @copyright Copyright (C) 1992-1993 Jean-loup Gailly
* This is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public
* License, see the file COPYING
* 
*/
#ifndef FUNCTIONSDECLER_H
#define FUNCTIONSDECLER_H
#include "WavStructs.h"
/**
 * @brief Listing Header .
 * prints the header of wav
 * @param fileNum number of wavs that were given
 * @param argv command line input
 */
void listing(int fileNum, char *argv[]);

/**
 * @brief Stereo To Mono.
 * converts stereo wav files to mono
 * @param fileNum  number of wavs that were given
 * @param argv 
 */
void StereoToMono(int fileNum, char *argv[]);

/**
 * @brief Mix 2 Wavs .
 * combines two wavs by making 
 * the left channel of the second wav as the left channel of the new wav
 * and the right channel of the first wav as the right channel of the new wav
 * @param argv command line input
 */
void MixTwoTracks(char *argv[]);

/**
 * @brief Chop Wavs.
 * chop a wav from a given point to another point
 * @param argv command line input
 */
void ChopTracks(char *argv[]);

/**
 * @brief Reverse Tracks.
 * reverse the wav file(if you reverse the reversed file it turns back 
 * to the original one)
 * @param fileNum  number of wavs that were given
 * @param argv command line input
 */
void ReversedTrack(int fileNum, char *argv[]);

/**
 * @brief Encrypt secret message.
 * hide a text from a .txt file
 * inside the wav files at a low level(bitwise) 
 * @param argv command line input
 */
void Encrypt(char *argv[]);

/**
 * @brief Decrypt encrypted message.
 * decrypt a hidden message from a "encoded-<file>.wav"
 * by entering the known length of the encrypted message
 * @param argv command line input
 */
void Decrypt(char *argv[]);

/**
 * @brief SlowMotion.
 * turns the sound of a wav into slow motion
 * doubles the length of the file
 * @param fileNum  number of wavs that were given
 * @param argv command line input
 */
void SlowMotion(int fileNum, char *argv[]);

/**
 * @brief Get Bit.
 * get bit(1|0) at n position of msg 
 * @param m message
 * @param n index for character
 * @return int bit 1|0 
 */
int getBit(char *m,int n);

/**
 * @brief Create a Permutation Function 
 * Κάνε N φορές 
   Διάλεξε «τυχαία» (με βάση το system-key-integer) δυο ακέραιους i και j  
   Μετάτρεψε τους στο διάστημα [0..N − 1]  
   Αντάλλαξε τα στοιχεία στις θέσεις i και j του πίνακα 
 * @param N size of data chunk
 * @param systemkey define ins FunctionsLib.c
 * @return int* returns the premutation
 */
int* createPermutationFunction(int N, unsigned int systemkey);

#endif