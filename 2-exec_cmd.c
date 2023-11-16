#include "main.h"

void exec_cmd(char **args, char **env);
/**
 * exec_cmd - This function will execute the command
 * @args: The command and its arguments
 * @env: The environment variables
 * Return: Nothing
 */
void exec_cmd(char **args, char **env)
{
	char *full_path = getenv("PATH"), *path, *token;
	char our_path[1024];


	if (args[0] == NULL)
	{
		perror("Command not provided");
		exit(2);
	}

	if (args[0][0] == '/')
	{
		if (access(args[0], X_OK) == 0)
		{
			execve(args[0], args, env);
			exit(2);
		}

		else
		{
			perror("execve");
			exit(2);
		}
	}

	if (full_path == NULL)
	{
		perror("Unable to locate PATH environment variable");
		exit(2);
	}

	path = gb_strdup(full_path);
	if (path == NULL)
	{
		perror("gb_strdup");
		exit(2);
	}

	
