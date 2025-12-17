/*-------------------------------------------------------------------------------------------------------
* Name         : Unnathi.N
* Date         : 24-06-25
* File         : update.c
* Title        : Inverted Search - Update Database
* Description  : This program file adds a new, non-duplicate, valid file to the list and updates
                 the database with it.
--------------------------------------------------------------------------------------------------------*/

#include "header.h"

int update_database(htable *arr, int size, flist **head)
{
    char filename[100];
    printf("Enter the filename to update the database: ");
    scanf("%s", filename);

    // Check extension
    if (strstr(filename, ".txt") == NULL || strcmp(strrchr(filename, '.'), ".txt") != 0)
    {
        printf("ERROR: Please provide a valid .txt file.\n");
        return FAILURE;
    }

    // Try to open the file
    FILE *fptr = fopen(filename, "r");
    if (fptr == NULL)
    {
        printf("ERROR: File '%s' not found.\n", filename);
        return FAILURE;
    }

    // Check if file is empty
    fseek(fptr, 0, SEEK_END);
    if (ftell(fptr) == 0)
    {
        printf("ERROR: File '%s' is empty.\n", filename);
        fclose(fptr);
        return FAILURE;
    }
    rewind(fptr); // Reset file pointer

    // Check for duplicate
    flist *temp = *head;
    while (temp != NULL)
    {
        if (strcmp(temp->fname, filename) == 0)
        {
            printf("ERROR: File '%s' is already present in the database.\n", filename);
            fclose(fptr);
            return DUPLICATE_FOUND;
        }
        temp = temp->link;
    }

    // Add to file list
    if (insert_at_last(head, filename) == SUCCESS)
    {
        printf("File '%s' successfully added to file list.\n", filename);
        
        // Create database entry for only the new file
        flist *last = *head;
        while (last->link != NULL)
            last = last->link;

        create_database(arr, size, last);  // Pass only the last node
        printf("Database updated for file '%s'.\n", filename);
    }

    fclose(fptr);
    return SUCCESS;
}

