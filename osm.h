/* xmllib2 */
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

/* shape */
#include "shape.h"
#include "transform.h"
#include "keyvals.h"

xmlNodePtr tagElement(KEYVAL *tag);
xmlNodePtr nodeElement(NODE *node);
xmlNodePtr wayElement(int id);
xmlDocPtr createXmlDoc(SHAPE *shape);
