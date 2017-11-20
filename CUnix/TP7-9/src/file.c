#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/types.h"
#include "../include/functions.h" // extern functions declarations

// ------------------------------------------------------------------------
// inner functions declarations
// ------------------------------------------------------------------------

int filelist_not_full(listfile_entry *);
void add_word(hash_table *, char *, int);
void add_filelist(char *, listfile_entry *);

//------------------------------------------------------------------------
// global functions definitions
//------------------------------------------------------------------------

/**
   Create and initialize file table of capacity maxfiles

   parameters :
   maxfiles : capacity of file table

   returns : pointer to table or NULL in case of error
 */
listfile_entry *create_filelist(int maxfiles)
{
  listfile_entry *listfile_ptr;
  listfile_ptr = (listfile_entry*)malloc(sizeof(listfile_entry) * maxfiles);
  return listfile_ptr;
}

/**
   add words from file to table
   - checks if the file has already been loaded
   - updates the file table (if file not already loaded)
   - reads every word in the file (idem)
   - updates the hash table (idem)

   parameters :
   filename   : name of file :)
   filelist   : pointer to table of files
   htable_ptr : pointer to hash table

   returns :
    1 if file already present in table
    2 if no space left in filelist
   -1 if file doesn't exist or can't be read
   -2 if allocation error
    0 if everything ok
*/
int add_file(char filename[],listfile_entry * filelist, hash_table * htable_ptr)
{
  FILE *file;
  char buffer[MAX_LENGTH];

  int return_value;
  int i;


  file = fopen(filename, "r");

  for (i = 0; i < MAX_FILES; i++) {
    if(strcmp(filename, filelist[i].filename) == 0 && filelist[i].loaded) {
      printf("File already loaded !\n");
      return_value = 1;
    }
  }

  if(filelist_not_full(filelist) == 0) {
    return_value = 2;
  }

  if(file == NULL) {
    return_value = -1;
  }

  add_filelist(filename, filelist);

  while (fscanf(file, "%s", buffer) == 1) {
    int hash = hashcode(buffer, MAX_LENGTH);
    printf("%d->%s\n", hash, buffer);
    add_word(htable_ptr, buffer, hash);
    }
  if(feof(file)) {
    return_value = 0;
  }
  else {
    return_value = -2;
  }





  return return_value; // all fine
}

/**
   remove file from file table

   parameters :
   filename   : name of file to remove
   filelist   : pointer to table of files
   htable_ptr : pointer to hash table

   returns :
   -1 if file not in table
    0 if file removed
*/
int remove_file(char filename[], listfile_entry * filelist, hash_table * htable_ptr)
{

  // TO BE COMPLETED

  return 0;
}

/*
  print file table (only loaded files)

  parameters :
   filelist : pointer to table of files
*/
void print_list(listfile_entry * filelist)
{
  int i;
  for (i = 0;i < MAX_FILES; i++) {
      printf("%d -> Filename : %s, Status: %d\n", i, filelist[i].filename, filelist[i].loaded);
  }
}

/**
   free file table

parameters :
   filelist   : pointer to table of files
*/
void free_filelist(listfile_entry * filelist)

{
  // TO BE COMPLETED
}

// ************************************************************************
// inner functions
// ************************************************************************

/**
  returns:
    1 if space left in the filelist
    0 if filelist is full
**/
int filelist_not_full(listfile_entry * filelist) {
  return 1;
}

void add_word(hash_table * htable_ptr, char * buffer, int hash) {
  word_entry * newelt = (word_entry*)malloc(sizeof(word_entry));
  if(newelt != NULL) {
    strcpy(newelt->word, buffer);
    newelt->in_file = 0;
    newelt->times = 1;
    newelt->next = NULL;
  }
  word_entry *current = htable_ptr->htable[hash].first_word;
  if(current == NULL) {
    current = newelt;
  }
  else {
    while (current->next != NULL)
    {
      current = current->next;
    }
    current->next = newelt;
  }
}

void add_filelist(char * filename, listfile_entry * filelist) {
  int i;
  int ok = 0;
  for (i = 0; i < MAX_FILES; i++) {
    if(filelist[i].loaded == 0 && ok == 0) {
      strcpy(filelist[i].filename, filename);
      filelist[i].loaded = 1;
      ok = 1;
    }
  }
}
