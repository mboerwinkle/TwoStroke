#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mesh.h"
void loadmesh(char name[20], mesh *final, double centerx, double centery, double centerz){
	memset(final, 0, sizeof(mesh));
	final->center = calloc(sizeof(double), 3);
	final->centertest = calloc(sizeof(double), 3);
	final->center[0] = centerx;
	final->center[1] = centery;
	final->center[2] = centerz;
	final->rot = calloc(sizeof(double), 4); //calloc zeroes them for you.
	final->rot2 = calloc(sizeof(double), 4);
	final->rotloc = calloc(sizeof(double), 4); //calloc zeroes them for you.
	final->rotloc2 = calloc(sizeof(double), 4);
	final->moves = 1;
	final->mass = 1;
	FILE *fp;
	fp = fopen(name, "r");
	if(fp == NULL) printf("error opening %s\n", name);
	int temp, corner, one, two, run = 1;
	double x3[3], y3[3], z3[3], x, y, z;
	while(run){
		if(EOF == fscanf(fp, "%lf %lf %lf %lf %lf %lf %lf %lf %lf", &x3[0], &y3[0], &z3[0], &x3[1], &y3[1], &z3[1], &x3[2], &y3[2], &z3[2])) return;
		final->triangles++;
		final->trianglematrix = realloc(final->trianglematrix, sizeof(triangle)*final->triangles);
		for(corner = 0; corner < 3; corner++){
			x = x3[corner];
			y = y3[corner];
			z = z3[corner];
			temp = 0;
			while(temp < final->points && !(x == final->cpointmatrix[temp*3+0] && y == final->cpointmatrix[temp*3+1] && z == final->cpointmatrix[temp*3+2])){
				temp++;
			}
			if(temp == final->points){
				final->points++;
				final->cpointmatrix = realloc(final->cpointmatrix, (final->points*sizeof(double)*3));
				final->pointmatrix = realloc(final->pointmatrix, (final->points*sizeof(double)*3));
				final->cpointmatrix[temp*3+0] = x;
				final->cpointmatrix[temp*3+1] = y;
				final->cpointmatrix[temp*3+2] = z;
				final->pointmatrix[temp*3+0] = x;
				final->pointmatrix[temp*3+1] = y;
				final->pointmatrix[temp*3+2] = z;
				double newRad = sqrt(x*x+y*y+z*z);
				if(newRad > final->radius) final->radius = newRad;
			}
			final->trianglematrix[final->triangles-1].points[corner] = temp;
		}
		for(corner =  0; corner < 3; corner++){
			one = final->trianglematrix[final->triangles-1].points[corner];
			two = final->trianglematrix[final->triangles-1].points[(corner+1)%3];
			temp = 0;
			while(temp < final->rays && !((one == final->raymatrix[temp].ends[0] && two == final->raymatrix[temp].ends[1]) || (two == final->raymatrix[temp].ends[0] && one == final->raymatrix[temp].ends[1]))){
				temp++;
			}
			if(temp == final->rays){
				final->rays++;
				final->raymatrix = realloc(final->raymatrix, final->rays*sizeof(ray));
				final->raymatrix[temp].ends[0] = one;
				final->raymatrix[temp].ends[1] = two;
			}
		}
	}
	fclose(fp);
}
