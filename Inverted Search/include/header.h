/*-------------------------------------------------------------------------------------------------------------------
* Name            : Unnathi.N
* Date            : 24-06-25
* File            : header.h
* Title           : Inverted search header file
* Description     : This program file contains ll necessary structure definitions, macros and function prototypes 
                    used across the project.
----------------------------------------------------------------------------------------------------------------------*/

#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


// Define macro
#define SUCCESS 1
#define FAILURE 0
#define DUPLICATE_FOUND -1

//define structure
typedef struct node
{
    char fname[20];
    struct node *link;
}flist;

typedef struct subnode
{
    int wordcount;
    char filename[20];
    struct subnode *sub_link;
}snode;

typedef struct mainnode
{
    int filecount;
    char word[20];
    struct mainnode *mlink;
    snode *slink;
}mnode;

typedef struct hashtable
{
    int index;
    mnode *link;
}htable;

//Function prototype
int read_and_validate(int argc, char *argv[], flist **head);
int insert_at_last(flist **head, char *argv);
void print_list(flist *head);
int create_database(htable *arr, int size, flist *head);
int display_database(htable *arr, int size);
int search_database(htable *arr, int size);
int save_database(htable *arr, int size);
int update_database(htable *arr, int size, flist **head);

#endif



