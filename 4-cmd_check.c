#include "main.h"

#define MAX_ALIASES 10

typedef struct {
    char *name;
    char *value;
} Alias;

Alias aliases[MAX_ALIASES];

int check_cmd(char **input);

/**
 * check_cmd - Check if the command exists in the path or aliases
 * @input: Pointer to the command.
 * Return: Return 1 on success and 0 on failure.
 */
int check_cmd(char **input) {
    char *path, *token, *bufa;
    static char path_bufa[1024];
    int i, num_aliases = MAX_ALIASES;

    for (i = 0; i < num_aliases; i++) {
        if (aliases[i].name != NULL && gb_strcmp(*input, aliases[i].name) == 0) {
            *input = aliases[i].value; /** Replace the alias with its value **/
            return 1;
        }
    }

    path = getenv("PATH");
    if (path == NULL || input == NULL || *input == NULL) {
        return 0;
    }

    if (access(*input, X_OK) == 0 && (*input)[0] == '/') {
        return 1;
    }

    gb_strcpy(path_bufa, path);
    token = gb_strtok(path_bufa, ":");
    while (token != NULL) {
        bufa = malloc(gb_strlen(token) + gb_strlen(*input) + 2);
        if (bufa == NULL) {
            perror("malloc");
            return 0;
        }

        gb_strcpy(bufa, token);
        gb_strcat(bufa, "/");
        gb_strcat(bufa, *input);

        if (access(bufa, X_OK) == 0) {
            free(bufa);
            return 1;
        }

        free(bufa);
        token = gb_strtok(NULL, ":");
    }

    return 0;
}
