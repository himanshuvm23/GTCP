#include <bits/stdc++.h>
using namespace std;

class GameNode {
public:
    int score;
    GameNode* leftChild;
    GameNode* rightChild;

    GameNode(int val) : score(val), leftChild(nullptr), rightChild(nullptr) {}
};

pair<int, string> playGame(GameNode* node, bool isMaximizing) {
    if (!node->leftChild && !node->rightChild) {
        return {node->score, ""};
    }

    auto leftMove = playGame(node->leftChild, !isMaximizing);
    auto rightMove = playGame(node->rightChild, !isMaximizing);

    if (isMaximizing) {
        if (leftMove.first >= rightMove.first) {
            return {leftMove.first, "Left"};
        }
        return {rightMove.first, "Right"};
    } else {
        if (leftMove.first <= rightMove.first) {
            return {leftMove.first, "Left"};
        }
        return {rightMove.first, "Right"};
    }
}

int main() {
    GameNode* rootNode = new GameNode(-1);
    rootNode->leftChild = new GameNode(-1);
    rootNode->rightChild = new GameNode(-1);
    rootNode->leftChild->leftChild = new GameNode(3);
    rootNode->leftChild->rightChild = new GameNode(5);
    rootNode->rightChild->leftChild = new GameNode(2);
    rootNode->rightChild->rightChild = new GameNode(9);

    auto result = playGame(rootNode, true);

    cout << "Optimal Outcome: " << result.first << endl;
    cout << "Best Path: " << result.second << endl;

    // Clean up dynamic memory
    delete rootNode->leftChild->leftChild;
    delete rootNode->leftChild->rightChild;
    delete rootNode->rightChild->leftChild;
    delete rootNode->rightChild->rightChild;
    delete rootNode->leftChild;
    delete rootNode->rightChild;
    delete rootNode;

    return 0;
}
