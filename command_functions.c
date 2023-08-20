#include "main.h"
#include "stdlib.h"
#include "stddef.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>

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
 * this function to get the path without using /bin
*/

char *which(const char *command)
{
    char *path = getenv("PATH");
    char *full_path = NULL;
    char *token;
    char *delim = ":";

    if (!path)
        return NULL;

    token = strtok(path, delim);
    while (token)
    {
 	full_path = malloc(strlen(token) + strlen(command) + 2);
        if (!full_path)
            return NULL;

        sprintf(full_path, "%s/%s", token, command);
        if (access(full_path, X_OK) == 0)
            return full_path;


        free(full_path);
        token = strtok(NULL, delim);
    }

    return NULL;
}
