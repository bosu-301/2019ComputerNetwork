#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SIZE sizeof(struct sockaddr_in)
void closesock(int sig);
int sockfd_connect;

int main()
{
        int sockfd_listen;
        int port;
        char c;

        struct sockaddr_in server = {AF_INET, 3578,  INADDR_ANY};
        struct sigaction act;

        act.sa_handler = closesock;
        sigfillset(&(act.sa_mask));
        sigaction(SIGPIPE, &act, NULL);

        if((sockfd_listen = socket(AF_INET, SOCK_STREAM, 0)) == -1) {

        printf("fail to call socket()\n");
        exit(1);
        }

        if(bind(sockfd_listen, (struct sockaddr *)&server, SIZE) == -1) {
        printf("fail to call bind()\n");
        exit(1);
        }

        if(listen(sockfd_listen, 5) == -1) {
        printf("fail to call listen()\n");
        exit(1);
        }

        while(1) {
        if((sockfd_connect = accept(sockfd_listen, NULL, NULL)) == -1) {
        printf("fail to call accept()\n");
        continue;
                }

        printf("accepted\n");

        while(recv(sockfd_connect, &c, 1, 0) > 0){
        printf("%c", c);
        send(sockfd_connect, &c, 1, 0);
        }
        printf("close(sockfd_connect)\n");
        close(sockfd_connect);

        }

}
void closesock(int sig)
{
        close(sockfd_connect);
        printf("connection is lost\n");
        exit(0);

}
