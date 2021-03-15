/*******************************************************************************
author     :Longhao Zhu, Hang Sheng
date       :07/02/2021

description:
This function can be used to sort users. In this job, 
we sort users by account balance. Of course, 
it can also be sorted by other variables with simply change a few variables.
*******************************************************************************/

#include "project_utils.h"

#include <stdio.h>/*printf,scanf,fopen,fclose,fgets,fcanf,fprintf*/
#include <string.h>/*memset*/
#include <stdlib.h>/*calloc*/

#define MAX_FILE_NAME_SIZE 80/*constant-The maximum size of file name*/
#define MAX_NAME_SIZE 20/*constant-The maximum size of name*/
#define MAX_BUF_SIZE 100/*constant-The maximum size of temporary buf*/
  
struct target
{
	char name[MAX_NAME_SIZE];
	int  num;
};
typedef struct target target_t;

void swap1(target_t* a, target_t* b);
void bubbleSort1(target_t* target, int len);
void insertSort1(target_t * target, int len);
void quickSort1(target_t * target, int start, int end);
int partition1(target_t arr[], int start, int end);

void sort_by_user_input()
{
	int i;/*A temporary index*/
	int index = 0;/*To count the number of lines that file have*/
    int choice;/*To sotre the choice of sort*/
	char buf[MAX_BUF_SIZE];/*To temporarily store each line*/
	char fileName[MAX_FILE_NAME_SIZE];/*To store the file name*/
 	target_t target;/*To temporarily store each target*/   

    printf("\n"
			"Please manually create a file by the following instructions:\n"
	 		"1. Create a new file with any filename you like\n"
			"2. No matter how many rows of data are added, it must have"
	        " two columns:\n"
			"   First column -> name attribute \n"
			"   Second column -> Any numerical type attribute, "
	       "Such as age, balance, ID, etc\n"
			"   Separate them by space \n"
			"\n"
		    "For example, you can create a file name 'test.txt' and put" 
		    " these contents into the file:\n"
		    "Bruce 2\n"
		    "Leslie 1\n"
		    "Barry 4\n"
		    "Daisy 3\n"
			"\n"
			"If you have created the file by the instructions above, please"
	        " input the filename to sort its contents -> ");

    scanf("%s",fileName);

	/*Read the file name from user and open it*/
	FILE* p = NULL;
	p = fopen(fileName, "r");
	
	if (p == NULL)
	{
		printf("Open file error\n");
		return;
	}
	else
	{
		while (!feof(p))
		/* A simple while loop to get the number of line of the files*/
		{
			fgets(buf, sizeof(buf), p);
			memset(buf, 0, sizeof(buf));
			index++;
		}
		fclose(p);
	}

	target_t* array = calloc(sizeof(target_t), index);
	/*Create a dynamic array with the same number of lines as the file*/

	p = fopen(fileName, "r");
	index = 0;
	/*Set the index to 0 again and use it as the index of dynamic array*/
	if (p == NULL)
	{
		printf("error\n");
		return;
	}
	else
	{
		while(feof(p)==0)/*If not reach the end of the file */
		{
			fscanf(p,"%s %d \n",
			target.name,
			&target.num);
			array[index]=target;
			/*Store the target in the dynamic array*/
			index++;
		}
		 fclose(p);
	}

	printf("\n"
		   "Get ready to sort the 'Customer.txt' by the account balance...\n"
		   "There are three algorithm to sort the file:\n"
		   "1 Bubble sort\n"
		   "2 Insertion sort\n"
		   "3 Quick sort\n"
		   "Please choose one of them -> ");
	scanf("%d",&choice);

	switch(choice){
		case 1: bubbleSort1(array,index); break; 
		case 2: insertSort1(array, index); break;
		case 3: quickSort1(array, 0 , index - 1);  break; 
		default: printf("Input error!"); return;
	} 

    printf("Saving the sorted infromation into" 
           "'Sorted_file.txt' \n");
	FILE* p1=NULL;
	p1 = fopen("Sorted_file.txt", "w");

	for (i = 0; i < index; i++) {
		fprintf(p1,"%s ",array[i].name);
		fprintf(p1,"%d \n",array[i].num);
		/*Store the array which is after sorted into the file*/
	}
	fclose(p1);
	printf("Sort successfully!\n");
}
/*******************************************************************************
 * This function is used to exchange the values ​​between two variables
 * inputs:
 * - a:A target
 * - b:B target
*******************************************************************************/
void swap1(target_t* a, target_t* b)
{
	target_t temp = *a;
	*a = *b;
	*b = temp;
}

/*******************************************************************************
 * This function uses bubble sort to sort target
 * according to the user input number
 * inputs:
 * - customer:The array of the target
 * - n:The length of the array
*******************************************************************************/
void bubbleSort1(target_t* target, int len)
{
	int i, j;
	for (i = 0; i < len; i++)
	{
		for (j = 1; j < len - i; j++)
		{
			if (target[j - 1].num > target[j].num)
			{
				swap1(&target[j - 1] , &target[j]);
			}
		}
	}
}
/*******************************************************************************
 * This function is used to sort users according to their account balance
 * inputs:
 * - target:The array of the customer
 * - len:The length of the array
*******************************************************************************/
void insertSort1(target_t * target, int len)
{
	int i, j;
	int temp;/*To store the number that needs to be compare*/
	target_t tempTar;/*To store the entire target message*/
 
	for(i = 1; i < len; i ++)
	{
		temp = target[i].num;
		tempTar=target[i];
		for(j = i - 1; j >= 0; j --)
		{
			if(target[j].num > temp)
			/*Compare the number of target*/
			{
				target[j + 1] = target[j];
				/*If the number larger than temp number,
				then the target in the array will shift right*/	
			}else
			{
				break;
			}
		}
		target[j + 1] = tempTar;
		/*The number that larger than temp is all go to the right
		side of the tempTar,then we can store the tempTar directly 
		on the left side */
	}
}

/*******************************************************************************
 * This function uses quick sort to sort target
 * inputs:
 * - target:The array of the customer
 * - start: first index of the array
 * - end: last index of the array 
*******************************************************************************/
void quickSort1(target_t * target, int start, int end)
{
	if(start > end) return;
	/* Get the benchmark to spilt the array to two parts,
	   so that every elements in the right side of the benchmark are higher
	   than the benchmark, every elements in the left side  of the benchmark 
	   are lower than the benchmark. */
	int benchmark = partition1(target, start, end);

	/* Recursively sort two parts of the array mentioned above */
	quickSort1(target, start, benchmark - 1);
	quickSort1(target, benchmark + 1, end);
}

/*******************************************************************************
 * This function is the helper function of quick sort algorithm
 * inputs:
 * - target:The array of the customer
 * - start: first index of the array
 * - end: last index of the array 
*******************************************************************************/
int partition1(target_t arr[], int start, int end)
{
	/* Get the first element of the array, regard it as the pivot */
	target_t pivot = arr[start];

	/* Define the dynamic left pointer and right pointer */
	int left = start;
	int right = end;

	/* Before the left pointer and right pointer meets */
	while(left != right)
	{
		/* Get the index of first element that is lower than the 
		pivot's "num" */
		while(arr[right].num  >= pivot.num && left < right ) right--;
		/* Get the index of first element that is higher than the 
		pivot's "num" */
		while(arr[left].num <= pivot.num && left < right ) left++;

		/* swap the two elements mentioned above */
		if(left < right)
		{
			target_t temp = arr[left];
			arr[left] = arr[right];
			arr[right] = temp;
		}
	}

	/* Indirectly swap the value of the current left pointer position 
	   and the pivot(first elemtn in the array), to make sure every element
	   in the right side are higher than the pivot, every elemtent in the 
	   left side are lower than the pivot */
	arr[start] = arr[left];
	arr[left] = pivot;

	/* Return  the position of the left pointer as the split point 
	   of the array for the next round sort */
	return left;
}


