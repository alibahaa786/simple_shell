#include "main.h"
#include "stdlib.h"
#include "stddef.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>

/**
 * get_command - gets command fromuser input
 * Return: an array of strings with the command and its arguments
*/

char **get_command(void)
{
	char **command;
	char *fcommand;
	size_t size = 1024;
	int i = 1;

	fcommand = malloc(sizeof(char) * size);
	if (!fcommand)
		return (NULL);
	getline(&fcommand, &size, stdin);
	fcommand[strlen(fcommand) - 1] = '\0';
	command = malloc(sizeof(char *) * 1024);
	if (!command)
		return (NULL);
	command[0] = strtok(fcommand, " ");
	for (i = 1; ; i++)
	{
		command[i] =  strtok(NULL, " ");
		if (!command[i])
			break;
	}
	return (command);
}

/**
 * which - function that check command in every directory of path
 * @command: command user entered
 * @path: array of directories in PATH
 * Return: full path of command
*/

char *which(char *command, char **path)
{
	char *full_path;
	struct stat st, st2;
	int i;

	if (!stat(command, &st))
		return (command);
	if (!path)
		return (NULL);
	full_path = malloc(sizeof(char *));
	if (!full_path)
		return (NULL);
	for (i = 0; path[i]; i++)
	{
	sprintf(full_path, "%s/%s", path[i], command);
	if (!stat(full_path, &st2))
	return (full_path);
	}
	return (NULL);
}

/**
 * get_path - function to declare path as an array
 * Return: array of directories in PATH
*/

char **get_path(void)
{
	int i = 0;
	char **path;

	path = malloc(sizeof(char *) * 1024);
	path[0] = strtok(getenv("PATH"), ":");
	while (path[i])
	{
		i++;
		path[i] = strtok(NULL, ":");
	}
	return (path);
}

/**
 * builtin_commands - perfoms commands for exit and env
 * @command: command user entered
 * @env: environment
 * Return: -1 for exit, 1 for env, otherwise 0
*/

int builtin_commands(char *command, char **env)
{
	int i;

	if (!strcmp(command, "exit"))
	{
		printf("exit\n\n\n[Disconnected...]\n");
		return (-1);
	}
	else if (!strcmp(command, "env"))
	{
		for (i = 0; env[i]; i++)
			printf("%s\n", env[i]);
		return (1);
	}
	return (0);
}
