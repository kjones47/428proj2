#include <stdio.h> 
#include <iostream>
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <netdb.h> 
#include <stdio.h> 
#include <time.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <cstdio>
#include <ctime>

#define MAX 80 
#define PORT	 15642

int main() { 
	int sockfd, connfd, n;
	socklen_t len;
	struct sockaddr_in servaddr;
	char const * message = "Client Y: Bob"; 
	char buffer[1024];
	//create the udp socket
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		perror("error creating client socket");
		return errno;
	}
	
	//allocate address space
	memset(&servaddr, 0, sizeof(servaddr)); 
	len = sizeof(servaddr);

	//FILL IN SERVER INFORMATION
	servaddr.sin_family = AF_INET; // IPv4 
	servaddr.sin_addr.s_addr = INADDR_ANY; // localhost
	servaddr.sin_port = htons(PORT); // port number


  	if(connect(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) != 0) { 
        	printf("connection with the server failed...\n"); 
       	 	exit(0); 
    	} 

	sendto(sockfd, (const char *)message, strlen(message), 
		MSG_CONFIRM, (const struct sockaddr *) &servaddr, 
			sizeof(servaddr)); 
	printf("Message: %s\n", message); 
	n = recvfrom(sockfd, (char *)buffer, MAX, 
				MSG_WAITALL, (struct sockaddr *) &servaddr, 
				&len); 
	buffer[n] = '\0'; 
	printf("Acknowledgement from server: %s\n", buffer); 
	close(sockfd); 


    	return 0; 
}


