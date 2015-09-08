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
unsigned char twoPow[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
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
	char msg[10];//maximum message size
	socklen_t len;
	int msgSize;
	while(1){
		len = sizeof(bindAddr);
		msgSize = recvfrom(sockfd, msg, 10, 0, (struct sockaddr*)&bindAddr, &len);
		int testClient = 0;
		while(testClient < clientCount){
			if(clientList[testClient].addr.sin_addr.s_addr == bindAddr.sin_addr.s_addr){
				if(*msg == 1){//move forward, back, left, right, jump, crouch
					if(msg[1]&twoPow[0]) puts("moved forward");
					if(msg[1]&twoPow[1]) puts("moved backward");
				}
				//if(*msg == '2'){//fire
					 
				if(*msg == 0){//Reply
					struct sockaddr_in sendAddr = {.sin_family=AF_INET, .sin_port=htons(1213), .sin_addr={.s_addr=bindAddr.sin_addr.s_addr}};
					sendto(sockfd, "H", 1, 0, (struct sockaddr*)&sendAddr, sizeof(sendAddr));
				}else{//other things (chat, option screens, etc)
				}
				break;
			}
		}
		if(testClient >= clientCount){//first time seen
			if(*msg != 0) continue; //I is for Init. or something
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
