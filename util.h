#ifndef _UTIL_WSH_H_
#define _UTIL_WSH_H_

char* args[512];


void splitLine(char* cmd);
char* trimLeadingWhiteSpace(char* s);
void cleanUp(int n);

#endif
