#include <unistd.h> /* chdir, pipe, fork, dup2, STDOUT_FILENO, STDIN_FILENO, execvp, _exit */
#include <stdlib.h> /* EXIT_FAILURE */
#include <stdio.h>  /* perror, printf */
#include <string.h> /* strcmp */

#include "execution.h"
#include "util.h"

char *builtin_str[] = {
  "cd",
  "wait",
  "exit",
  "help"
};

int (*builtin_func[]) (char **) = {
  &shellCD,
  &waitBG,
  &shellExit,
  &shellHelp
};

int builtins_Size() {
  return sizeof(builtin_str) / sizeof(char *);
}

int shellCD(char **args)
{
  if (args[1] == NULL) {
    fprintf(stderr, "wsh: expected argument to \"cd\"\n");
  } else {
    if (chdir(args[1]) != 0) {
      perror("wsh");
    }
  }
  return 1;
}

int waitBG(char **args)
{
  printf("Not yet implemented.\n");

  return 1;
}

int shellHelp(char **args)
{
  int i;
  printf("\nThe following are built in:\n");

  for (i = 0; i < builtins_Size(); i++) {
    printf("  %s\n", builtin_str[i]);
  }

  printf("\n");

  return 1;
}

int shellExit(char **args)
{
  printf("\nThank you for using wsh!\n\n");
  return 0;
}

int shell_exe(char* cmd, int input, int first, int last)
{
  int i;
	splitLine(cmd);
	if (args[0] != NULL) {

    for (i = 0; i < builtins_Size(); i++) {
      if (strcmp(args[0], builtin_str[i]) == 0) {
        return (*builtin_func[i])(args);
      }
    }

		timesCommandWasCalled += 1;
		return sys_exe(input, first, last);
	}
	return 0;
}

/*
 * input: return value from previous command
 * first: 1 if first command in pipe
 * last: 1 if last command in pipe
 */
int sys_exe(int input, int first, int last)
{
	int fd[2];

	pipe( fd );
	pid_t pid = fork();


	if (pid == 0) {
		if (first == true && last == false && input == false) {
			/* First */
			dup2( fd[WRITE], STDOUT_FILENO );
		} else if (first == false && last == false && input != false) {
			/* Middle */
			dup2(input, STDIN_FILENO);
			dup2(fd[WRITE], STDOUT_FILENO);
		} else {
			/* Last */
			dup2( input, STDIN_FILENO );
		}

		if (execvp( args[0], args) == -1)
			_exit(EXIT_FAILURE);
	}

	if (input != false)
		close(input);

	/* Done writting */
	close(fd[WRITE]);

	/* Done reading */
	if (last == 1)
		close(fd[READ]);

	return fd[READ];
}
