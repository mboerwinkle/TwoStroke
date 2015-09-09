#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <SDL2/SDL.h>
#include <time.h>
#include "networking.h"
static SDL_Window* window;
SDL_Renderer* render;
int running = 1;
int sockfd;
struct sockaddr_in serverAddr;
unsigned char twoPow[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
unsigned char keys = 0;
#define NUMKEYS 5
int keyBindings[NUMKEYS] = {SDLK_w, SDLK_s, SDLK_a, SDLK_d, SDLK_SPACE};
unsigned char keyAction(int bit, char pressed){
	int i = 0;
	for(; i < NUMKEYS && bit !=keyBindings[i]; i++);
	if(i==NUMKEYS) return 1;
	unsigned char old = keys;
	if(pressed) keys |= twoPow[i];
	else keys &= 0xFF-twoPow[i];
	if(keys == old) return 1;
	return 0;
}
int main(int argc, char** argv){
	struct timespec t = {.tv_sec=0};
	struct timespec lastTime = {.tv_sec = 0, .tv_nsec = 0};
	struct timespec otherTime = {.tv_sec = 0, .tv_nsec = 0};
	SDL_Event evnt;

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
	char test[10];
	test[0] = 0;
	sendto(sockfd, test, 10, 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	sendto(sockfd, test, 10, 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	while(running){
		netListen();
		while(SDL_PollEvent(&evnt)){
			if(evnt.type == SDL_KEYDOWN){
				if(!keyAction(evnt.key.keysym.sym, 1)){
					test[0] = 1;
					sendto(sockfd, test, 10, 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
				}
			}else if(evnt.type == SDL_KEYUP){
				if(!keyAction(evnt.key.keysym.sym, 0)){
					test[0] = 1;
					sendto(sockfd, test, 10, 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
				}
			}else if(evnt.type == SDL_QUIT){
				running = 0;
			}
		}
		clock_gettime(CLOCK_MONOTONIC, &otherTime);
		int32_t sleep = (int32_t)(1000000000/50) - (otherTime.tv_nsec-lastTime.tv_nsec) - 1000000001*(otherTime.tv_sec-lastTime.tv_sec);
		if(sleep > 0){
			t.tv_nsec = sleep;
			nanosleep(&t, NULL);
		}
		clock_gettime(CLOCK_MONOTONIC, &lastTime);
	}
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
