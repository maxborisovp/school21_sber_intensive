#include <stdio.h>
#include <stdlib.h>

#include "s21_string.h"

#define MAX_LENGTH 100

int input_n(int *n);
int input_str(char *str);
int find_slovo(char *str, int *pos);
void print_slovo(char *str, int pos_ot, int pos_do);
void format_str(char *str, int n);
void split_long_word(char *str, int *slovo_start, int slovo_len, int n, int *cur_line_len, int *first_word);

int main(int argc, char *argv[]) {
    int n;
    char str[MAX_LENGTH];
    int flag = 1;
    flag = flag && (argc == 2) && (s21_strcmp(argv[1], "-w") == 0);
    flag = flag && input_n(&n);
    flag = flag && input_str(str);
    if (flag) {
        format_str(str, n);
    } else
        printf("n/a");
    return 0;
}

int input_n(int *n) {
    int flag = 1;
    char ch;
    if (scanf("%d%c", n, &ch) != 2 || *n <= 0 || ch != '\n') flag = 0;
    return flag;
}

int input_str(char *str) {
    int flag = 1;

    if (fgets(str, MAX_LENGTH, stdin) == NULL)
        flag = 0;
    else {
        int i = 0;
        int stop = 1;
        while (str[i] != '\0' && stop) {
            if (str[i] == '\n') {
                str[i] = '\0';
                stop = 0;
            }
            i++;
        }
    }
    return flag;
}

int find_slovo(char *str, int *pos) {
    int len = 0;
    while (str[*pos] == ' ') {
        (*pos)++;
    }
    while (str[*pos] != ' ' && str[*pos] != '\0') {
        len++;
        (*pos)++;
    }
    return len;
}

void print_slovo(char *str, int pos_ot, int pos_do) {
    for (int i = pos_ot; i < pos_do; i++) printf("%c", str[i]);
}

void format_str(char *str, int n) {
    int pos = 0;
    int cur_line_len = 0;
    int slovo_start, slovo_len;
    int first_word = 1;

    while (str[pos] != '\0') {
        while (str[pos] == ' ') {
            pos++;
        }
        if (str[pos] == '\0') break;
        slovo_start = pos;
        slovo_len = find_slovo(str, &pos);

        if (slovo_len == 0) continue;

        if (first_word) {
            if (slovo_len > n) {
                split_long_word(str, &slovo_start, slovo_len, n, &cur_line_len, &first_word);
            } else {
                print_slovo(str, slovo_start, slovo_start + slovo_len);
                cur_line_len = slovo_len;
                first_word = 0;
            }
        } else {
            if (cur_line_len + 1 + slovo_len <= n) {
                printf(" ");
                print_slovo(str, slovo_start, slovo_start + slovo_len);
                cur_line_len += 1 + slovo_len;
            } else if (slovo_len > n) {
                printf("\n");
                split_long_word(str, &slovo_start, slovo_len, n, &cur_line_len, &first_word);
            } else {
                printf("\n");
                print_slovo(str, slovo_start, slovo_start + slovo_len);
                cur_line_len = slovo_len;
            }
        }
    }
    if (cur_line_len > 0) {
        printf("\n");
    }
}

void split_long_word(char *str, int *slovo_start, int slovo_len, int n, int *cur_line_len, int *first_word) {
    int ost_len = slovo_len;
    while (ost_len > 0) {
        int piece_slovo;
        if (ost_len > n - 1)
            piece_slovo = n - 1;
        else
            piece_slovo = ost_len;
        print_slovo(str, *slovo_start, *slovo_start + piece_slovo);
        if (piece_slovo < ost_len) printf("-");
        printf("\n");
        *slovo_start += piece_slovo;
        ost_len -= piece_slovo;
    }
    *cur_line_len = 0;
    *first_word = 1;
}
