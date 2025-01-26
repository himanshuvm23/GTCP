
#include <iostream>
#include <vector>
using namespace std;

vector<int> calculateDivisors(int number) {
    vector<int> divisorsList;
    for (int i = 1; i < number; ++i) {
        if (number % i == 0) {
            divisorsList.push_back(i);
        }
    }
    return divisorsList;
}

bool determineWinningPosition(int currentNumber) {
    vector<int> possibleMoves = calculateDivisors(currentNumber);
    for (int move : possibleMoves) {
        int resultingState = currentNumber - move;
        if (!determineWinningPosition(resultingState)) {
            return true; // Winning move found
        }
    }
    return false; // No winning move, so it's a losing state
}

int main() {
    int maxNumber;
    cout << "Enter the maximum value to check: ";
    cin >> maxNumber;

    cout << "State Analysis:\n";
    for (int value = 1; value <= maxNumber; ++value) {
        if (determineWinningPosition(value)) {
            cout << "Value " << value << ": Winning State\n";
        } else {
            cout << "Value " << value << ": Losing State\n";
        }
    }

    return 0;
}
