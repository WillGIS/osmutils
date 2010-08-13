#include "osm2shp.h"

void usage()
{
	printf("USAGE: osm2shp [<options>] <osmfile> <shapefile>\n");
}

static void parseWay(xmlDocPtr doc, xmlNodePtr cur)
{
	xmlChar *way;
	cur = cur->xmlChildrenNode;
	while (cur != NULL)
	{
		fprintf(stderr, "way name: %s\n", cur->name);
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"way")))
		{
			way = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			fprintf(stderr, "way: %s\n", way);
			xmlFree(way);
		}
		cur = cur->next;
	}
	return;	
}

static void parseDoc(char *docname)
{
	xmlDocPtr doc;
	xmlNodePtr cur;

	doc = xmlParseFile(docname);

	if (doc == NULL) 
	{
		fprintf(stderr, "Document not found.\n");
		exit(0);
	}

	cur = xmlDocGetRootElement(doc);

	if (cur == NULL)
	{
		fprintf(stderr, "Empty document\n");
		xmlFreeDoc(doc);
		exit(0);
	}

	if (xmlStrcmp(cur->name, (const xmlChar *) "osm"))
	{
		fprintf(stderr, "Wrong type of file\n");
		xmlFreeDoc(doc);
		exit(0);
	}

	fprintf(stderr, "Parsing doc...\n");
	
	cur = cur->xmlChildrenNode;
	while (cur != NULL)
	{
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"way")))
		{
			printf("parse way\n");
			parseWay(doc, cur);
		}

		cur = cur->next;
	}

	fprintf(stderr, "Done parsing\n");

	xmlFreeDoc(doc);

	return;	
}

int main(int argc, char **argv)
{
	int c;
	char *docname;

	if (argc == 1)
	{
		usage();
		exit(0);
	}

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
				fprintf(stderr, "Input file: %s\n", optarg);
				docname = optarg;
				break;
			case 'o':
				fprintf(stderr, "Output file: %s\n", optarg);
				break;
			case '?':
				usage();
				exit(0);
			default:
				usage();
				exit(0);
		}
	}	

	fprintf(stderr, "Doc name: %s\n", docname);
	parseDoc(docname);
	fprintf(stderr, "Done");	

	return 0;
}
