@mainpage EPL232 HomeWork4 GroupProject TEAM 1 <br>
@author Sotiris Rafail Meletiou AM941797

@license Copyright (C) 1992-1993 Jean-loup Gailly This is free software; you can redistribute it and/ormodify it under the terms of the GNU General Public License, see the file COPYING

Files :<br>
StenographyFuncs.c  ReverseTrack.c  MixTwoTracks.c  ChopTracks.c  List.c  Encrypt.c       StereoToMono.c SlowMotion.c  headInit.c  main.c  Decrypt.c 
FunctionsDecler.h helpFuncDec.h WavStructs.h

Library : WavLib.a

@bug no known bugs 

How to Compile :<br> 
without library :<br>
make <br>
gcc -o wavengine StenographyFuncs.o  ReverseTrack.o  MixTwoTracks.o  ChopTracks.o  List.o  Encrypt.o  StereoToMono.o  SlowMotion.o  headInit.o  main.o  Decrypt.o

with Library : <br>
gcc -o wavengine main.c WavLib.a

Run : <br>
./wavengine -list <wav> {<wav2.....wavN} <br>
./wavengine -mono <wav> {<wav2.....wavN} <br>
./wavengine -mix <wav> <wav2> <br>
./wavengine -chop <wav> <startSec> <endSec> <br>
./wavengine -reverse <wav> {<wav2.....wavN} <br>
./wavengine -encodeText <wav> <inputTXT> <br>
./wavengine -decodeText <wav> <msgLength> <outputTXT> <br>
./wavengine -slow <wav> {<wav2.....wavN} <br><br>

Driver Test :(functions that can take more than one wavs at the same time only test one of hem in driver)\n
gcc -DDList -o listTest List.c headInit.c <br>
  ./listTest -list <wav> <br>

gcc -DDMono -o monoTest StereoToMono.c headInit.c <br>
   ./monoTest -mono <wav> <br>

gcc -DDMix -o mixTest MixTwoTracks.c headInit.c <br>
   ./mixTest -mix <wav><br>

gcc -DDChop -o chopTest ChopTracks.c headInit.c <br>
   ./chopTest -chop <wav> <startPoint> <endPoint><br>

gcc -DDRev -o revTest ReverseTrack.c headInit.c <br>
   ./revTest -rev <wav><br>

gcc -DDEncod -o encTest Encrypt.c headInit.c StenographyFuncs.c <br>
   ./encTest -encodeText <wav> <txt> <br>

gcc -DDDecod -o decTest Decrypt.c headInit.c StenographyFuncs.c <br>
   ./decTest -decodeText <wav> <msglen> <outputtxt> <br>

gcc -DDSlow -o slowTest SlowMotion.c headInit.c <br>
   ./slowTest -slow <wav> <br>

gcc -DDeInit -o testHead headInit.c  <br>
   ./testHead <wav file> <br> 

gcc -DDSteno -o testSten StenographyFuncs.c <br>
 ./testSten <br><br>

Use of program :<br>
Modify wav files with 8 different functions such as <br>
Listing : shows the header of a wav file <br>
StereoToMono : converts a wav from stereo audio to mono (1 channel)<br>
MixTracks : mix two wavs together (the new file is the size of of hte smaller wav)<br>
ChopTracks : chop a wav file at the given seconds the user gave<br>
Reverse : play the wav file backwards<br>
Encryption : hide a secret message in a bit level inside the wav<br>
Decryption : extract the hidden message from a wav file<br>
SlowMotion : make a wav file playing in slow motion <br>

Only one function can be called a time.<br>
Every Function starts by reading the header of the wav file and the sound data of the wav (data after the 44 bytes of the header).Then they create the new file that the modified data will go to by adding infornt of the original name the name of the process that we chose.Then starts the modification of the sound data depending on the chosen process and saves all the altered data inside the new file that was made
