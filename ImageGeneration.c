#include <stdio.h>
#include <string.h>

#define N 4

int utility(char *board) {
    int count = 0;
    for (int i = 0; i < N; i++) {
        if (board[i] == 'B') {
            count++;
        }
    }
    return count;
}

int is_terminal(char *board) {
    for (int i = 0; i < N; i++) {
        if (board[i] == '0') {
            return 0; // Game not in terminal state
        }
    }
    return 1; // Game in terminal state
}

int max_value(char *board);

int min_value(char *board, int action) {
    char new_board[N];
    memcpy(new_board, board, N);

    new_board[action] = 'W'; // Player 2 (MIN) places a white coin

    // Flip adjacent coins
    if (action > 0 && new_board[action - 1] == 'B') {
        new_board[action - 1] = 'W';
    }
    if (action < N - 1 && new_board[action + 1] == 'B') {
        new_board[action + 1] = 'W';
    }

    if (is_terminal(new_board)) {
        return utility(new_board);
    }

    int min_val = N + 1;

    for (int i = 0; i < N; i++) {
        if (new_board[i] == '0') {
            int max_val = max_value(new_board);
            if (max_val < min_val) {
                min_val = max_val;
            }
        }
    }

    return min_val;
}

int max_value(char *board) {
    char new_board[N];
    memcpy(new_board, board, N);

    int max_val = -1;

    for (int i = 0; i < N; i++) {
        if (new_board[i] == '0') {
            new_board[i] = 'B'; // Player 1 (MAX) places a black coin

            // Flip adjacent coins
            if (i > 0 && new_board[i - 1] == 'W') {
                new_board[i - 1] = 'B';
            }
            if (i < N - 1 && new_board[i + 1] == 'W') {
                new_board[i + 1] = 'B';
            }

            if (is_terminal(new_board)) {
                int utility_val = utility(new_board);
                if (utility_val > max_val) {
                    max_val = utility_val;
                }
            } else {
                for (int j = 0; j < N; j++) {
                    if (new_board[j] == '0') {
                        int min_val = min_value(new_board, j);
                        if (min_val > max_val) {
                            max_val = min_val;
                        }
                    }
                }
            }
        }
    }

    return max_val;
}

int main() {
    char board[] = "0000W00BBW0";
    int max_utility = max_value(board);
    printf("Utility of Player 1 (MAX): %d\n", max_utility);

    return 0;
}