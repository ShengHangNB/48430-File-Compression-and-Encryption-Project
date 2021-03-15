/*******************************************************************************
author     : Hang Sheng
date       : 07/02/2021

description:
This function can compress the text file by using the Huffman coding algorithm.
*******************************************************************************/

/*******************************************************************************
Header Files
*******************************************************************************/
#include "project_utils.h" 
#include<stdio.h> /* printf,scanf,fopen,fclose, fprintf */ 
#include<stdlib.h> /* malloc, free */

/*******************************************************************************
Preprocessing directives 
*******************************************************************************/
#define OUTPUT_FILENAME1 "Huffman_Codes.txt"
#define OUTPUT_FILENAME2 "HFT_Model"
#define STR_SIZE 20000
#define FILE_SIZE 100
#define CHAR_COUNT_SIZE 1000
#define HUFFMAN_CODE_SIZE 10000
#define BIT_SIZE 100
/* #define DEBUG */

/*******************************************************************************
Two structs used for implemented the Huffman coding algorithm:

1.node: the node of the Huffman tree. 
  - value: this variable exists only when the node is the leaf node
  - value_to_ASCII: the ASCII number of the variable "value" above
  - weight: store the frequency of the char in the text
  - parent, left and right : the index of the parent, left child and right 
    child of this node respectively.

2. codes: the huffman codes for one char
  - bit: a array that contains the Huffman Codes
  - from: start index of the Huffman codes in the bit array above (included)
  - to: end index of the Huffman codes in the bit array above (excluded)
  - value: the character mapped into the Huffman codes
  post: After constructing the Huffman tree, each path from the root to the 
  leaf node will represent a bunch of Huffman codes, and each bunch represents 
  a unique char. So this codes struct is used to build a huffman codes 
  dictionary according to the constructed Huffman Tree.
*******************************************************************************/

struct node
{
    char value;
    int value_to_ASCII;
    int weight;
    int parent;
    int left;
    int right;
};
typedef struct node node_t;

struct codes
{
    int bit[BIT_SIZE];
    int from;
    int to;
    char value;
};
typedef struct codes codes_t;

/*******************************************************************************
 Function prototypes (Description is in the function implementation)
*******************************************************************************/

void read_files(char filename[], char str[]);

void calculate_frequency(char str[], int count[]);

void initiate_HuffmanTree(node_t huffman_tree[], int tree_size, int count[]);

void construct_HuffmanTree(node_t huffman_tree[], int n, int tree_size);

void get_minWeight(node_t huffman_tree[], int range, 
    int* min1_p, int* min2_p, int* position1_p, int* position2_p);

void get_HuffmanDictionary(node_t huffman_tree[], 
                            codes_t huffman_codes_dic[], int n);

void encode(const char str[], const codes_t huffman_codes_dic[], 
                              int huffman_codes[], int n, int* length_p);

void print_HuffmanDictionary(int n, const codes_t huffman_codes_dic[]);

void print_binary(int number, int *binary_length_p);

void save_HuffmanCode(char filename[], const int huffman_codes[], int length);

void save_HuffmanTree(char filename[], 
                                  const node_t huffman_tree[], int tree_size);

/*******************************************************************************
 This function is the main process to achieve compression
*******************************************************************************/
void compress_file2()
{
    /* Read the contents from the input file and store 
       the characters in the file to the "str" string */
    char str[STR_SIZE];
    char file_to_compress[FILE_SIZE];
    printf("Please enter the file you want to compress: ");
    scanf("%[^\n]s", file_to_compress);
    read_files(file_to_compress, str);

    /* Use the count array to calculate the frequency of each character, the 
       ASCII number of each character is the index in count array */
    int count[CHAR_COUNT_SIZE];
    calculate_frequency(str,count);

    /* Calculate the number of unique character in the "count array", 
       this number is exactly the number of leaf nodes in Huffman trees*/
	int i, n = 0;
    for(i = 0; i< CHAR_COUNT_SIZE; i++){
        if(count[i] != 0)
        {   
            #ifdef DEBUG
                printf("ASCII = %d; char is: %c; Frequency: %d\n", 
                                 i, i, count[i]);
			#endif
            n++;
        }
    }

    /*-------------------------------------------------
      If the number of leaf nodes are n, there should be 
       (2 * n - 1) nodes in the Huffman tree.
    -------------------------------------------------*/
    int tree_size = 2 * n - 1;

    /* Create the Huffman tree by dynamic allocation, because the tree size
       is decided during the runtime of the program */
    node_t* huffman_tree;
    printf("tree_size is: %d\n", tree_size);
    huffman_tree = (node_t*) malloc(tree_size * sizeof(node_t));
    if(huffman_tree == NULL){
        printf("Allocation failed.\n");
        return;
    }

    /* The construction of the Huffman tree */
    initiate_HuffmanTree(huffman_tree, tree_size,  count);
    construct_HuffmanTree(huffman_tree, n, tree_size);

    /* Create the Huffman codes dictionary  array by dynamic allocation, 
      because the size of this array is the number of leaf nodes */
    codes_t* huffman_codes_dic;
    huffman_codes_dic = (codes_t*) malloc(n * sizeof(codes_t));
    if(huffman_codes_dic == NULL){
        printf("Allocation failed.\n");
        return;
    }

    /* Get the Huffman codes for each unique character in the dictionary */
    get_HuffmanDictionary(huffman_tree, huffman_codes_dic, n);

    /* Get the Huffman Codes by the input string, and the dictionary */
    int huffman_codes[HUFFMAN_CODE_SIZE];
    int huffman_codes_length = 0;
    encode(str,huffman_codes_dic,huffman_codes,n, &huffman_codes_length);

    /* Print the dictionay as the key:value format */
    print_HuffmanDictionary(n,huffman_codes_dic);

    /* Compare the number of binary number before and after compression */
    printf("\n");
    printf("The original bit numbers are: \n");
    int char_to_ASCII = 0;
    int total_binary_length = 0;
    int single_binary_length = 0;
    for(i = 0; str[i] != '\0'; i++)
    {
        char_to_ASCII = str[i];
        print_binary(char_to_ASCII, &single_binary_length);
        total_binary_length += single_binary_length;
        single_binary_length = 0;
    }
    
    printf("\n\n");
    printf("After Compression, the Huffman Codes are: \n");
    for(i = 0; i < huffman_codes_length; i++)
    {
        printf("%d",huffman_codes[i]);
    }
    printf("\n\n");

    /* Calculate the compression ratio and output */
    double compression_ratio = (double)huffman_codes_length / 
                                (double)total_binary_length;
    printf("The size of original bit numbers is : %d\n", total_binary_length);
    printf("The size of bit numbers after compression is : %d\n", 
                                                        huffman_codes_length);
    printf("The compression ratio is: %.2lf \n", compression_ratio);
    printf("\n");

    /* Save the Huffman codes and Huffman Tree models into the directory, 
       just for the preparation for the decompression and search algorithm */
    printf("Writing the Huffman Codes to the file 'Huffman_Codes'...\n");
    save_HuffmanCode(OUTPUT_FILENAME1,huffman_codes,huffman_codes_length);
    printf("Saving the Huffman Tree Model to the file 'Huffman_Tree'...\n");
    save_HuffmanTree(OUTPUT_FILENAME2,huffman_tree,tree_size);

    /* Release memory of the dynamic allocationnd and make the pointer 
       point to NULL */
    free(huffman_tree);
    huffman_tree = NULL;
    free(huffman_codes_dic);
    huffman_codes_dic = NULL;
}

/*******************************************************************************
 This function reads the chars from the text file and stores every char to the
 pre-defined char array str[].
 inputs:
    filename: the input filename
    str: the array that stores all characters from the input text file 
*******************************************************************************/
void read_files(char filename[], char str[]){
    FILE * fp = NULL;
    fp = fopen(filename, "r");
    if(fp == NULL)
    {
        printf("Error: The file is not existed.\n");
    }
    
    int index = 0;
    char ch = fgetc(fp);
    while (ch != EOF) {
        str[index++] = ch;
        ch = fgetc(fp);
    }   

    str[index] = '\0';
    fclose(fp);
}

/*******************************************************************************
 This function calculates the frequency of each character from the input.
 inputs:
    str: the array that stores all characters from the input text file 
    count: the array that stores the frequency of the character
 post:
    Each index in the count array can represent one character, because I use 
    the ASCII code of each existed character as the index.
*******************************************************************************/
void calculate_frequency(char str[], int count[])
{
	
    /* initiate each value in the count to 0 to avoid the strange value */
    int i;
    for(i = 0; i< CHAR_COUNT_SIZE; i++){
        count[i] = 0;
    }

    int index;
    int char_to_ASCII;
    for(index = 0; str[index] != '\0'; index++ )
    {
        /* Convert the char to the ASCII and add 1 to its corresponding 
           position in the count array */
        char_to_ASCII = str[index];
        count[char_to_ASCII]++;
    }   
}

/*******************************************************************************
 This function initiates the Huffman tree.
 inputs:
    huffman_tree: the array with each element as the node_t type
    tree_size: capacity of the huffman tree
    count: the array that stores the frequency of the character
*******************************************************************************/

void initiate_HuffmanTree(node_t huffman_tree[], int tree_size, int count[])
{
    /* set the variable field of each node in the huffman_tree to -1 or ' ' */
    int i;
    for(i = 0; i < tree_size; i++)
    {
        huffman_tree[i].parent = -1;
        huffman_tree[i].left = -1;
        huffman_tree[i].right = -1;
        huffman_tree[i].weight = 0;
        huffman_tree[i].value = ' ';
        /* 32 is the ASCII number to the character ' ' */
        huffman_tree[i].value_to_ASCII = 32;
    }

    /* set the value of the leaf node */
	int ASCII, node_index = 0;
    char ASCII_to_char;

    for(ASCII = 0; ASCII < CHAR_COUNT_SIZE; ASCII++)
    {
        if(count[ASCII] != 0)
        {
            ASCII_to_char = ASCII;
            huffman_tree[node_index].value = ASCII_to_char;
            huffman_tree[node_index].value_to_ASCII = ASCII;
            huffman_tree[node_index].weight = count[ASCII];
            node_index++;
        }
    }
}

/*******************************************************************************
 This function constructs the Huffman tree from bottom(leaft) to the top(root):
 1. Select the 2 nodes with minimum weight, the node to be considered should be 
    the single node with no parent.
 2. Create a new parent whose weight is the sum of these 2 nodes.
 3. Repeat the step 1 and 2 until reaching the tree size.

 inputs:
    huffman_tree: the array with each element as the node_t type
    n: number of leaf nodes / unique characters
    tree_size: capacity of the huffman tree
*******************************************************************************/
void construct_HuffmanTree(node_t huffman_tree[], int n, int tree_size)
{
    int min1, min2;
    int position1, position2;

    /* The new parent position should be located after all the leaf nodes' 
        index */
    int new_parent_position = n;

    while(new_parent_position < tree_size)
    {
        min1 = min2 = 9999999;
        position1 = position2 = 0;

        /* ---------------------------------------------------------------
          Recall the get_minWeight function to get the smallest two weights 
          and the corresponding positions. parameters are passed by reference 
          so that any change in the get_minWeight function will change the 
          value of min1, min2, position1, position2 in this 
          "construct_HuffmanTree" function.
        ----------------------------------------------------------------- */
        get_minWeight(huffman_tree, new_parent_position, 
                                &min1, &min2, &position1, &position2);

        /* update the children nodes' information */
        huffman_tree[position1].parent = new_parent_position;
        huffman_tree[position2].parent = new_parent_position;

        /* update the parent node's information */
        huffman_tree[new_parent_position].left = position1;
        huffman_tree[new_parent_position].right = position2;
        huffman_tree[new_parent_position].weight = 
            huffman_tree[position1].weight + huffman_tree[position2].weight;

        /* move the valid position to the next position to prepare for 
           storing the next parent node */
        new_parent_position++;
    }
}

/*******************************************************************************
 This function can get the smallest two weights and the corresponding positions.
 inputs:
    huffman_tree: the array with each element as the node_t type
    range: current size of the Huffman tree
    min1_p, min2_p: the pointer to the smallest two weights of all nodes 
                    with no parent
    position1_p, position2_p: the pointer to the index of the huffman_tree 
                              array related to min1, min2
*******************************************************************************/
void get_minWeight(node_t huffman_tree[], int range, int* min1_p, int* min2_p, 
                                            int* position1_p, int* position2_p)
{
    int i;
    for(i = 0; i < range; i++)
    {
        /* Only compare the weight of the node with no parent */
        if(huffman_tree[i].parent == -1)
        {
            if(huffman_tree[i].weight < *min1_p)
            {
                *min2_p = *min1_p;
                *min1_p = huffman_tree[i].weight;
                *position2_p = *position1_p;
                *position1_p = i;
            }
            else if(huffman_tree[i].weight < *min2_p)
            {
                *min2_p = huffman_tree[i].weight;
                *position2_p = i;
            }
        }
    }
}

/*******************************************************************************
 This function gets the Huffman coding dictionary accroding to the Huffman Tree.
 input:
    huffman_tree: the array with each element as the node_t type
    huffman_codes_dic: stores each unique character along with its Huffman Codes
    n: number of leaf nodes / unique characters
*******************************************************************************/
void get_HuffmanDictionary(node_t huffman_tree[], 
                                        codes_t huffman_codes_dic[],  int n)
{
    int start;
    int i, child, parent;

    /* For each leaf node, traverse the Huffman tree from bottom to top */
    for(i = 0; i < n; i++)
    {
        /* ---------------------------------------------------------------
         Since the traversal is started at the leaf, the Huffman coding
        should be stored from the back position to the front position 
        in the "bit" array in the codes_t variable.
        ----------------------------------------------------------------*/
        start = n;
        huffman_codes_dic[i].to = n;
        huffman_codes_dic[i].value = huffman_tree[i].value;

        /* Get the current leaf node and its parent */
        child = i;
        parent = huffman_tree[i].parent;

        /* Store the Huffman code during the traversal path from leaf node to
           the root, update the current child and parent each time */
        while(parent != -1){
            /* Set the huffman code in the "bit" array in the codes_t variable.
               according to different condition */
            if(child == huffman_tree[parent].left)
            {
                start--;
                huffman_codes_dic[i].bit[start] = 0;
            } 
            else if(child == huffman_tree[parent].right) 
            {
                start--;
                huffman_codes_dic[i].bit[start] = 1;
            }

            /* Reset the current child and the current parent  */
            child = parent;
            parent = huffman_tree[parent].parent;
        }

        /* Because the root have been reached, the current start position
           should be set to to the "from" field in the codes_t variable */
        huffman_codes_dic[i].from = start; 
    }
}

/*******************************************************************************
 This function encodes the input string to the Huffman codes based on the 
 Huffman codes dictionary.
 input:
    str: the array that stores all characters from the input text file 
    huffman_codes_dic: stores each unique character along with its Huffman 
                       Codes
    huffman_codes: Huffman codes of the input string
    n: number of leaf nodes / unique characters
    length_p: a pointer to the actual size of the Huffman codes in the 
              "huffman_codes" array.
*******************************************************************************/
void encode(const char str[], const codes_t huffman_codes_dic[], 
                                   int huffman_codes[], int n, int* length_p)
{
    int str_index,i,j;
    char c;

    /* Loop every character of the input string */
    for(str_index = 0; str[str_index] != '\0'; str_index++)
    {
        c = str[str_index];

        /* Select the required character in the Huffman codes dictionary */
        for(i = 0; i < n; i++)
        {
            if(huffman_codes_dic[i].value == c)
            {
                /* Store Huffman code of this character to the 
                "huffman_codes" array */
                for(j = huffman_codes_dic[i].from ; 
                                          j < huffman_codes_dic[i].to; j++)
                {
                    huffman_codes[*length_p] = huffman_codes_dic[i].bit[j];
                    *length_p = *length_p + 1;
                }
            }
        }
    }
}

/*******************************************************************************
 This function prints the each character along with its huffman codes in the
 Huffman codes dictionary. 
 input:
    n:number of leaf nodes / unique characters
    huffman_codes_dic: stores each unique character along with its Huffman Codes.
*******************************************************************************/
void print_HuffmanDictionary(int n, const codes_t huffman_codes_dic[])
{
    int i,j;
    printf("\n--------------Huffman Codes Dictionary:-------------- \n");
    for(i = 0; i < n; i++){
        printf("%c: ",huffman_codes_dic[i].value);
        for(j = huffman_codes_dic[i].from ; 
                                        j < huffman_codes_dic[i].to;  j++)
        {
            printf("%d", huffman_codes_dic[i].bit[j]); 
        }
        printf("\n");
    }
    printf("------------------------------------------------------\n");

}
/*******************************************************************************
 This function prints the binary number corresponding to a decimal number, it 
 implemented with recursive algorithm and bit operation.
 input:
    number: a decimal number
    binary_length_p: pointer to the binary length of a binary number
 post:
    the binary length of this decimal number will be calculated during the 
    return path process.
*******************************************************************************/
void print_binary(int number, int *binary_length_p)
{
    /* Termination condition */
    if(number == 0) return;
    
    /* move all bit right one place recursively, the highest position will be 
       inserted by 0 */
    print_binary(number >> 1, binary_length_p);

    /* update the length of the binary number during the recursion 
       return process*/
    *binary_length_p += 1;

    /* print the binary number one by one during the recursion return process,
       number & 0x1 can get the lowest(rightest side) value of the bit number*/
    printf("%d", number & 0x1);
}
/*******************************************************************************
 This function can export the Huffman codes to the "Huffman_Codes.txt" 
 file.
 input:
    filename: the output filename
    huffman_codes:Huffman codes of the input string
    length: actual size of the Huffman codes in the "Huffman_Codes.txt" array.
********************************************************************************/
void save_HuffmanCode(char filename[], const int huffman_codes[], int length)
{
    FILE * fp = NULL;
    fp = fopen(filename, "w");
    if(fp == NULL)
    {
        printf("Error: Failed to write the data into the file.\n");
        return;
    }

    int i;
    for(i = 0; i < length; i++)
    {
        fprintf(fp, "%d", huffman_codes[i]);
    }

    printf("Succeed\n");
    fclose(fp);
}
/*******************************************************************************
 This function can export the Huffman tree model to the "HFT_Model" file.

 There are 5 attributes for each line, the format should be:
 weight parent left_children right_children ASCII of this charcater
 Such as:
 2 46 -1 -1 2
 means the weight is 2, the parent index of this node is 46, the left child and 
 right child of this node are both -1 which means this node is the leaf node,
 the ASCII number mapped into this node's character is 2.

 input:
    filename: the output filename
    huffman_tree: the array with each element as the node_t type
    tree_size: capacity of the huffman tree
*******************************************************************************/
void save_HuffmanTree(char filename[], const node_t huffman_tree[], 
                                                                int tree_size)
{
	FILE * fp = NULL;
    fp = fopen(filename, "w");
    if(fp == NULL)
    {
        printf("Error: Failed to write the data into the file.\n");
		return;
    }

	int i;

	for(i = 0; i < tree_size; i++){
		fprintf(fp, "%d %d %d %d %d\n", 
					huffman_tree[i].weight, 
					huffman_tree[i].parent, 
					huffman_tree[i].left, 
					huffman_tree[i].right,
                    huffman_tree[i].value_to_ASCII);
	}
	printf("Succeed\n");

	fclose(fp);
}
