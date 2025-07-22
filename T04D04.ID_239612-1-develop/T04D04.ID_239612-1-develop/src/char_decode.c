#include <stdio.h>

void encode();
void decode();

int main(int argc, char **argv) {
    if (argc == 2 && (argv[1][0] == '1' || argv[1][0] == '0') && argv[1][1] == '\0') {
        if (argv[1][0] == '0')
            encode();
        else
            decode();
    } else {
        printf("n/a");
    }
    return 0;
}

void encode() {
    char ch1, ch2;
    int stop = 0;
    while (stop == 0) {
        scanf("%c%c", &ch1, &ch2);
        if (ch2 == ' ')
            printf("%02X ", ch1);
        else if (ch2 == '\n') {
            printf("%02X", ch1);
            stop = 1;
        } else {
            printf("\rn/a");
            stop = 1;
        }
    }
}

void decode() {
    int x;
    char ch;
    int stop = 0;
    while (stop == 0) {
        scanf("%02X%c", &x, &ch);
        if (ch == ' ')
            printf("%c ", (char)x);
        else if (ch == '\n') {
            printf("%c", (char)x);
            stop = 1;
        } else {
            printf("\rn/a");
            stop = 1;
        }
    }
}
