/*******************************************************************************
author     : Liam Jiang
date       : 03/02/2021

description:
This funciton can encrypt the text file by using the Caesar cipher method.
This is a simple algorithm that is mainly used to encrypt strings, originally
used by Julius Caesar himself. 

*******************************************************************************/

#include "project_utils.h"
#include<stdio.h>/*printf,scanf,fopen,fclose,fgetc*/

#define OUTPUT_FILENAME "Caesar_Encryption.txt"/* constant-output file name*/
#define MAX_LENGTH 256

char encrypt(char ch_to_encrypt ,int key, char benchmark, int scale);
int checkKey(int key);

void encrypt_file2()
{
    FILE *f1, *f2;
    /*char strinp[MAX_LENGTH];*/
    char name[MAX_LENGTH];
    char ch;
    int key;

    printf("Input the name of file you want to encrypt: ");
    scanf("%s",name);

    /*Get the file name from the user 
    and input to the function to open the file*/
    f1 = fopen(name, "r");
    
    if( f1 == NULL) {/*If the file not exist*/
    printf("Open file1 failed!\n");
    return;
    }

    printf("Input the key without 0 and consists of only 6 numbers：");
    scanf("%d",&key);
    getchar();
    while((checkKey(key)==0))
    {
        printf("Please try another key without 0 and only contains numbers\n");
        printf("Input the key：");
        scanf("%d",&key);
        getchar();
    }

    f2 = fopen(OUTPUT_FILENAME, "w");

    char encryption;
    while((ch = fgetc(f1)) != EOF)
    {   

        if(ch>='a' && ch<='z')
        {
            encryption = encrypt(ch, key, 'a', 26);
            fprintf(f2,"%c",encryption);
        }
        else if(ch >='A'&& ch <='Z')
        {
            encryption = encrypt(ch, key, 'A', 26);
            fprintf(f2,"%c",encryption);
        }
        
        else if(ch>='0'&& ch<='9')
        {
            encryption = encrypt(ch, key, '0', 10);
            fprintf(f2,"%c",encryption);
        }

        else{
            fprintf(f2,"%c",ch);
        }
    }

    printf("File successfully encrypted!\n");
    fclose(f1);
    fclose(f2);
}

/*******************************************************************************
 This function can encrypt the character
 input:
    ch_to_encrypt: the character to be encrypted
    key: the key used to encrypt the character
    benchmark: to mark what range the input character should be located
    scale: range size
 output:
    encryption: encrypted character
 post:
    The benchmark will be different based on the input character.
    If the input character is 'c', then the benchmark should be 'a', 
    so that the position of the character'c' in the 26 alphabet can be 
    calculated separately. If the input character is '5', then the benchmark 
    should be '0', so that the  position of the character'5' in the range (0~9) 
    can be calculated separately.
*******************************************************************************/
char encrypt(char ch_to_encrypt ,int key, char benchmark, int scale)
{
    /* The position within the scale */
    int position = ch_to_encrypt - benchmark;

    /* Total displacement */
    int displacement = position  + key;

    /* Limit the displacement within the scale by using mod */
    int scale_dis = displacement % scale;

    /* Move the character based on the benchmark to make encryption 
       the integer will be automatically converted into the char with 
       the corresponding ASCII number */
    char encryption  =  benchmark + scale_dis;

    return encryption;
}


