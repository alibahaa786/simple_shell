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
	int error;

	if (!ac)
	{
	}
	if (!isatty(STDIN_FILENO))
		printf("$ ");
	do {
		if (isatty(STDIN_FILENO))
			printf("$ ");
		command = get_command();
		if (!isatty(STDIN_FILENO) && (command[0][0] == 127 || command[0][0] <= 31) )
			 break;
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
			error = execve(full_path, command, NULL);
                        if (error < 0)
                                printf("%s: No such file or directory\n", av[0]);
                }
		free(command);
	}while (!feof(stdin));
	free(path);
	return (error);
}
