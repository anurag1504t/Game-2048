#include<bits/stdc++.h>
using namespace std;

int const BOARD_SIZE = 4;

class Game {
    int score;
    int board[BOARD_SIZE][BOARD_SIZE];

    // Member Functions
    int get_score();
    bool is_full();
    bool has_won();
    bool is_game_over();
    void print_board();
    void move_left();
    void move_right();
    void move_up();
    void move_down();
    void add_tile();
public:
    Game() {
        score = 0;
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                board[i][j] = 0;
            }
        }
        add_tile();
        add_tile();
    }

    void play() {
        while (!is_game_over()) {
            print_board();
            char move;
            cout << "Enter move (L, R, U, D): ";
            cin >> move;
            switch (move) {
            case 'L':
            case 'l':
                move_left();
                break;
            case 'R':
            case 'r':
                move_right();
                break;
            case 'U':
            case 'u':
                move_up();
                break;
            case 'D':
            case 'd':
                move_down();
                break;
            case 'Q':
            case 'q':
                print_board();
                exit(0);
                break;
            default:
                cout << "Invalid move! Please enter L, R, U, or D." << endl;
                break;
            }
        }
        
        if (has_won()) {
            cout << "Congratulations, you won with a score of " << score << "!" << endl;
        } else {
            cout << "Game over with a score of " << score << "." << endl;
        }
    }
};

void Game::add_tile() {
    if (is_full()) {
        return;
    }
    int i, j;
    do {
        i = rand() % BOARD_SIZE;
        j = rand() % BOARD_SIZE;
    } while (board[i][j] != 0);
    board[i][j] = (rand() % 10 == 0) ? 4 : 2;
}

void Game::print_board() {
    cout << "\nScore: " << score << endl;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            cout << board[i][j] << "\t";
        }
        cout << endl;
    }
}

bool Game::is_full() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == 0) {
                return false;
            }
        }
    }
    return true;
}

bool Game::has_won() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == 2048) {
                return true;
            }
        }
    }
    return false;
}

bool Game::is_game_over() {
    if (!is_full()) {
        return false;
    }

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (i > 0 && board[i][j] == board[i - 1][j]) {
                return false;
            }
            if (j > 0 && board[i][j] == board[i][j - 1]) {
                return false;
            }
        }
    }
    return true;
}

int Game::get_score() {
    return score;
}

void Game::move_left() {
    bool moved = false;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (!board[i][j]) {
                for (int k = j + 1; k < 4; k++) {
                    if (board[i][k]) {
                        board[i][j] = board[i][k];
                        board[i][k] = 0;
                        moved = true;
                        break;
                    }
                }
            }
        }
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] && board[i][j] == board[i][j + 1]) {
                board[i][j] = board[i][j] + board[i][j + 1];
                board[i][j + 1] = 0;
                score += board[i][j];
                moved = true;
            }
        }
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (!board[i][j]) {
                for (int k = j + 1; k < 4; k++) {
                    if (board[i][k]) {
                        board[i][j] = board[i][k];
                        board[i][k] = 0;
                        moved = true;
                        break;
                    }
                }
            }
        }
    }
    if (moved) {
        add_tile();
    }
}

void Game::move_right() {
    bool moved = false;

    for (int i = 0; i < 4; i++) {
        for (int j = 3; j >= 0; j--) {
            if (!board[i][j]) {
                for (int k = j - 1; k >= 0; k--) {
                    if (board[i][k]) {
                        board[i][j] = board[i][k];
                        board[i][k] = 0;
                        moved = true;
                        break;
                    }
                }
            }
        }
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 3; j > 0; j--) {
            if (board[i][j] && board[i][j] == board[i][j - 1]) {
                board[i][j] = board[i][j] + board[i][j - 1];
                board[i][j - 1] = 0;
                score = score + board[i][j];
                moved = true;
            }
        }
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 3; j >= 0; j--) {
            if (!board[i][j]) {
                for (int k = j - 1; k >= 0; k--) {
                    if (board[i][k]) {
                        board[i][j] = board[i][k];
                        board[i][k] = 0;
                        moved = true;
                        break;
                    }
                }
            }
        }
    }

    if (moved) {
        add_tile();
    }
}

void Game::move_up() {
    bool moved = false;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (!board[j][i]) {
                for (int k = j + 1; k < 4; k++) {
                    if (board[k][i]) {
                        board[j][i] = board[k][i];
                        board[k][i] = 0;
                        moved = true;
                        break;
                    }
                }
            }
        }
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[j][i] && board[j][i] == board[j + 1][i]) {
                board[j][i] = board[j][i] + board[j + 1][i];
                board[j + 1][i] = 0;
                score += board[j][i];
                moved = true;
            }
        }
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (!board[j][i]) {
                for (int k = j + 1; k < 4; k++) {
                    if (board[k][i]) {
                        board[j][i] = board[k][i];
                        board[k][i] = 0;
                        moved = true;
                        break;
                    }
                }
            }
        }
    }

    if (moved) {
        add_tile();
    }
}

void Game::move_down() {
    bool moved = false;
    for (int i = 0; i < 4; i++) {
        for (int j = 3; j >= 0; j--) {
            if (!board[j][i]) {
                for (int k = j - 1; k >= 0; k--) {
                    if (board[k][i]) {
                        board[j][i] = board[k][i];
                        board[k][i] = 0;
                        moved = true;
                        break;
                    }
                }
            }
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 3; j > 0; j--) {
            if (board[j][i] && board[j][i] == board[j - 1][i]) {
                board[j][i] = board[j][i] + board[j - 1][i];
                board[j - 1][i] = 0;
                score += board[j][i];
                moved = true;
            }
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 3; j >= 0; j--) {
            if (!board[j][i]) {
                for (int k = j - 1; k >= 0; k--) {
                    if (board[k][i]) {
                        board[j][i] = board[k][i];
                        board[k][i] = 0;
                        moved = true;
                        break;
                    }
                }
            }
        }
    }
    if (moved) {
        add_tile();
    }
}

int main() {
    srand(time(NULL));
    cout << "Game 2048!" << endl;
    cout << "Use the arrow keys to move the tiles." << endl;
    cout << "Press Q to quit." << endl;
    Game game;
    game.play();
    return 0;
}