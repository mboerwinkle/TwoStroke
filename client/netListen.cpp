#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "networking.h"
void netListen(){
	static int8_t data[6000];
	struct sockaddr_in addr;
	socklen_t addrLen = sizeof(addr);
	int len;
	while(0<(len = recvfrom(sockfd, (char*)data, 6000, 0, (struct sockaddr*)&addr, &addrLen))){
		addrLen = sizeof(addr);
		if(addr.sin_addr.s_addr != serverAddr.sin_addr.s_addr) continue;
		if(*data == 0){//mesh
			displayMesh(data[1]
		}
	}
}
int initNetwork(char* ip, int port){
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd < 0){
		puts("socket error");
		return 1;
	}
	serverAddr.sin_family=AF_INET;
	serverAddr.sin_addr.s_addr=htonl(INADDR_ANY);
	serverAddr.sin_port=htons(port+1);
	if(0 > bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr))){
		puts("network error");
		return 1;
	}
	fcntl(sockfd, F_SETFL, O_NONBLOCK);
	serverAddr.sin_port = htons(port);
	inet_aton(ip, &serverAddr.sin_addr);
	return 0;
}
	
