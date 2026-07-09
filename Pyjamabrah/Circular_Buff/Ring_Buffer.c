/*
Author: MysticWiz
Date:09-07-2026

This is simple Ring/Circular Buffer implentation using c
it stores and load the data

*/


#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "ring_buffer.h"

void RingBuffer_Init(RingBuffer_t *buf)
{
    // Intialize head and tail of the buffer to Zero
    RingBuffer_t *buffer = buf;
    buffer->head=0;
    buffer->tail=0;
    
}

bool RingBuffer_Put(RingBuffer_t *buf, uint8_t val)
{
    RingBuffer_t *buffer = buf;
    // Check if the buffer is full by comparing head and tail
    if((buffer->head + 1) % BUFFER_SIZE == buffer->tail)
    {
        return false;
    }
    //store the val in storage 
    buffer->storage[buffer->head &(BUFFER_SIZE-1)]=val;
    buffer->head++;
    return true;

}

bool RingBuffer_Get(RingBuffer_t *buf, uint8_t *dest)
{
    RingBuffer_t *buffer = buf;
    // check if buffer is empty 
    if(buffer->head == buffer->tail)
    {
        return false;
    }

    //returnt the value stored in storage
    *dest = buffer->storage[buffer->tail&(BUFFER_SIZE-1)]; //we are using tail because the head is used for write and its incremented
    buffer->tail++;
    return true;


}

int main(void) {
    RingBuffer_t my_buffer;
    RingBuffer_Init(&my_buffer);
    uint8_t data;
    
    printf("--- Simulating Incoming CAN/UART Data Stream ---\n");
    
    // 1. Fill buffer up with initial bytes
    do
    {
       printf("Please enter the data to be written :");
    scanf("%hhu",&data);
    
    } while (RingBuffer_Put(&my_buffer, data) == true);
    
    
   
    
    // 2. Read back data byte-by-byte safely via pointers
    uint8_t received_byte;
    while(RingBuffer_Get(&my_buffer, &received_byte)) {
        printf("Processed Byte: 0x%X \n", received_byte);
    }
    
    return 0;
}