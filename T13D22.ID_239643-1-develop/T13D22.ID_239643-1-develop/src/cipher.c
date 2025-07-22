#include <dirent.h>
#include <openssl/des.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int read_line(char **expr);
int read_from_file(char **filename, int is_after_write);
int write_in_file(char *filename);
int pass_in_dir_caesar(int shift);
void caesar_shyfr(long file_size, char *filetext, int shift);
int pass_in_dir_des();
void des_encrypt(long file_size, unsigned char *filetext, unsigned char **ciphertext);

int main() {
    int stop = 1;
    int flag = 1;
    char *filename = NULL;
    int after_write;
    while (stop) {
        int act;
        if (scanf("%d", &act) == 1 && getchar() == '\n') {
            if (flag && act == 1) {
                after_write = 0;
                flag = read_from_file(&filename, after_write);
            } else if (flag && act == 2) {
                flag = write_in_file(filename);
                after_write = 1;
                read_from_file(&filename, after_write);
            } else if (flag && act == 3) {
                int shift;
                if (scanf("%d", &shift) == 1 && getchar() == '\n') {
                    flag = pass_in_dir_caesar(shift);
                } else {
                    flag = 0;
                    while (getchar() != '\n');
                }
            } else if (flag && act == 4) {
                flag = pass_in_dir_des();
            } else if (flag && act == -1)
                stop = 0;
            else
                flag = 0;
        } else {
            flag = 0;
            while (getchar() != '\n');
        }
        if (!flag) {
            printf("n/a\n");
            flag = 1;
        } else if (stop)
            printf("\n");
    }
    free(filename);
    return 0;
}

int read_from_file(char **filename, int is_after_write) {
    int flag = 1;
    FILE *file;
    char *filetext = NULL;
    if (is_after_write == 0) {
        if (read_line(filename) == 0) flag = 0;
    }
    if (flag) {
        file = fopen(*filename, "r");
        if (!file) flag = 0;
    }
    if (flag) {
        fseek(file, 0, SEEK_END);
        long file_size = ftell(file);
        rewind(file);
        filetext = (char *)malloc(file_size + 1);
        if (!filetext)
            flag = 0;
        else {
            fread(filetext, 1, file_size, file);
            filetext[file_size] = '\0';
            if (filetext[0] == '\0')
                flag = 0;
            else
                printf("%s", filetext);
        }
        fclose(file);
    }
    free(filetext);
    return flag;
}

int write_in_file(char *filename) {
    int flag = 1;
    FILE *file;
    char *filetext = NULL;
    if (read_line(&filetext) == 0) flag = 0;
    if (flag) {
        file = fopen(filename, "r+");
        if (!file) flag = 0;
    }
    if (flag) {
        fseek(file, 0, SEEK_END);
        fprintf(file, "%s", filetext);
        fclose(file);
    }
    free(filetext);
    return flag;
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

int pass_in_dir_caesar(int shift) {
    DIR *dir;
    struct dirent *entry;
    char *dir_path = "ai_modules";
    int flag = 1;
    FILE *file;
    dir = opendir(dir_path);
    if (!dir) {
        flag = 0;
    }

    while (flag && (entry = readdir(dir)) != NULL) {
        char *filename = entry->d_name;
        char filepath[4096];
        snprintf(filepath, sizeof(filepath), "%s/%s", dir_path, filename);
        int len = strlen(filepath);
        if (filepath[len - 2] == '.' && filepath[len - 1] == 'c') {
            file = fopen(filepath, "r");
            if (file) {
                fseek(file, 0, SEEK_END);
                long file_size = ftell(file);
                rewind(file);
                char *filetext = (char *)malloc(file_size + 1);
                if (filetext) {
                    fread(filetext, 1, file_size, file);
                    filetext[file_size] = '\0';
                } else
                    flag = 0;
                fclose(file);
                if (flag) {
                    caesar_shyfr(file_size, filetext, shift);
                    file = fopen(filepath, "w");
                    fprintf(file, "%s", filetext);
                    free(filetext);
                    fclose(file);
                }
            } else {
                flag = 0;
            }
        } else if (filepath[len - 2] == '.' && filepath[len - 1] == 'h') {
            file = fopen(filepath, "w");
            if (file) {
                fclose(file);
            } else {
                flag = 0;
            }
        }
    }

    closedir(dir);
    return flag;
}

void caesar_shyfr(long file_size, char *filetext, int shift) {
    for (long i = 0; i < file_size; i++) {
        if (filetext[i] >= 'a' && filetext[i] <= 'z') {
            filetext[i] = 'a' + (filetext[i] - 'a' + shift) % 26;
        } else if (filetext[i] >= 'A' && filetext[i] <= 'Z') {
            filetext[i] = 'A' + (filetext[i] - 'A' + shift) % 26;
        }
    }
}

int pass_in_dir_des() {
    DIR *dir;
    struct dirent *entry;
    char *dir_path = "ai_modules";
    int flag = 1;
    FILE *file;
    dir = opendir(dir_path);
    if (!dir) {
        flag = 0;
    }

    while (flag && (entry = readdir(dir)) != NULL) {
        char *filename = entry->d_name;
        char filepath[4096];
        snprintf(filepath, sizeof(filepath), "%s/%s", dir_path, filename);
        int len = strlen(filepath);
        if (filepath[len - 2] == '.' && filepath[len - 1] == 'c') {
            file = fopen(filepath, "rb");
            if (file) {
                fseek(file, 0, SEEK_END);
                long file_size = ftell(file);
                rewind(file);
                unsigned char *filetext = malloc(file_size + 1 * sizeof(unsigned char));
                unsigned char *ciphertext = malloc(file_size + 1 * sizeof(unsigned char));
                if (filetext && ciphertext) {
                    fread(filetext, 1, file_size, file);
                    filetext[file_size] = '\0';
                } else
                    flag = 0;
                fclose(file);
                if (flag) {
                    des_encrypt(file_size, filetext, &ciphertext);
                    file = fopen(filepath, "wb");
                    fprintf(file, "%s", ciphertext);
                    free(filetext);
                    free(ciphertext);
                    fclose(file);
                }
            } else {
                flag = 0;
            }
        } else if (filepath[len - 2] == '.' && filepath[len - 1] == 'h') {
            file = fopen(filepath, "w");
            if (file) {
                fclose(file);
            } else {
                flag = 0;
            }
        }
    }

    closedir(dir);
    return flag;
}

void des_encrypt(long file_size, unsigned char *filetext, unsigned char **ciphertext) {
    DES_cblock key = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
    DES_key_schedule ks;
    DES_set_key_unchecked(&key, &ks);

    DES_cblock ivec = {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0};

    DES_ncbc_encrypt(filetext, *ciphertext, file_size, &ks, &ivec, DES_ENCRYPT);
}
