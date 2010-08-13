/* from shp2pgsql-core */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <iconv.h>

/* from osm2pgsql */
/* note: there is a postgis specific version of getopt */
#include <getopt.h>

/* xmllib2 */
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

/* shpconvert includes */
//#include "shape.h"
#include "osm.h"

typedef struct shp_convert_config
{
	char *infile;
	char *outfile;
	char *cliptable;
	char *clipcolumn;
	char *clipval;
} SHPCONVERTCONFIG;
