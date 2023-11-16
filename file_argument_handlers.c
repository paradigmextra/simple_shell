#include "header.h"

/**
 * read_file - Reads commands from the argument File
 * @file_name: File containing commands
 * @argv: Arguments passed
 * Return: -1 or 0
 */
int read_file(const char *file_name, char **argv) {
  FILE *fp = fopen(file_name, "r");
  if (!fp) {
    error_file(argv, 0);
    return 127;
  }

  char line[1024];
  while (fgets(line, sizeof(line), fp)) {
    treat_line(line, fp, argv);
  }

  fclose(fp);
  return 0;
}

/**
 * treat_line - Parse and execute commands from a file line
 * @line: Line from file
 * @fp: File descriptor
 * @argv: Command line arguments
 */
void treat_line(char *line, FILE *fp, char **argv) {
  char *cmd[MAX_ARGS + 1];
  int num_tokens = parse_cmd(line, cmd);

  if (!strcmp(cmd[0], "exit")) {
    exit_bul_for_file(cmd, fp);
  } else if (check_builtin(cmd)) {
    handle_builtin(cmd);
  } else {
    check_cmd(cmd, line, num_tokens, argv);
  }
}

/**
 * exit_bul_for_file - Exit status handler for file input
 * @cmd: Parsed command
 * @fp: File Descriptor
 */
void exit_bul_for_file(char **cmd, FILE *fp) {
  if (!cmd[1]) {
    fclose(fp);
    exit(errno);
  }

  int status = atoi(cmd[1]);
  fclose(fp);
  exit(status);
}
