/*-------------------------------------------------------------------------------------------------------------------
* Name            : Unnathi.N
* Date            : 24-06-25
* File            : main.c
* Title           : Inverted search main file
* Description     : This program file act as the entry point of the program. It handles command line validation, menu
                    display and function calls based on the user choice.

* Sample I/P      : ./a.out file1.txt file2.txt file3.txt

* Sample O/P      : validate successfully
                    List of validated files:
                    file1.txt->file2.txt->file3.txt->NULL

                    1. Create database
                    2. Display database
                    3. Search database
                    4. Save database
                    5. Update database
                    6. Exit

                    Enter your choice : 1
                    database created for file1.txt
                    database created for file2.txt
                    database created for file3.txt

                    Enter your choice : 2
                    -----------------------------------------------------------------------------------------------
                    Index        Word           File Count           File Name                      Word Count
                    -----------------------------------------------------------------------------------------------
                    [0]          are                  1               file3.txt                            1
                    [7]          hi                   2               file1.txt                            2
                                                                      file2.txt                            1
                                 hello                2               file1.txt                            1
                                                                      file2.txt                            2
                    [22]         welcome              1               file3.txt                            1
                    -----------------------------------------------------------------------------------------------

                    Enter your choice : 3
                    Enter the data you want to search : hi
                    ---------------------------------------------------
                    "hi" is present in 7th index in 2 files
                     In file:
                     file1.txt : 2 times
                     file2.txt : 1 times
                   ---------------------------------------------------

                   Enter your choice : 4
                   Enter the filename to save the database (with .txt extension): save.txt
                   Database saved successfully to 'save.txt'

                   Enter your choice : 6
                   Exited successfully

 ----------------------------------------------------------------------------------------------------------------------*/
#include "header.h"

int main(int argc, char *argv[])
{
    flist *head = NULL;
    int choice;
    // Create hash table
    htable arr[27];
    for(int i = 0; i < 27; i++)
    {
        arr[i].index = i;
        arr[i].link = NULL;
    }

    // Check CLA is passed
    if(argc > 1)
    {
        if (read_and_validate(argc, argv, &head) == SUCCESS)
        {
            printf("validate successfully\n");
            print_list(head);

            // Display menu
            printf("1. Create database\n2. Display database\n3. Search database\n4. Save database\n5. Update database\n6. Exit\n");
            do
            {
                printf("Enter your choice : ");
                scanf("%d",&choice);
                switch(choice)
                {
                    case 1:
                        create_database(arr, 27, head);
                        break;

                    case 2:
                        display_database(arr, 27);
                        break;

                    case 3:
                        search_database(arr, 27);
                        break;

                    case 4:
                        save_database(arr, 27);
                        break;

                    case 5:
                        update_database(arr, 27, &head);
                        break;

                    case 6:
                        printf("Exited successfully\n");
                        break; 

                    default:
                        printf("Invalid choice\n");
                }
            }while(choice != 6);
            
        }
     }
    else
    {
        printf("Error : pass CLA like file1.txt file2.txt\n");
    }
}

