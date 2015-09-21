#include "geo3d.h"
#define MESH_PATH "../meshes/"
typedef struct mesh{
	double mass;
	int moves;
	int pcount, tcount, rcount;//point count, triangle count, ray count
	point *pointList;
	triangle *trianglematrix;
	ray *raymatrix;
}mesh;
typedef struct shadow{
	mesh *myMesh;
	vector v, vnxt;//velocity of this tick, and the velocity of the next tick that is in the process of being calculated
	quat r, rnxt;//rotational velocity of this tick, and the rotational velocity of the next tick that is being calculated
	quat orient, torient;//orientation and test orientation of the shadow
	point c, tc;//center and test center of the shadow
	point *pointList;//rotated list of points
}shadow;
extern void initMeshes();
