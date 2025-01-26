#include <iostream>
#include <unordered_set>
using namespace std;

// Function to calculate the minimum excluded value (MEX)
int findMex(const unordered_set<int>& values) {
    int mex = 0;
    while (values.count(mex)) {
        ++mex;
    }
    return mex;
}

// Grundy number calculation for the simple stone game
int calculateGrundy(int stones) {
    return stones; // For the simple stone game, the Grundy number is the number of stones.
}

int main() {
    int totalStones;
    cout << "Enter the number of stones for the Simple Stone Game: ";
    cin >> totalStones;

    int grundyNumber = calculateGrundy(totalStones);
    cout << "Grundy Number (Simple Stone Game) for " << totalStones << " is: " << grundyNumber << "\n";

    return 0;
}
