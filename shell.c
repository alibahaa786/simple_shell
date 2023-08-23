#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "main.h"

/**
 * main - main shell
 * @ac: number of arguments
 * @av: array of arguments
 * @env: environment
 * Return: 0 on success
*/

int main(int ac, char **av, char **env)
{
	char **command;
	pid_t pid;
	int status;
	char **path = get_path();
	char *full_path;
	int builtin;

	if (!ac)
	{
	}
	do
	{
		printf("#cisfun$ ");
		command = get_command();
		builtin = builtin_commands(command[0], env);
		if (builtin < 0)
			break;
		else if (builtin > 0)
			continue;
		full_path = which(command[0], path);
		if (!full_path)
		{
			printf("%s: %s: not found\n", av[0], command[0]);
			continue;
		}
		pid = fork();
		if (pid)
			wait(&status);
		else
		{
			if (execve(full_path, command, NULL) < 0)
				printf("%s: No such file or directory\n", av[0]);
		}
		free(command);
	} while (!feof(stdin) && isatty(STDIN_FILENO));
	free(path);
	return (0);
}
