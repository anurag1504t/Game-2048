#include<bits/stdc++.h>
using namespace std;

class Game {
    int score;
    int board_size;
    vector<vector<int>> board;

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
    void move_left_helper(bool&);
    void move_right_helper(bool&);
    void move_up_helper(bool&);
    void move_down_helper(bool&);
    void add_tile();
    void init_board();
public:
    Game(int board_size) {
        this->board_size = board_size;
        init_board();
    }

    Game() {
        this->board_size = 4;
        init_board();
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
                case 'X':
                case 'x':
                    init_board();
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

void Game::init_board() {
    score = 0;
    board.clear();
    for (int i = 0; i < board_size; i++) {
        vector<int> temp;
        for (int j = 0; j < board_size; j++) {
            temp.push_back(0);
        }
        board.push_back(temp);
    }
    add_tile();
    add_tile();
}

void Game::add_tile() {
    if (is_full()) {
        return;
    }
    int i, j;
    do {
        i = rand() % board_size;
        j = rand() % board_size;
    } while (board[i][j] != 0);
    board[i][j] = (rand() % 10 == 0) ? 4 : 2;
}

void Game::print_board() {
    cout << "\nScore: " << score << endl;
    for (int i = 0; i < board_size; i++) {
        for (int j = 0; j < board_size; j++) {
            cout << board[i][j] << "\t";
        }
        cout << endl;
    }
}

bool Game::is_full() {
    for (int i = 0; i < board_size; i++) {
        for (int j = 0; j < board_size; j++) {
            if (board[i][j] == 0) {
                return false;
            }
        }
    }
    return true;
}

bool Game::has_won() {
    for (int i = 0; i < board_size; i++) {
        for (int j = 0; j < board_size; j++) {
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

    for (int i = 0; i < board_size; i++) {
        for (int j = 0; j < board_size; j++) {
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
    move_left_helper(moved);

    for (int i = 0; i < board_size; i++) {
        for (int j = 0; j < board_size - 1; j++) {
            if (board[i][j] && board[i][j] == board[i][j + 1]) {
                board[i][j] = board[i][j] + board[i][j + 1];
                board[i][j + 1] = 0;
                score += board[i][j];
                moved = true;
            }
        }
    }

    move_left_helper(moved);
    if (moved) {
        add_tile();
    }
}

void Game::move_left_helper(bool &moved) {
    for (int i = 0; i < board_size; i++) {
        for (int j = 0; j < board_size; j++) {
            if (!board[i][j]) {
                for (int k = j + 1; k < board_size; k++) {
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
}

void Game::move_right() {
    bool moved = false;
    move_right_helper(moved);

    for (int i = 0; i < board_size; i++) {
        for (int j = board_size - 1; j > 0; j--) {
            if (board[i][j] && board[i][j] == board[i][j - 1]) {
                board[i][j] = board[i][j] + board[i][j - 1];
                board[i][j - 1] = 0;
                score = score + board[i][j];
                moved = true;
            }
        }
    }

    move_right_helper(moved);
    if (moved) {
        add_tile();
    }
}

void Game::move_right_helper(bool &moved) {
    for (int i = 0; i < board_size; i++) {
        for (int j = board_size - 1; j >= 0; j--) {
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
}

void Game::move_up() {
    bool moved = false;
    move_up_helper(moved);

    for (int i = 0; i < board_size; i++) {
        for (int j = 0; j < board_size - 1; j++) {
            if (board[j][i] && board[j][i] == board[j + 1][i]) {
                board[j][i] = board[j][i] + board[j + 1][i];
                board[j + 1][i] = 0;
                score += board[j][i];
                moved = true;
            }
        }
    }

    move_up_helper(moved);
    if (moved) {
        add_tile();
    }
}

void Game::move_up_helper(bool &moved) {
    for (int i = 0; i < board_size; i++) {
        for (int j = 0; j < board_size; j++) {
            if (!board[j][i]) {
                for (int k = j + 1; k < board_size; k++) {
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
}

void Game::move_down() {
    bool moved = false;
    move_down_helper(moved);
    
    for (int i = 0; i < board_size; i++) {
        for (int j = board_size - 1; j > 0; j--) {
            if (board[j][i] && board[j][i] == board[j - 1][i]) {
                board[j][i] = board[j][i] + board[j - 1][i];
                board[j - 1][i] = 0;
                score += board[j][i];
                moved = true;
            }
        }
    }
    
    move_down_helper(moved);
    if (moved) {
        add_tile();
    }
}

void Game::move_down_helper(bool &moved) {
    for (int i = 0; i < board_size; i++) {
        for (int j = board_size - 1; j >= 0; j--) {
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
}

int main() {
    srand(time(NULL));
    cout << "Game 2048!" << endl;
    cout << "Press Q to quit." << endl;
    cout << "Press X to restart game." << endl;
    cout << "Enter Dimension for board to Play: ";
    int board_size;
    cin >> board_size; 
    Game game(board_size);
    game.play();
    return 0;
}