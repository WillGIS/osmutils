#include "transform.h"

void transformPoint(NODE *node)
{
	projPJ wgs84, epsg2804;

	wgs84 = pj_init_plus("+proj=longlat +ellps=WGS84 +datum=WGS84 +no_defs");
	epsg2804 = pj_init_plus("+proj=lcc +lat_1=38.3 +lat_2=39.45 +lat_0=37.66666666666666 +lon_0=-77 +x_0=400000 +y_0=0 +ellps=GRS80 +datum=NAD83 +units=m +no_defs");

	pj_transform(epsg2804, wgs84, 1, 1, &node->x, &node->y, NULL);

	node->x *= RAD_TO_DEG;
	node->y *= RAD_TO_DEG;
}
