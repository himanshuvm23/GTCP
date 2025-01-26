#include <bits/stdc++.h>
using namespace std;

const int NUM_ROWS = 3;
const int NUM_COLS = 3;

// Zobrist hashing data structures
vector<vector<uint64_t>> zobristData;
unordered_map<string, int> pieceToID;  // Maps piece names to unique IDs

default_random_engine rng(random_device{}());  // Random engine for hash generation
uniform_int_distribution<uint64_t> randomGen(0, UINT64_MAX);  // Generate random 64-bit numbers

void initializeHashTable() {
    zobristData.resize(NUM_ROWS, vector<uint64_t>(NUM_COLS * 10));

    for (int row = 0; row < NUM_ROWS; ++row) {
        for (int col = 0; col < NUM_COLS * 10; ++col) {
            zobristData[row][col] = randomGen(rng);  // Fill table with random 64-bit numbers
        }
    }
}

uint64_t generateBoardHash(const vector<vector<string>>& gameBoard) {
    uint64_t hashResult = 0;

    for (int row = 0; row < NUM_ROWS; ++row) {
        for (int col = 0; col < NUM_COLS; ++col) {
            if (!gameBoard[row][col].empty()) {
                int pieceID = pieceToID[gameBoard[row][col]];
                hashResult ^= zobristData[row][col * 10 + pieceID];  // Apply Zobrist hash for each piece
            }
        }
    }

    return hashResult;
}

void modifyHash(uint64_t& currentHash, int startRow, int startCol, int endRow, int endCol, const string& pieceType) {
    int pieceID = pieceToID[pieceType];

    // Remove piece from its starting position
    currentHash ^= zobristData[startRow][startCol * 10 + pieceID];
    // Add piece to its new position
    currentHash ^= zobristData[endRow][endCol * 10 + pieceID];
}

int main() {
    // Assign unique IDs to pieces
    pieceToID["Rook"] = 0;
    pieceToID["Knight"] = 1;
    pieceToID["Pawn"] = 2;

    // Initialize the Zobrist hashing table
    initializeHashTable();

    // Initial board setup
    vector<vector<string>> gameBoard = {
        {"Rook", "", "Knight"},
        {"", "Pawn", ""},
        {"", "", ""}
    };

    uint64_t boardHash = generateBoardHash(gameBoard);
    cout << "Initial Board Hash: " << boardHash << endl;

    // Update the board and hash value after a move
    modifyHash(boardHash, 0, 2, 2, 2, "Knight");
    gameBoard[0][2] = "";  // Knight moves
    gameBoard[2][2] = "Knight";

    cout << "Updated Board Hash: " << boardHash << endl;

    uint64_t newHash = generateBoardHash(gameBoard);
    cout << "Recomputed Board Hash: " << newHash << endl;

    if (boardHash == newHash) {
        cout << "Hash values are consistent." << endl;
    } else {
        cout << "Hash values are inconsistent!" << endl;
    }

    return 0;
}
