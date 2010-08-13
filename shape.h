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

void shpReadFields(SHAPE *shape);
int ShpConvertOpenShape(SHAPE *shape);
