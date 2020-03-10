// UDP Pinger

// Must have this server running before you can run the UDP Pinger Client code

#include <iostream>
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <time.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <stdio.h> 
#include <string.h> 
#define MAX 1024 
#define PORT	 15642


int main() { 
	int sockfd, connfd, n, flag;
	socklen_t len;
	struct sockaddr_in servaddr, cliaddr; 
	char buff[MAX]; 
	char msg1[MAX];
	char msg2[MAX];
	char ack[MAX];
	char buffer[1024];
	int clients[2] = {0,0};
	int count = 0;
	// Create a TCP socket
	// Notice the use of SOCK_STREAM for TCP packets
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
  	if (sockfd == -1) { 
        	printf("socket creation failed...\n"); 
       		exit(0); 
    	} 
	
	memset(&servaddr, 0, sizeof(servaddr)); 
	memset(&cliaddr, 0, sizeof(cliaddr)); 
	
	// Fill server information 
	servaddr.sin_family = AF_INET; // IPv4 
	servaddr.sin_addr.s_addr = INADDR_ANY; // localhost
	servaddr.sin_port = htons(PORT); // port number
	
	// Bind the socket with the server address 
	if((bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr))) != 0){
		printf("socket bind failed...\n"); 
		exit(0);
	}
	
	// Listen for max 2 connections/clients
  	if((listen(sockfd, 5)) != 0) { 
        	printf("Listen failed...\n"); 
        	exit(0); 
    	} 
 	len = sizeof(cliaddr); 
	count = 0;
	while(count < 2){
		connfd = accept(sockfd, (struct sockaddr *)&cliaddr, &len);
		if (connfd < 0) { 
        		printf("server acccept failed...\n"); 
       			exit(0); 
    		}else{
			n = recvfrom(sockfd, (char *)buffer, MAX, 
				MSG_WAITALL, ( struct sockaddr *) &cliaddr, 
				&len);
			buffer[n] = '\0';
			printf("Client %d said %s.\n", count, buffer);
			clients[count] = connfd;
			if(count == 0){
				strcat(ack, buff);
				strcat(ack, " received before ");
				
			}else{
				strcat(ack, buff);
			}
			count++;		
		}		
	}
	printf("acknoweldgement: %s", ack);
	close(sockfd);
} 

		

		/*if(flag == 0){
			bzero(msg1, MAX);
			read(sockfd, msg1, sizeof(msg1));
			printf("First from Client %s\n",msg1);
			flag = 1;
		}else{
			bzero(msg2, MAX);
			bzero(ack, MAX);
			read(sockfd, msg2, sizeof(msg2));
			strcat(ack, msg1);
			strcat(ack, " received before ");
			strcat(ack, msg2);
			printf("%s received before %s\n", msg1, msg2); 
			printf("Second from Client %s\n",msg2);
			write(sockfd, ack, sizeof(ack)); 
		}*/
    	




