/* proj */
#include "proj_api.h"

typedef struct node {
	int id;
	double x;
	double y;
} NODE;

void transformPoint(NODE *node);
