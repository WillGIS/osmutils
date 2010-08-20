#include "keyvals.h"

typedef struct ruleset
{
	char *rulesfile;
	int num_rules;
	KEYVAL *rules;	
} RULESET;

RULESET * parseRules(char *rulesfile);
