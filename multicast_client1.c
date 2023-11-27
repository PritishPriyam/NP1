#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<fcntl.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
int main()
{
int r=1;
int sock;
struct sockaddr_in serv;
struct ip_mreq mreq;
char str1[100],str2[10];
bzero(&serv,sizeof(serv));
sock=socket(AF_INET,SOCK_DGRAM,0);
serv.sin_family=AF_INET;
serv.sin_port=htons(12345);
serv.sin_addr.s_addr=INADDR_ANY;
bind(sock,(struct sockaddr *)&serv,sizeof(serv));
mreq.imr_multiaddr.s_addr=inet_addr("224.1.1.5");
mreq.imr_interface.s_addr=INADDR_ANY;
setsockopt(sock,IPPROTO_IP,IP_ADD_MEMBERSHIP,&mreq,sizeof(mreq));
while(1)
{
bzero(str1,100);
recvfrom(sock,str1,100,0,NULL,NULL);
printf("recvd data is %s",str1);}
close(sock);}

