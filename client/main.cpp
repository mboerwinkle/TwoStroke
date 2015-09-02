#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <SDL2/SDL.h>
#include "networking.h"
static SDL_Window* window;
SDL_Renderer* render;
int running = 1;
int sockfd;
struct sockaddr_in serverAddr;
int main(int argc, char** argv){
	if(argc < 2){
		puts("Please specify an ip.");
		return 5;
	}
	SDL_Init(SDL_INIT_VIDEO|SDL_INIT_EVENTS);
	window = SDL_CreateWindow("TwoStroke", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
	if(window == NULL){
		puts("no SDL2 window");
		SDL_Quit();
		return 1;
	}
	render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	initNetwork(argv[1], 1212);
	char test[5];
	strcpy(test, "I");
	sendto(sockfd, test, 4, 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
//	while(running){
//		netListen();

//	}
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
