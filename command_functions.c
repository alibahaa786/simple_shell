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
	fcommand[strlen(fcommand)-1] = '\0';
	command = malloc(sizeof(char *) * 1024);
	if (!command)
		return (NULL);
	command[0] = strtok(fcommand, " ");
	for (i = 1;;i++)
	{
		command[i] =  strtok(NULL, " ");
		if (!command[i])
			break;
	}
	return (command);
}
