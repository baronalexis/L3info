#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "functions.h"

//------------------------------------------------------------------------

void display_loaded_files(listfile_entry *);

//------------------------------------------------------------------------

int main()
{
  // create hash table
  hash_table *hashtable = create_table();
  // create filelist array
  listfile_entry *filelist = create_filelist(MAX_FILES);

  int ret;
  char str[50];


  // display menu
  while (1) {
    int nbchoices = 0;
    fprintf(stderr, "\nChoisir une action\n");
    fprintf(stderr, "%d. Load a file in dictionary\n", ++nbchoices);
    fprintf(stderr, "%d. Search a word in dictionary\n", ++nbchoices);
    fprintf(stderr, "%d. Remove file from dictionary\n", ++nbchoices);
    fprintf(stderr, "\n");
    fprintf(stderr, "%d. Print dictionary\n", ++nbchoices);
    fprintf(stderr, "%d. Print file list\n", ++nbchoices);
    fprintf(stderr, "\n0. Quit\n");
    int choice;
    while (1) {
      fprintf(stderr, "Your choice ? ");
      scanf("%d", & choice);
      if (choice >= 0 && choice <= nbchoices) { break; }
      fprintf(stderr, "\nError %d is an incorrect choice\n", choice);
    }
    if (choice == 0) { break; }

    fprintf(stderr, "-------------------------------------------------\n");

    // TO BE COMPLETED

    switch (choice) {
      // Load a file in dictionary
    case 1:
      fprintf(stderr, "Enter the file name:\n");
      scanf("%s", str);

      ret = add_file(str, filelist, hashtable);

      switch(ret) {
        case -2:
          printf("Allocation error\n");
          break;
        case -1:
          printf("File doesn't exist or cant be read\n");
          break;
        case 1:
          printf("File already loaded\n");
          break;
        case 2:
          printf("No space left in filelist, too many files loaded\n");
          break;
      }
      break;

      // Search a word in dictionary
    case 2:
      fprintf(stderr, "Enter the word you are looking for:\n");
      scanf("%s", str);
      ret = search_word(str, filelist, hashtable);
      if (ret == 0) {
        printf("Word not found !\n");
      }
      break;

      // Remove file from dictionary
    case 3:
      printf("This are the loaded files: \n");
      //function displaying all the loaded files
      display_loaded_files(filelist);
      printf("Enter the file you want to remove:\n");
      scanf("%s", str);

      ret = remove_file(str, filelist, hashtable);
      switch (ret) {
        case 0:
          printf("File successfully removed !\n");
          break;
        case -1:
          printf("File isn't loaded !\n");
      }

      break;

      // Print dictionary
    case 4:
      print_table(hashtable, filelist);
      break;

      // Print file list
    case 5:
      print_list(filelist);

      break;
    }
    fprintf(stderr, "-------------------------------------------------\n");

  }

  free_filelist(filelist);
  free_table(hashtable);

  return 0;
}

// compute hash value for word
// returns : N ; 0 <= N < size
int hashcode(char word[], int size)
{
  int hash = 0;
  while(*word != '\0') {
    hash += *word++;
  }
  return (hash % size);
}


void display_loaded_files(listfile_entry * filelist) {
  printf("\n");
  for (int i = 0; i < MAX_FILES; i++) {
    if(filelist[i].loaded == 1) {
        printf("%s\n", filelist[i].filename);
    }
  }
  printf("\n");
}
