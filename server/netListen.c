#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "networking.h"
#include "entity.h"
int clientCount = 0;
int maxClients = 5;
client* clientList;
void* netListen(void* whatever){
	clientList = (client*)calloc(sizeof(client), maxClients);
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd < 0){
		puts("network error");
		return NULL;
	}
	struct sockaddr_in bindAddr = {.sin_family=AF_INET, .sin_port=htons(1212), .sin_addr={.s_addr=htonl(INADDR_ANY)}};
	if(0 > bind(sockfd, (struct sockaddr*)&bindAddr, sizeof(bindAddr))){
		puts("network error");
		return NULL;
	}
	char msg[100];//maximum message size
	socklen_t len;
	int msgSize;
	while(1){
		len = sizeof(bindAddr);
		msgSize = recvfrom(sockfd, msg, 100, 0, (struct sockaddr*)&bindAddr, &len);
		int testClient = 0;
		while(testClient < clientCount){
			if(clientList[testClient].addr.sin_addr.s_addr == bindAddr.sin_addr.s_addr){
				//client is already in list
				break;
			}
		}
		if(testClient >= clientCount){//first time seen
			puts("success!");
			if(*msg != 'I') continue; //I is for Init. or something
			if(strnlen(msg, 100) > 99){
				puts("message too long");
				continue;
			}
			if(clientCount+1 > maxClients){
				puts("too many clients trying to connect");
				continue;
			}
			//make new client
			clientList[clientCount].myEntity = makeNewEntity(0, 0, 0);
			clientList[clientCount].addr.sin_addr.s_addr = bindAddr.sin_addr.s_addr;
			puts("adding client");
			clientCount++;
		}
	}
	return NULL;
}
