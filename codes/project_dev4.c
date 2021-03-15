/*******************************************************************************
author     : Longhao Zhu
date       : 07/02/2021

description:
This function is used to decrypt files encrypted by XOR, the user needs to enter 
the correct key to get the correct information
*******************************************************************************/

#include "project_utils.h"
#include<stdio.h>/*printf,scanf,fopen,fclose,fgetc*/

int checkKey(int key);

#define OUTPUT_FILENAME "XOR_Decryption.txt"/* constant-output file name*/
#define MAX_NAME_SIZE 80/*constant-The maximum size of name*/

void decrypt_file1()
{
    FILE *f1=NULL;
    FILE *f2=NULL;

    int decryption,key;
    /*decryption-to temporarily store the  XOR result
    key- to store the user input key*/
    char c;/*To store the char of file*/
    char name[MAX_NAME_SIZE];/*To store the file name*/
    
    printf("Input the name of file you want to decrypt ->");
    scanf("%s",name);
    
    /*Get the file name from the user 
    and input to the function to open the file*/

    f1 = fopen(name, "r");
    if( f1 == NULL) {/*If the file not exist*/
        printf("Open file failed!\n");
        return;
    }

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
    while((c = fgetc(f1)) != EOF)/*Use XOR to each char*/
    {
        decryption=c ^ key;
        fprintf(f2,"%c",decryption);        
    }

    fclose(f2);
    fclose(f1);
    printf("The file is decrypted!\n");
}

