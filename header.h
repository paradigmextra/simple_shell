#ifndef HEADER_H
#define HEADER_H

// ---- MACROS ----
#define PRINT_ERROR(c) (write(STDERR_FILENO, c, _strlen(c)))
#define BUFFER_SIZE 10240
#define TOKEN_DELIMITER " \t\r\n\a"

// ---- STANDARD LIBRARIES ----
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/limits.h>

// ---- STRING HANDLING FUNCTIONS ----
char *_copy_partial(char *dest, char *src, int n);
int _string_length(char *s);
int _put_character(char c);
int _convert_to_integer(char *s);
void _display_string(char *str);
int _compare_strings(char *s1, char *s2);
int _is_alphabetic(int c);
void _reverse_array(char *arr, int len);
int _calculate_integer_length(int num);
char *_integer_to_string(unsigned int n);
char *_concatenate_strings(char *dest, char *src);
char *_copy_string(char *dest, char *src);
char *_locate_character(char *s, char c);
int _compare_strings_partial(const char *s1, const char *s2, size_t n);
char *_duplicate_string(char *str);

// ---- MEMORY HANDLING FUNCTIONS ----
void _release_environment(char **env);
void *_initialize_array(void *a, int element_size, unsigned int length);
char *_copy_memory(char *dest, char *src, unsigned int n);
void *_allocate_memory(unsigned int size);
void *_resize_memory(void *ptr, unsigned int old_size, unsigned int new_size);
void _free_all(char **input, char *line);

// ---- MISC AND INPUT FUNCTIONS ----
char *_get_input();
char *_remove_spaces(char *str);
char *_replace_newline(char *string);
void _handle_hashtag(char *buffer);
void _display_prompt();
unsigned int _check_delimiter(char c, const char *str);
char *_tokenize_string(char *str, const char *delimiter);
int _handle_history(char *input);
char **_separate_input(char *input);

// ---- FILE ARGUMENT HANDLING FUNCTIONS ----
void _read_file(char *file, char **argv);
void _process_file_line(char *line, int count, FILE *fp, char **argv);
void _exit_for_file(char **cmd, char *line, FILE *fd);

// ---- PARSED ARGUMENT HANDLING FUNCTIONS ----
char **_parse_command(char *input);
int _handle_builtin(char **cmd, int er);
int _check_command(char **cmd, char *input, int c, char **argv);
void _handle_signal(int sig);

// ---- ERROR HANDLING ----
void _print_error_message(char *input, int counter, char **argv);
void _print_custom_error(char **argv, int c, char **cmd);
void _handle_file_error(char **argv, int c);

// ---- ENVIRONMENT HANDLING ----
extern char **environ;
void _initialize_environment(char **env);
void _release_environment(char **env);

// ---- PRINTING FUNCTIONS ----
void _print_unsigned_integer(unsigned int n);
void _print_integer(int n);
int _print_echo(char **cmd);

// ---- PATH HANDLER ----
int _handle_path_command(char **cmd);
char *_build_path(char *token, char *value);
char *_get_environment_variable(char *name);

// ---- HELP FUNCTIONS ----
void _display_env_help();
void _display_setenv_help();
void _display_unsetenv_help();
void _display_history_help();
void _display_all_help();
void _display_alias_help();
void _display_cd_help();
void _display_exit_help();
void _display_help_help();
int _show_help(char **cmd, __attribute__((unused))int st);

// ---- BUILTIN COMMAND HANDLERS AND EXECUTION ----
int _check_builtin_command(char **cmd);
int _handle_builtin_command(char **cmd, int st);
void _exit_builtin(char **cmd, char *input, char **argv, int c, int stat);
int _change_directory(char **cmd, __attribute__((unused))int st);
int _display_environment(__attribute__((unused)) char **cmd,
	    __attribute__((unused)) int st);
int _execute_echo_builtin(char **cmd, int st);
int _display_history(__attribute__((unused))char **c,
		__attribute__((unused)) int st);

// ---- STRUCT FOR BUILTIN COMMANDS ----
typedef struct _builtin_command {
	char *command;
	int (*function)(char **line, int st);
} builtin;

#endif /* HEADER_H */
