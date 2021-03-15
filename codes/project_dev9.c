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

#define INPUT_FILE_NAME "Customer.txt" /*Initial database */
#define MAX_NAME_SIZE 20/*constant-The maximum size of customer name*/
#define GENDER_SIZE 7/*constant-The maximum size of gender*/
#define ACCOUNT_TYPE_SIZE 7/*constant-The maximum size of account type*/
#define ANNUAL_INCOME_SIZE 6/*constant-The maximum size of annual income*/
#define MAX_BUF_SIZE 100/*constant-The maximum size of temporary buf*/

struct customer
{
    int ID;
	char name[MAX_NAME_SIZE];
    char gender[GENDER_SIZE];
    char account_type[ACCOUNT_TYPE_SIZE];
	int balance;
	char annual_income[ANNUAL_INCOME_SIZE];
};
typedef struct customer customer_t;

void swap(customer_t* a, customer_t* b);
void bubbleSort(customer_t* customer, int len);
void insertSort(customer_t * customer, int len);
void quickSort(customer_t * target, int start, int end);
int partition(customer_t arr[], int start, int end);

void sort_original_database()
{
	int i;/*A temporary index*/
	int index = 0;/*To count the number of lines that file have*/
	int choice;/*To sotre the choice of sort*/
	char buf[MAX_BUF_SIZE];/*To temporarily store each line*/
 	customer_t customer;/*To temporarily store each customer*/   
    
	/*Read the file name from user and open it*/
	FILE* p = NULL;
	p = fopen(INPUT_FILE_NAME, "r");
	
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

	customer_t* array = calloc(sizeof(customer_t), index);
	/*Create a dynamic array with the same number of lines as the file*/

	 p = fopen(INPUT_FILE_NAME, "r");
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
			fscanf(p,"%d %s %s %s %d %s\n",
			&customer.ID,
			customer.name,
			customer.gender,
			customer.account_type,				
			&customer.balance,
			customer.annual_income);
			array[index]=customer;
			/*Store the customer in the dynamic array*/
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
		case 1: bubbleSort(array,index); break; 
		case 2: insertSort(array, index); break;
		case 3: quickSort(array, 0 , index - 1);  break; 
		default: printf("Input error!"); return;
	} 


	FILE* p1=NULL;
    printf("Saving the sorted infromation into" 
           "'Sorted_file.txt' \n");
	p1 = fopen("Sorted_file.txt", "w");

	for (i = 0; i < index; i++) {
		fprintf(p1,"%d ",array[i].ID);
		fprintf(p1,"%s ",array[i].name);
		fprintf(p1,"%s ",array[i].gender);
		fprintf(p1,"%s ",array[i].account_type);
		fprintf(p1,"%d ",array[i].balance);
		fprintf(p1,"%s\n",array[i].annual_income);
		/*Store the array which is after sorted into the file*/
	}
	fclose(p1);

	printf("Sort successfully!\n");
}

/*******************************************************************************
 * This function is used to exchange the values ​​between two variables
 * inputs:
 * - a:A customer
 * - b:B customer
*******************************************************************************/
void swap(customer_t* a, customer_t* b)
{
	customer_t temp = *a;
	*a = *b;
	*b = temp;
}

/*******************************************************************************
 * This function is use bubble sort to sort customer 
 * according to their account balance
 * inputs:
 * - customer:The array of the customer
 * - n:The length of the array
*******************************************************************************/
void bubbleSort(customer_t* customer, int len)
{
	int i, j;
	for (i = 0; i < len; i++)
	{
		for (j = 1; j < len - i; j++)
		{
			if (customer[j - 1].balance > customer[j].balance)
			{
				swap(&customer[j - 1] , &customer[j]);
			}
		}
	}
}
/*******************************************************************************
 * This function is use insertion sort to sort customer 
 * according to their account balance
 * inputs:
 * - customer:The array of the customer
 * - len:The length of the array
*******************************************************************************/
void insertSort(customer_t * customer, int len)
{
	int i, j;
	int temp;/*To store the number that needs to be compare*/
	customer_t tempCus;/*To store the entire one customer message*/
 
	for(i = 1; i < len; i ++)
	{
		temp = customer[i].balance;
		tempCus=customer[i];
		for(j = i - 1; j >= 0; j --)
		{
			if(customer[j].balance > temp)
			/*Compare the account balance of customer*/
			{
				customer[j + 1] = customer[j];
				/*If the number larger than temp number,
				then the customer in the array will shift right*/	
			}else
			{
				break;
			}
		}
		customer[j + 1] = tempCus;
		/*The number that larger than temp is all go to the right
		side of the tempCus,then we can store the tempCus directly 
		on the left side of that customer*/
	}
}

/*******************************************************************************
 * This function uses quick sort to sort target
 * inputs:
 * - target:The array of the customer
 * - start: first index of the array
 * - end: last index of the array 
*******************************************************************************/
void quickSort(customer_t * customer, int start, int end)
{
	if(start > end) return;
	/* Get the benchmark to spilt the array to two parts,
	   so that every elements in the right side of the benchmark are higher
	   than the benchmark, every elements in the left side  of the benchmark 
	   are lower than the benchmark. */
	int benchmark = partition(customer, start, end);

	/* Recursively sort two parts of the array mentioned above */
	quickSort(customer, start, benchmark - 1);
	quickSort(customer, benchmark + 1, end);
}

/*******************************************************************************
 * This function is the helper function of quick sort algorithm
 * inputs:
 * - target:The array of the customer
 * - start: first index of the array
 * - end: last index of the array 
*******************************************************************************/
int partition(customer_t arr[], int start, int end)
{
	/* Get the first element of the array, regard it as the pivot */
	customer_t pivot = arr[start];

	/* Define the dynamic left pointer and right pointer */
	int left = start;
	int right = end;

	/* Before the left pointer and right pointer meets */
	while(left != right)
	{
		/* Get the index of first element that is lower than 
		the pivot's "balance" */
		while(arr[right].balance  >= pivot.balance && left < right ) right--;
		
		/* Get the index of first element that is higher than 
		the pivot's "balance" */
		while(arr[left].balance <= pivot.balance && left < right ) left++;

		/* swap the two elements mentioned above */
		if(left < right)
		{
			customer_t temp = arr[left];
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

