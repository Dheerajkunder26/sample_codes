/*
Author: MysticWiz
Date:12-07-2026

Binary Tree Implementation
- Add Root
- Add Left child
- Add Right Child
- Enqueue
- Dequque
- Delete Queuee
- Inorder Traverse
- PreOrder Traverse
- Postorder Travese

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "BT_queue.h"

typedef struct node
{
    char data;
    struct node *l_child; 
    struct node *r_child; 

}node_t;

node_t *__root = NULL; 

typedef struct queue_node
{
    void * node;
    struct queue_node *next_node;
} queue_node_t;

queue_node_t *__queue_front = NULL;
queue_node_t *__queue_end = NULL;






void add(char data)
{

  node_t *new_node = malloc(sizeof(node_t));
  new_node->data =  data;
  new_node->l_child = NULL;
  new_node->r_child = NULL;

  // Create Root Node if node is not created
  if(!__root)
  {
    // add the node details to root and enqueue the root address for further traverse
    __root =  new_node;
   
    return;
  }
// check if left root child is empty 
  if (__root->l_child == NULL)
      {
        // add node to root if empty and destory queue since new node is added 
          __root->l_child = new_node;
          destory_queue();
          return;
      }
      else
      {
        // if it has data add the node address in queue for future traverse
          enqueue((void *)__root->l_child);
      }
      // Check if right root child is empty
      if (__root->r_child == NULL)
      {
        // add node to root if empty and destory queue since new node is added 
          __root->r_child = new_node;
          destory_queue();
          return;
      }
      else
      {
        // if it has data add the node address in queue for future traverse
          enqueue((void *)__root->r_child);
      }


  // Add children in the tree
 
  while (queue_empty() == false)
  {
    
      node_t *node = (node_t*)dequeue(); // dequeue the head node address and delete the head 
      // check if left child is empty 
      if (node->l_child == NULL)
      {
        // add node if empty and destory queue since new node is added 
          node->l_child = new_node;
          //printf("next queue : %p\n",node->l_child);
          destory_queue();
          return;
      }
      else
      {
        // if it has data add the node address in queue for future traverse
          enqueue((void *)node->l_child);
      }
      // Check if right child is empty
      if (node->r_child == NULL)
      {
        // add node if empty and destory queue since new node is added 
          node->r_child = new_node;
          destory_queue();
          return;
      }
      else
      {
        // if it has data add the node address in queue for future traverse
          enqueue((void *)node->r_child);
      }
  }
}


void enqueue(void *node_to_explore)
{
    //printf("enqueu:%p\n",node_to_explore);
    queue_node_t *store = (queue_node_t *)malloc(sizeof(queue_node_t));
    store->node=node_to_explore;
    store->next_node = NULL;
    if(__queue_end)
    {
        __queue_end->next_node=store;
        __queue_end= store;
        
    }
    else
    {
        __queue_front = store;
        __queue_end = store;
    }
    
   

}

bool queue_empty(void)
{
    if(__queue_front == NULL)
    {
        return true;
    }
    else
    {
       // printf("front:0x%016llx, end:0x%016llx\n",__queue_front->node,__queue_end->node);
        return false;
    }
}

void* dequeue(void)
{
    void *dequeue_address =NULL;
    if(!__queue_front)
    {
       
      return 0;   
    } 
    
    dequeue_address = __queue_front->node;
    queue_node_t *temp = __queue_front->next_node;

    free(__queue_front);
    __queue_front = temp;
    return dequeue_address;


}

void destory_queue(void)
{

    for(queue_node_t *ptr = __queue_front;
        ptr!=NULL;
        ptr=ptr->next_node)
        {
           // printf("free : %p\n",ptr->node);
            free(ptr);
        }
    __queue_front = NULL;
    __queue_end = NULL;

}



void Preorder(node_t *node)
{
 if(!node)
 {
    return;
 }
 printf(" :%c: ",node->data);
 Preorder(node->l_child);
 Preorder(node->r_child);
}

void print_Preorder(void)
{
    printf("Preorder :");
    Preorder(__root);
    printf("\n");
}



void Inorder(node_t *node)
{
 if(!node)
 {
    return;
 }
 
 Inorder(node->l_child);
 printf(" :%c: ",node->data);
 Inorder(node->r_child);
}

void print_Inorder(void)
{
    printf("Inorder :");
    Inorder(__root);
    printf("\n");
}


void Postorder(node_t *node)
{
 if(!node)
 {
    return;
 }
 Postorder(node->r_child);
 Postorder(node->l_child);
 printf(" :%c: ",node->data);
 
}

void print_Postorder(void)
{
    printf("Postorder :");
    Postorder(__root);
    printf("\n");
}