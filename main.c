#include "buffer.h"
#include "parrot.h"
#include <pthread.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

// global variable declarations
char term_cache[64][64];
pthread_mutex_t sock_lock;
pthread_mutex_t msg_lock;
buffer flock;
buffer msgs;
int flock_index = 0;
Bird me;

int main() {
    if (pthread_mutex_init(&sock_lock, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return 1;
    }
    
    chirp();
    int port = 0;

    struct sockaddr_in addr;

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(port);

    // (1) Create socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        perror("Error opening stream socket");
        // exit(1);
        return -1;
    }

    // (2) Set the "reuse port" socket option
    int yesval = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &yesval, sizeof(yesval)) == -1)
    {
        perror("Error setting socket options");
        // exit(1);
        return -1;
    }
    // (3) Bind to the port.
    if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) == -1)
    {
        perror("Error binding stream socket");
        // exit(1);
        return -1;
    }

    // (3b) Detect which port was chosen.
    port = get_port_number(sock);

    listen(sock, 30);

    printf("@@@ port %d\n", port);

    me.port = port;
    me.connectionfd = sock;
    
    // start thread to listen for connections
    init();

    fflush( stdout );
    while (1)
    {
        int clientsocket = accept(me.connectionfd, 0, 0);
        if (clientsocket == -1)
        {
            perror("Error accepting connection");
            // exit(1);
            return -1;
        }

        handle_connection(me.connectionfd);

        // threading comes later...

        // pthread_create();
        // std::thread s(handle_connection, clientsocket);
        // s.detach();
    }
    pthread_mutex_destroy(&sock_lock);
}
