#include <sys/stat.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <signal.h>

#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#define PORTNUM 80
#define MAXLINE 1024
#define HEADERSIZE 1024

#define SERVER "happyweb/1.0 (Linux)"

struct user_request
{
	char method[20];	//
	char page[255];		//page name
	char http_ver[80];	//ver of HTTP protocol
};

char root[MAXLINE];

int webserv(int sockfd);
int protocol_parser(char *str, struct user_request *request);
int sendpage(int sockfd, char *filename, char *http_ver, char *codemsg);


int main(int argc, char **argv)
{
	int listenfd;
	int clientfd;
	socklen_t clilen;
	int pid;
	int optval = 1;
	struct sockaddr_in addr, cliaddr;

	if(argc !=2)
	{
		printf("Usage : %s [root directory]\n", argv[0]);
		return 1;
	}
	memset(root, 0x00, MAXLINE);
	sprintf(root, "%s", argv[1]);
