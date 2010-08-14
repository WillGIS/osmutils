/* proj */
#include "proj_api.h"

typedef struct node {
	int id;
	double x;
	double y;
} NODE;

int sridIsValid(char *srid);
NODE transformPoint(NODE node, char *epsg);
