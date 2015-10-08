#include <stdio.h> /* printf, fflush, fgets, stdin */
#include <string.h> /* strchr */

#include "util.h"
#include "execution.h"

int main()
{
  n=0;

  int advance = 1;

	while (advance) {
		/* Print the command prompt */
		printf("wsh: ");
		fflush(NULL);

		/* Read a command line */
		if (!fgets(line, 1024, stdin))
			return 0;

		int input = 0;
		int first = 1;

		char* cmd = line;
		char* next = strchr(cmd, '|'); /* Find first '|' */

		while (next != NULL) {
			/* 'next' points to '|' */
			*next = '\0';
			input = run(cmd, input, first, 0);

			cmd = next + 1;
			next = strchr(cmd, '|'); /* Find next '|' */
			first = 0;
		}
		advance = run(cmd, input, first, 1);
		cleanUp(n);
		n = 0;
	}
	return 0;
}
