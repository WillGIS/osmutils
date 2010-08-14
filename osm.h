/* xmllib2 */
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

/* shape */
#include "shape.h"
#include "transform.h"
#include "keyvals.h"

typedef unsigned char uchar;

typedef struct node_array {
	uchar *serialized_nodelist;
	uchar dims;
	int nnodes;
	int maxnodes;
} NODEARRAY;

typedef struct dyn_node_array {
	NODEARRAY *na;
	size_t nodesize;
	size_t capacity;
} DYNNODEARRAY;

#define TYPE_NDIMS(t) ((((t)&0x20)>>5)+(((t)&0x10)>>4)+2)

/* Create a new dynamic nodearray */
extern DYNNODEARRAY *dynnodearray_create(size_t initial_capacity, int dims);
extern int dynnodearray_addNode(DYNNODEARRAY *dna, NODE *node);
extern int nodeArray_nodesize(const NODEARRAY *na);

xmlNodePtr tagElement(KEYVAL *tag);
xmlNodePtr nodeElement(NODE node);
xmlNodePtr wayElement(int id);
xmlNodePtr nodeRef(NODE node);
xmlDocPtr createXmlDoc(SHAPE *shape);
