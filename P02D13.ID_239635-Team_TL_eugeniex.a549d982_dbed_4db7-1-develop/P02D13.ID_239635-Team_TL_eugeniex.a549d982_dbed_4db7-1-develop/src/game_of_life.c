#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void initial_colors();
int input_stdin(int **matrix, int m, int n);
void free_matrix(int **matrix, int m);
void play_game(int **matrix, int m, int n);
void change_matrix(int **matrix, int m, int n);
int number_sosedi(int **matrix, int m, int n, int x, int y);
void draw_matrix(int **matrix, int m, int n);

int main() {
    int **matrix = NULL;
    int n = 80, m = 25;
    int flag = 1;
    matrix = malloc(m * sizeof(int *));
    for (int i = 0; i < m; i++) matrix[i] = malloc(n * sizeof(int));
    if (isatty(fileno(stdin))) {
        free_matrix(matrix, m);
        flag = 0;
    } else {
        if (input_stdin(matrix, m, n) == 0) {
            free_matrix(matrix, m);
            flag = 0;
        }
    }
    if (flag) {
        initscr();
        start_color();
        initial_colors();
        noecho();
        cbreak();
        nodelay(stdscr, TRUE);
        play_game(matrix, m, n);
        endwin();
        free_matrix(matrix, m);
    } else
        printf("n/a");
    return 0;
}

void initial_colors() {
    curs_set(0);
    init_pair(7, COLOR_GREEN, COLOR_WHITE);
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_CYAN, COLOR_BLACK);
    init_pair(5, COLOR_BLUE, COLOR_BLACK);
    init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
    attron(COLOR_PAIR(1));
}

int input_stdin(int **matrix, int m, int n) {
    int stop = 1;
    for (int i = 0; i < m && stop; i++) {
        for (int j = 0; j < n && stop; j++) {
            if (scanf("%d", &matrix[i][j]) != 1 || (matrix[i][j] != 1 && matrix[i][j] != 0)) {
                stop = 0;
            }
        }
    }
    stdin = freopen("/dev/tty", "r", stdin);
    return stop;
}

void free_matrix(int **matrix, int m) {
    for (int i = 0; i < m; i++) free(matrix[i]);
    free(matrix);
}

int number_sosedi(int **matrix, int m, int n, int x, int y) {
    int sum = 0;

    for (int i = x - 1; i <= x + 1; i++) {
        for (int j = y - 1; j <= y + 1; j++) {
            if (i != x || j != y) {
                sum = sum + matrix[(i + m) % m][(j + n) % n];
            }
        }
    }
    return sum;
}

void change_matrix(int **matrix, int m, int n) {
    int **matrix_pred = malloc(m * sizeof(int *));

    for (int i = 0; i < m; i++) matrix_pred[i] = malloc(n * sizeof(int));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            matrix_pred[i][j] = matrix[i][j];
        }
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int number = number_sosedi(matrix_pred, m, n, i, j);
            if (matrix_pred[i][j] == 0 && number == 3) {
                matrix[i][j] = 1;
            }
            if (matrix_pred[i][j] == 1 && (number < 2 || number > 3)) {
                matrix[i][j] = 0;
            }
        }
    }

    free_matrix(matrix_pred, m);
}

void play_game(int **matrix, int m, int n) {
    int flag = 1;
    int speed = 50000;
    while (flag) {
        char action = getch();
        switch (action) {
            case ' ':
                flag = 0;
                break;
            case 'a':
                if (speed > 10000) speed -= 5000;
                break;
            case 'z':
                if (speed < 500000) speed += 5000;
                break;
        }
        change_matrix(matrix, m, n);
        draw_matrix(matrix, m, n);
        usleep(speed);
    }
}

void draw_matrix(int **matrix, int m, int n) {
    erase();
    bkgd(COLOR_PAIR(7));
    for (int y = 0; y < m; y++) {
        for (int x = 0; x < n; x++) {
            attrset(COLOR_PAIR((x % 6) + 1) | A_BOLD);
            printw("%s", matrix[y][x] ? "*" : " ");
        }
        printw("\n");
    }
    refresh();
}
