/*-------------------------------------------------------------------------------------------------------
* Name         : Unnathi.N
* Date         : 24-06-25
* File         : search.c
* Title        : Inverted Search - Search Database
* Description  : This program file search the word and displays its occurence info across files.
--------------------------------------------------------------------------------------------------------*/

#include "header.h"

// Function to search a word in the hash table
int search_database(htable *arr, int size)
{
    char word[20];
    printf("Enter the data you want to search : ");
    scanf("%s", word);

    int index;
    if (isalpha(word[0]))
        index = tolower(word[0]) % 97;    // Hashing: convert to lowercase and map to index
    else
        index = 26;  // Non - alphabetic

    mnode *mtemp = arr[index].link;
    while (mtemp != NULL)
    {
        if (strcmp(mtemp->word, word) == 0)
        {
            printf("---------------------------------------------------\n");
            printf("\"%s\" is present in %dth index in %d file%s\n", word, index, mtemp->filecount,
                   mtemp->filecount > 1 ? "s" : ""); // word found, print info
            printf("In file:\n");

            snode *stemp = mtemp->slink;
            while (stemp != NULL)
            {
                printf("%s  : %d times\n", stemp->filename, stemp->wordcount);   // print filename and word count
                stemp = stemp->sub_link;
            }

            printf("---------------------------------------------------\n");
            return SUCCESS;
        }
        mtemp = mtemp->mlink;
    }

    // if word not found
    printf("INFO : Not found\n");
    return FAILURE;
}

