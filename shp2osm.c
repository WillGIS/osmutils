#include "shp2osm.h"

static void usage()
{
	fprintf(stderr, "USAGE: shp2osm [<options>] <shapefile> <osmfile>\n");
        fprintf(stderr, "For detailed usage information:\n");
        fprintf(stderr, "\tshp2osm -h|--help\n");
}

static void longUsage()
{
	fprintf(stderr, "USAGE: shp2osm [<options>] <shapefile> <osmfile>\n");
	fprintf(stderr, "\nOptions\n");
	fprintf(stderr, "    -h|--help\t\tHelp information.\n");
	fprintf(stderr, "    -i|--infile\t\tShapefile input.\n");
	fprintf(stderr, "    -o|--outfile\tOutput OSM file.\n");
	fprintf(stderr, "    -s|--srid\t\tSpecify source SRID (default: EPSG 4326).\n");
	fprintf(stderr, "\n");
}

void setConfigDefaults(SHPCONVERTCONFIG *config)
{
	config->infile = NULL;
	config->outfile = NULL;
	config->cliptable = NULL;
	config->clipcolumn = NULL;
	config->clipval = NULL;
}

int main(int argc, char **argv)
{
	SHPCONVERTCONFIG *config;
	SHAPE *shape;

	int c, ret;

	if (argc == 1)
	{
		usage();
		exit(0);
	}

	config = malloc(sizeof(SHPCONVERTCONFIG));
	setConfigDefaults(config);

	shape = malloc(sizeof(SHAPE));

	/* Parse arguments and set configuration */
	// TODO -h option does not require argument
	int option_index = 0;
	static struct option long_options[] = {
		{"help", 0, 0, 'h'},
		{"infile", 1, 0, 'i'},
		{"outfile", 1, 0, 'o'},
		{"srid", 1, 0, 's'}
	};

	// TODO infile and outfile as params, not options
	while ((c = getopt_long(argc, argv, "i:o:h:s:", long_options, &option_index)) != -1)
	{
		switch(c)
		{
			case 'i':
				config->infile = optarg;
				break;
			case 'o':
				config->outfile = optarg;
				break;
			// specify srid
			case 's':
				setShapeSrid(shape, optarg);
				break;
			case 'h':
				longUsage();
				exit(0);
			case '?':
				usage();
				exit(0);
			default:
				usage();
				exit(0);
		}
	}	

	if (config->infile == NULL)
	{
		fprintf(stderr, "Error: Input file not specified.\n");
		usage();
		exit(0);
	}

	if (config->outfile == NULL)
	{
		fprintf(stderr, "Error: Output file not specified.\n");
		usage();
		exit(0);
	}

	shape->shpfile = config->infile;

	/* Open the shapefile */
	ret = shpConvertOpenShape(shape);

	if (ret != SHPCONVERTOK)
	{
		fprintf(stderr, "Error reading shapefile");
		exit(1);
	} else {
		xmlDocPtr doc;

		doc = createXmlDoc(shape);
		xmlSaveFormatFileEnc(config->outfile, doc, "UTF-8", 1);
		xmlFreeDoc(doc);
	}

	free(config);

	return 0;
}
