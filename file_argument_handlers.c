#include "header.h"

/**
 * @brief Reads and executes commands from the specified file.
 *
 * @param file File containing commands.
 * @param argv Command line arguments.
 * @return -1 or 0.
 */
void read_file(char *file, char **argv)
{
    FILE *fp = fopen(file, "r");
    if (!fp)
    {
        error_file(argv, 0);
        exit(127);
    }

    char *line = NULL;
    size_t len = 0;
    int count = 0;

    while (getline(&line, &len, fp) != -1)
    {
        count++;
        treat_file(line, count, fp, argv);
    }

    free(line);
    fclose(fp);
    exit(0);
}

/**
 * @brief Parses and executes commands from a file line.
 *
 * @param line Line from the file.
 * @param count Error counter.
 * @param fp File descriptor.
 * @param argv Command line arguments.
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
 * @brief Handles exit status for file input.
 *
 * @param cmd Parsed command.
 * @param line Line from a file.
 * @param fd File descriptor.
 */
void exit_bul_for_file(char **cmd, char *line, FILE *fd)
{
    int status = 0;

    if (cmd[1] == NULL)
    {
        free(line);
        free(cmd);
        fclose(fd);
        exit(errno);
    }

    int i = 0;
    while (cmd[1][i])
    {
        if (_isalpha(cmd[1][i++]) < 0)
            perror("Illegal number");
    }

    status = _atoi(cmd[1]);
    free(line);
    free(cmd);
    fclose(fd);
    exit(status);
}
