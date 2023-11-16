#include "main.h"

ssize_t gb_getline(char **line_ptr, size_t *len_siz, FILE *stream);

/**
 * gb_getline - Custom getline function
 * @line_ptr: Pointer to line buffer
 * @len_siz: Pointer to length of buffer
 * @stream: Stream to read from
 * Return: Number of characters read or -1 if fail
 */
ssize_t gb_getline(char **line_ptr, size_t *len_siz, FILE *stream) {
    ssize_t read_char, p_len = 0;
    char *line = *line_ptr, *new_line;

    if (line == NULL || *len_siz == 0) {
        *len_siz = 1024;
        line = malloc(*len_siz);
        if (line == NULL)
            return -1;
    }

    while (1) {
        char *the_getline = fgets(line + p_len, (int)(*len_siz - p_len), stream);
        if (the_getline == NULL) {
            if (p_len == 0) {
                free(line);
                *line_ptr = NULL;
                *len_siz = 0;
                return -1;
            } else {
                *line_ptr = line;
                *len_siz = *len_siz;
                return p_len;
            }
        }

        read_char = gb_strlen(line + p_len);

        if (read_char > 0 && line[p_len + read_char - 1] == '\n') {
            line[p_len + read_char - 1] = '\0';
            *line_ptr = line;
            *len_siz = *len_siz;
            return p_len + read_char;
        }

        p_len += read_char;

        if (*len_siz - p_len <= 1) {
            *len_siz *= 2;
            new_line = realloc(line, *len_siz);
            if (new_line == NULL) {
                free(line);
                *line_ptr = NULL;
                *len_siz = 0;
                return -1;
            }
            line = new_line;
        }
    }
}
