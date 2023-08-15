#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main() {
  size_t size = 1024;
  pid_t pid;
  int status;
  char *command;
  char **argv;

  command = malloc(sizeof (char *));
  argv = malloc(sizeof(char *) * 3);
  argv[0] = NULL;

  while (1) {
    printf("#cisfun$ ");
    getline(&command, &size, stdin);

    if (strcmp(command, "exit") == 0) {
      break;
    }

    argv[0] = command;
    pid = fork();
    if (pid) {
      wait(&status);
    } else {
      execve(command, argv, NULL);
    }
  }

  for (int i = 0; i < 3; i++) {
    free(argv[i]);
  }

  free(argv);

  return 0;
}
