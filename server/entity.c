#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entity.h"
void initEntities(){
	entityList = calloc(sizeof(entity), 5);
	entityCount = 0;
}
entity* makeNewEntity(double x, double y, double z){
	entity* target = &entityList[entityCount];
	target->center[0] = x;
	target->center[1] = y;
	target->center[2] = z;
	memset(target->vel, 0, 3*sizeof(double));
	target->mass = 1;
	target->radius = 5;
	return target;
}
