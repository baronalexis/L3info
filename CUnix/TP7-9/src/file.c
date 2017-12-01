#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/types.h"
#include "../include/functions.h" // extern functions declarations

// ------------------------------------------------------------------------
// inner functions declarations
// ------------------------------------------------------------------------

word_entry * add_word(char *, int, word_list *);
void add_filelist(char *, listfile_entry *, int);
int find_free_index(listfile_entry *, char *);




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
  listfile_entry *listfile_ptr = NULL;
  listfile_ptr = (listfile_entry*)malloc(sizeof(listfile_entry) * maxfiles);
  for (int i = 0; i < maxfiles; i++) {
    strcpy(listfile_ptr[i].filename, "");
    listfile_ptr[i].loaded = 0;
  }

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
  int index = find_free_index(filelist,filename);

  file = fopen(filename, "r");

	if(index == -1) {
		return 1;
	}
	if(index == -2) {
		return 2;
	}

  if(file == NULL) {
    return -1;
  }

  add_filelist(filename, filelist, index);
  while (fscanf(file, "%s", buffer) == 1) {
    int hash = hashcode(buffer, MAX_LENGTH);
    printf("%d->%s\n", hash, buffer);
    add_word(buffer, index, &(htable_ptr->htable[hash]));
  }

  if(feof(file)) {
		return 0;
  } else {
		return -2;
  }
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
  for (int i = 0; i < MAX_FILES; i++) {
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
	free(filelist);
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

word_entry* add_word(char* name, int fileindex,word_list* list) {

  word_entry* newelt = (word_entry*)malloc(sizeof(word_entry));

	if(newelt != NULL) {
		strcpy(newelt->word,name);
		newelt->in_file= fileindex;
		newelt->times = 0;
		newelt->next = NULL;

		if (list->last_word != NULL) {
			list->last_word->next = newelt;
		}else {
			list->first_word = newelt;
		}
		list->last_word = newelt;
	}

	return newelt;
}



void add_filelist(char * filename, listfile_entry * filelist, int index) {
      strcpy(filelist[index].filename, filename);
      filelist[index].loaded = 1;
}


/*
	returns:
		-2: if filelist full
		-1: if file already present in filelist
		else:
			free index if free space
*/
int find_free_index(listfile_entry * list, char* word) {

	int index = 0;

	while(index < MAX_FILES) {
		if(strcmp(list[index].filename, word) == 0) {
			return -1;
		}
		if(list[index].loaded == 0) {
			return index;
		}
		index++;
	}
	return -2;
}
