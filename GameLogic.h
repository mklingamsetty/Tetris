// File: GameLogic.h

#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <vector>

using namespace std;

class GameLogic {
public:
    vector<vector<int>> board;  // The game board

    GameLogic(int width, int height) {
        // Initialize the board with all zeros
        board = vector<vector<int>>(height, vector<int>(width, 0));
    }

    // Function to check for collision
    bool checkCollision(const vector<vector<int>>& shape, int x, int y) {
        for (int i = 0; i < shape.size(); i++) {
            for (int j = 0; j < shape[i].size(); j++) {
                if (shape[i][j] != 0) {
                    int newX = x + j;
                    int newY = y + i;
                    if (newX < 0 || newX >= board[0].size() || newY >= board.size() || board[newY][newX]) {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    // Function to fix the Tetrimino to the board with different colors
    void fixTetrimino(const vector<vector<int>>& shape, int x, int y, int blockType) {
        for (int i = 0; i < shape.size(); i++) {
            for (int j = 0; j < shape[i].size(); j++) {
                if (shape[i][j] != 0) {
                    board[y + i][x + j] = blockType;  // Assign the block type
                }
            }
        }
    }
};

#endif // GAMELOGIC_H
