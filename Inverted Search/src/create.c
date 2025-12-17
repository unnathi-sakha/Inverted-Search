/*-------------------------------------------------------------------------------------------------------
* Name         : Unnathi.N
* Date         : 24-06-25
* File         : create.c
* Title        : Inverted Search - Create Database
* Description  : This program file creates the inverted index [ hash table, with words, file counts
                 and occurences]
--------------------------------------------------------------------------------------------------------*/
#include "header.h"

int create_database(htable *arr, int size, flist *head)
{
    char str[20];
    int index;

    // Take each file from the linked list
    flist *temp = head;
    while (temp != NULL)
    {
        // ✅ Print file currently being processed
        printf("database created for %s\n", temp->fname);

        // Open the file in read mode
        FILE *fptr = fopen(temp->fname, "r");
        if (fptr == NULL)
        {
            printf("Error: Could not open file %s\n", temp->fname);
            temp = temp->link;
            continue;
        }

        // Read words one by one
        while (fscanf(fptr, "%s", str) != EOF)
        {
            // Convert word to lowercase
            for (int i = 0; str[i]; i++)
                str[i] = tolower(str[i]);

            // Determine hash index
            if (isalpha(str[0]))
                index = tolower(str[0]) - 'a';  // 'a' → 0, ..., 'z' → 25
            else
                index = 26;

            // If no main node exists at this index
            if (arr[index].link == NULL)
            {
                mnode *mnew = malloc(sizeof(mnode));
                snode *snew = malloc(sizeof(snode));
                if (!mnew || !snew)
                {
                    perror("malloc");
                    fclose(fptr);
                    return FAILURE;
                }

                mnew->filecount = 1;
                strcpy(mnew->word, str);
                mnew->mlink = NULL;
                mnew->slink = snew;

                snew->wordcount = 1;
                strcpy(snew->filename, temp->fname);
                snew->sub_link = NULL;

                arr[index].link = mnew;
            }
            else
            {
                mnode *mtemp = arr[index].link;
                mnode *mprev = NULL;
                int mflag = 0;

                while (mtemp != NULL)
                {
                    if (strcmp(mtemp->word, str) == 0)
                    {
                        mflag = 1;
                        snode *stemp = mtemp->slink;
                        snode *sprev = NULL;
                        int sflag = 0;

                        while (stemp != NULL)
                        {
                            if (strcmp(stemp->filename, temp->fname) == 0)
                            {
                                stemp->wordcount++;
                                sflag = 1;
                                break;
                            }
                            sprev = stemp;
                            stemp = stemp->sub_link;
                        }

                        if (sflag == 0)
                        {
                            snode *snew = malloc(sizeof(snode));
                            if (!snew)
                            {
                                perror("malloc");
                                fclose(fptr);
                                return FAILURE;
                            }

                            snew->wordcount = 1;
                            strcpy(snew->filename, temp->fname);
                            snew->sub_link = NULL;
                            sprev->sub_link = snew;

                            mtemp->filecount++;
                        }
                        break;
                    }

                    mprev = mtemp;
                    mtemp = mtemp->mlink;
                }

                if (mflag == 0)
                {
                    mnode *mnew = malloc(sizeof(mnode));
                    snode *snew = malloc(sizeof(snode));
                    if (!mnew || !snew)
                    {
                        perror("malloc");
                        fclose(fptr);
                        return FAILURE;
                    }

                    mnew->filecount = 1;
                    strcpy(mnew->word, str);
                    mnew->mlink = NULL;
                    mnew->slink = snew;

                    snew->wordcount = 1;
                    strcpy(snew->filename, temp->fname);
                    snew->sub_link = NULL;

                    mprev->mlink = mnew;
                }
            }
        }

        fclose(fptr);
        temp = temp->link;
    }

    return SUCCESS;
}

