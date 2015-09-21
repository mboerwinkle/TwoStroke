typedef struct point{
	int c[3];
}point;
typedef struct triangle{
	point *p[3];
}triangle;
typedef struct ray{
	point *p[2];
}ray;
typedef int vector[3];
typedef int quat[4];
	
