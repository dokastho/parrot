#ifndef PARROT
#define PARROT

#include <pthread.h>

int chirp();

// fifo terms passed by command line
extern char term_cache[64][64];

// mutex for listening for connections
extern pthread_mutex_t sock_lock;

// struct for a Parrot connection
struct Bird {
    int connectionfd;
    char buffer[1024];
} Flock[64];

#endif
