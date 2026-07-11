/*
Author: MysticWiz
Date:11-07-2026

Queue Implementation
- Initalized node
- Add node at the End
- Traverse Linked List
- Fetch Node

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    int data;
    struct node *next_node; // Create a pointer pointing to address of next node
}node_t;

node_t *__head = NULL; 
node_t *__tail= NULL;


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

    // Set tail and head as same pointer

    __tail = __head ;

    return 0;

}

/*
 Adding list at the start takes O(1) time 
*/




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
    node_1->next_node =NULL;
    // set tail as the last node so no need to itrate every node to find the last node
    __tail->next_node = node_1;
    __tail = node_1;
    

   
   return 0;


}




void travers(void)
{
    printf("Linked List : "); 
    for (node_t *cursor =__head;cursor != NULL; cursor= cursor->next_node)
    {
        printf("%d-->",cursor->data);
    } 
 printf(" {}\n"); 
}



int fetch(void)
{
    int data;
    node_t *to_be_deleted;

    if(!__head)
    {
        printf("Empty Queue !!\n");
    }

    data = __head->data;
    to_be_deleted = __head;
    __head = __head->next_node;
    free(to_be_deleted);
    return 0;


}

int main()
{
    init(101);
    add_end(121);
    add_end(131);
    add_end(141);
    travers();
    fetch();
    travers();
    fetch();
    travers();

    return 0;

}