#include "transform.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

NODE transformPoint(NODE node, char *epsg)
{
	projPJ wgs84;
	projPJ fromEpsg = NULL;

	wgs84 = pj_init_plus("+proj=longlat +ellps=WGS84 +datum=WGS84 +no_defs");

//	switch (epsg) {
//		case '2804':
			fromEpsg = pj_init_plus("+proj=lcc +lat_1=38.3 +lat_2=39.45 +lat_0=37.66666666666666 +lon_0=-77 +x_0=400000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs");
//			break;
//		default: 
//			fprintf(stderr, "Error: EPSG %s is invalid.", epsg);
//			break;
//	}
		
	if (fromEpsg != NULL)
	{
		pj_transform(fromEpsg, wgs84, 1, 1, &node.x, &node.y, NULL);
		node.x *= RAD_TO_DEG;
		node.y *= RAD_TO_DEG;
	}

	return node;

}
