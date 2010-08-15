/* xmllib2 */
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

/* shape */
#include "shape.h"
#include "transform.h"

xmlNodePtr tagElement(KEYVAL *tag);
xmlNodePtr nodeElement(NODE node);
xmlNodePtr wayElement(int id);
xmlNodePtr nodeRef(NODE node);
xmlDocPtr createXmlDoc(SHAPE *shape);
