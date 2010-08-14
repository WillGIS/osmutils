#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* include shapelib */
#include "shapefil.h"

#define SHPCONVERTOK		-1
#define SHPCONVERTERR		0
#define SHPCONVERTWARN		1

#define MAXFIELDNAMELEN 64
#define MAXVALUELEN 1024

typedef struct shape
{
	char *shpfile;

	SHPHandle handleShp;
	DBFHandle handleDbf;

	int filetype;

	char *srid;

	int num_entities;
	int num_fields;
	int num_records;

	char **field_names;	
	DBFFieldType *types;
	int *widths;
	int *precisions;

	double minbound[4];
	double maxbound[4];
} SHAPE;

typedef struct point {
	double x;
	double y;
} POINT;

typedef struct multipoint {
	double bbox[4];
	int num_points;
	POINT *points;
} MULTIPOINT;

void shpReadFields(SHAPE *shape);
int shpConvertOpenShape(SHAPE *shape);
void setShapeSrid(SHAPE *shape, char *srid);
MULTIPOINT parsePoints(SHAPE *shape);
