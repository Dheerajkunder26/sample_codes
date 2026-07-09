#pragma once
#include <stdint.h>
#include <stdbool.h>

#define BUFFER_SIZE  8  // Must be a power of 2 for easy bitwise optimization

typedef struct {
    uint8_t storage[BUFFER_SIZE];
    uint32_t head; // Tracks where we write new incoming bytes
    uint32_t tail; // Tracks where we read processed bytes
} RingBuffer_t;

// Function declarations
void RingBuffer_Init(RingBuffer_t *buf);
bool RingBuffer_Put(RingBuffer_t *buf, uint8_t val);
bool RingBuffer_Get(RingBuffer_t *buf, uint8_t *dest);