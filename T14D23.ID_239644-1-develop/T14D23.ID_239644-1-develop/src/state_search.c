#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "door_state.h"

int read_line(char **expr);
int input_date(int *year, int *month, int *day);
int search_in_file(FILE *file);
door_state read_record_from_file(FILE *pfile, int index);
int get_file_size_in_bytes(FILE *pfile);
int get_records_count_in_file(FILE *pfile);

int main() {
    int flag = 1;
    char *filename = NULL;
    if (read_line(&filename) == 0) flag = 0;
    if (flag) {
        FILE *file;
        char path[4096];
        snprintf(path, sizeof(path), "../%s", filename);
        file = fopen(path, "rb");
        if (!file)
            flag = 0;
        else {
            if (get_file_size_in_bytes(file) == 0) flag = 0;
            flag = flag && search_in_file(file);
            fclose(file);
        }
    }
    if (!flag) printf("n/a");
    free(filename);
    return 0;
}

int read_line(char **expr) {
    int flag = 1;
    char ch;
    int len = 0;
    while (flag == 1) {
        scanf("%c", &ch);
        *expr = realloc(*expr, (len + 1) * sizeof(char));
        if (!*expr)
            flag = 0;
        else {
            (*expr)[len] = ch;
            if (ch == '\n') {
                (*expr)[len] = '\0';
                flag = -1;
            }
            len++;
        }
    }
    return flag;
}

int input_date(int *year, int *month, int *day) {
    int flag = 1;
    if (scanf("%d.%d.%d", day, month, year) != 3 || *year < 0 || *month <= 0 || *month >= 13 || *day <= 0 ||
        *day >= 32)
        flag = 0;
    return flag;
}

int search_in_file(FILE *file) {
    int year, month, day;
    int flag = 1;
    flag = input_date(&year, &month, &day);
    if (flag) {
        int number_records = get_records_count_in_file(file);
        int stop = 1;
        for (int i = 0; stop && i < number_records; i++) {
            door_state record = read_record_from_file(file, i);
            if (record.year == year && record.month == month && record.day == day) {
                stop = 0;
                printf("%d", record.code);
            }
        }
        if (stop) flag = 0;
    }
    return flag;
}

door_state read_record_from_file(FILE *pfile, int index) {
    int offset = index * sizeof(door_state);
    fseek(pfile, offset, SEEK_SET);
    door_state record;
    fread(&record, sizeof(door_state), 1, pfile);
    rewind(pfile);
    return record;
}

int get_file_size_in_bytes(FILE *pfile) {
    int size = 0;
    fseek(pfile, 0, SEEK_END);
    size = ftell(pfile);
    rewind(pfile);
    return size;
}

int get_records_count_in_file(FILE *pfile) { return get_file_size_in_bytes(pfile) / sizeof(door_state); }
