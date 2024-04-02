@mainpage EPL232 HomeWork4 GroupProject TEAM 1 \n
@author Sotiris Rafail Meletiou AM941797

@license Copyright (C) 1992-1993 Jean-loup Gailly This is free software; you can redistribute it and/ormodify it under the terms of the GNU General Public License, see the file COPYING

Files :\n
StenographyFuncs.c  ReverseTrack.c  MixTwoTracks.c  ChopTracks.c  List.c  Encrypt.c       StereoToMono.c SlowMotion.c  headInit.c  main.c  Decrypt.c 
FunctionsDecler.h helpFuncDec.h WavStructs.h

Library : WavLib.a

@bug no known bugs 

How to Compile :\n 
without library :\n
make \n
gcc -o wavengine StenographyFuncs.o  ReverseTrack.o  MixTwoTracks.o  ChopTracks.o  List.o  Encrypt.o  StereoToMono.o  SlowMotion.o  headInit.o  main.o  Decrypt.o

with Library : \n
gcc -o wavengine main.c WavLib.a

Run : \n
./wavengine -list <wav> {<wav2.....wavN} \n
./wavengine -mono <wav> {<wav2.....wavN} \n
./wavengine -mix <wav> <wav2> \n
./wavengine -chop <wav> <startSec> <endSec> \n
./wavengine -reverse <wav> {<wav2.....wavN} \n
./wavengine -encodeText <wav> <inputTXT> \n
./wavengine -decodeText <wav> <msgLength> <outputTXT> \n
./wavengine -slow <wav> {<wav2.....wavN} \n\n

Driver Test :(functions that can take more than one wavs at the same time only test one of hem in driver)\n
gcc -DDList -o listTest List.c headInit.c \n
  ./listTest -list <wav> \n

gcc -DDMono -o monoTest StereoToMono.c headInit.c \n
   ./monoTest -mono <wav> \n

gcc -DDMix -o mixTest MixTwoTracks.c headInit.c \n
   ./mixTest -mix <wav>\n

gcc -DDChop -o chopTest ChopTracks.c headInit.c \n
   ./chopTest -chop <wav> <startPoint> <endPoint>\n

gcc -DDRev -o revTest ReverseTrack.c headInit.c \n
   ./revTest -rev <wav>\n

gcc -DDEncod -o encTest Encrypt.c headInit.c StenographyFuncs.c \n
   ./encTest -encodeText <wav> <txt> \n

gcc -DDDecod -o decTest Decrypt.c headInit.c StenographyFuncs.c \n
   ./decTest -decodeText <wav> <msglen> <outputtxt> \n

gcc -DDSlow -o slowTest SlowMotion.c headInit.c \n
   ./slowTest -slow <wav> \n

gcc -DDeInit -o testHead headInit.c  \n
   ./testHead <wav file>\n

gcc -DDSteno -o testSten StenographyFuncs.c \n
 ./testSten \n\n

Use of program :\n
Modify wav files with 8 different functions such as\n
Listing : shows the header of a wav file\n
StereoToMono : converts a wav from stereo audio to mono (1 channel)\n
MixTracks : mix two wavs together (the new file is the size of of hte smaller wav)\n
ChopTracks : chop a wav file at the given seconds the user gave\n
Reverse : play the wav file backwards\n
Encryption : hide a secret message in a bit level inside the wav\n
Decryption : extract the hidden message from a wav file\n
SlowMotion : make a wav file playing in slow motion \n

Only one function can be called a time.
Every Function starts by reading the header of the wav file and the sound data of the wav (data after the 44 bytes of the header).Then they create the new file that the modified data will go to by adding infornt of the original name the name of the process that we chose.Then starts the modification of the sound data depending on the chosen process and saves all the altered data inside the new file that was made
