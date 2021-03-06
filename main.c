#include "project_utils.h"
#include<stdio.h>

/*******************************************************************************
 48430 Fundamentals of C Programming Activity 02
 Group 03
 please type "make" command in the terminal to compile all the c sources codes,
 then type "./main.out" to run the Program

 Another commands:
 make clean: clean all the compiled files in the directory.
 make cleanf: clean all the intermediate  files generated during the program.
*******************************************************************************/
int main(void){
    int choice = 0;
    int choice_inside;
    char temp;

    while(choice != -1)
    {
        choice_inside = 0;
        print_menu();
        printf("\n");
        printf("Plese enter your choice > ");
        scanf("%d",&choice);
        scanf("%c",&temp);

        switch(choice){
            case 1: 
            {
                printf( "\n"
                        "Do you want efficient compression or"
                        " inefficient compression?\n"
                        "1. Efficient compression \n"
                        "2. Inefficient compression (Decompression" 
                        " not support)\n"
                        "If you want to back to the menu, please type -1\n"
                        "\n"
                        "Plese enter your choice > "
                        );
                scanf("%d",&choice_inside);
                scanf("%c",&temp);
                switch(choice_inside)
                {
                    case 1: compress_file2(); break; 
                    case 2: compress_file1();break;
                    case -1: break;
                    default: printf("Invalid Input\n"); continue;
                }
                continue;
            }
            
            case 2:
            {
                printf( "\n"
                        "Do you want to encrypt files with high security"
                        " or low security?\n"
                        "1. High security\n"
                        "2. Low security\n"
                        "If you want to back to the menu, please type -1\n"
                        "\n"
                        "Plese enter your choice > "
                        );
                scanf("%d",&choice_inside);
                scanf("%c",&temp);
                switch(choice_inside)
                {
                    case 1: encrypt_file2(); break; 
                    case 2: encrypt_file1();break;
                    case -1: break;
                    default: printf("Invalid Input\n"); continue;
                }
                continue;
            }
            case 3: decompress_file2(); continue;
            case 4:
            {
                printf( "\n"
                        "Do you want to decrypt files with high security"
                        " or low security?\n"
                        "1. High security\n"
                        "2. Low security\n"
                        "If you want to back to the menu, please type -1\n"
                        "\n"
                        "Plese enter your choice > "
                        );
                scanf("%d",&choice_inside);
                scanf("%c",&temp);
                switch(choice_inside)
                {
                    case 1: decrypt_file2(); break; 
                    case 2: decrypt_file1();break;
                    case -1: break;
                    default: printf("Invalid Input\n"); continue;
                }
                continue;
            }
            case 5: search_keyword(); continue;
            case 6:
            {
                printf( "\n"
                        "What kind of file do you want to sort?\n"
                        "1. Original database -> Customer.txt \n"
                        "2. Self-defined file \n"
                        "If you want to back to the menu, please type -1\n"
                        "\n"
                        "Plese enter your choice > "
                        );
                scanf("%d",&choice_inside);
                scanf("%c",&temp);
                switch(choice_inside)
                {
                    case 1: sort_original_database(); break; 
                    case 2: sort_by_user_input();break;
                    case -1: break;
                    default: printf("Invalid Input\n"); continue;
                }
                continue;
            }
            case -1: break;
            default: printf("Invalid Input\n");
        }
    }
    return 0;
}
