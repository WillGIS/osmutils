#ifndef KEYVAL_H
#define KEYVAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <string.h>

// see osm2pgsql/keyvals.h
typedef struct keyval {
	char *key;
	char *value;
	struct keyval *next;
	struct keyval *prev;
} KEYVAL;

void initList(KEYVAL *head);
void setKey(KEYVAL *tag, char *key);
void setValue(KEYVAL *tag, char *value);
char * getKey(KEYVAL *tag);
char * getValue(KEYVAL *tag);
#endif
