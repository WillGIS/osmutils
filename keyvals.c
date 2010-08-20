#include "keyvals.h"
#include <assert.h>

void initList(KEYVAL *head)
{
	assert(head);

	head->next = head;
	head->prev = head;
	head->key = NULL;
	head->value = NULL;
}

void setKey(KEYVAL *tag, char *key)
{
	tag->key = key;
}

void setValue(KEYVAL *tag, char *value)
{
	tag->value = value;
}

char * getKey(KEYVAL *tag)
{
	return tag->key;
}

char * getValue(KEYVAL *tag)
{
	return tag->value;
}
