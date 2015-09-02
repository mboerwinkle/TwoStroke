typedef struct entity{
	double center[3];
	double center2[3];
	double vel[3];
	double vel2[3];
	double mass;
	double radius;
	
}entity;
extern entity* entityList;
extern int entityCount;
extern void initEntities();
