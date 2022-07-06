#ifndef PARROT
#define PARROT

#include <pthread.h>

int chirp();

// struct for a Parrot connection
typedef struct {
    int connectionfd;
    char buffer[1024];
} Bird;

// fifo terms passed by command line
extern char term_cache[64][64];

// mutex for listening for connections
extern pthread_mutex_t sock_lock;

extern Bird Flock[64];

#endif
