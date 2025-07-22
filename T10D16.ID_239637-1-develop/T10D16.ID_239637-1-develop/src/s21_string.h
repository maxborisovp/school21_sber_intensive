#ifndef S21_STRING_H
#define S21_STRING_H

int s21_strlen(const char *str);
int s21_strcmp(const char *str1, const char *str2);
char *s21_strcpy(char *dest_str, const char *source_str);
char *s21_strcat(char *dest_str, const char *source_str);
char *s21_strchr(const char *str, int target);
char *s21_strstr(const char *str, const char *substr);
char *s21_strtok(char *str, const char *delin);

#endif
