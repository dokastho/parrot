#include "parrot.h"
#include <sys/socket.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

// global variable declarations
char term_cache[64][64];
pthread_mutex_t sock_lock;

int main() {
    if (pthread_mutex_init(&sock_lock, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return 1;
    }
    chirp();
    pthread_mutex_destroy(&sock_lock);
}
