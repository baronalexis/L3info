#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/functions.h" // global functions declarations

// ------------------------------------------------------------------------
// inner functions declarations
// ------------------------------------------------------------------------

// TO BE COMPLETED

//------------------------------------------------------------------------
// global functions definitions
//------------------------------------------------------------------------

/**
   create and initialize hash table

   returns : pointer to table or NULL if creation error
*/
hash_table *create_table()
{
  int i;
  hash_table *htable_ptr;
  htable_ptr = (hash_table*)malloc(sizeof(hash_table));
  htable_ptr->hsize = MAX_ENTRIES;
  htable_ptr->htable = (word_list*)malloc(sizeof(word_list) * htable_ptr->hsize);
  for (i = 0; i < htable_ptr->hsize; i++) {
    htable_ptr->htable[i].first_word = NULL;
    htable_ptr->htable[i].last_word = NULL;
  }
  return htable_ptr;
}

/**
   search a word in table ; print word if found, with number of occurrences
   and file where word is found

   parameters :
   word : the word to look for
   filelist   : pointer to table of files
   htable_ptr : pointer to hash table

   returns : true if found, false otherwise
*/
int search_word(char word[], listfile_entry * filelist, hash_table * htable_ptr)
{

  // TO BE COMPLETED
  //printf("%s\n", );
  return true;
}

/**
   print table contents

   parameters :
   htable_ptr : pointer to hash table
   filelist   : pointer to table of files
*/
void print_table(hash_table * htable_ptr, listfile_entry * filelist)
{
  int i;
  int j = 0;
  word_entry * temp = htable_ptr[j].htable->first_word;
  for (i = 0; i < htable_ptr->hsize; i++) {
    if(htable_ptr->htable->first_word != NULL) {
      printf("Hashcode: %d", i);
      while(temp->next != htable_ptr[j].htable->last_word) {
        if(filelist[temp->in_file].loaded == 1)
        printf("%s -> ",temp->word);
      }
    }
  }
}


/**
   free hash table

   parameters :
   htable_ptr : pointer to hash table
*/
void free_table(hash_table * htable_ptr)
{

  // TO BE COMPLETED

}

// ------------------------------------------------------------------------
// inner functions definitions
// ------------------------------------------------------------------------

// TO BE COMPLETED
