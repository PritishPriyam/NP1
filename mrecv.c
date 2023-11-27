#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

int main(){
    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    struct sockaddr_in serv;
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = INADDR_ANY;
    serv.sin_port = htons(12345);

    bind(sock, (struct sockaddr*)&serv, sizeof(serv));

    struct ip_mreq ipmreq;
    ipmreq.imr_interface.s_addr = htonl(INADDR_ANY);
    ipmreq.imr_multiaddr.s_addr = inet_addr("224.1.1.2");

    setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (void*)&ipmreq, sizeof(ipmreq));
    char buf[100];
    bzero(&buf, 100);
    recvfrom(sock, buf, 100, 0, NULL, NULL);
    printf("%s,..", buf);
    setsockopt(sock, IPPROTO_IP, IP_DROP_MEMBERSHIP, (void*)&ipmreq, sizeof(ipmreq));
    return -1;
}
