#include <iostream>
#include <cstdlib>
using namespace std;

#define PLAYER_ONE 1
#define PLAYER_TWO 2

struct Move {
    int pileIndex;
    int stonesRemoved;
};

void displayPiles(int piles[], int numPiles) {
    cout << "Current Game Status: ";
    for (int i = 0; i < numPiles; ++i)
        cout << piles[i] << " ";
    cout << "\n";
}

bool isGameOver(int piles[], int numPiles) {
    for (int i = 0; i < numPiles; ++i)
        if (piles[i] != 0)
            return false;
    return true;
}

void announceWinner(int currentPlayer) {
    if (currentPlayer == PLAYER_ONE)
        cout << "\nPLAYER TWO wins!\n";
    else
        cout << "\nPLAYER ONE wins!\n";
}

int computeNimSum(int piles[], int numPiles) {
    int nimSum = piles[0];
    for (int i = 1; i < numPiles; ++i)
        nimSum ^= piles[i];
    return nimSum;
}

void executeMove(int piles[], int numPiles, Move* move) {
    int nimSum = computeNimSum(piles, numPiles);

    if (nimSum != 0) {
        for (int i = 0; i < numPiles; ++i) {
            if ((piles[i] ^ nimSum) < piles[i]) {
                move->pileIndex = i;
                move->stonesRemoved = piles[i] - (piles[i] ^ nimSum);
                piles[i] = piles[i] ^ nimSum;
                break;
            }
        }
    } else {
        int validPiles[numPiles], count = 0;
        for (int i = 0; i < numPiles; ++i) {
            if (piles[i] > 0)
                validPiles[count++] = i;
        }

        move->pileIndex = validPiles[rand() % count];
        move->stonesRemoved = 1 + (rand() % piles[move->pileIndex]);
        piles[move->pileIndex] -= move->stonesRemoved;

        if (piles[move->pileIndex] < 0)
            piles[move->pileIndex] = 0;
    }
}

void startGame(int piles[], int numPiles, int startingPlayer) {
    cout << "\nGAME BEGINS\n";
    Move move;

    while (!isGameOver(piles, numPiles)) {
        displayPiles(piles, numPiles);

        executeMove(piles, numPiles, &move);

        if (startingPlayer == PLAYER_ONE) {
            cout << "COMPUTER removes " << move.stonesRemoved 
                 << " stones from pile " << move.pileIndex << "\n";
            startingPlayer = PLAYER_TWO;
        } else {
            cout << "PLAYER TWO removes " << move.stonesRemoved 
                 << " stones from pile " << move.pileIndex << "\n";
            startingPlayer = PLAYER_ONE;
        }
    }

    displayPiles(piles, numPiles);
    announceWinner(startingPlayer);
}

void predictWinner(int piles[], int numPiles, int startingPlayer) {
    cout << "Prediction before the game: ";
    if (computeNimSum(piles, numPiles) != 0) {
        if (startingPlayer == PLAYER_ONE)
            cout << "PLAYER ONE will win\n";
        else
            cout << "PLAYER TWO will win\n";
    } else {
        if (startingPlayer == PLAYER_ONE)
            cout << "PLAYER TWO will win\n";
        else
            cout << "PLAYER ONE will win\n";
    }
}

int main() {
    int piles[] = {3, 4, 5};
    int numPiles = sizeof(piles) / sizeof(piles[0]);

    // PLAYER_ONE starts first
    predictWinner(piles, numPiles, PLAYER_ONE);

    startGame(piles, numPiles, PLAYER_ONE);

    return 0;
}
