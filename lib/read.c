#include "read.h"

int is_delim(const char* delim, char c);
int skip_delim(const char* delim);

int
is_delim(const char* delim, char c) {
    while (*delim) {
        if (*delim++ == c) {
            return __OK;
        }
    }
    return NOT_FOUNDED;
}

int
skip_delim(const char* delim) {
    int c;
    while (is_delim(delim, (c = getchar())) == __OK)
        ;
    if (c != '\n' && c != EOF) {
        ungetc(c, stdin);
    }
    return c;
}

char*
get_word(const char* delim) {
    int size_inc = 10;
    char* buffer = (char*)malloc(size_inc);
    char* cur_pos = buffer;
    int max_len = size_inc;
    int len = 0, call_back;
    char c;
    if (cur_pos == NULL) {
        return NULL;
    }
    if ((call_back = skip_delim(delim)) == EOF) {
        free(buffer);
        return NULL;
    } else if (call_back != '\n') {
        while (is_delim(delim, (c = getchar())) == NOT_FOUNDED) {
            if (c == '\n') {
                ungetc(c, stdin);
                break;
            }
            if (++len >= max_len) {
                char* tmp = (char*)realloc(buffer, max_len += size_inc);
                if (tmp == NULL) {
                    free(buffer);
                    return NULL;
                }
                cur_pos = tmp + len - 1;
                buffer = tmp;
            }
            *cur_pos++ = c;
        }
    }
    *cur_pos = '\0';
    return buffer;
}
