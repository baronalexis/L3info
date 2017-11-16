#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int nb_malloc = 0;


static list_elem_t *create_element(int value)
{
  list_elem_t *newelt = malloc(sizeof(list_elem_t));
  if (newelt != NULL)
  {
    ++nb_malloc;
    newelt->value = value;
    newelt->next = NULL;
  }
  return newelt;
}

static void free_element(list_elem_t *l)
{
  --nb_malloc;
  free(l);
}


int insert_head(list_elem_t **l, int value)
{
  if (l == NULL)
  {
    return -1;
  }
  list_elem_t *new_elt = create_element(value);
  if (new_elt == NULL)
  {
    return -1;
  }
  new_elt->next = *l;
  *l = new_elt;
  return 0;
}


int insert_tail(list_elem_t **l, int value)
{


  list_elem_t *new_elt = create_element(value);
  if (new_elt == NULL)
  {
    return -1;
  }
  list_elem_t *current = *l;
	
if(*l == NULL) {
	*l = new_elt;
	return 0;
}

  while (current->next != NULL)
  {
    current = current->next;
  }	
  current->next = new_elt;
  return 0;
}


list_elem_t * find_element(list_elem_t *l, int index)
{
  if(nb_malloc < index)
  {
    printf("Index impossible !");
    return NULL;
  }
  if (l == NULL)
  {
    return NULL;
  }
  if (index < 0)
  {
    return NULL;
  }
  list_elem_t *current = l;
  for (int i = 0; i < index; i++)
  {
    current = current->next;
  }
  return current;
}


int remove_element(list_elem_t **p, int value)
{
  if(p == NULL || *p == NULL)
  {
    return -1;
  }
  list_elem_t *current = *p;
  list_elem_t *pre = NULL;
  if (current->value == value)
  {
    if (current->next == NULL)
    {
      free_element(current);
      *p = NULL;
    }
    else
    {
      *p = current->next;
      free_element(current);
    }
    return 0;
  }
  while (current != NULL)
  {
    pre = current;
    current = current->next;
    if (current != NULL && current->value == value)
    {
      if (current->next == NULL)
      {
        pre->next = NULL;
        free_element(current);
      }
      else
      {
        pre->next = current->next;
        free_element(current);
      }
      return 0;
    }
  }
  return -1;
}


void reverse_list(list_elem_t **l)
{
  if (l != NULL)
  {
    list_elem_t *pre = NULL;
    list_elem_t *cursor = *l;
    list_elem_t *post;
    while (cursor != NULL)
    {
      post = cursor->next;
      cursor->next = pre;
      pre = cursor;
      cursor = post;
    }
    *l = pre;
  }
}
