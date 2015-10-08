#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "execution.h"
#include "util.h"

/*
  List of builtin commands, followed by their corresponding functions.
 */
char *builtin_str[] = {
  "cd",
  "wait",
  "exit"
};

int (*builtin_func[]) (char **) = {
  &shellCD,
  &waitForBackground,
  &shellExit
};

int wsh_num_builtins() {
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

int waitForBackground(char **args)
{
  int i;
  printf("The following are built in:\n");

  for (i = 0; i < wsh_num_builtins(); i++) {
    printf("  %s\n", builtin_str[i]);
  }

  return 1;
}

int shellExit(char **args)
{
  return 0;
}

int run(char* cmd, int input, int first, int last)
{
  int i;
	splitLine(cmd);
	if (args[0] != NULL) {

    for (i = 0; i < wsh_num_builtins(); i++) {
      if (strcmp(args[0], builtin_str[i]) == 0) {
        return (*builtin_func[i])(args);
      }
    }

		n += 1;
		return command(input, first, last);
	}
	return 0;
}

/*
 * Handle commands separatly
 * input: return value from previous command (useful for pipe file descriptor)
 * first: 1 if first command in pipe-sequence (no input from previous pipe)
 * last: 1 if last command in pipe-sequence (no input from previous pipe)
 *
 * EXAMPLE: If you type "ls | grep shell | wc" in your shell:
 *    fd1 = command(0, 1, 0), with args[0] = "ls"
 *    fd2 = command(fd1, 0, 0), with args[0] = "grep" and args[1] = "shell"
 *    fd3 = command(fd2, 0, 1), with args[0] = "wc"
 *
 * So if 'command' returns a file descriptor, the next 'command' has this
 * descriptor as its 'input'.
 */
int command(int input, int first, int last)
{
	int fd[2];

	/* Invoke pipe */
	pipe( fd );
	pid_t pid = fork();

	/*
	 SCHEME:
	 	STDIN --> O --> O --> O --> STDOUT
	*/

	if (pid == 0) {
		if (first == 1 && last == 0 && input == 0) {
			// First command
			dup2( fd[WRITE], STDOUT_FILENO );
		} else if (first == 0 && last == 0 && input != 0) {
			// Middle command
			dup2(input, STDIN_FILENO);
			dup2(fd[WRITE], STDOUT_FILENO);
		} else {
			// Last command
			dup2( input, STDIN_FILENO );
		}

		if (execvp( args[0], args) == -1)
			_exit(EXIT_FAILURE); // If child fails
	}

	if (input != 0)
		close(input);

	// Nothing more needs to be written
	close(fd[WRITE]);

	// If it's the last command, nothing more needs to be read
	if (last == 1)
		close(fd[READ]);

	return fd[READ];
}

/*
int systemExecute(char **args)
{
  pid_t pid;
  int status;

  pid = fork();
  if (pid == 0) {

    if (execvp(args[0], args) == -1) {
      perror("wsh");
    }
    exit(EXIT_FAILURE);
  } else if (pid < 0) {

    perror("wsh");
  } else {

    do {
      waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 1;
}


int shellExecute(char **args)
{
  int i;

  if (args[0] == NULL) {

    return 1;
  }

  for (i = 0; i < wsh_num_builtins(); i++) {
    if (strcmp(args[0], builtin_str[i]) == 0) {
      return (*builtin_func[i])(args);
    }
  }

  return systemExecute(args);
}




void REPL(void)
{
  char *line;
  int advance;
  List* running = list_NewList();
  List* finished = list_NewList();

  WSHCommand* command;
  struct Job* j = 0;
  do {
    printf("wsh: ");
    line = readInput();
    command = processInput(line);
    advance = shellExecute(command->args);

    command=NULL;
    free(line);
  } while (advance);
}
*/
