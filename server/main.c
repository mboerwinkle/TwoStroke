#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "entity.h"
#include "networking.h"
int main(){//Server
	
	pthread_t id;
	pthread_create(&id, NULL, netListen, NULL);
	pthread_detach(id);
	struct timespec t = {.tv_sec=0};
	struct timespec lastTime = {.tv_sec = 0, .tv_nsec = 0};
	struct timespec otherTime = {.tv_sec = 0, .tv_nsec = 0};
	initEntities();
	while(1){
		clock_gettime(CLOCK_MONOTONIC, &otherTime);
		int32_t sleep = (int32_t)(1000000000/40) - (otherTime.tv_nsec-lastTime.tv_nsec) - 1000000001*(otherTime.tv_sec-lastTime.tv_sec);
		if(sleep > 0){
			t.tv_nsec = sleep;
			nanosleep(&t, NULL);
		}
		clock_gettime(CLOCK_MONOTONIC, &lastTime);
	}
	return 0;
}
