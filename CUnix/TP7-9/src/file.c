#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "functions.h" // extern functions declarations

// ------------------------------------------------------------------------
// inner functions declarations
// ------------------------------------------------------------------------

void add_word(char *, int, word_list *);
void add_filelist(char *, listfile_entry *, int);
int find_free_index(listfile_entry *, char *);
void remove_words_from_file(word_entry **, int);
int is_word_loaded(char *, int, word_list *);




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
    for(int i = 0; buffer[i]; i++){
      buffer[i] = tolower(buffer[i]);
    }
    int hash = hashcode(buffer, MAX_LENGTH);
    // int word_loaded = is_word_loaded(buffer, index, &(htable_ptr->htable[hash]));
    // if(word_loaded == 0) {
      add_word(buffer, index, &(htable_ptr->htable[hash]));
    // } else {
    //   //inc_times_word(buffer);
    // }
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

  for (int i = 0; i < MAX_FILES; i++) {
    if(strcmp(filename, filelist[i].filename) == 0 && filelist[i].loaded == 1) {
      filelist[i].loaded = 0;
      // for (int y = 0; i < MAX_ENTRIES; y++) {
      //   remove_words_from_file(&(htable_ptr->htable[y].first_word), i);
      // }
      return 0;
    }
  }
  return -1;
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




void remove_words_from_file(word_entry **head, int filelist_position)
{


    // If linked list is empty
   if (head == NULL || *head == NULL)
      return;

    // Store head node
    word_entry* current = *head;
    word_entry* pre = NULL;

    if (current->in_file == filelist_position)
    {
      if (current->next == NULL)
      {
        free(current);
        *head = NULL;
      }
      else
      {
        *head = current->next;
        free(current);
      }
      return;
    }
    while (current != NULL)
    {
      pre = current;
      current = current->next;
      if (current != NULL && current->in_file == filelist_position)
      {
        if (current->next == NULL)
        {
          pre->next = NULL;
          free(current);
        }
        else
        {
          pre->next = current->next;
          free(current);
        }
        return;
      }
    }
    return;
}



void add_word(char* name, int fileindex, word_list* list) {

  word_entry* newelt = (word_entry*)malloc(sizeof(word_entry));

	if(newelt != NULL) {
		strcpy(newelt->word,name);
		newelt->in_file = fileindex;
		newelt->times = 1;
		newelt->next = NULL;

		if (list->last_word != NULL) {
			list->last_word->next = newelt;
		}else {
			list->first_word = newelt;
		}
		list->last_word = newelt;
	}
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
