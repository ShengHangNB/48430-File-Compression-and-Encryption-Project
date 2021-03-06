/*******************************************************************************
author     : Liam Jiang, Hang Sheng
date       : 03/02/2021

description:
This funciton can decrypt the text file by using the Caesar cipher method.
This is a simple algorithm that is mainly used to decrypt strings that have
been encrypted using the Caesar Cipher method

*******************************************************************************/
#include "project_utils.h"
#include<stdio.h>/*printf,scanf,fopen,fclose,fgetc*/
#include<stdlib.h>/*abs*/

#define OUTPUT_FILENAME "Caesar_Decryption.txt"/* constant-output file name*/
#define MAX_LENGTH 256

char decrypt(char ch_to_decrypt ,int key, char benchmark, int scale);
int checkKey(int key);
int negative_mod(int act_dis, int scale);

void decrypt_file2()
{
    FILE *f1, *f2;
    char name[MAX_LENGTH];
    char ch;
    int key;

    printf("Input the name of file you want to decrypt ->");
    scanf("%s",name);
    
    /*Get the file name from the user 
    and input to the function to open the file*/

    f1 = fopen(name, "r");
    
    if( f1 == NULL) {/*If the file not exist*/
    printf("Open file1 failed!\n");
    return;
    }
    /*ask user to input key*/
    printf("Input the key without 0 and consists of only 6 numbers：");
    scanf("%d",&key);
    getchar();/*To avoid user input a char to break the program*/
    while((checkKey(key)==0))
    {
        printf("Please try another key without 0 and only contains numbers\n");
        printf("Input the key：");
        scanf("%d",&key);
        getchar();
    }
    
    f2 = fopen(OUTPUT_FILENAME, "w");

    char decryption;
    /*decrypt characters after opening file*/
    while((ch = fgetc(f1)) != EOF)
    {   
        if(ch>='a' && ch<='z')
        {
            decryption = decrypt(ch, key, 'a', 26);
            fprintf(f2,"%c",decryption); 
        }
        else if(ch >='A'&& ch <='Z')
        {
            decryption = decrypt(ch, key, 'A', 26);
            fprintf(f2,"%c",decryption); 
        }

        else if(ch>='0'&& ch<='9')
        {
            decryption = decrypt(ch, key, '0', 10);
            fprintf(f2,"%c",decryption);         
        }
        else
        {
            fprintf(f2,"%c",ch);
        }
    }
    printf("File successfully decrypted!\n");
    fclose(f1);
    fclose(f2);
}

/*******************************************************************************
 This function can decrypt the character
 input:
    ch_to_decrypt: the character to be encrypted
    key: the key used to encrypt the character
    benchmark: to mark what range the input character should be located
    scale: range size
 output:
    decryption: decrypted character
 post:
    The benchmark will be different based on the input character.
    If the input character is 'c', then the benchmark should be 'a', so that 
    the position of the character'c' in the 26 alphabet can be calculated 
    separately. If the input character is '5', then the benchmark should be 
    '0', so that the position of the character'5' in the range [0~9] can be 
    calculated separately.
*******************************************************************************/
char decrypt(char ch_to_decrypt ,int key, char benchmark, int scale)
{
    /* The position within the scale */
    int position = ch_to_decrypt - benchmark;

    /* Actual displacement */
    int act_dis = position + (scale - key);

    /* Displacement within the scale */
    int scale_dis;
    if(act_dis >= 0) scale_dis = act_dis % scale;
    else if(act_dis < 0) scale_dis = negative_mod(act_dis, scale);
    
    /* Move the character based on the benchmark to make decryption ,
       the integer will be automatically converted into the char with 
       the corresponding ASCII number */
    char decryption  =  benchmark + scale_dis;

    return decryption;
}

/*******************************************************************************
 This function can calculate the mod of a negative number
 input:
    act_dis: a negative number
    scale: range size 
 output:
    mod of the negative number
*******************************************************************************/
int negative_mod(int act_dis, int scale)
{
    /* Calculate the mod of act_dis's absolute value first */
    int abs_mod = abs(act_dis) % scale;

    /* Use the mod of act_dis's absolute value to get the negative mode value */
    int scale_dis = (scale - abs_mod) % scale;

    return scale_dis;
}


