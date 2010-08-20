#include "ruleset.h"

// TODO - handle quotes and tags containing colons, such as addr:street
RULESET * parseRules(char *rulesfile)
{
	FILE *f;
	RULESET *ruleset;
	int nLines = 0;

	if ((f = fopen(rulesfile, "rt")))
	{
		char LineCount[256];

		ruleset = malloc(sizeof(RULESET));
		ruleset->rulesfile = rulesfile;	

		while(fgets(LineCount, sizeof(LineCount), f))
		{
			nLines++;
		}
	}

	ruleset->num_rules = nLines;

	fclose(f);

	if ((f = fopen(rulesfile, "rt")))
	{	
		char Line[256];
		char *L_text;	

		ruleset->rules = malloc(nLines * sizeof(KEYVAL));

		nLines = 0;

		while(fgets(Line, sizeof(Line), f))
		{	
			initList(&ruleset->rules[nLines]);

			L_text = strtok(Line, ",");
			setKey(&ruleset->rules[nLines], strdup(L_text));

			L_text = strtok(NULL, ",");
			L_text = strtok(L_text, "\n");
			setValue(&ruleset->rules[nLines], strdup(L_text));
          
			nLines++;
		}

		fclose(f);
	} else {
		fprintf(stderr, "Error: cannot open rules file.\n");
	}

	return ruleset;
}
