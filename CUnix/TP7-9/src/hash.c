#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h" // global functions declarations

//------------------------------------------------------------------------
// global functions definitions
//------------------------------------------------------------------------

/**
   create and initialize hash table

   returns : pointer to table or NULL if creation error
*/
hash_table *create_table(){
    int i;
    hash_table *htable_ptr = NULL;
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
int search_word(char word[], listfile_entry * filelist, hash_table * htable_ptr) {

    int i = 0;
    for(i = 0; word[i]; i++){
        word[i] = tolower(word[i]);
    }
    int hash = hashcode(word, MAX_ENTRIES);

    int file_indexes[MAX_FILES];

    for(i = 0; i < MAX_FILES; i++) {
        file_indexes[i] = 0;
    }
    int found = 0;

    word_list list = (htable_ptr->htable)[hash];
    word_entry * current_word = list.first_word;

    if(current_word == NULL) {
        return found;
    }
    else {
        while (current_word != NULL) {
            if (strcmp(current_word->word,word) == 0) {
                file_indexes[current_word->in_file] = current_word->times;
                found = 1;
            }
            current_word = current_word->next;
        }
    }

    if (found) {
        for (i = 0; i < MAX_FILES; i++) {
            if(file_indexes[i] != 0) {
                printf("Word(%s) found %d times in File(%s)\n", word, file_indexes[i], filelist[i].filename);
            }
        }
    }
    return found;
}

void search_word_not(char word[], listfile_entry * filelist, hash_table * htable_ptr) {

      int i = 0;
      for(i = 0; word[i]; i++){
          word[i] = tolower(word[i]);
      }
      int hash = hashcode(word, MAX_ENTRIES);

      int file_indexes[MAX_FILES];

      for(i = 0; i < MAX_FILES; i++) {
          file_indexes[i] = 0;
      }

      word_list list = (htable_ptr->htable)[hash];
      word_entry * current_word = list.first_word;

      if(current_word == NULL) {
        for (i = 0; i < MAX_FILES; i++) {
            if(file_indexes[i] == 0 && filelist[i].loaded == 1) {
                printf("Word(%s) not in File(%s)\n", word, filelist[i].filename);
            }
        }
        return;
      }
      else {
          while (current_word != NULL) {
              if (strcmp(current_word->word,word) == 0) {
                  file_indexes[current_word->in_file] = current_word->times;
              }
              current_word = current_word->next;
          }
      }
      for (i = 0; i < MAX_FILES; i++) {
          if(file_indexes[i] == 0 && filelist[i].loaded == 1) {
              printf("Word(%s) not in File(%s)\n", word, filelist[i].filename);
          }
      }
}



/**
   print table contents

   parameters :
   htable_ptr : pointer to hash table
   filelist   : pointer to table of files
*/
void print_table(hash_table * htable_ptr, listfile_entry * filelist)
{
    int i = 0;
    for (i = 0; i < htable_ptr->hsize; i++) {

        word_entry *temp = htable_ptr->htable[i].first_word;
        while(temp != NULL) {
            if(filelist[temp->in_file].loaded == 1) {
                printf("\nHashcode(%d) - Word(%s) appears %d times - File(%s)", i, temp->word, temp->times, filelist[temp->in_file].filename);
                temp = temp->next;
            }
        }
    }
    printf("\n\n");
}


/**
   free hash table

   parameters :
   htable_ptr : pointer to hash table
*/
void free_table(hash_table * htable_ptr) {
    int i = 0;
    word_entry * tmp;
    for (i = 0; i < htable_ptr->hsize; i++) {
        word_entry *head = htable_ptr->htable[i].first_word;
        while (head != NULL) {
            tmp = head;
            head = head->next;
            free(tmp);
        }
    }
    free(htable_ptr->htable);
    free(htable_ptr);

}
