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

	while (!feof(stdin))
	{
		printf("#cisfun$ ");
		command = get_command();
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
