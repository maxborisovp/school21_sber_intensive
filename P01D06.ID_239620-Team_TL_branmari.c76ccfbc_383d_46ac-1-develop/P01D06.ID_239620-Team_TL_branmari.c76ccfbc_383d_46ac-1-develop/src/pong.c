#include <stdio.h>

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

    print_pong_game(ball_x, ball_y, mv_ball_x, mv_ball_y, toe_left_center_y, toe_right_center_y,
                    score_player1, score_player2);

    return 0;
}

void move_toe_center(int ball_x, int ball_y, int mv_ball_x, int mv_ball_y, int toe_left_center_y,
                     int toe_right_center_y, int score_player1, int score_player2) {
    char action;
    scanf("%c", &action);
    int stop = 0;

    if (action == 'a') {
        if (toe_left_center_y < height - 3) toe_left_center_y = toe_left_center_y + 1;
    } else if (action == 'k') {
        if (toe_right_center_y < height - 3) toe_right_center_y = toe_right_center_y + 1;
    } else if (action == 'z') {
        if (toe_left_center_y > 2) toe_left_center_y = toe_left_center_y - 1;
    } else if (action == 'm') {
        if (toe_right_center_y > 2) toe_right_center_y = toe_right_center_y - 1;
    } else if (action == ' ') {
    } else
        stop = 1;
    if (stop == 1)
        print_pong_game(ball_x, ball_y, mv_ball_x, mv_ball_y, toe_left_center_y, toe_right_center_y,
                        score_player1, score_player2);
    else
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
    printf("\033[H\033[J");
    for (int y = height - 1; y >= 0; y--) {
        for (int x = 0; x < width; x++) {
            if (y == 0 || y == height - 1)
                printf("-");

            else if ((x == 0 &&
                      (y == toe_left_center_y || y == toe_left_center_y + 1 || y == toe_left_center_y - 1)) ||
                     (x == width - 1 && (y == toe_right_center_y || y == toe_right_center_y + 1 ||
                                         y == toe_right_center_y - 1)))
                printf("|");
            else if (x == ball_x && y == ball_y)
                printf("*");
            else if (x == width / 2)
                printf("|");
            else
                printf(" ");
        }
        printf("\n");
    }
    printf("Player1     %d : %d    Player2\n", score_player1, score_player2);
    if (score_player1 == 21 || score_player2 == 21) {
        printf("\033[H\033[J");
        if (score_player1 == 21)
            printf("Game end!!! Player1 win!!!\n");
        else
            printf("Game end!!! Player2 win!!!\n");
    } else
        move_toe_center(ball_x, ball_y, mv_ball_x, mv_ball_y, toe_left_center_y, toe_right_center_y,
                        score_player1, score_player2);
}
