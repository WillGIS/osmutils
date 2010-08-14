#include "transform.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

projPJ toSRID;
projPJ fromSRID = NULL;

int sridIsValid(char *srid)
{
	int valid = 0;
	char *p, srid_string[32];	

	sprintf(srid_string, "+init=epsg:%s", srid);
	p = srid_string;

	if ((fromSRID = pj_init_plus(p))) {
		toSRID = pj_init_plus("+init=epsg:4326");
		valid = 1;
	}

	return valid;
}

NODE transformPoint(NODE node, char *srid)
{
	// TODO
	if (sridIsValid(srid) == 1) 
	{
		pj_transform(fromSRID, toSRID, 1, 1, &node.x, &node.y, NULL);
		node.x *= RAD_TO_DEG;
		node.y *= RAD_TO_DEG;
		free(fromSRID);
	} 

	return node;
}
