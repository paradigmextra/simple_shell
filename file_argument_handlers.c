#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAX_LINE_SIZE 1024

/**
 * Function prototypes
 */
void error_file(char **argv, int count);
char **parse_cmd(char *line);
int _strncmp(const char *s1, const char *s2, size_t n);
int check_builtin(char **cmd);
int handle_builtin(char **cmd, int stat);
int check_cmd(char **cmd, char *line, int count, char **argv);
int _atoi(const char *str);
void exit_bul_for_file(char **cmd, char *line, FILE *fd);

/**
 * read_file - Reads commands from the argument File
 */
void read_file(char *file, char **argv)
{
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    int count = 0;

    fp = fopen(file, "r");
    if (fp == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    while (getline(&line, &len, fp) != -1)
    {
        count++;
        treat_file(line, count, fp, argv);
    }

    if (line)
        free(line);

    fclose(fp);
    exit(EXIT_SUCCESS);
}

/**
 * treat_file - Parse commands and handle their execution
 */
void treat_file(char *line, int count, FILE *fp, char **argv)
{
    char **cmd = parse_cmd(line);
    int stat = 0;

    if (_strncmp(cmd[0], "exit", 4) == 0)
        exit_bul_for_file(cmd, line, fp);
    else if (check_builtin(cmd) == 0)
    {
        stat = handle_builtin(cmd, stat);
        free(cmd);
    }
    else
    {
        stat = check_cmd(cmd, line, count, argv);
        free(cmd);
    }
}

/**
 * exit_bul_for_file - Exit status handler for file input
 */
void exit_bul_for_file(char **cmd, char *line, FILE *fd)
{
    int status;

    if (cmd[1] == NULL)
    {
        free(line);
        free(cmd);
        fclose(fd);
        exit(errno);
    }

    // Validate if cmd[1] is a valid integer
    for (int i = 0; cmd[1][i]; i++)
    {
        if (!isdigit(cmd[1][i]))
        {
            perror("Illegal number");
            free(line);
            free(cmd);
            fclose(fd);
            exit(EXIT_FAILURE);
        }
    }

    status = _atoi(cmd[1]);
    free(line);
    free(cmd);
    fclose(fd);
    exit(status);
}

// Add the remaining function implementations (parse_cmd, check_builtin, handle_builtin, check_cmd, _atoi, etc.)
