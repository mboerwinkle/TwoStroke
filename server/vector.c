#include <math.h>
#include "matrixFuncs.h"
void norm(double target[3], double dist){
	if(target[0] == 0 && target[1] == 0 && target[2] == 0) return;
	double howmuch = sqrt(target[0]*target[0]+target[1]*target[1]+target[2]*target[2]);
	target[0] *= dist/howmuch;
	target[1] *= dist/howmuch;
	target[2] *= dist/howmuch;
}

double distance(double vect[3], double point[3]){
	double a[3] = {vect[0], vect[1], vect[2]};
	double b[3] = {point[0], point[1], point[2]};
	double distb = sqrt(b[0]*b[0] + b[1]*b[1] + b[2]*b[2]);
	double dista = sqrt(a[0]*a[0] + a[1]*a[1] + a[2]*a[2]);
	double angle = acos(DOT(a, b)/(dista*distb));
	double ans = sin(angle)*distb;
	if(isnan(ans) || !isfinite(ans)) return 0;
	return ans;
}

