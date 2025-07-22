#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>

#define height 25
#define width 80

void move_toe_center(int ball_x, int ball_y, int mv_ball_x, int mv_ball_y, int toe_left_center_y,
                     int toe_right_center_y, int score_player1, int score_player2);
void move_ball(int ball_x, int ball_y, int mv_ball_x, int mv_ball_y, int toe_left_center_y,
               int toe_right_center_y, int score_player1, int score_player2);
void print_pong_game(int ball_x, int ball_y, int mv_ball_x, int mv_ball_y, int toe_left_center_y,
                     int toe_right_center_y, int score_player1, int score_player2);

int main() {
    int ball_x = width / 2;
    int ball_y = height / 2 + 1;
    int toe_left_center_y = height / 2 + 1;
    int toe_right_center_y = height / 2 + 1;
    int mv_ball_x = 1;
    int mv_ball_y = 1;
    int score_player1 = 0;
    int score_player2 = 0;

    initscr();
    noecho();
    cbreak();
    nodelay(stdscr, TRUE);

    print_pong_game(ball_x, ball_y, mv_ball_x, mv_ball_y, toe_left_center_y, toe_right_center_y,
                    score_player1, score_player2);

    endwin();
    return 0;
}

void move_toe_center(int ball_x, int ball_y, int mv_ball_x, int mv_ball_y, int toe_left_center_y,
                     int toe_right_center_y, int score_player1, int score_player2) {
    char action = getch();
    if (action == 'a' && toe_left_center_y < height - 3) toe_left_center_y = toe_left_center_y + 1;
    if (action == 'k' && toe_right_center_y < height - 3) toe_right_center_y = toe_right_center_y + 1;
    if (action == 'z' && toe_left_center_y > 2) toe_left_center_y = toe_left_center_y - 1;
    if (action == 'm' && toe_right_center_y > 2) toe_right_center_y = toe_right_center_y - 1;

    move_ball(ball_x, ball_y, mv_ball_x, mv_ball_y, toe_left_center_y, toe_right_center_y, score_player1,
              score_player2);
}

void move_ball(int ball_x, int ball_y, int mv_ball_x, int mv_ball_y, int toe_left_center_y,
               int toe_right_center_y, int score_player1, int score_player2) {
    if (ball_x == 1) {
        if (ball_y == toe_left_center_y || ball_y == toe_left_center_y - 1 ||
            ball_y == toe_left_center_y + 1) {
            mv_ball_x = -mv_ball_x;
        } else {
            score_player2 = score_player2 + 1;
            ball_x = width / 2;
            ball_y = height / 2 + 1;
        }
    }

    if (ball_x == width - 2) {
        if (ball_y == toe_right_center_y || ball_y == toe_right_center_y - 1 ||
            ball_y == toe_right_center_y + 1) {
            mv_ball_x = -mv_ball_x;
        } else {
            score_player1 = score_player1 + 1;
            ball_x = width / 2;
            ball_y = height / 2 + 1;
        }
    }

    if (ball_y == 1 || ball_y == height - 2) {
        mv_ball_y = -mv_ball_y;
    }

    ball_x = ball_x + mv_ball_x;
    ball_y = ball_y + mv_ball_y;

    print_pong_game(ball_x, ball_y, mv_ball_x, mv_ball_y, toe_left_center_y, toe_right_center_y,
                    score_player1, score_player2);
}

void print_pong_game(int ball_x, int ball_y, int mv_ball_x, int mv_ball_y, int toe_left_center_y,
                     int toe_right_center_y, int score_player1, int score_player2) {
    clear();
    for (int y = height - 1; y >= 0; y--) {
        for (int x = 0; x < width; x++) {
            if (y == 0 || y == height - 1)
                printw("-");
            else if ((x == 0 &&
                      (y == toe_left_center_y || y == toe_left_center_y + 1 || y == toe_left_center_y - 1)) ||
                     (x == width - 1 && (y == toe_right_center_y || y == toe_right_center_y + 1 ||
                                         y == toe_right_center_y - 1)))
                printw("|");
            else if (x == ball_x && y == ball_y)
                printw("*");
            else if (x == width / 2)
                printw("|");
            else
                printw(" ");
        }
        printw("\n");
    }
    printw("Player1     %d : %d    Player2\n", score_player1, score_player2);
    refresh();
    usleep(80000);
    if (score_player1 == 21 || score_player2 == 21) {
        clear();
        if (score_player1 == 21)
            printw("Game end!!! Player1 win!!!\n");
        else
            printw("Game end!!! Player2 win!!!\n");
        refresh();
        sleep(10);
    } else
        move_toe_center(ball_x, ball_y, mv_ball_x, mv_ball_y, toe_left_center_y, toe_right_center_y,
                        score_player1, score_player2);
}
