#include <ctype.h>
#include <stdbool.h>
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
  htable_ptr->htable = (word_list*)malloc(sizeof(word_list) * (MAX_ENTRIES + 1));
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

  int fileIndexs[MAX_FILES];
  for(int i=0;i<MAX_FILES;i++){
    fileIndexs[i]=-1;
  }
  int nbFound=0;
  bool found=false;

  int hash = hashcode(word,MAX_ENTRIES);
  word_list * list = &((htable_ptr->htable)[hash]);//+(sizeof(word_list)*hash);//access to the word_list from hash
  word_entry * current_word = list->first_word;
  word_entry * last_word = list->last_word;
  if(current_word == NULL){
      printf("no words\n");
      return found;//no words
  }else{
      do{
          if (strcmp(current_word->word,word)==0){
              //fileindexs[++last_index]=current_word->in_file;
              foundIn(fileIndexs,current_word);
              nbFound+=current_word->times;
              found=true;
          }
          current_word = current_word->next;
      }while(current_word != last_word);
      //last word test
      if (strcmp(current_word->word,word)==0){
              foundIn(fileIndexs,current_word);
              nbFound+=current_word->times;
              found=true;
      }
  }

  if (found){
      printf("word %s found %d times in files : \n",word,nbFound);
      foundInPrint(fileIndexs,filelist);
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
  int i;
  for (i = 0; i < htable_ptr->hsize; i++) {
    word_entry *temp = htable_ptr->htable[i].first_word;
    if(temp != NULL) {
      printf("\nHashcode: %d\n", i);
      while(temp != NULL) {
        // if(filelist[temp->in_file].loaded == 1) {
        printf("[%s]", temp->word);
        temp = temp->next;
        if (temp != NULL)
        {
          printf("->");
        }
        else {
          printf("\n");
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


void foundIn(int tab[],word_entry* ptr){
    int last_index = -1;
    int i;
    for (i =0;i<MAX_FILES ;i++ ){
        if(tab[i]!= -1){
            last_index=i;
        }else{
            i=MAX_FILES;
        }
    }
    tab[last_index]=ptr->in_file;

}


void foundInPrint(int tab[], listfile_entry * filelist){
    int i;
    for(i = 0 ; i<MAX_FILES;i++){
        if(tab[i]!=-1){
            printf("\t %s \n",filelist[tab[i]].filename);
        }else{
            i=MAX_FILES;
        }
    }


}
// TO BE COMPLETED
