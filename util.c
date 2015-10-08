#include <string.h> /* strchr */
#include <ctype.h> /* isspace */
#include <sys/wait.h> /* wait */

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
