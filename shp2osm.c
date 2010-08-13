#include "shp2osm.h"

static void usage()
{
	printf("USAGE: shp2osm [<options>] <shapefile> <osmfile>\n");
}	

void set_config_defaults(SHPCONVERTCONFIG *config)
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
	set_config_defaults(config);

	shape = malloc(sizeof(SHAPE));

	/* Parse arguments and set configation */
	int option_index = 0;
	static struct option long_options[] = {
		{"infile", 1, 0, 'i'},
		{"outfile", 1, 0, 'o'}
	};

	while ((c = getopt_long(argc, argv, "i:o:", long_options, &option_index)) != -1)
	{
		switch(c)
		{
			case 'i':
				config->infile = optarg;
				break;
			case 'o':
				config->outfile = optarg;
				break;
			case '?':
				usage();
				exit(0);
			default:
				usage();
				exit(0);
		}
	}	

	shape->shpfile = config->infile;

	/* Open the shapefile */
	ret = ShpConvertOpenShape(shape);

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
