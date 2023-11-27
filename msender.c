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
    char m_enable = 1;
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(12345);
    addr.sin_addr.s_addr = inet_addr("224.1.1.2");

    if(setsockopt(sock, IPPROTO_IP, IP_MULTICAST_TTL, &m_enable, sizeof(m_enable)) < 0){
        perror("set sock");
        return -1;
    }

    while(1){
        char buf[100];
        bzero(&buf, 100);
        fgets(buf, 100, stdin);
        sendto(sock, buf, 100, 0, (struct sockaddr*)&addr, sizeof(addr));
    }
    return 0;
}
