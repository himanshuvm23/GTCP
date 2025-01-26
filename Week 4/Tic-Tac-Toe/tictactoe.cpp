#include <bits/stdc++.h>

using namespace std;

const int WIN_SCORE = 10;
const int LOSE_SCORE = -10;
const int SIZE = 3;

typedef vector<vector<char>> Grid;

bool hasEmptyCells(const Grid& board) {
    for (auto& row : board) {
        for (char cell : row) {
            if (cell == '_') {
                return true;
            }
        }
    }
    return false;
}

int evaluateBoard(const Grid& board) {
    for (int row = 0; row < SIZE; ++row) {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2] && board[row][0] != '_') {
            return (board[row][0] == 'X') ? WIN_SCORE : LOSE_SCORE;
        }
    }

    for (int col = 0; col < SIZE; ++col) {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col] && board[0][col] != '_') {
            return (board[0][col] == 'X') ? WIN_SCORE : LOSE_SCORE;
        }
    }

    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != '_') {
        return (board[0][0] == 'X') ? WIN_SCORE : LOSE_SCORE;
    }

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != '_') {
        return (board[0][2] == 'X') ? WIN_SCORE : LOSE_SCORE;
    }

    return 0;
}

int minimaxEvaluation(Grid& board, int depth, bool isMaximizing) {
    int score = evaluateBoard(board);

    if (score == WIN_SCORE || score == LOSE_SCORE) {
        return score - depth * (score == WIN_SCORE ? 1 : -1);
    }

    if (!hasEmptyCells(board)) {
        return 0;
    }

    int best = isMaximizing ? numeric_limits<int>::min() : numeric_limits<int>::max();
    char currentPlayer = isMaximizing ? 'X' : 'O';
    char nextPlayer = isMaximizing ? 'O' : 'X';

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == '_') {
                board[i][j] = currentPlayer;
                int eval = minimaxEvaluation(board, depth + 1, !isMaximizing);
                best = isMaximizing ? max(best, eval) : min(best, eval);
                board[i][j] = '_';
            }
        }
    }

    return best;
}

pair<int, int> optimalMove(Grid& board) {
    int bestValue = numeric_limits<int>::min();
    pair<int, int> move = {-1, -1};

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == '_') {
                board[i][j] = 'X';
                int moveValue = minimaxEvaluation(board, 0, false);
                board[i][j] = '_';

                if (moveValue > bestValue) {
                    bestValue = moveValue;
                    move = {i, j};
                }
            }
        }
    }

    return move;
}

int main() {
    Grid gameBoard = {
        {'X', 'O', 'X'},
        {'_', 'O', '_'},
        {'_', '_', 'X'}
    };

    pair<int, int> bestMove = optimalMove(gameBoard);
    cout << "Best Move for Player X: (" << bestMove.first << ", " << bestMove.second << ")\n";

    return 0;
}
