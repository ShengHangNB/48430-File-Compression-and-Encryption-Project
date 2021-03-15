/*******************************************************************************
author     : Longhao Zhu
date       : 07/02/2021

description:
This function uses the XOR encryption algorithm, 
the user can enter the key to encrypt the file
*******************************************************************************/

#include "project_utils.h"
#include<stdio.h>/*printf,scanf,fopen,fclose,fgetc*/

int checkKey(int key);

#define OUTPUT_FILENAME "XOR_Encryption.txt"/* constant-output file name*/
#define MAX_NAME_SIZE 80/*constant-The maximum size of name*/

void encrypt_file1()
{
    FILE *f1=NULL;
    FILE *f2=NULL;
    int encryption,key;
    /*encryption-to temporarily store the XOR result
    key- to store the user input key*/
    char c;/*To store the char of file*/
    char name[MAX_NAME_SIZE];/*To store the file name*/
    
    printf("Input the name of file you want to encrypt: ");
    scanf("%s",name);
    
    /*Get the file name from the user 
    and input to the function to open the file*/

    f1 = fopen(name, "r");
    if( f1 == NULL) {/*If the file not exist*/
        printf("Open file failed!\n");
        return;
    }

    printf("Input the key without 0 and consists of only 6 numbers：");
    /*Ask user for the key*/
    scanf("%d",&key);
    getchar();
    while((checkKey(key)==0))
    {
        printf("Please try another key without 0 and consists of only 6 numbers\n");
        printf("Input the key：");
        scanf("%d",&key);
        getchar();
    }
    

    f2 = fopen(OUTPUT_FILENAME, "w");

    while((c = fgetc(f1)) != EOF)/*Use XOR to each char*/
    {
        encryption=c ^ key;
        fprintf(f2,"%c",encryption);        
    }

    fclose(f2);
    fclose(f1);
    printf("The file is encrypted!\n");
}
/*******************************************************************************
 * This function is used to confirm whether the password entered 
 by the user contains 0 or more than six digits. 
 When these two situations occur, 
 the compression function may not work well on encrypted files, 
 so we hope to avoid this situation
 * inputs:
 * - key：The key that input by user;
 * outputs:
 * - 0-The key is not satisfied;
 * - 1-The key can be used;
*******************************************************************************/
int checkKey(int key){
    if(key<100000 || key>999999)
    {
        return 0;
    }    
    while(key!=0)
    {
        if(key % 10==0)
        {
            return 0;
        }
        else
        {
            key = key/10;
        }
    }
    return 1;
}
