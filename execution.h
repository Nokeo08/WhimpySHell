#ifndef _EXECUTION_WSH_H_
#define _EXECUTION_WSH_H_

#define READ  0
#define WRITE 1

#define true 1
#define false 0

#define LINE_BUFFER 256

char line[LINE_BUFFER];
int timesCommandWasCalled; /* number of calls to 'command' */


int shellCD(char **args);
int waitBG(char **args);
int shellHelp(char **args);
int shellExit(char **args);

int shell_exe(char* cmd, int input, int first, int last);
int sys_exe(int input, int first, int last);

#endif
