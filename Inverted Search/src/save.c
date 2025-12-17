/*-------------------------------------------------------------------------------------------------------
* Name         : Unnathi.N
* Date         : 24-06-25
* File         : save.c
* Title        : Inverted Search - Save Database
* Description  : This program file saves the entire database into a user provided .txt file in a compact format.
--------------------------------------------------------------------------------------------------------*/

#include "header.h"

int save_database(htable *arr, int size)
{
    char filename[100];

    printf("Enter the filename to save the database (with .txt extension): ");
    scanf("%s", filename);

    // Check for .txt extension
    if (strstr(filename, ".txt") == NULL || strcmp(strrchr(filename, '.'), ".txt") != 0)
    {
        printf("ERROR: Please enter a file with .txt extension.\n");
        return FAILURE;
    }
    //open file in write mode
    FILE *fptr = fopen(filename, "w");
    if (fptr == NULL)
    {
        printf("ERROR: Unable to open file for writing.\n");
        return FAILURE;
    }

    for (int i = 0; i < size; i++)
    {
        if (arr[i].link != NULL)
        {
            fprintf(fptr, "# : %d\n", i);  // index line

            mnode *mtemp = arr[i].link;
            while (mtemp != NULL)
            {
                fprintf(fptr, "%s : %d", mtemp->word, mtemp->filecount);

                snode *stemp = mtemp->slink;
                while (stemp != NULL)
                {
                    fprintf(fptr, " : %s : %d", stemp->filename, stemp->wordcount);
                    stemp = stemp->sub_link;
                }

                fprintf(fptr, " #\n");  // end of word entry
                mtemp = mtemp->mlink;
            }
        }
    }

    fclose(fptr);
    printf("Database saved successfully to '%s'\n", filename);
    return SUCCESS;
}

