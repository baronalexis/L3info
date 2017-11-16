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



  for (i = 0; i < MAX_FILES; i++) {
    if(strcmp(filename, filelist[i].filename) == 0 && filelist[i].loaded) {
      return_value = 1;
    }
  }

  if(filelist_not_full(filelist) == 0) {
    return_value = 2;
  }

  if(file == NULL) {
    return_value = -1;
  }
  file = fopen(filename, "r");

  //gérer la filelist

  while (fscanf(file, "%s", buffer) == 1) {
    int hash = hashcode(buffer, MAX_LENGTH);
    //test si le mot existe ou pas
    strcpy(htable_ptr->htable->first_word->word, buffer);
    htable_ptr->htable->first_word->times = 1;
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

  // TO BE COMPLETED

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
