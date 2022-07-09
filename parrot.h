#ifndef PARROT
#define PARROT

#include <pthread.h>
#define BUF_SIZE 1024

int chirp();

// handle an incoming message
int handle_connection(int connectionfd);

int get_port_number(int sockfd);

// initialize with other connections
int init();

// wait for user input
int
listen_keys();

// send messages in buffer
int
dump_buffer();

// note on structs: Flock array is to hold other connections, Chirp array is to
// cache messages that have not been replied to

// struct for a Parrot host
typedef struct {
    int connectionfd;
    char buffer[BUF_SIZE];
} Bird;

// struct for a msg to send to a Parrot host
typedef struct {
    char term[64];
    Bird* sender;
} Chirp;

typedef struct {
    int read_head;
    int write_head;
    void** cache[64];
} buffer;

void buffer_set(buffer *, void *);
void* buffer_get(buffer *);
int buffer_size(buffer *);

// fifo terms passed by command line
extern char term_cache[64][64];

// mutex for listening for connections
extern pthread_mutex_t sock_lock, msg_lock;

extern buffer msgs, flock;

extern int flock_index;

#endif
