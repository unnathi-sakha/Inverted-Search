/*---------------------------------------------------------------------------------------------------------
* Name           : Unnathi.N
* Date           : 24-06-25
* File           : validate.c
* Title          : Inverted Search - Validation, insert at last, print function
* Description    : This program files validates input file and adds valid files to a linked list and prints it.
-----------------------------------------------------------------------------------------------------------*/

#include "header.h"

int read_and_validate(int argc, char *argv[], flist **head)
{
    int file_validated = 0;  // Variable to check if any file is validated successfully

    // Take argument one by one
    for(int i = 1; i < argc; i++)
    {
        // Check the extension of file is ".txt"
        if (strrchr(argv[i], '.') != NULL)  // check if there is a '.' in the file name
        {
            if (strcmp(strrchr(argv[i], '.'), ".txt") == 0)  // Compare the extension with .txt
            {
                // If yes, open the file in read mode
                FILE *fptr = fopen(argv[i], "r");

                // Check if the file is present or not
                if (fptr == NULL)
                {
                    printf("Error : file %s is not present\n", argv[i]);
                    continue;
                }

                // If file is present, check if the file is empty or not
                fseek(fptr, 0, SEEK_END);
                if ((ftell(fptr)) == 0)
                {
                    printf("Error : File %s is empty\n", argv[i]);
                    fclose(fptr);
                    continue;
                }

                int ret = insert_at_last(head, argv[i]);
                if (ret == DUPLICATE_FOUND)
                {
                    printf("Error : %s is a duplicate file\n", argv[i]);
                }
                else
                {
                    file_validated++;  // Increment if file is successfully added
                    fclose(fptr);  // Close file after processing
                }
            }
            else
            {
                printf("Error: %s is not a valid .txt file\n", argv[i]);
            }
        }
    }

    // Return SUCCESS only if at least one file was validated successfully
    return (file_validated > 0) ? SUCCESS : FAILURE;
}

int insert_at_last(flist **head, char *argv)
{
    // Create a new node
    flist *new_node = (flist*)malloc(sizeof(flist));
    if (new_node == NULL)
    {
        printf("Memory allocation failed\n");
        return FAILURE;
    }

    // Assign file name to the new node
    strcpy(new_node->fname, argv);
    new_node->link = NULL;  // New node will point to NULL as it's the last node

    // If the list is empty, make the new node the head
    if (*head == NULL)
    {
        *head = new_node;
        return SUCCESS;
    }

    // Check for duplicate file name in the list
    flist *temp = *head;
    while (temp != NULL)
    {
        if (strcmp(temp->fname, argv) == 0)
        {
            // Duplicate found, free the memory for new node
            free(new_node);
            return DUPLICATE_FOUND;
        }
        temp = temp->link;
    }

    // Add the new node at the end of the list if no duplicates found
    temp = *head;
    while (temp->link != NULL)
    {
        temp = temp->link;
    }
    temp->link = new_node;  // Link the last node to the new node

    return SUCCESS;
}



void print_list(flist *head)
{
    if (head == NULL)
    {
        printf("The list is empty.\n");
        return;
    }

    printf("List of validated files:\n");

    flist *temp = head;
    while (temp != NULL)
    {
        printf("%s", temp->fname);
        if(temp->link != NULL)  // Check if there's a next node
            printf("->");
        temp = temp->link;
    }
    printf("->NULL\n");  // print at the end
}
