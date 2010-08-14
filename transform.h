/* proj */
#include "proj_api.h"

typedef struct node {
	int id;
	double x;
	double y;
} NODE;

NODE transformPoint(NODE node);
