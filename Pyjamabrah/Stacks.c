/*
Author: MysticWiz
Date:11-07-2026

Stacks Implementation

- Push Operation
- Peek Operation
- Pop  Operation
- Traverse Operation

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    int data;
    struct node *next_node; // Create a pointer pointing to address of next node
}node_t;

node_t *__top = NULL; 


int push(int data)
{
    node_t *node_1;
    if(!data)
    {
        printf("Invalid data....!\n");
        return -1;
    }

    node_1 = malloc(sizeof(node_t));

     /*
    Throw an error if memory allocation failed
    */
     if(!node_1)
    {
        printf("Memory Allocation Failed..!\n");
        return -2;
    }

    node_1->data = data;
    node_1->next_node = __top;
    __top = node_1;
    return 0;

}

int traverse(void)
{
    for(node_t *node = __top; node !=NULL; node= node->next_node)
    {
        printf("%d\n", node->data);
        printf("--\n");
    }
    return 0;

}

int peek()
{
    if(!__top)
    {
        printf("Stack is Empty !!!\n");
        return -1;
    }
    printf("Top data of stack :%d\n", __top->data);
    return 0;
}

int pop()
{
    
    node_t * to_be_poppedd;
    int data;
    if(!__top)
    {
        printf("Stack is Empty!!!\n");
        return -1;
    }
    data = __top->data;
    to_be_poppedd= __top;
    __top= __top->next_node;
    free(to_be_poppedd);
    printf("Data popped: %d\n", data);
    return 0;
}

int main()
{
    push(1);
    push(2);
    push(4);
    push(7);
    push(8);
    traverse();
    peek();
    pop();
    traverse();
    for(int i =0;i<10;i++)
    {
        pop();
    }

    return 0;
}