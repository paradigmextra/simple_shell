#include "header.h"

/**
 * check_builtin - Checks if parsed command in built-in
 * @cmd: Parsed command to be check
 * Return: 0 Success -1 Fail
 */
int check_builtin(char **cmd)
{
    builtin fun[] = {
        {"cd", NULL},
        {"help", NULL},
        {"echo", NULL},
        {"env", NULL},
        {"history", NULL},
        {NULL, NULL}
    };
    int i = 0;

    if (*cmd == NULL)
    {
        return (-1);
    }
    while ((fun + i)->command)
    {
        if (_strcmp(cmd[0], (fun + i)->command) == 0)
            return (0);
        i++;
    }
    return (-1);
}

/**
 * handle_builtin - Handles predefined built in commands
 * @cmd: Array of parsed command strings
 * @st: Status of last execution
 * Return: -1 Failure 0 Success
 */
int handle_builtin(char **cmd, int st)
{
    builtin built_in[] = {
        {"cd", change_dir},
        {"env", dis_env},
        {"help", display_help},
        {"echo", echo_bul},
        {"history", history_dis},
        {NULL, NULL}
    };
    int i = 0;

    while ((built_in + i)->command)
    {
        if (_strcmp(cmd[0], (built_in + i)->command) == 0)
        {
            return ((built_in + i)->function(cmd, st));
        }
        i++;
    }
    return (-1);
}

/**
 * exit_bul - Exit Status for built-in commands
 * @cmd: Array of parsed command strings
 * @input: Input received from user (to be freed)
 * @argv: Arguments before program starts (argv[0] == Shell Program Name)
 * @c: Shell execution count
 * @stat: Exit status
 */
void exit_bul(char **cmd, char *input, char **argv, int c, int stat)
{
    int status, i = 0;

    if (cmd[1] == NULL)
    {
        free(input);
        free(cmd);
        exit(stat);
    }
    while (cmd[1][i])
    {
        if (_isalpha(cmd[1][i++]) != 0)
        {
            _prerror(argv, c, cmd);
            free(input);
            free(cmd);
            exit(2);
        }
        else
        {
            status = _atoi(cmd[1]);
            if (status == 2)
            {
                _prerror(argv, c, cmd);
                free(input);
                free(cmd);
                exit(status);
            }
            free(input);
            free(cmd);
            exit(status);
        }
    }
}

/**
 * change_dir - Changes directory
 * @cmd: Parsed command
 * @st: Status of last command executed
 * Return: 0 on success 1 if failed (For OLDPWD Always 0 incase of no OLDPWD)
 */
int change_dir(char **cmd, __attribute__((unused))int st)
{
    int value = -1;
    char cwd[PATH_MAX];

    if (cmd[1] == NULL)
        value = chdir(getenv("HOME"));
    else if (_strcmp(cmd[1], "-") == 0)
    {
        value = chdir(getenv("OLDPWD"));
    }
    else
        value = chdir(cmd[1]);

    if (value == -1)
    {
        perror("hsh");
        return (-1);
    }
    else if (value != -1)
    {
        getcwd(cwd, sizeof(cwd));
        setenv("OLDPWD", getenv("PWD"), 1);
        setenv("PWD", cwd, 1);
    }
    return (0);
}

/**
 * dis_env - Display environment variable
 * @cmd: Parsed command
 * @st: Status of last command executed
 * Return: Always 0
 */
int dis_env(__attribute__((unused)) char **cmd, __attribute__((unused)) int st)
{
    size_t i;
    int len;

    for (i = 0; environ[i] != NULL; i++)
    {
        len = _strlen(environ[i]);
        write(1, environ[i], len);
        write(STDOUT_FILENO, "\n", 1);
    }
    return (0);
}

/**
 * echo_bul - Execute echo cases
 * @st: Status of the last command executed
 * @cmd: Parsed command
 * Return: Always 1 Or execute normal echo
 */
int echo_bul(char **cmd, int st)
{
    char *path;
    unsigned int pid = getppid();

    if (_strncmp(cmd[1], "$?", 2) == 0)
    {
        print_number_int(st);
        PRINT("\n");
    }
    else if (_strncmp(cmd[1], "$$", 2) == 0)
    {
        print_number(pid);
        PRINT("\n");
    }
    else if (_strncmp(cmd[1], "$PATH", 5) == 0)
    {
        path = _getenv("PATH");
        PRINT(path);
        PRINT("\n");
        free(path);
    }
    else
        return (print_echo(cmd));

    return (1);
}

/**
 * history_dis - Display history of user input on simple_shell
 * @c: Parsed command
 * @st: Status of last command executed
 * Return: 0 success or -1 if fail
 */
int history_dis(__attribute__((unused))char **c, __attribute__((unused))int st)
{
    char *filename = ".simple_shell_history";
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    int counter = 0;
    char *er;

    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        return (-1);
    }
    while ((getline(&line, &len, fp)) != -1)
    {
        counter++;
        er = _itoa(counter);
        PRINT(er);
        free(er);
        PRINT(" ");
        PRINT(line);
    }
    if (line)
        free(line);
    fclose(fp);
    return (0);
}
