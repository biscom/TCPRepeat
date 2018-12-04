#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <sys/syscall.h> 
#include <sys/types.h> 
#include <sys/socket.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#define MAX_BUFFER 1024

int main(int argc, char ** argv) {

    int tcp_sock = socket(PF_INET, SOCK_STREAM, 0);
	if (tcp_sock == -1){
		perror("ERROR socket() failed");
		exit(EXIT_FAILURE);
	}
	struct sockaddr_in server;
	bzero(&server, sizeof(struct sockaddr_in));
	server.sin_family = PF_INET;
	server.sin_port = htons(12345);
	inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);
	
	/* attempt to connect */
	if (connect(tcp_sock,(struct sockaddr *)&server, sizeof(server)) == -1) {
		perror("ERROR connect() failed" );
		exit(EXIT_FAILURE);
	}

	sleep(5);
	int i;
	i = send(tcp_sock, "test\n\0", 5, 0);
	printf("%d\n", i);
	sleep(5);
	i = syscall(340, tcp_sock, "test\n\0", 6, 0, 5);
	printf("%d\n", i);
	sleep(5);
}
