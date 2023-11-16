#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read_file(char *file, char **argv);
void treat_file(char *line, int count, FILE *fp, char **argv);
void exit_bul_for_file(char **cmd, char *line, FILE *fd);

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
        exit(1);
    }
    while ((getline(&line, &len, fp)) != -1)
    {
        count++;
        treat_file(line, count, fp, argv);
    }
    if (line)
        free(line);
    fclose(fp);
    exit(0);
}

void treat_file(char *line, int count, FILE *fp, char **argv)
{
    char **cmd;
    int stat = 0;

    cmd = parse_cmd(line); // Assuming the `parse_cmd` function is defined elsewhere
    if (strncmp(cmd[0], "exit", 4) == 0)
        exit_bul_for_file(cmd, line, fp);
    else if (check_builtin(cmd) == 0) // Assuming the `check_builtin` function is defined elsewhere
    {
        stat = handle_builtin(cmd, stat); // Assuming the `handle_builtin` function is defined elsewhere
        free(cmd);
    }
    else
    {
        stat = check_cmd(cmd, line, count, argv); // Assuming the `check_cmd` function is defined elsewhere
        free(cmd);
    }
}

void exit_bul_for_file(char **cmd, char *line, FILE *fd)
{
    int status;
    int i = 0;

    if (cmd[i] == NULL)
    {
        free(line);
        free(cmd);
        fclose(fd);
        exit(errno);
    }
    while (cmd[1][i])
    {
        if (isalpha(cmd[1][i++]) == 0) // Assuming the `_isalpha` function is defined elsewhere
        {
            perror("Illegal number");
            exit(1);
        }
    }
    status = atoi(cmd[1]); // Assuming the `_atoi` function is defined elsewhere
    free(line);
    free(cmd);
    fclose(fd);
    exit(status);
}
