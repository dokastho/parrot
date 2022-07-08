#ifndef PARROT
#define PARROT

#include <pthread.h>
#define BUF_SIZE 1024

int chirp();

// send len bytes from buf over sock
int send_bytes(int sock, const char *buf, int len);

int get_port_number(int sockfd);

// initialize with other connections
int init();

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

// fifo terms passed by command line
extern char term_cache[64][64];

// mutex for listening for connections
extern pthread_mutex_t sock_lock, msg_lock;

extern Bird flock[64];

extern Chirp msg_cache[64];

#endif
