#include <iostream>
#include <vector>
#include <limits>
using namespace std;

// Alpha-Beta Pruning implementation of Minimax algorithm
int alphaBetaMinimax(int level, int index, bool isMaximizingPlayer, vector<int>& scores, 
                     int alpha, int beta, int maxLevel) {
    // Base case: if we have reached the maximum depth
    if (level == maxLevel) {
        return scores[index];
    }

    if (isMaximizingPlayer) {
        int maxScore = numeric_limits<int>::min();  // Initialize to negative infinity

        // Explore both child nodes
        for (int i = 0; i < 2; ++i) {
            int currentScore = alphaBetaMinimax(level + 1, index * 2 + i, false, scores, alpha, beta, maxLevel);
            maxScore = max(maxScore, currentScore);
            alpha = max(alpha, maxScore);

            // Beta cut-off
            if (beta <= alpha) {
                break;
            }
        }

        return maxScore;
    } else {
        int minScore = numeric_limits<int>::max();  // Initialize to positive infinity

        // Explore both child nodes
        for (int i = 0; i < 2; ++i) {
            int currentScore = alphaBetaMinimax(level + 1, index * 2 + i, true, scores, alpha, beta, maxLevel);
            minScore = min(minScore, currentScore);
            beta = min(beta, minScore);

            // Alpha cut-off
            if (beta <= alpha) {
                break;
            }
        }

        return minScore;
    }
}

int main() {
    vector<int> scores = {3, 5, 6, 9, 1, 2, 0, -1}; // Leaf node values

    int maxDepth = 3; // Maximum depth for the search

    // Perform Alpha-Beta Pruning to get the optimal value
    int result = alphaBetaMinimax(0, 0, true, scores, 
                                  numeric_limits<int>::min(), 
                                  numeric_limits<int>::max(), 
                                  maxDepth);

    cout << "Optimal Value (after pruning): " << result << endl;

    return 0;
}
