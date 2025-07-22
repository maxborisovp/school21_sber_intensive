#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parsing.h"
#include "polish_notation.h"
#include "token.h"

#define WIDTH 80
#define HEIGHT 25
#define x_min 0.0
#define x_max (4.0 * M_PI)
#define y_min -1.0
#define y_max 1.0

int read_line(char **expr);
int input_pole(char pole[HEIGHT][WIDTH], tokens_massive *postfix);
void draw_graph(char pole[HEIGHT][WIDTH]);

int main() {
    int flag = 1;
    char *expr = NULL;
    if (read_line(&expr) == 0 || expr[0] == '\0') {
        flag = 0;
    }
    tokens_massive tokens;
    if (flag) {
        if (!parsing(expr, &tokens)) {
            tokens_massive_destroy(&tokens);
            flag = 0;
        }
    }
    tokens_massive postfix;
    if (flag) {
        if (!to_postfix(&tokens, &postfix)) {
            tokens_massive_destroy(&tokens);
            tokens_massive_destroy(&postfix);
            flag = 0;
        }
    }
    char pole[HEIGHT][WIDTH];
    if (flag) {
        if (!input_pole(pole, &postfix)) {
            tokens_massive_destroy(&tokens);
            tokens_massive_destroy(&postfix);
            flag = 0;
        }
    }
    if (flag) {
        draw_graph(pole);
        tokens_massive_destroy(&tokens);
        tokens_massive_destroy(&postfix);
    } else
        printf("n/a");
    free(expr);
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

int input_pole(char pole[HEIGHT][WIDTH], tokens_massive *postfix) {
    int flag = 1;
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            pole[i][j] = '.';
        }
    }
    double step_x = (x_max - x_min) / (WIDTH - 1);
    for (int j = 0; flag && j < WIDTH; j++) {
        double xi = x_min + step_x * j;
        double yi;
        int stop = evaluate_postfix(postfix, xi, &yi);
        if (stop == 0) {
            flag = 0;
        } else if (stop == 1) {
            double normalized = (y_max - yi) / (y_max - y_min);  // 0..1
            double pos = normalized * (HEIGHT - 1);

            int i = (int)round(pos);
            if (i < 0) i = 0;
            if (i >= HEIGHT) i = HEIGHT - 1;

            pole[i][j] = '*';
        }
    }
    return flag;
}

void draw_graph(char pole[HEIGHT][WIDTH]) {
    for (int i = HEIGHT - 1; i >= 0; i--) {
        for (int j = 0; j < WIDTH; j++) {
            printf("%c", pole[i][j]);
        }
        printf("\n");
    }
}
