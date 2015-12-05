#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrixFuncs.h"
#include "mesh.h"
#define EPSILON 1;
int intersect_triangle(ray seg, triangle tri, double *t, double *u, double *v, int offsetx, int offsety, int offsetz){//credit Tomas Moller and Ben Trumbore "Fast, minimum storage ray/triangle intersection"
	int dir[3], orig[3];
	dir[0] = *(seg[1])[0]-*(seg[0])[0];
	dir[1] = *(seg[1])[1]-*(seg[0])[1];
	dir[2] = *(seg[1])[2]-*(seg[0])[2];
	orig[0] = *(seg[0])[0] + offsetx;
	orig[1] = *(seg[0])[1] + offsety;
	orig[2] = *(seg[0])[2] + offsetz;
	int edge1[3], edge2[3];
	double tvec[3], pvec[3], qvec[3];
	double det, inv_det;
	/* find vectors for two edges sharing vert0 */
	SUB(edge1, *(tri[1]), *(tri[0]));
	SUB(edge2, *(tri[2]), *(tri[0]));

	/* begin calculating determinant - also used to calculate U parameter */
	CROSS(pvec, dir, edge2);

	/* if determinant is near zero, ray lies in plane of triangle */
	det = DOT(edge1, pvec);
	if (det > -EPSILON && det < EPSILON) return 0;
	inv_det = 1 / det;
	/* calculate distance from vert0 to ray origin */
	SUB(tvec, orig, *(tri[0]));
	/* calculate U parameter and test bounds */
	*u = DOT(tvec, pvec) * inv_det;
	if (*u < 0 || *u > 1) return 0;
	/* prepare to test V parameter */
	CROSS(qvec, tvec, edge1);
	/* calculate V parameter and test bounds */
	*v = DOT(dir, qvec) * inv_det;
	if (*v < 0 || *u + *v > 1)return 0;
	/* calculate t, ray intersects triangle */
	*t = DOT(edge2, qvec) * inv_det;
	if(*t > 1 || *t <0) return 0;
	return 1;
}
