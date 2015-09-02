#include "entity.h"
typedef struct client{
	struct sockaddr_in addr;
	entity* myEntity;
	char keys;
}client;
extern client* clientList;
extern int maxClients;
extern int clientCount;
extern void* netListen(void* whatever);
