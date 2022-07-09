#include "buffer.h"
#include "parrot.h"
#include <netinet/in.h>
#include <stdio.h>
#include <pthread.h>
#include <memory.h>
#include <sys/socket.h>
#include <unistd.h>

// CONNECTION FUNCTIONS

// send len bytes from buf over sock
int send_bytes(int sock, const char *buf, int len)
{
    int sent = 0;
    int n = 0;
    do
    {
        n = send(sock, buf + sent, len - sent, MSG_NOSIGNAL);
        sent += n;
    } while (sent < len);
    return 0;
}

int get_port_number(int sockfd)
{
    struct sockaddr_in addr;
    socklen_t length = sizeof(addr);
    if (getsockname(sockfd, (struct sockaddr *)&addr, &length) == -1)
    {
        perror("Error getting port of socket");
        // exit(1);
        return -1;
    }
    // Use ntohs to convert from network byte order to host byte order.
    return ntohs(addr.sin_port);
}

int init()
{
    if (pthread_mutex_init(&msg_lock, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return 1;
    }
    // add current bird to flock
    buffer_set(&flock, &me);

    // search for other birds
    return 0;
}

int handle_connection(int connectionfd)
{
    // (1) Receive message from client.

    char msg_cstr[MSG_SIZE];
    memset(msg_cstr, 0, sizeof(msg_cstr));

    // Call recv() enough times to consume all the data the client sends.
    size_t recvd = 0;
    ssize_t rval;

    pthread_mutex_lock(&msg_lock);

    do
    {
        // Receive as many additional bytes as we can in one call to recv()
        // (while not exceeding 1024 bytes in total).
        rval = recv(connectionfd, msg_cstr + recvd, MSG_SIZE - recvd, 0);
        if (rval == -1)
        {
            perror("Error reading stream message");
            // exit(1);
            return -1;
        }
        recvd += rval;
    } while (msg_cstr[strlen(msg_cstr)] != '\0'); // old: recv() returns 0 when client closes

    pthread_mutex_unlock(&msg_lock);

    close(connectionfd);
    // (2) Print out the message
    // lock print

    // (3) reply (if necessary)

    // char reply[MSG_SIZE] = {'\0'};
    // for (size_t i = 0; i < strlen(response.c_str()); i++)
    // {
    //     reply[i] = response.c_str()[i];
    // }

    // (4) Send reply

    // send_bytes(send_sock, reply, MAX_MESSAGE_SIZE);

    // (5) Close connection
    // close(send_sock);

    return 0;
}

int sendall(Chirp *c)
{
    for (int i = 0; i < buffer_size(&flock); i++)
    {
        // get receiver
        Bird *dest = buffer_read(&flock, i);

        // copy message to receiver
        strcpy(dest->charbuf, c->term);

        // socket code goes here
        // don't forget mutex for socket
        // open current socket & open connection with dest
        send_bytes(dest->connectionfd, c->term, strlen(c->term));
        // close
    }
    return 0;
}

// UTILITY FUNCTIONS

// PURPOSEFUL FUNCTIONS
int chirp()
{
    printf("squawk 🐣\n");
    return 0;
}

void listen_keys()
{
    while (1)
    {
        Chirp c;
        printf("> ");
        fgets(c.term, 64, stdin);
        c.sender = &me;
        // lock
        buffer_set(&msgs, &c);
        // signal
    }
}

void dump_buffer()
{
    // monitor code goes here

    while (buffer_size(&msgs) != 0)
    {
        Chirp *c = buffer_get(&msgs);

        sendall(c);
    }
    msgs.read_head = msgs.write_head = 0;
}

// send to the dest all of the known hosts in the flock
void send_flock()
{
}