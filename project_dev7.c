/******************************************************************************
author     : Wei Chen
date       : 01/02/2021

description:
This funciton can compress the text file by using the Run Length Encoding 
algorithm.
******************************************************************************/

#include "project_utils.h"
#include<stdio.h>/*scanf, printf, fopen, fclose, fscanf, fprintf*/

#define DB_FILE_NAME "RLE_Compression.txt"
#define FILENAME_SIZE 100
#define PAIR_SIZE 128
#define STR_SIZE 2000

struct pair
{
    char value;
    int count;
};
typedef struct pair pair_t;

int if_Exist(pair_t pairs[], int length, char c);

void compress_file1(void)
{
    char fname[FILENAME_SIZE];

    printf("Please enter the name of file to compress> ");
    scanf("%s", fname);

    FILE* fp1 = NULL;
    fp1 = fopen(fname, "r");
    if(fp1 == NULL)
    {
        printf("Open failed.\n");
        return;
    }

    FILE* fp2 = NULL;
    fp2 = fopen(DB_FILE_NAME, "w");
    if(fp2 == NULL)
    {
        printf("Open failed.\n");
        return;
    }

    pair_t pairs[PAIR_SIZE];
    int i;

    /*Initialise the pairs array*/
    for(i = 0; i < PAIR_SIZE; i++)
    {
        pairs[i].value = ' ';
        pairs[i].count = 0;
    }

    int size = 0;
    char str[STR_SIZE];
    char ch = fgetc(fp1);
    while (ch != EOF) 
    {
        if(ch == '\n')
        {
            ch = fgetc(fp1);
            continue;
        } 
        str[size] = ch;
        size++;
        ch = fgetc(fp1);
    }

    str[size] = '\0';

    int j = 0;
    int index = 0;
    int length = 0;/*Number of elements in pairs array*/
    while(str[j] != '\0'){
        index = if_Exist(pairs, length, str[j]);/*Check current char 
                                            with value in pairs array*/
        if(index != -1)
        {
            pairs[index].count += 1;/*If the char is same as a 
                                        value in pairs array, the 
                                        count of the value increase by 1*/
        }
        else
        {
            pairs[length].value = str[j];/*If the the char is not same as 
                                            each value in pairs array, 
                                            store this char in pairs 
                                            array*/
            pairs[length].count += 1;/*Increase the count of new value by 1*/
            length++;/*Increase number of elements by 1, after 
                    new char is stored in pairs array*/
        }
        j++;
    }

    int k;
    for(k = 0; k < length ; k++)
    {
        if(pairs[k].count == 1)/*If the count of value is 1, only 
                                output the value*/
        {
            fprintf(fp2, "%c", pairs[k].value);
        }
        else
        {
        /*If the count of value is more the 1, output both count and value*/
            fprintf(fp2, "%d%c", pairs[k].count, pairs[k].value);
        }
    }
    printf("\n");
    fclose(fp1);
    fclose(fp2);
}

/******************************************************************************
 Description:
 This function is to check characters in str array that are duplicated in pairs
 array.
 Input:
   pairs[] - array store char and number of each char in file
   length[] - number of elements in pairs array 
   c - current char in str array
 Output>
   i - If the char is same as value in pairs array
   1 - If the char is not duplicate with values in pairs array
******************************************************************************/

int if_Exist(pair_t pairs[], int length, char c)
{
    int i;
    for(i = 0; i < length; i++)
    {
        if(pairs[i].value == c)
        {
            return i;
        }
    }
    return -1;
}


