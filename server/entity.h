#ifndef ENTITY_H
#define ENTITY_H
typedef struct entity{
	double center[3];
	double testcenter[3];
	double vel[3];
	double testvel[3];
	double mass;
	double radius;
	char keys;
}entity;
extern entity* entityList;
extern int entityCount;
extern void initEntities();
extern entity* makeNewEntity(double x, double y, double z);
#endif
