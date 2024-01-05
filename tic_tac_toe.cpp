#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function to initialize the game board
void initializeBoard(vector<vector<char>> &board) {
    for (int i = 0; i < 3; ++i) {
        vector<char> row;
        for (int j = 0; j < 3; ++j) {
            row.push_back(' ');
        }
        board.push_back(row);
    }
}

// Function to display the game board
void displayBoard(const vector<vector<char>> &board) {
    cout << "-------------" << endl;
    for (int i = 0; i < 3; ++i) {
        cout << "| ";
        for (int j = 0; j < 3; ++j) {
            cout << board[i][j] << " | ";
        }
        cout << endl << "-------------" << endl;
    }
}

// Function to check if a player has won the game
bool checkWin(const vector<vector<char>> &board, char player) {
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) return true;
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) return true;
    }
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) return true;
    return false;
}

// Function to check if the game is a draw
bool checkDraw(const vector<vector<char>> &board) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == ' ') {
                return false; // If any empty cell found, game is not a draw
            }
        }
    }
    return true; // All cells are filled, game is a draw
}

// Function to take player's move input
void playerMove(vector<vector<char>> &board, char player) {
    int row, col;
    do {
        cout << "Player " << player << ", enter your move (row and column): ";
        cin >> row >> col;
        if (row < 1 || row > 3 || col < 1 || col > 3 || board[row - 1][col - 1] != ' ') {
            cout << "Invalid move. Try again." << endl;
        } else {
            board[row - 1][col - 1] = player;
            break;
        }
    } while (true);
}

// Function for computer's move
void computerMove(vector<vector<char>> &board, char player) {
    cout << "Computer's turn..." << endl;
    srand(static_cast<unsigned int>(time(nullptr)));
    int row, col;
    do {
        row = rand() % 3;
        col = rand() % 3;
    } while (board[row][col] != ' ');
    board[row][col] = player;
}

int main() {
    vector<vector<char>> board;
    initializeBoard(board);
    string player1, player2;
    char currentPlayer = 'X';
    char winner = ' ';

    cout << "Enter Player 1's name: ";
    cin >> player1;
    cout << "Enter Player 2's name: ";
    cin >> player2;

    int gameMode;
    cout << "Select game mode (1 - Player vs Player, 2 - Player vs Computer): ";
    cin >> gameMode;

    do {
        displayBoard(board);
        if (currentPlayer == 'X') {
            if (gameMode == 1) {
                cout << player1 << "'s turn (X):" << endl;
                playerMove(board, currentPlayer);
            } else {
                cout << player1 << "'s turn (X):" << endl;
                playerMove(board, currentPlayer);
            }
        } else {
            if (gameMode == 1) {
                cout << player2 << "'s turn (O):" << endl;
                playerMove(board, currentPlayer);
            } else {
                cout << "Computer's turn (O):" << endl;
                computerMove(board, currentPlayer);
            }
        }

        if (checkWin(board, currentPlayer)) {
            winner = currentPlayer;
            break;
        } else if (checkDraw(board)) {
            break;
        }

        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';

    } while (true);

    displayBoard(board);

    if (winner != ' ') {
        if (winner == 'X' && gameMode == 1) {
            cout << "Congratulations, " << player1 << "! You win!" << endl;
        } else if (winner == 'O' && gameMode == 1) {
            cout << "Congratulations, " << player2 << "! You win!" << endl;
        } else if (winner == 'X' && gameMode == 2) {
            cout << "Congratulations, " << player1 << "! You win!" << endl;
        } else {
            cout << "Computer wins!" << endl;
        }
    } else {
        cout << "It's a draw!" << endl;
    }

    char playAgain;
    cout << "Do you want to play again? (y/n): ";
    cin >> playAgain;

    if (playAgain == 'y' || playAgain == 'Y') {
        currentPlayer = 'X';
        winner = ' ';
        initializeBoard(board);
    }

    return 0;
}
