#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "main.h"

/**
 * main - main shell
 * Return: 0 on success
*/

int main(void)
{
	char **command;
	pid_t pid;
	int status;
	char *full_path;

	while (!feof(stdin))
	{
		printf("#cisfun$ ");
		command = get_command();
		full_path = which(command[0]);
		if (!full_path)
		{
			printf("Could not find command: %s\n", command[0]);
			continue;
		}
		pid = fork();
		if (pid)
			wait(&status);
		else
		{
			if (execve(command[0], command, NULL) < 0)
				printf("No such file or directory\n");
		}
	}
	return (0);
}
