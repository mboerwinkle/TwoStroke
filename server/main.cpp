#include "networking.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
int main(){//Server
	pthread_t id;
	pthread_create(&id, NULL, netListen, NULL);
	pthread_detach(id);
	return 0;
}
