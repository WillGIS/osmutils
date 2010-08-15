#include "shape.h"

/* Convert the string to lower case */
char * strtolower(char *s)
{
	int j;

	for (j = 0; j < strlen(s); j++)
		s[j] = tolower(s[j]);

	return s;
}

void shpReadFields(SHAPE *shape)
{
	int j;
	int field_precision, field_width;
	DBFFieldType type = -1;
	char name[MAXFIELDNAMELEN];

	shape->num_fields = DBFGetFieldCount(shape->handleDbf);
	shape->num_records = DBFGetRecordCount(shape->handleDbf);

	shape->field_names = malloc(shape->num_fields * sizeof(char*));
	shape->types = (DBFFieldType *)malloc(shape->num_fields * sizeof(int));
	shape->widths = malloc(shape->num_fields * sizeof(int));
	shape->precisions = malloc(shape->num_fields * sizeof(int));
	shape->fields = malloc(shape->num_fields * sizeof(KEYVAL));

	for (j = 0; j < shape->num_fields; j++)
	{	
		initList(&shape->fields[j]);

		type = DBFGetFieldInfo(shape->handleDbf, j, name, &field_width, &field_precision);

		shape->types[j] = type;
		shape->widths[j] = field_width;
		shape->precisions[j] = field_precision;

		shape->field_names[j] = malloc(strlen(name) + 1);
		strcpy(shape->field_names[j], name);
		
		setKey(&shape->fields[j], shape->field_names[j]);
		setValue(&shape->fields[j], strtolower(getKey(&shape->fields[j])));
	}
}

int shpConvertOpenShape(SHAPE *shape)
{
	int ret = SHPCONVERTOK;

	shape->handleShp = SHPOpen(shape->shpfile, "rb");
	
	if (shape->handleShp == NULL)
	{
		fprintf(stderr, "Error reading shapefile");
		return SHPCONVERTERR;
	} else {
		SHPGetInfo(shape->handleShp, &shape->num_entities, &shape->filetype, shape->minbound, shape->maxbound);
		fprintf(stderr, "Reading shapefile: %s\n", shape->shpfile);
		shape->handleDbf = DBFOpen(shape->shpfile, "rb");
		
		if (shape->handleDbf == NULL)
		{
			fprintf(stderr, "Error reading DBF file\n");
			return SHPCONVERTERR;
		} else {
			shpReadFields(shape);
		}
	}

	return ret;
}

void setShapeSrid(SHAPE *shape, char *srid)
{
	// TODO validate srid
	shape->srid = srid;
}

MULTIPOINT parsePoints(SHAPE *shape)
{
	int i, k = 0;
	POINT pt;
	MULTIPOINT pts;

	SHPObject *obj = NULL;
	obj = malloc(sizeof(SHPObject));

	pts.num_points = shape->num_entities;
	pts.points = malloc(sizeof(POINT) * pts.num_points);

	// negative ids required for new osm nodes
	for (i = 0; i < pts.num_points; i++)
	{
		obj = SHPReadObject(shape->handleShp, k);

		pt.x = obj->padfX[0];
		pt.y = obj->padfY[0];
		pts.points[k] = pt;

		k++;
	}

	return pts;
}
