#ifndef FUNCTIONS
#define FUNCTIONS
char **get_command(void);
extern char *which(char *command, char **path);
char **get_path(void);
int builtin_commands(char *command, char **env);
#endif /*FUNCTIONS*/
