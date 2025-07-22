#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "door_state.h"

int read_line(char **expr);
int input_dates(int *year1, int *month1, int *day1, int *year2, int *month2, int *day2);
int delete_from_file(const char *path);
void read_from_file(FILE *file);
door_state read_record_from_file(FILE *pfile, int index);
void write_record_in_file(FILE *pfile, const door_state *record_to_write, int index);
int get_file_size_in_bytes(FILE *pfile);
int get_records_count_in_file(FILE *pfile);
int compare_day(const door_state record, int year, int month, int day);

int main() {
    int flag = 1;
    char *filename = NULL;
    if (read_line(&filename) == 0) flag = 0;
    if (flag) {
        char path[4096];
        snprintf(path, sizeof(path), "../%s", filename);
        flag = flag && delete_from_file(path);
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

int input_dates(int *year1, int *month1, int *day1, int *year2, int *month2, int *day2) {
    int flag = 1;
    if (scanf("%d.%d.%d %d.%d.%d", day1, month1, year1, day2, month2, year2) != 6 || *year1 < 0 ||
        *month1 <= 0 || *month1 >= 13 || *day1 <= 0 || *day1 >= 32 || *year2 < 0 || *month2 <= 0 ||
        *month2 >= 13 || *day2 <= 0 || *day2 >= 32)
        flag = 0;
    return flag;
}

int delete_from_file(const char *path) {
    int flag = 1;
    FILE *file = fopen(path, "rb");
    if (!file)
        flag = 0;
    else {
        if (get_file_size_in_bytes(file) == 0) flag = 0;
    }
    int year1, month1, day1, year2, month2, day2;
    flag = flag && input_dates(&year1, &month1, &day1, &year2, &month2, &day2);
    FILE *tmp;
    if (flag) {
        tmp = tmpfile();
        if (!tmp) flag = 0;
    }
    if (flag) {
        int number_records = get_records_count_in_file(file);
        int k = 0;
        for (int i = 0; i < number_records; i++) {
            door_state record = read_record_from_file(file, i);
            if (compare_day(record, year1, month1, day1) < 0 ||
                compare_day(record, year2, month2, day2) > 0) {
                write_record_in_file(tmp, &record, k);
                k++;
            }
        }
        fclose(file);
        file = fopen(path, "wb+");
        if (!file) flag = 0;
    }
    if (flag) {
        int number_records = get_records_count_in_file(tmp);
        for (int i = 0; i < number_records; i++) {
            door_state record = read_record_from_file(tmp, i);
            write_record_in_file(file, &record, i);
        }
        read_from_file(file);
        fclose(tmp);
        fclose(file);
    }
    return flag;
}

void read_from_file(FILE *file) {
    int number_records = get_records_count_in_file(file);
    for (int i = 0; i < number_records; i++) {
        door_state record = read_record_from_file(file, i);
        printf("%d %d %d %d %d %d %d %d", record.year, record.month, record.day, record.hour, record.minute,
               record.second, record.status, record.code);
        if (i != number_records - 1) printf("\n");
    }
}

door_state read_record_from_file(FILE *pfile, int index) {
    int offset = index * sizeof(door_state);
    fseek(pfile, offset, SEEK_SET);
    door_state record;
    fread(&record, sizeof(door_state), 1, pfile);
    rewind(pfile);
    return record;
}

void write_record_in_file(FILE *pfile, const door_state *record_to_write, int index) {
    int offset = index * sizeof(door_state);
    fseek(pfile, offset, SEEK_SET);
    fwrite(record_to_write, sizeof(door_state), 1, pfile);
    fflush(pfile);
    rewind(pfile);
}

int get_file_size_in_bytes(FILE *pfile) {
    int size = 0;
    fseek(pfile, 0, SEEK_END);
    size = ftell(pfile);
    rewind(pfile);
    return size;
}

int get_records_count_in_file(FILE *pfile) { return get_file_size_in_bytes(pfile) / sizeof(door_state); }

int compare_day(const door_state record, int year, int month, int day) {
    int res = 0;
    res = record.year - year;
    if (res == 0) res = record.month - month;
    if (res == 0) res = record.day - day;
    return res;
}
