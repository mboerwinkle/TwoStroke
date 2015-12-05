#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mesh.h"
static double orig[3], dir[3];

void quatMult(double qwrite[4], double q1[4], double q2[4]){
	double qret[4];
	qret[3] = q1[3]*q2[3]-q1[0]*q2[0]-q1[1]*q2[1]-q1[2]*q2[2];
	qret[0] = q1[3]*q2[0]+q1[0]*q2[3]+q1[1]*q2[2]-q1[2]*q2[1]; 
	qret[1] = q1[3]*q2[1]+q1[0]*q2[2]+q1[1]*q2[3]-q1[2]*q2[0];  
	qret[2] = q1[3]*q2[2]+q1[0]*q2[1]+q1[1]*q2[0]-q1[2]*q2[3];  
	qwrite[0] = qret[0];
	qwrite[1] = qret[1];
	qwrite[2] = qret[2];
	qwrite[3] = qret[3];
}


