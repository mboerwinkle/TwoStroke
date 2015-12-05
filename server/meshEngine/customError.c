#include <stdio.h>
#include <stdlib.h>
void customFatalError(const char *reason){
	printf("%s\n", reason);
	exit(1);
}
void customError(const char *reason){
	printf("%s\n", reason);
}
