#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

// Function to compute the Minimum Excluded Value (MEX) of a set
int findMex(const unordered_set<int>& values) {
    int mex = 0;
    while (values.count(mex)) {
        ++mex;
    }
    return mex;
}

// Recursive function to compute the Grundy number for the division game
int computeGrundy(int number, vector<int>& memo) {
    if (number == 0) return 0; // Base case: Grundy number for 0 is 0
    if (memo[number] != -1) return memo[number]; // Memoized result

    unordered_set<int> reachableStates;
    reachableStates.insert(computeGrundy(number / 2, memo));
    reachableStates.insert(computeGrundy(number / 3, memo));
    reachableStates.insert(computeGrundy(number / 6, memo));

    return memo[number] = findMex(reachableStates);
}

int main() {
    int inputNumber;
    cout << "Enter the number for the Division Game: ";
    cin >> inputNumber;

    // Memoization array to store Grundy numbers
    vector<int> memo(inputNumber + 1, -1);

    // Calculate and display the Grundy number for the given input
    int grundyNumber = computeGrundy(inputNumber, memo);
    cout << "Grundy Number (Division Game) for " << inputNumber << " is: " << grundyNumber << "\n";

    return 0;
}
