#include "buffer.h"

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

void*
buffer_read(buffer *b, int offset)
{
    return b->cache[b->read_head + offset];
}

int
buffer_size(buffer *b)
{
    return b->write_head - b->read_head;
}