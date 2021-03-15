/*******************************************************************************
author     : Hang Sheng
date       : 08/02/2021

description:
This function can look for a specific keyword or column within an encrypted 
and compressed file.
*******************************************************************************/

/*******************************************************************************
Header Files
*******************************************************************************/
#include "project_utils.h"
#include <stdio.h> /* scanf, printf, */
#include <stdlib.h> /* malloc, free */
#include<string.h> /* strtok, strcpy, strlen */

/*******************************************************************************
Preprocessing directives 
*******************************************************************************/

#define ENCRYPTION_FILENAME1 "Caesar_Encryption.txt"
#define ENCRYPTION_FILENAME2 "XOR_Encryption.txt"
#define HUFFMAN_FILENAME "HFT_Model"
#define HUFFMAN_CODES "Huffman_Codes.txt"
#define LINE_BUFFER_SIZE 100
#define HUFFMAN_CODE_SIZE 10000
#define STR_SIZE 2000
#define KEY_WORD_SIZE 20

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
 Function prototypes
*******************************************************************************/

void convert_lowercase(char str[], char converted_str[], int length);

/* This function has been implemented in the "project_dev3.c" file */
int checkKey(int key);

int Caesar_decrypt(char filename[], int received_huffman_code[], int key);

int XOR_decrypt(char filename[], int received_huffman_code[], int key);

/* This function has been implemented in the "project_dev6.c" file */
char decrypt(char ch_to_decrypt ,int key, char benchmark, int scale);

/* This function has been implemented in the "project_dev2.c" file */
int read_code_size(char filename[]);

/* This function has been implemented in the "project_dev2.c" file */
void read_HuffmanCode(char filename[], int received_array[], int code_size);

/* This function has been implemented in the "project_dev2.c" file */
int read_tree_size(char filename[]);

/* This function has been implemented in the "project_dev2.c" file */
void read_HuffmanTree(char filename[], node_t received_huffman_tree[], 
                                                            int tree_length);

void temp_decompress(const node_t huffman_tree[], int tree_size, 
           const int huffman_codes[], int code_length, char received_str[]);

/*******************************************************************************
 This function is the main process to search the word in the compressed and
 encrypted file.
*******************************************************************************/
void search_keyword()
{
    int key;
    char temp;
    int choice;
    int inner_choice;
    int received_huffman_code[HUFFMAN_CODE_SIZE];
    int code_size = 0;
    int tree_length;
    char received_str[STR_SIZE];

    printf("\n");
    printf("Could you please tell me the order you process the files?\n"
           "1. Compress and then encrypt\n"
           "2. Encrypt and then compress\n"
           "If you want to back to the menu, please type -1\n"
           "\n"
           "Please enter your your choice > ");

    scanf("%d",&choice);
    scanf("%c",&temp);
    switch(choice)
    {
        /* Decrypt and then decompress */
        case 1:
        {
            printf("What level of security did you use to"
                   "encrypt the file?\n"
                   "1. High security\n"
                   "2. Low security\n"
                   "If you want to back to the menu, please type -1\n"
                   "\n"
                   "Please enter your your choice > ");

            scanf("%d",&inner_choice);
            scanf("%c",&temp);
            switch(inner_choice)
            {
                case 1:
                {
                    printf("Input the key without 0 and consists of"
                           " only 6 numbers：");
                    scanf("%d",&key);
                    getchar();
                    while((checkKey(key)==0))
                    {
                        printf("Please try another key without 0 and"
                               " consists of only 6 numbers\n");
                        printf("Input the key：");
                        scanf("%d",&key);
                        getchar();
                    }
                    /* Get the decrypted Huffman Codes and its size */
                    code_size = Caesar_decrypt(ENCRYPTION_FILENAME1, 
                                            received_huffman_code , key);
                    break;
                }
                case 2:
                {
                    printf("Input the key without 0 and consists of"
                           " only 6 numbers：");
                    scanf("%d",&key);
                    getchar();
                    while((checkKey(key)==0))
                    {
                        printf("Please try another key without 0 and"
                               " consists of only 6 numbers\n");
                        printf("Input the key：");
                        scanf("%d",&key);
                        getchar();
                    }
                    code_size = XOR_decrypt(ENCRYPTION_FILENAME2, 
                                            received_huffman_code , key);
                    break;
                }
                default: printf("Invalid Input\n"); return;
            }

            /* Read the length of the tree */
            tree_length = read_tree_size(HUFFMAN_FILENAME);

            /* Create the Huffman tree by dynamic allocation, because 
            the tree size is decided during the runtime of the program */
            node_t* received_huffman_tree;
            received_huffman_tree=(node_t*)malloc(tree_length*sizeof(node_t));
            if(received_huffman_tree == NULL){
                printf("Allocation failed.\n");
                return;
            }

            /* Read the data for the input file "HFT_Model" and store each node
            of the Huffman tree into the "received_huffman_tree" array */
            read_HuffmanTree(HUFFMAN_FILENAME,
                                        received_huffman_tree, tree_length);

            /* decode the Huffman codes, store the decompressed characters into 
            the "received_str" array and record the size of this string */
            temp_decompress(received_huffman_tree,tree_length, 
                            received_huffman_code, code_size, received_str);

            /* Release memory of the dynamic allocationnd and make the pointer 
            point to NULL */
            free(received_huffman_tree);
            received_huffman_tree = NULL;
            break;
        }

        /* Decompress and then decrypt */
        case 2:
        {
            /* Read the Huffman codes size */
            code_size = read_code_size(HUFFMAN_CODES);

            /* Read the Huffman codes and store the codes 
               in an integer array */
            read_HuffmanCode(HUFFMAN_CODES, 
                                        received_huffman_code, code_size);
            
            /* Read the length of the tree */
            tree_length = read_tree_size(HUFFMAN_FILENAME);

            /* Create the Huffman tree by dynamic allocation, because 
            the tree size is decided during the runtime of the program */
            node_t* received_huffman_tree;
            received_huffman_tree=(node_t*)malloc(tree_length*sizeof(node_t));
            if(received_huffman_tree == NULL){
                printf("Allocation failed.\n");
                return;
            }

            /* Read the data for the input file "HFT_Model" and store each node
            of the Huffman tree into the "received_huffman_tree" array */
            read_HuffmanTree(HUFFMAN_FILENAME,
                                        received_huffman_tree, tree_length);

            char temp_received_str[STR_SIZE];
            temp_decompress(received_huffman_tree,tree_length, 
                            received_huffman_code, code_size, 
                            temp_received_str);

            free(received_huffman_tree);
            received_huffman_tree = NULL;

            printf("What level of security did you use to"
                   "encrypt the file?\n"
                   "1. High security\n"
                   "2. Low security\n"
                   "If you want to back to the menu, please type -1\n"
                   "\n"
                   "Please enter your your choice > ");

            scanf("%d",&inner_choice);
            scanf("%c",&temp);

            switch(inner_choice)
            {
                case 1:
                {
                    printf("Input the key without 0 and consists of"
                           " only 6 numbers：");
                    scanf("%d",&key);
                    getchar();
                    while((checkKey(key)==0))
                    {
                        printf("Please try another key without 0 and"
                               " consists of only 6 numbers\n");
                        printf("Input the key：");
                        scanf("%d",&key);
                        getchar();
                    }
                    int i = 0;
                    int decryption;
                    char ch;
                    while(temp_received_str[i] != '\0')
                    {
                        ch = temp_received_str[i];
                        if(ch>='a' && ch<='z')
                        {
                            decryption = decrypt(ch, key, 'a', 26);
                            received_str[i] = decryption;
                        }
                        else if(ch >='A'&& ch <='Z')
                        {
                            decryption = decrypt(ch, key, 'A', 26);
                            received_str[i] = decryption;
                        }

                        else if(ch>='0'&& ch<='9')
                        {
                            decryption = decrypt(ch, key, '0', 10);
                            received_str[i] = decryption;        
                        }
                        else
                        {
                            received_str[i] = ch;
                        }
                        i++;
                    }
                    received_str[i] = '\0';
                    break;
                }
                case 2:
                {
                    printf("Input the key without 0 and consists of"
                           " only 6 numbers：");
                    scanf("%d",&key);
                    getchar();
                    while((checkKey(key)==0))
                    {
                        printf("Please try another key without 0 and"
                               " consists of only 6 numbers\n");
                        printf("Input the key：");
                        scanf("%d",&key);
                        getchar();
                    }
                   
                    int i = 0;
                    while(temp_received_str[i] != '\0')
                    {
                        received_str[i] = temp_received_str[i] ^ key;
                        i++;
                    }
                    received_str[i] = '\0';

                    break;
                }
                default: printf("Invalid Input\n"); return;
            }

            break;
        }

        default: printf("Invalid Input\n"); return;
    }

    /* Read the key word from the user and convert it to the lowercase */
    char keyword[KEY_WORD_SIZE];
    char converted_keyword[KEY_WORD_SIZE];
    strcpy(converted_keyword, keyword);

    printf("\nDo you want to search a column or (a) row(s)?\n"
           "1. Column by the column number\n"
           "2. Row(s) by the keyword\n"
           "\n"
           "Please enter your your choice > ");
    scanf("%d", &choice);
    scanf("%c",&temp);
    printf("\n");

    int search_choice = 0;
    int inp_column_number = 0;

    switch(choice)
    {
        case 1:
        {
            search_choice = 1;
            printf("Please type the column number that higher "
                   "or equals to 1 > ");
            scanf("%d", &inp_column_number);
            scanf("%c",&temp);
            break;
        }
        case 2:
        {
            search_choice = 2;
            printf("Please enter the word you want to search > ");
            scanf("%[^\n]s", keyword);
            break;
        }
        default: printf("Invalid input\n"); return;
    }
    printf("\n");

    convert_lowercase(keyword, converted_keyword, strlen(keyword));

    /* The flag means whether the keyword you want is in the string */
    int flag = 0;

    /* Use the p to point each token "line by line", the 
      "received_str" has the character "\n" so that I can 
      simulate the process of reading files line by line */
    char* p = NULL;

    /* index of the stirng */
    int index = 0; 

    /* length of each line */
    int length_each_line; 

    /* Actual column number */
    int act_column_number;

    while(received_str[index] != '\0')
    {
        /* Initiate the line string */
        char line_buffer[LINE_BUFFER_SIZE];
        char temp_line[LINE_BUFFER_SIZE];

        /* Initiate the length of each line */
        length_each_line = 0;

        /* Get one line for each inner loop */
        while(received_str[index] != '\n')
        {
            line_buffer[length_each_line] = received_str[index];
            length_each_line++;
            index++;
        }

        /* Manually add '\n' and '\0' to the line_buffer*/
        line_buffer[length_each_line] = '\n';
        line_buffer[length_each_line+1] = '\0';

        /* Add 1 to the index to work for the next inner while loop */
        index++;

        strcpy(temp_line, line_buffer);

        /* Initiate the column number */
        act_column_number = 1;

        /* Compare the token with the keyword one by one */
        p = strtok (line_buffer,", \n");

        while(p != NULL) 
        {
            if(search_choice == 1)
            {
                if(act_column_number == inp_column_number)
                {
                    printf("%s\n", p);
                    flag = 1;
                }
            }

            /* If the keyword is the same as the token, then print
               the result of the stinrg line, which is the information
               of the customer */
            else if(search_choice == 2)
            {
                char temp_word[KEY_WORD_SIZE];
                strcpy(temp_word, p);
                convert_lowercase(p,temp_word, strlen(temp_word));
                if(strcmp(temp_word , converted_keyword) == 0)
                {
                    printf("%s", temp_line);
                    flag = 1;
                    break;
                }
            }

            /* Move to next token */
            p = strtok (NULL,", \n");

            /* Move to next column */
            act_column_number++;
        }
    }

    if(inp_column_number >= act_column_number)
    {
        printf("Sorry, this file has at most %d columns\n", 
                                                act_column_number - 1 );
        return;
    }

    /* If nowhere can find the keyword, which means the key to decrypt the 
       decompressed is not correct, or the keyword is not in the decrypted
       string */
    if(flag == 0)
    {
        printf("Sorry, not results found, please check: \n"
               "1. Whether you have selected the correct order of "
               "file processing or the correct \n"
               "2. Whether you have selected the correct choice of "
               "encryption's level in this feature \n");
    }
}

/*******************************************************************************
 This function convert the input string to the string with all lowercases.
 input:
    str: The input stirng with no limitation 
    converted_str: The converted string whose uppercases have all been changed 
                   into the lowercases
    length: length of the input string
*******************************************************************************/
void convert_lowercase(char str[], char converted_str[], int length)
{
    int i;
	for (i = 0; i < length; i++)
	{
        /* Add 32 for the ASCII number if the character is uppercase */
		if (str[i] >= 'A' && str[i] <= 'Z') 
        {
            converted_str[i] = str[i] + 32;
        }
		else converted_str[i] = str[i];
	}

    /* Manually add the '\0' to the converted_str so that the converted_str 
       can work in "printf" function*/
    converted_str[length] = '\0';
}

/*******************************************************************************
 This function decrypts the files by Caesar algorithm, store the decrypted 
 character one by one in the "received_huffman_code" array and return the size 
 of its array.
 input:
    filename: the file to be decrypted
    received_huffman_code: the integer array to store the bit number of 
                           the decrypted Huffman Codes.
    key: the key to decrypt the characters.
*******************************************************************************/
int Caesar_decrypt(char filename[], int received_huffman_code[], int key)
{
    FILE * fp = NULL;
    fp = fopen(filename, "r");
    if(fp == NULL)
    {
        return -1;
    }

    int size = 0;
    char ch = fgetc(fp);
    char decryption;
    while (ch != EOF) {
        decryption = decrypt(ch, key, '0', 10);
        if(decryption == '0') received_huffman_code[size] = 0;
        else if(decryption == '1') received_huffman_code[size] = 1;
        size++;
        ch = fgetc(fp);
    }

    fclose(fp);
    return size;
}

/*******************************************************************************
 This function decrypts the files by XOR algorithm, store the decrypted 
 character one by one in the "received_huffman_code" array and return the size 
 of its array.
 input:
    filename: the file to be decrypted
    received_huffman_code: the integer array to store the bit number of 
                           the decrypted Huffman Codes.
    key: the key to decrypt the characters.
*******************************************************************************/
int XOR_decrypt(char filename[], int received_huffman_code[], int key)
{
    FILE * fp = NULL;
    fp = fopen(filename, "r");
    if(fp == NULL)
    {
        return -1;
    }

    int size = 0;
    char ch = fgetc(fp);
    char decryption;
    while (ch != EOF) {
        decryption = ch ^ key;
        if(decryption == '0') received_huffman_code[size] = 0;
        else if(decryption == '1') received_huffman_code[size] = 1;
        size++;
        ch = fgetc(fp);
    }

    fclose(fp);
    return size;
}

/*******************************************************************************
 This function is same as the "decode" function in project_dev4.c,the only
 difference is that this function does not have any return values 
********************************************************************************/
void temp_decompress(const node_t huffman_tree[], int tree_size, 
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
            if(huffman_codes[i] == 0){
                parent = huffman_tree[parent].left;
                i++;
            }
            /* Turn to the right children if the Huffman code is 1 */
            else if(huffman_codes[i] == 1){
                parent = huffman_tree[parent].right;
                i++;
            }
        }

        /* Store the ASCII of the value in the leaf node to the 
           "received_str" char array */
        received_str[str_size++] = huffman_tree[parent].value_to_ASCII;

        /* print the decoded character into the terminal */
        /* printf("%c",huffman_tree[parent].value_to_ASCII); */

        /* Reset the parent to the root to traverse the tree again */
        parent = tree_size - 1;
    }

}

