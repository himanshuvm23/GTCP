#include <iostream>
#include <vector>
using namespace std;

// Function to show the current state of the heaps
void showHeaps(const vector<int>& heaps) {
    cout << "Current Heap Status:\n";
    for (size_t index = 0; index < heaps.size(); ++index) {
        cout << "Heap " << index + 1 << ": " << heaps[index] << " stones\n";
    }
    cout << endl;
}

// Function to check if the game is finished
bool gameFinished(const vector<int>& heaps) {
    for (int heap : heaps) {
        if (heap > 0) return false;
    }
    return true;
}

int main() {
    int heapCount;
    cout << "Enter the number of heaps: ";
    cin >> heapCount;

    vector<int> heaps(heapCount);
    cout << "Enter the number of stones in each heap:\n";
    for (int i = 0; i < heapCount; ++i) {
        cout << "Heap " << i + 1 << ": ";
        cin >> heaps[i];
    }

    int currentTurn = 1; // Player 1 starts
    while (!gameFinished(heaps)) {
        showHeaps(heaps);

        int chosenHeap, stonesToRemove;
        cout << "Player " << currentTurn << ", select a heap (1 to " << heapCount << "): ";
        cin >> chosenHeap;

        if (chosenHeap < 1 || chosenHeap > heapCount || heaps[chosenHeap - 1] == 0) {
            cout << "Invalid heap selection. Try again.\n";
            continue;
        }

        cout << "Enter the number of stones to remove from Heap " << chosenHeap << ": ";
        cin >> stonesToRemove;

        if (stonesToRemove <= 0 || stonesToRemove > heaps[chosenHeap - 1]) {
            cout << "Invalid number of stones. Try again.\n";
            continue;
        }

        heaps[chosenHeap - 1] -= stonesToRemove;

        if (gameFinished(heaps)) {
            cout << "Player " << (currentTurn == 1 ? 2 : 1) << " wins! (Misere Rule)\n";
            break;
        }

        // Switch turns
        currentTurn = (currentTurn == 1) ? 2 : 1;
    }

    return 0;
}
