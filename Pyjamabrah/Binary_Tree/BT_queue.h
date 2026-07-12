/*
Author: MysticWiz
Date:12-07-2026

Binary Tree Header file

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


void add(char data);

void enqueue(void *node_to_explore);

bool queue_empty(void);

void* dequeue(void);

void destory_queue(void);

void print_Preorder(void);

void print_Postorder(void);

void print_Inorder(void);