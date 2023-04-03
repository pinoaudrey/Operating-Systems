/** @file libpriqueue.c
 */

#include <stdlib.h>
#include <stdio.h>

#include "libpriqueue.h"


/**
  Initializes the priqueue_t data structure.
  
  Assumtions
    - You may assume this function will only be called once per instance of priqueue_t
    - You may assume this function will be the first function called using an instance of priqueue_t.
  @param q a pointer to an instance of the priqueue_t data structure
  @param comparer a function pointer that compares two elements.
  See also @ref comparer-page
 */
void priqueue_init(priqueue_t *q, int(*comparer)(const void *, const void *))
{
  q -> comp = comparer;
  q -> size = 0;
  q -> head = NULL;
}


/**
  Insert the specified element into this priority queue.

  @param q a pointer to an instance of the priqueue_t data structure
  @param ptr a pointer to the data to be inserted into the priority queue
  @return The zero-based index where ptr is stored in the priority queue, where 0 indicates that ptr was stored at the front of the priority queue.
 */
int priqueue_offer(priqueue_t *q, void *ptr)
{
  Node *temp = malloc(sizeof(Node));
  temp -> data = ptr;
  temp -> next = NULL;
  if(q -> size == 0)
  {
    q -> head = temp;
  }
  else
  {
    Node* curr = q -> head;
    Node* prev = NULL;
    int index = 0;
    while(curr != NULL && q -> comp(curr -> data, ptr) < 0)
    {
      prev = curr;
      curr = curr -> next;
      index++;
    }
    if(index == 0)
    {
      temp -> next = q -> head;
      q -> head = temp;
    }
    else
    {
      temp -> next = curr;
      prev -> next = temp;
    }
  }
  q -> size++;
  return (q -> size);
}


/**
  Retrieves, but does not remove, the head of this queue, returning NULL if
  this queue is empty.
 
  @param q a pointer to an instance of the priqueue_t data structure
  @return pointer to element at the head of the queue
  @return NULL if the queue is empty
 */
void *priqueue_peek(priqueue_t *q)
{
  if(q -> size == 0)
  {
    return NULL;
  }
  else
  {
    return q -> head -> data;
  }
}


/**
  Retrieves and removes the head of this queue, or NULL if this queue
  is empty.
 
  @param q a pointer to an instance of the priqueue_t data structure
  @return the head of this queue
  @return NULL if this queue is empty
 */
void *priqueue_poll(priqueue_t *q)
{
  if(q -> size == 0)
  {
    return NULL;
  }
  else
  {
    Node* temp = q -> head;
    void *ptr =0;
    if(temp -> next != NULL){
      q -> head = q -> head -> next;
    }
    else{
      q -> head = NULL;
    }
    ptr = temp -> data;
    free(temp);
    q -> size--;
    return ptr;
  }
}


/**
  Returns the element at the specified position in this list, or NULL if
  the queue does not contain an index'th element.
 
  @param q a pointer to an instance of the priqueue_t data structure
  @param index position of retrieved element
  @return the index'th element in the queue
  @return NULL if the queue does not contain the index'th element
 */
void *priqueue_at(priqueue_t *q, int index)
{
  if(index < 0 || index >= q -> size)
  {
    return NULL;
  }
  else
  {
    Node *curr = q -> head;
    for(int i = 0; i < index; i++)
    {
      curr = curr -> next;
    }
    return curr -> data;
  }
}


/**
  Removes all instances of ptr from the queue. 
  
  This function should not use the comparer function, but check if the data contained in each element of the queue is equal (==) to ptr.
 
  @param q a pointer to an instance of the priqueue_t data structure
  @param ptr address of element to be removed
  @return the number of entries removed
 */
int priqueue_remove(priqueue_t *q, void *ptr)
{
  if(q -> size == 0)
  {
    return 0;
  }
  if(q -> comp(ptr, q -> head -> data) == 0)
  {
    Node *temp = q -> head;
    q -> head = q -> head -> next;
    q -> size--;
    free(temp);

    return (priqueue_remove(q, ptr) + 1);
  }
  Node* curr = q -> head;
  Node* prev = q -> head;
  int count = 0;
  while(curr != NULL)
  {
    if(curr -> data == ptr)
    {
      count++;
      q -> size--;
      Node* temp = curr;
      curr = curr -> next;
      prev -> next = curr;
      free(temp);
    }
    else
    {
      prev = curr;
      curr = curr -> next;
    }
  }
  return count;
}


/**
  Removes the specified index from the queue, moving later elements up
  a spot in the queue to fill the gap.
 
  @param q a pointer to an instance of the priqueue_t data structure
  @param index position of element to be removed
  @return the element removed from the queue
  @return NULL if the specified index does not exist
 */
void *priqueue_remove_at(priqueue_t *q, int index)
{
  if(index >= q -> size)
  {
    return NULL;
  }

  Node* curr = q -> head;
  q -> size--;

  if(index == 0){
    q -> head = q -> head -> next;
    return curr;
  }

  Node* prev = curr;
  curr = curr -> next;

  for(int i = 0; i < index; i++)
  {
    prev = curr;
    curr = curr -> next;
  }
  prev -> next = curr -> next;
  return curr;
}


/**
  Return the number of elements in the queue.
 
  @param q a pointer to an instance of the priqueue_t data structure
  @return the number of elements in the queue
 */
int priqueue_size(priqueue_t *q)
{
  return q -> size;
}


/**
  Destroys and frees all the memory associated with q.
  
  @param q a pointer to an instance of the priqueue_t data structure
 */
void priqueue_destroy(priqueue_t *q)
{
  while(q -> size != 0)
  {
    void *temp = priqueue_remove_at(q, 0);
    free(temp);
  }
}