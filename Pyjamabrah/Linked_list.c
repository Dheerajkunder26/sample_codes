/*
Author: MysticWiz
Date:10-07-2026

Linked List Implementation
- Initalized node
- Add node at the Start
- Add node at the End
- Traverse Linked List
- Delete Node

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    int data;
    struct node *next_node; // Create a pointer pointing to address of next node
}node_t;

node_t *__head; 


int init(int data)
{

    /* 
    -Check if head is initaliazed, if it is and user tried to initialze it again throw error
    -if we initalize it again the old head memory will be lost and it will be memory leak
    */
    if(__head)
    {
        printf("The linked list is already initalized...!!\n");
        return -1;
    }

    __head = malloc(sizeof(node_t));

    /*
    Throw an error if memory allocation failed
    */

    if(!__head)
    {
        printf("Memory Allocation Failed..!\n");
        return -2;
    }


    __head->next_node = NULL; // since this is the only node it is set as NULL
    //memcpy(__head->data,data,strlen(data));
    __head->data=data;

    return 0;

}

/*
 Adding list at the start takes O(1) time 
*/


int add_start(int data)
{
    /*
    Check if valid data is updated by the user
    */
    if(!data)
    {
        printf("Invalid data....!\n");
        return -1;
    }

    node_t *node_1 = malloc(sizeof(node_t));

     /*
    Throw an error if memory allocation failed
    */
     if(!node_1)
    {
        printf("Memory Allocation Failed..!\n");
        return -2;
    }
    
    node_1->next_node=__head; // here the Head node is set as last node and new nodes are added before the head
   // memcpy(node_1->data,data,strlen(data));
    node_1->data=data;
    __head = node_1; // updating the current node as head node (address of head is replaced by node_1 address and only head address is strored in above code)
    
    return 0;


}

/*
 Adding list at the end takes O(n) time 
*/

int add_end(int data)
{
    node_t *cur;
    /*
    Check if valid data is updated by the user
    */
    if(!data)
    {
        printf("Invalid data....!\n");
        return -1;
    }

    node_t *node_1 = malloc(sizeof(node_t));

     /*
    Throw an error if memory allocation failed
    */
     if(!node_1)
    {
        printf("Memory Allocation Failed..!\n");
        return -2;
    }
    //memcpy(node_1->data,data,strlen(data));
    node_1->data=data;
    node_1->next_node=NULL;
    

    for(cur =__head;cur->next_node!=NULL;cur=cur->next_node)
    {
        //Do nothing just Traverse to end to the linked list
    }
   cur->next_node=node_1; // at first head->next node is empty so it exit the for loop and here the next_node is set to newly created node_1 and it continues...
   return 0;


}

int search (int data)
{
    for (node_t *cursor =__head;cursor != NULL; cursor= cursor->next_node)
    {
        if(cursor->data == data)
        {
            printf("Found the data %d \n", data);
            return 1;
        }
    } 
    return 0;

}

int delete(int data)
{
    node_t *head;
    if(__head->data ==data)
    {
        head = __head->next_node;
        printf("Deleted %d\n", data);
        free(__head);
        __head=head;
        return 0;
    }
    for ( node_t *prev = NULL,*curr = __head;
          curr != NULL;
          prev = curr,curr = curr->next_node)
    {
        if(curr->data == data)
        {
            prev->next_node = curr->next_node;
            free(curr);
            printf("Deleted %d\n", data);
            
        }
    }
    return 0;
}

void travers(void)
{
    printf("Linked List : "); 
    for (node_t *cursor =__head;cursor != NULL; cursor= cursor->next_node)
    {
        printf("  %d ",cursor->data);
    } 
 printf("\n"); 
}

int insert(int key, int data)
{
    node_t *key_node,*new_node;
    for (key_node =__head;key_node != NULL; key_node= key_node->next_node)
    {
        if(key_node->data == key)
        {
            break;
        }
    } 
    if(!key_node)
    {
        printf("Insertion Failed: Key not found \n");
        return -1;
    }
     new_node = malloc(sizeof(node_t));

     /*
    Throw an error if memory allocation failed
    */
     if(!new_node)
    {
        printf(" Insertion Failed : Memory Allocation Failed..!\n");
        return -2;
    }
    new_node->data = data;
    new_node->next_node = key_node->next_node;
    key_node->next_node = new_node;

    return 1;

}

int main()
{
    init(101);
    add_end(121);
    add_end(131);
    add_end(121);
    travers();
    search(121);

    delete(121);
    travers();
    insert(101,121);
    travers();
    return 0;

}