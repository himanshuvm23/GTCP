#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

// Function to compute the Grundy number for a pile of stones
int computeGrundyNumber(int stones, int maxStonesToTake) {
    vector<int> grundyValues(stones + 1, 0);

    for (int current = 1; current <= stones; ++current) {
        unordered_set<int> reachableStates;

        for (int stonesTaken = 1; stonesTaken <= min(maxStonesToTake, current); ++stonesTaken) {
            reachableStates.insert(grundyValues[current - stonesTaken]);
        }

        int mexValue = 0;
        while (reachableStates.count(mexValue)) {
            ++mexValue;
        }
        grundyValues[current] = mexValue;
    }

    return grundyValues[stones];
}

// Function to determine the winner based on Sprague-Grundy theorem
string getWinner(const vector<int>& heaps, int maxStonesToTake) {
    int xorTotal = 0;

    for (int heapSize : heaps) {
        xorTotal ^= computeGrundyNumber(heapSize, maxStonesToTake);
    }

    return (xorTotal != 0) ? "First Player Wins" : "Second Player Wins";
}

int main() {
    vector<int> heaps = {3, 4, 5}; // Initial heap sizes
    int maxStonesPerTurn = 3;      // Maximum stones a player can take in one turn

    cout << getWinner(heaps, maxStonesPerTurn) << endl;

    return 0;
}
