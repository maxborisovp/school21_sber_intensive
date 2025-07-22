#include "s21_string.h"

#include <stdio.h>
#include <stdlib.h>

int s21_strlen(const char *str) {
    if (str == NULL) return -1;
    int len = 0;
    while (str[len] != '\0') len++;
    return len;
}

int s21_strcmp(const char *str1, const char *str2) {
    int i = 0;
    while (str1[i] == str2[i] && (str1[i] != '\0' || str2[i] != '\0')) i++;
    return str1[i] - str2[i];
}

char *s21_strcpy(char *dest_str, const char *source_str) {
    int i = 0;
    while (source_str[i] != '\0') {
        dest_str[i] = source_str[i];
        i++;
    }
    dest_str[i] = '\0';
    return dest_str;
}

char *s21_strcat(char *dest_str, const char *source_str) {
    int i = 0;
    while (dest_str[i] != '\0') i++;
    int j = 0;
    while (source_str[j] != '\0') {
        dest_str[i] = source_str[j];
        i++;
        j++;
    }
    dest_str[i] = '\0';
    return dest_str;
}

char *s21_strchr(const char *str, int target) {
    int i = 0;
    while (str[i] != target && str[i] != '\0') i++;
    char *res = NULL;
    if (str[i] != '\0') res = (char *)&str[i];
    return res;
}

char *s21_strstr(const char *str, const char *substr) {
    if (str == NULL || substr == NULL) return NULL;
    char *res = NULL;
    int stop = 1;
    for (int i = 0; str[i] != '\0' && stop; i++) {
        int j = 0;
        while (substr[j] != '\0' && str[i + j] == substr[j]) {
            j++;
        }
        if (substr[j] == '\0') {
            res = (char *)(str + i);
            stop = 0;
        }
    }
    return res;
}

char *s21_strtok(char *str, const char *delim) {
    static char *last_token = NULL;
    char *token = NULL;

    if (str == NULL) {
        str = last_token;
        if (str == NULL) {
            return NULL;
        }
    }
    while (*str != '\0') {
        const char *d = delim;
        int is_delim = 0;
        while (*d != '\0') {
            if (*str == *d) {
                is_delim = 1;
                break;
            }
            d++;
        }
        if (!is_delim) {
            break;
        }
        str++;
    }

    if (*str == '\0') {
        last_token = NULL;
        return NULL;
    }

    token = str;

    while (*str != '\0') {
        const char *d = delim;
        int is_delim = 0;
        while (*d != '\0') {
            if (*str == *d) {
                is_delim = 1;
                break;
            }
            d++;
        }
        if (is_delim) {
            break;
        }
        str++;
    }

    if (*str != '\0') {
        *str = '\0';
        last_token = str + 1;
    } else {
        last_token = NULL;
    }

    return token;
}
