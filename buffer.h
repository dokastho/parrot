#define BUF_SIZE 64


typedef struct {
    int read_head;
    int write_head;
    void** cache[BUF_SIZE];
} buffer;

void buffer_set(buffer *, void *);
void* buffer_get(buffer *);
void* buffer_read(buffer *, int);
int buffer_size(buffer *);
