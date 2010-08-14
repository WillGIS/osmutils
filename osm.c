#include "osm.h"

char *srid;

/*
 * utility functions to convert
 * dbl or int to char
 */
char * dbl2char(double d) 
{
	char *p, text[32];
	sprintf(text, "%.8g", d);
	p = text;
	return p;
}

char * int2char(int i)
{
	char *p, text[32];
	sprintf(text, "%d", i);
	p = text;
	return p;
}	

/*
 * source: openstreetmap utils
 *		planet.osm/C/output_osm.c
 * FIXME: add iconv support
 */
const char *xmlEscape(const char *in)
{
	static char escape_tmp[1024];
	int len;
	
	len = 0;
	while (*in)
	{
		int left = sizeof(escape_tmp) - len - 1;

		if (left < 7)
			break;

		if (*in == '&')
		{
			strcpy(&escape_tmp[len], "&amp;");
			len += strlen("&amp;");
		} else if (*in == '<') {
			strcpy(&escape_tmp[len], "&lt;");
			len += strlen("&lt;");
		} else if (*in == '>') {
			strcpy(&escape_tmp[len], "&gt;");
			len += strlen("&gt");
		} else if (*in == '"') {
			strcpy(&escape_tmp[len], "&quot;");
			len += strlen("&quot;");
		} else if ((*in == 9) || (*in == 10) || (*in == 13)) {
			len+=sprintf(&escape_tmp[len], "&#%d;", *in);
		} else if ((*in >= 0) && (*in < 32)) {
			/* These characters are not valid in XML output
			 * http://www.w3.org/TR/REC-xml/#NT-Char
			 * (tab, newline, carriage return are handled above)
			 */
			escape_tmp[len] = '?';
			len++;
		} else {
			escape_tmp[len] = *in;
			len++;
		}

		in++;
	}

	escape_tmp[len] = '\0';
	return escape_tmp;
}

xmlNodePtr tagElement(KEYVAL *tag)
{        
	xmlNodePtr tagNode;
	tagNode = xmlNewNode(NULL, BAD_CAST "tag");
	xmlNewProp(tagNode, BAD_CAST "k", BAD_CAST xmlEscape(getKey(tag)));
	xmlNewProp(tagNode, BAD_CAST "v", BAD_CAST xmlEscape(getValue(tag)));
	return tagNode;
}

xmlNodePtr nodeElement(NODE node)
{
	if (strcmp(srid, "4326") != 0) 
	{
		node = transformPoint(node, srid);
	}

	xmlNodePtr osmNode;
	osmNode = xmlNewNode(NULL, BAD_CAST "node");
	xmlNewProp(osmNode, BAD_CAST "id", BAD_CAST xmlEscape(int2char(node.id)));
	xmlNewProp(osmNode, BAD_CAST "lon", BAD_CAST xmlEscape(dbl2char(node.x)));
	xmlNewProp(osmNode, BAD_CAST "lat", BAD_CAST xmlEscape(dbl2char(node.y))); 
	return osmNode;
	
}

xmlNodePtr nodeRef(NODE node)
{
	xmlNodePtr nd;
	nd = xmlNewNode(NULL, BAD_CAST "nd");
	xmlNewProp(nd, BAD_CAST "ref", BAD_CAST xmlEscape(int2char(node.id)));
	
	return nd;
}

xmlNodePtr wayElement(int id)
{
	xmlNodePtr osmWay;
	osmWay = xmlNewNode(NULL, BAD_CAST "way");
	xmlNewProp(osmWay, BAD_CAST "id", BAD_CAST xmlEscape(int2char(id)));
	
	return osmWay;
}

void parsePoint(xmlNodePtr root_node, SHAPE *shape)
{
	int i, k = 0;
	int l;
	char val[1024];

	xmlNodePtr osmNode;
	SHPObject *obj = NULL;
	NODE node;
	KEYVAL tags;

	obj = malloc(sizeof(SHPObject));
	initList(&tags);

	int j = 0 - shape->num_entities;

	// negative ids required for new osm nodes
	for (i = -1; i > j; i--)
	{
		obj = SHPReadObject(shape->handleShp, k);
		node.id = i;
		node.x = obj->padfX[0];
		node.y = obj->padfY[0];

		osmNode = nodeElement(node);

		if (shape->num_fields > 0)
		{
			// has tags
			for (l = 0; l < shape->num_fields; l++)
			{
				setKey(&tags, shape->field_names[l]);

				// set tag value
				snprintf(val, 1024, "%s", DBFReadStringAttribute(shape->handleDbf, k, l));
				setValue(&tags, val);

				xmlAddChild(osmNode, tagElement(&tags));
			}
		}
 
		xmlAddChild(root_node, osmNode);

		k++;
	}

}

void parseLine(xmlNodePtr root_node, SHAPE *shape)
{
	int i, l, m, v;
	int k = 0;
	int n = -1;
	int o = -1;

	int start_vertex, end_vertex;
	char val[1024];

	xmlNodePtr osmWay;
	SHPObject *obj = NULL;
	NODE node;
	KEYVAL tags;

	for (i = 0; i < shape->num_entities; i++)
	{
		obj = SHPReadObject(shape->handleShp, k);

		for (m = 0; m < obj->nParts; m++) 
		{
			osmWay = wayElement(o);
			
			if (m == obj->nParts-1)
			{
				// is linestring
				end_vertex = obj->nVertices;
			} else {
				// is multilinestring
				end_vertex = obj->panPartStart[m+1];
			}

			start_vertex = obj->panPartStart[m];

			for (v = start_vertex; v < end_vertex; v++)
			{
				node.id = n;
				node.x = obj->padfX[v];
				node.y = obj->padfY[v];
				xmlAddChild(root_node, nodeElement(node));
				xmlAddChild(osmWay, nodeRef(node));
				n--;
			}

			if (shape->num_fields > 0)
			{
				// has tags
				for (l = 0; l < shape->num_fields; l++)
				{
					setKey(&tags, shape->field_names[l]);

					// set tag value
					snprintf(val, 1024, "%s", DBFReadStringAttribute(shape->handleDbf, k, l));
					setValue(&tags, val);

					xmlAddChild(osmWay, tagElement(&tags));
				}
			}

			xmlAddChild(root_node, osmWay);
			o--;
		}

		k++;
	}
}

xmlDocPtr createXmlDoc(SHAPE *shape)
{
	xmlDocPtr doc = NULL;
	xmlNodePtr root_node = NULL;

	doc = xmlNewDoc(BAD_CAST "1.0");
	root_node = xmlNewNode(NULL, BAD_CAST "osm");
	xmlNewProp(root_node, BAD_CAST "version", BAD_CAST xmlEscape("0.6"));
	xmlDocSetRootElement(doc, root_node);

	srid = shape->srid;
	
	if (shape->filetype == SHPT_POINT)
	{
		parsePoint(root_node, shape);
	} else if (shape->filetype == SHPT_ARC) {
		parseLine(root_node, shape);
	} else {
		fprintf(stderr, "Error: Unknown or invalid shapefile type\n");
		exit(0);
	}

	return doc;
}
