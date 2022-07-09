#include "parrot.h"

void
buffer_set(buffer *b, void* item)
{
    b->cache[b->write_head] = item;
    b->write_head++;
}

void*
buffer_get(buffer *b)
{
    void* item = b->cache[b->read_head];
    b->read_head++;
    return item;
}

int
buffer_size(buffer *b)
{
    return b->write_head - b->read_head;
}