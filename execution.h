#ifndef _EXECUTION_WSH_H_
#define _EXECUTION_WSH_H_

#define READ  0
#define WRITE 1

char line[1024];
int n; /* number of calls to 'command' */

/*
  Function Declarations for builtin shell commands:
 */
int shellCD(char **args);
int waitForBackground(char **args);
int shellExit(char **args);

int run(char* cmd, int input, int first, int last);
int command(int input, int first, int last);

#endif
