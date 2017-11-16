/**************************************************************************
 * L3Informatique						C/Unix
 * 			TP de programmation en C :
 *		         Test de listes chaînées
 *
 * Groupe 	: 3.2
 * Nom Prénom 1 : Baron Alexis
 * Nom Prénom 2 : Foucheur Alexandre
 *
 **************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

extern int nb_malloc;

static int list_size(list_elem_t *p_list)
{
  int nb = 0;
  while (p_list != NULL)
  {
    nb += 1;
    p_list = p_list->next;
  }
  return nb;
}

void print_list(list_elem_t *p_list)
{
  list_elem_t *pl = p_list;
  printf("La liste contient %d élément(s)\n", list_size(p_list));
  while (pl != NULL)
  {
    printf("[%d]", pl->value);
    pl = pl->next;
    if (pl != NULL)
    {
      printf("->");
    }
  }
}

int main(int argc, char **argv)
{
  list_elem_t *la_liste = NULL; 
  char menu[] =
      "\n Programme de test de listes\n"
      "  't/q' : ajout d'un élément en tête/queue de liste\n"
      "  'f'   : recherche du xième élément de la liste\n"
      "  's'   : suppression d'un élément de la liste\n"
      "  'r'   : renverser l'ordre des éléments de la liste\n"
      "  'x'   : quitter le programme\n"
      " Quel est votre choix ?";
  int choix = 0; 
  int value = 0; 

  printf("%s", menu);
  fflush(stdout);

  while (1)
  {
    fflush(stdin);
    choix = getchar();
    printf("\n");

    switch (choix)
    {
    case 'H':
    case 'h':
      printf("Valeur du nouvel element en tête ? \n");
      scanf("%d", &value);
      if (insert_head(&la_liste, value) != 0)
      {
        printf("Erreur : impossible d'ajouter l'élément %d\n", value);
      };
      break;

    case 'T':
    case 't':
      printf("Valeur du nouvel element en queue ? \n");
      scanf("%d", &value);
      if (insert_tail(&la_liste, value) != 0)
      {
        printf("Erreur : impossible d'ajouter l'élément %d\n", value);
      };
      break;

    case 'F':
    case 'f':
      printf("Index recherché ? \n");
      scanf("%d", &value);
      list_elem_t *point = find_element(la_liste, value);
      if (point == NULL)
      {
        printf("Echec.\n");
      }
      else
      {
        printf("La valeur de l'element %d est %d\n", value, point->value);
      }
      break;

    case 'r':
    case 'R':
      reverse_list(&la_liste);
      printf("La liste a été renversée !\n");
      break;

    case 's':
    case 'S':
      printf("Valeur à supprimer ?\n");
      scanf("%d", &value);
      if (remove_element(&la_liste, value) == -1)
      {
        printf("Echec.\n");
      }
      else
      {
        printf("Element retiré avec succès.\n");
      }
      break;

    case 'x':
    case 'X':
      return 0;

    default:
      break;
    }
    print_list(la_liste);

    if (nb_malloc != list_size(la_liste))
    {
      printf("\nAttention : Fuite mémoire dans votre programme !\n");
      printf("la liste contient %d élement pour %d élément alloués en mémoire !\n",
             list_size(la_liste), nb_malloc);
    }
    getchar();
    printf("%s\n", menu);
  }
  return 0;
}
