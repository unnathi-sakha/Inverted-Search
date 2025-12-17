/*-------------------------------------------------------------------------------------------------------
* Name         : Unnathi.N
* Date         : 24-06-25
* File         : display.c
* Title        : Inverted Search - Display Database
* Description  : This program file displays the contents of the hash table in tabular form
--------------------------------------------------------------------------------------------------------*/


#include "header.h"

//Function to display the contents of the hash table
int display_database(htable *arr, int size)
{
    //print table header
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("%-12s %-14s %-20s %-30s %-15s\n", "Index", "Word", "File Count", "File Name", "Word Count");
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < size; i++)
    {
        if (arr[i].link != NULL)
        {
            mnode *mtemp = arr[i].link;

            while (mtemp != NULL)
            {
                snode *stemp = mtemp->slink;
                int first_line = 1;

                while (stemp != NULL)
                {
                    if (first_line)
                    {
                        // First line: print full info
                        printf("[%-2d]        %-14s %-20d %-30s %-15d\n",
                            i, mtemp->word, mtemp->filecount, stemp->filename, stemp->wordcount);
                        first_line = 0;
                    }
                    else
                    {
                        // Only print file name and word count
                        printf("                                                %-30s %-15d\n",
                            stemp->filename, stemp->wordcount);
                    }

                    stemp = stemp->sub_link;
                }

                mtemp = mtemp->mlink;
            }
        }
    }
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------\n");

    return SUCCESS;
}

