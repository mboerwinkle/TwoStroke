#ifndef ENTITY_H
#define ENTITY_H
typedef struct entity{
	int center[3];
	int testcenter[3];
	int vel[3];
	int testvel[3];
	int mass;
	int radius;
	char keys;
}entity;
extern entity* entityList;
extern int entityCount;
extern void initEntities();
extern entity* makeNewEntity(double x, double y, double z);
#endif
