#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h" // global functions declarations

// ------------------------------------------------------------------------
// inner functions declarations
// ------------------------------------------------------------------------

void foundIn(int[],word_entry*);
void foundInPrint(int[], listfile_entry *);


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
  hash_table *htable_ptr = NULL;
  htable_ptr = (hash_table*)malloc(sizeof(hash_table));
  htable_ptr->hsize = MAX_ENTRIES;
  htable_ptr->htable = (word_list*)malloc(sizeof(word_list) * MAX_ENTRIES);
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
  for(int i = 0; word[i]; i++){
    word[i] = tolower(word[i]);
  }
  int hash = hashcode(word, MAX_LENGTH);

  int file_indexes[MAX_FILES];

  for(int i = 0; i < MAX_FILES; i++) {
    file_indexes[i] = 0;
  }

  int nb_found = 0;
  int found = 0;

  word_list list = (htable_ptr->htable)[hash];
  word_entry * current_word = list.first_word;

  if(current_word == NULL) {
      printf("This word isn't loaded\n");
      return found;
  } else {
    while (current_word != NULL) {
      if (strcmp(current_word->word,word) == 0) {
        printf("Word: %s, Number of occurrences: %d\n", word, current_word->times);
        file_indexes[current_word->in_file] = 1;
        nb_found += current_word->times;
        found = 1;
      }
      current_word = current_word->next;
    }
  }

  if (found) {
      printf("Word %s found %d times in files : \n", word, nb_found);
      for (int i = 0; i < MAX_FILES; i++) {
        if(file_indexes[i] == 1) {
          printf("%s\n", filelist[i].filename);
        }
      }
  }
return found;//not found
}

/**
   print table contents

   parameters :
   htable_ptr : pointer to hash table
   filelist   : pointer to table of files
*/

void print_table(hash_table * htable_ptr, listfile_entry * filelist)
{
  for (int i = 0; i < htable_ptr->hsize; i++) {

    word_entry *temp = htable_ptr->htable[i].first_word;
    if(temp != NULL) {
      printf("\nHashcode: %d\n", i);
      while(temp != NULL) {
        if(filelist[temp->in_file].loaded == 1) {
          printf("[%s]", temp->word);
          temp = temp->next;
          if (temp != NULL) {
            printf("->");
          }
          else {
            printf("\n");
          }
        }
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
