#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>

#include "util.h"


void splitLine(char* cmd)
{
	cmd = trimLeadingWhiteSpace(cmd);
	char* next = strchr(cmd, ' ');
	int i = 0;

	while(next != NULL) {
		next[0] = '\0';
		args[i] = cmd;
		++i;
		cmd = trimLeadingWhiteSpace(next + 1);
		next = strchr(cmd, ' ');
	}

	if (cmd[0] != '\0') {
		args[i] = cmd;
		next = strchr(cmd, '\n');
		next[0] = '\0';
		++i;
	}

	args[i] = NULL;
}

char* trimLeadingWhiteSpace(char* s)
{
	while (isspace(*s)) ++s;
	return s;
}

void cleanUp(int n)
{
	int i;
	for (i = 0; i < n; ++i)
		wait(NULL);
}
