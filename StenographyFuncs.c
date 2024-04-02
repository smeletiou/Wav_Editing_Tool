/**
 * @file StenographyFucns.c
 * @author Sotiris Rafail Meletiou AM941797
 * @author Michalis Fykiris AK767066
 * @brief Funtictions for the encrypt and decode
 * @version 4 
 * @copyright Copyright (C) 1992-1993 Jean-loup Gailly
 * This is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License, see the file COPYING
 */
#include "helpFuncDec.h"

int *createPermutationFunction(int N, unsigned int systemkey)
{
    /*
   Κάνε N φορές 
   Διάλεξε «τυχαία» (με βάση το system-key-integer) δυο ακέραιους i και j  
   Μετάτρεψε τους στο διάστημα [0..N − 1]  
   Αντάλλαξε τα στοιχεία στις θέσεις i και j του πίνακα 
    */
    srand(systemkey);
    
    //N is the subchunk2 size 
    int *perm = malloc(N * sizeof(int));

    int p;
    for (p = 0; p < N; p++)
        perm[p] = p;

    for (p = 0; p < N; p++)
    {
        int i = (rand() % N);//random index 1
        int j = (rand() % N);//random index 2
        
        //reversing the 2 randoms indexes 
        int temp = perm[i];
        perm[i] = perm[j];
        perm[j] = temp;
    } 

    return perm;
}

int getBit(char *m, int n)
{
    /*
    mi το i-οστό byte αυτού του μηνύματος, και [mi]j το j-οστό bit 
    αυτού του i-οστού byte 
    */
    int I_char = m[n / 8];//take specific char from the binary string 
    int bit = I_char % 2;
    int J_char=(7 - (n % 8));
    I_char /= 2;
    int i;
    for (i = 0; i < J_char; i++)
    {
        bit = I_char % 2;
        I_char /= 2;
    }
    return bit; //returns the bit that was requested 
}

void binaryToText(char *binary, int binaryLength, char *text, int symbolCount)
{
    int i;
    for (i = 0; i < binaryLength; i += 8, binary += 8)
    {
        char *byte = binary;//breaks the binary string to 8s 
        byte[8] = '\0';
        *text++ = binaryToDecimal(byte, 8);//converts binary to decimal 
    }
    text -= symbolCount;//counts how many characters are left to be converted 
}

unsigned long binaryToDecimal(char *binary, int length)
{

    unsigned long decimal = 0, pow_2 = 1;//for the binary calculation
    binary += length - 1;                //128,64,32,16,8,4,2,1
    int i;
    for (i = 0; i < length; ++i, --binary)
    {
        if (*binary == '1')
            decimal += pow_2;// sums up 128,64,32,16,8,4,2,1 those numbers to take
                             //the corresponding number to that binary
        pow_2 *= 2;//goes to the next power 
    }
    return decimal;//returns converted binary to its decimal number
}

/**
 * gcc -DDSteno -o testSten StenographyFuncs.c
 * ./testSten 
 */
#ifdef DSteno
int main(int argc, char *argv[])
{  
unsigned int system=100;
   int* premut=createPermutationFunction(12563261,system);
   printf("Premutation : %d\n",premut[0]);

   int b=getBit("hi",1);
   printf("Bit : %d\n",b);

   char *bin="01110100011001010111001101110100011010010110111001100111";
   char *text=(char* )malloc(8);
    binaryToText(bin,56,text,7);
    text[8]='\0';
     printf("%s\n",text);
   return 0;
}
#endif