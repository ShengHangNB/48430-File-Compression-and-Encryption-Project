/*******************************************************************************
author     : Hang Sheng
date       : 07/02/2021

description:
This function can decompress the text file by using the Huffman coding 
algorithm. 
*******************************************************************************/

/*******************************************************************************
Header Files
*******************************************************************************/

#include "project_utils.h"
#include<stdio.h> /* printf,scanf,fopen,fclose, fscanf , fprintf */ 
#include<stdlib.h> /* malloc, free */

/*******************************************************************************
Preprocessing directives 
*******************************************************************************/

#define INPUT_FILENAME "HFT_Model"
#define OUTPUT_FILENAME "HFT_Decompression.txt"
#define FILE_SIZE 100
#define HUFFMAN_CODE_SIZE 10000
#define LINE_BUFFER_SIZE 100
#define STR_SIZE 2000

/*******************************************************************************
 struct design
*******************************************************************************/

struct node
{
    char value;
    int weight;
    int parent;
    int left;
    int right;
    int value_to_ASCII;
};
typedef struct node node_t;

/*******************************************************************************
 Function prototypes (Description is in the function implementation)
*******************************************************************************/

int read_code_size(char filename[]);

void read_HuffmanCode(char filename[], int received_array[], int code_size);

int read_tree_size(char filename[]);

void read_HuffmanTree(char filename[], node_t received_huffman_tree[], 
                                                            int tree_length);

int decode(const node_t huffman_tree[], int tree_size, 
           const int huffman_codes[], int code_length, char received_str[]);

void save_decoded_info(char filename[], const char received_str[], 
                                                               int str_size);

/*******************************************************************************
 This function is the main process to achieve decompression
*******************************************************************************/
void decompress_file2()
{

    printf("Please enter the file you want to decompress: ");
    char file_to_decompress[FILE_SIZE];
    scanf("%[^\n]s", file_to_decompress); 
    printf("\n");

    /* Read the Huffman codes size */
    int code_size = read_code_size(file_to_decompress);
    if(code_size == -1)
    {
        printf("Sorry, invalid Huffman Code detected, "
               "please check your input file again \n");
        return;
    }

    /* Read the Huffman codes and store the codes in an integer array */
    printf("Reading the Huffman Codes now...\n");
    int received_huffman_code[HUFFMAN_CODE_SIZE];
    read_HuffmanCode(file_to_decompress, received_huffman_code, code_size);
    printf("Succeed\n");

    printf("Reading the Huffman Tree from 'HFT_Model'...\n");
    /* Read the length of the tree */
    int tree_length = read_tree_size(INPUT_FILENAME);

    /* Create the Huffman tree by dynamic allocation, because the tree size
       is decided during the runtime of the program */
    node_t* received_huffman_tree;
    received_huffman_tree = (node_t*) malloc(tree_length * sizeof(node_t));
    if(received_huffman_tree == NULL){
        printf("Allocation failed.\n");
        return;
    }

    /* Read the data for the input file "HFT_Model" and store each node
       of the Huffman tree into the "received_huffman_tree" array */
    read_HuffmanTree(INPUT_FILENAME,received_huffman_tree, tree_length);
    printf("Succeed\n\n");

    /* decode the Huffman codes, store the decompressed characters into 
       the "received_str array" and record the size of this string */
    printf("Decompressing now:\n");
    char received_str[STR_SIZE];
    int actual_str_size = decode(received_huffman_tree,tree_length, 
                          received_huffman_code, code_size, received_str);

    printf("\n");

    /* Output the decompressed result */
    printf("Saving the decompressed infromation into" 
           "'HFT_Decompression.txt' \n");
    save_decoded_info(OUTPUT_FILENAME, received_str, actual_str_size);
    printf("Succeed\n");

    /* Release memory of the dynamic allocationnd and make the pointer 
       point to NULL */
    free(received_huffman_tree);
    received_huffman_tree = NULL;
}

/*******************************************************************************
 This function reads the file and return the codes size.
 input:
    filename: the input filename
 ouput:
    size: the length of the Huffman Codes in the file
*******************************************************************************/
int read_code_size(char filename[])
{
    FILE * fp = NULL;
    fp = fopen(filename, "r");
    if(fp == NULL)
    {
        printf("Error: Can't open the file\n");
        exit(0);
    }
    
    int size = 0;
    char ch = fgetc(fp);
    while (ch != EOF) {
        /* if the character in the text file is not 0 or 1 it means
         the contents in this file are not the Huffman Codes*/
        if(ch != '0' && ch != '1') return -1;
        size++;
        ch = fgetc(fp);
    }

    fclose(fp);
    return size;
}


/*******************************************************************************
 This function reads the file and stores the codes 
 into an integer array.
 input:
    filename: the input filename
    received_array: the integer array to store the bit number of the Huffman 
                    Codes.
    code_size: the length of the Huffman Codes in the file.
*******************************************************************************/
void read_HuffmanCode(char filename[], int received_array[], int code_size)
{
    FILE * fp = NULL;
    fp = fopen(filename, "r");
    if(fp == NULL)
    {
        printf("Error: Can't open the file\n");
        return;
    }
    
    int i;
    for(i = 0; i < code_size; i++){
        fscanf(fp, "%1d", &received_array[i]);
    }
    fclose(fp);
}


/*******************************************************************************
 This function reads the "HFT_Model" file and return the line count of this 
 file.
 input:
    filename: the input filename
 ouput:
    tree_size: the number of nodes in the Huffman Tree
 post:
    each line in the "HFT_Model" file is the information of each node, 
    so the line count of the file is actually the Huffman tree size.
*******************************************************************************/

int read_tree_size(char filename[])
{
    FILE * fp = NULL;
    fp = fopen(filename, "r");
    if(fp == NULL)
    {
        printf("Error: Can't open the file\n");
        return -1;
    }

    char line_buffer[LINE_BUFFER_SIZE];
    int tree_size = 0;

	while(fgets(line_buffer, LINE_BUFFER_SIZE, fp)) tree_size++;
    
    fclose(fp);
    return tree_size;
}


/*******************************************************************************
 This function reads the "HFT_Model" file and stores the node information 
 into an array.
 with node_t type.
 input:
    filename: the input filename
    received_huffman_tree: the array to store the Huffman tree node information
    tree_length: the number of nodes in the Huffman Tree
*******************************************************************************/

void read_HuffmanTree(char filename[], node_t received_huffman_tree[], 
                                                        int tree_length)
{
    FILE * fp = NULL;
    fp = fopen(filename, "r");
    if(fp == NULL)
    {
        printf("Error: Can't open the file\n");
        return;
    }

    int i;
    for(i = 0 ;i < tree_length; i++)
    {
		    fscanf(fp, "%d %d %d %d %d", 
					&received_huffman_tree[i].weight, 
					&received_huffman_tree[i].parent, 
					&received_huffman_tree[i].left, 
					&received_huffman_tree[i].right,
                    &received_huffman_tree[i].value_to_ASCII);
    }
    fclose(fp);
}


/*******************************************************************************
 This function decodes the Huffman codes according to the Huffman Tree, and 
 store the decoded char into the "received_str" array.

 input:
    huffman_tree: the array to store the Huffman tree node information
    tree_size: the number of nodes in the Huffman Tree
    huffman_codes: the integer array to store the bit number of the Huffman
                   Codes.
    code_length: the length of the Huffman Codes in the "Huffman_codes" file
    received_str: the char array to store the decoded information.
 ouput:
    str_size: size of the decoded information.
*******************************************************************************/

int decode(const node_t huffman_tree[], int tree_size, 
           const int huffman_codes[], int code_length, char received_str[])
{
    int str_size = 0;

    /* i is the index of the "huffman_codes" integer array */
    int i = 0;

    /* For each bit number in the Huffman Codes, traverse the 
       Huffman tree from top to bottom */
    int parent = tree_size - 1;
    while(i < code_length){
        /* Traverse the Huffman tree until reaching the leaf node */
        while(huffman_tree[parent].left != -1 || 
              huffman_tree[parent].right != -1)
        {
            /* Turn to the left children if the Huffman code is 0 */
            if(huffman_codes[i] == 0)
            {
                parent = huffman_tree[parent].left;
                i++;
            }
            /* Turn to the right children if the Huffman code is 1 */
            else if(huffman_codes[i] == 1)
            {
                parent = huffman_tree[parent].right;
                i++;
            }
        }

        /* Store the ASCII of the value in the leaf node to the 
           "received_str" char array */
        received_str[str_size++] = huffman_tree[parent].value_to_ASCII;

        /* print the decoded character into the terminal */
        printf("%c",huffman_tree[parent].value_to_ASCII); 

        /* Reset the parent to the root to traverse the tree again */
        parent = tree_size - 1;

    }

    return str_size;
}

/*******************************************************************************
 This function exports the decoded information into the "HFT_Decompression.txt" 
 file.
 input:
    filename: the ouput filename
    received_str: the char array to store the decoded information.
    tree_size: the number of nodes in the Huffman Tree
*******************************************************************************/

void save_decoded_info(char filename[], const char received_str[], 
                                                            int str_size)
{
	FILE * fp = NULL;
    fp = fopen(filename, "w");
    if(fp == NULL)
    {
        printf("Error: Can't open the file\n");
		return;
    }

	int i;
	for(i = 0; i < str_size; i++){
		fprintf(fp, "%c", received_str[i]);
	}
	
	fclose(fp);
}

