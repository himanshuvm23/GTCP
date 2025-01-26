#include <iostream>
using namespace std;

bool checkWinningPosition(int remainingSticks) {
    return (remainingSticks % 4 != 0);
}

int calculateBestMove(int remainingSticks) {
    for (int remove = 1; remove <= 3; ++remove) {
        if ((remainingSticks - remove) % 4 == 0) {
            return remove;
        }
    }
    return 1;
}

int main() {
    int sticksCount;
    cout << "Enter the total number of sticks in the game: ";
    cin >> sticksCount;

    if (sticksCount <= 0) {
        cout << "The total number of sticks must be a positive integer!" << endl;
        return 0;
    }

    cout << "Game rules: Remove 1, 2, or 3 sticks on your turn.\n";
    cout << "The player who is forced to take the last stick loses the game.\n";

    while (sticksCount > 0) {
        int playerChoice;
        cout << "\nSticks left: " << sticksCount << endl;
        cout << "Your turn: How many sticks will you pick (1-3)? ";
        cin >> playerChoice;

        if (playerChoice < 1 || playerChoice > 3 || playerChoice > sticksCount) {
            cout << "Invalid choice! Please select a number between 1 and 3 that doesn't exceed the remaining sticks.\n";
            continue;
        }

        sticksCount -= playerChoice;

        if (sticksCount == 0) {
            cout << "You lost! No sticks left for the computer.\n";
            break;
        }

        int computerMove = calculateBestMove(sticksCount);
        sticksCount -= computerMove;

        cout << "Computer removes " << computerMove << " stick(s).\n";

        if (sticksCount == 0) {
            cout << "Congratulations! You won! The computer has no sticks left.\n";
            break;
        }
    }

    return 0;
}
