#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "door_state.h"
int read_line(char **expr);
void read_from_file(FILE *file);
int write_in_file(FILE *file);
void sort_file(FILE *file);
door_state read_record_from_file(FILE *pfile, int index);
void write_record_in_file(FILE *pfile, const door_state *record_to_write, int index);
void swap_records_in_file(FILE *pfile, int record_index1, int record_index2);
int get_file_size_in_bytes(FILE *pfile);
int get_records_count_in_file(FILE *pfile);
int compare(const door_state record1, const door_state record2);

int main() {
    int flag = 1;
    char *filename = NULL;
    if (read_line(&filename) == 0) flag = 0;
    FILE *file;
    if (flag) {
        char path[4096];
        snprintf(path, sizeof(path), "../%s", filename);
        file = fopen(path, "rb+");
        if (!file) flag = 0;
    }
    if (flag) {
        int act;
        if (scanf("%d", &act) == 1) {
            while (getchar() != '\n') {
            }
            if (get_file_size_in_bytes(file) == 0 && act != 2) flag = 0;
            if (flag && act == 0) {
                read_from_file(file);
            } else if (flag && act == 1) {
                sort_file(file);
                read_from_file(file);
            } else if (flag && act == 2) {
                flag = write_in_file(file);
                if (flag) {
                    sort_file(file);
                    read_from_file(file);
                }
            } else {
                flag = 0;
            }
        } else
            flag = 0;
        fclose(file);
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

void read_from_file(FILE *file) {
    int number_records = get_records_count_in_file(file);
    for (int i = 0; i < number_records; i++) {
        door_state record = read_record_from_file(file, i);
        printf("%d %d %d %d %d %d %d %d", record.year, record.month, record.day, record.hour, record.minute,
               record.second, record.status, record.code);
        if (i != number_records - 1) printf("\n");
    }
}

int write_in_file(FILE *file) {
    int flag = 1;
    int number_records = get_records_count_in_file(file);
    door_state record;
    if (scanf("%d %d %d %d %d %d %d %d", &record.year, &record.month, &record.day, &record.hour,
              &record.minute, &record.second, &record.status, &record.code) == 8 &&
        record.month > 0 && record.month < 13 && record.day > 0 && record.day < 32 && record.hour >= 0 &&
        record.hour < 24 && record.minute >= 0 && record.minute < 60 && record.second >= 0 &&
        record.second < 60 && (record.status == 0 || record.status == 1)) {
        write_record_in_file(file, &record, number_records);
    } else
        flag = 0;
    return flag;
}

void sort_file(FILE *file) {
    int number_records = get_records_count_in_file(file);
    door_state record1, record2;
    for (int i = 0; i < number_records; i++) {
        for (int j = 0; j < number_records - 1; j++) {
            record1 = read_record_from_file(file, j);
            record2 = read_record_from_file(file, j + 1);
            if (compare(record1, record2) > 0) {
                swap_records_in_file(file, j, j + 1);
            }
        }
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

void swap_records_in_file(FILE *pfile, int record_index1, int record_index2) {
    door_state record1 = read_record_from_file(pfile, record_index1);
    door_state record2 = read_record_from_file(pfile, record_index2);

    write_record_in_file(pfile, &record1, record_index2);
    write_record_in_file(pfile, &record2, record_index1);
}

int get_file_size_in_bytes(FILE *pfile) {
    int size = 0;
    fseek(pfile, 0, SEEK_END);
    size = ftell(pfile);
    rewind(pfile);
    return size;
}

int get_records_count_in_file(FILE *pfile) { return get_file_size_in_bytes(pfile) / sizeof(door_state); }

int compare(const door_state record1, const door_state record2) {
    int res = 0;
    res = record1.year - record2.year;
    if (res == 0) res = record1.month - record2.month;
    if (res == 0) res = record1.day - record2.day;
    if (res == 0) res = record1.hour - record2.hour;
    if (res == 0) res = record1.minute - record2.minute;
    if (res == 0) res = record1.second - record2.second;
    return res;
}
