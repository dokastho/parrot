#include "parrot.h"
#include <netinet/in.h>
#include <stdio.h>

// connection functions

// send len bytes from buf over sock
int
send_bytes(int sock, const char *buf, int len)
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

int
get_port_number(int sockfd)
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

int
init()
{
    return 0;
}

// utility functions


// purposeful functions
int
chirp()
{
    printf("squawk 🐣\n");
    return 0;
}
