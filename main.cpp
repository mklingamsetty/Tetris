// File: main.cpp

#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameAssets.h"
#include "GameLogic.h"
#include "Timer.h"

using namespace sf;
using namespace std;

// Shapes as 2D vectors
vector<vector<int>> I = {
        {1, 1, 1, 1}
};

vector<vector<int>> J = {
        {1, 0, 0},
        {1, 1, 1}
};

vector<vector<int>> L = {
        {0, 0, 1},
        {1, 1, 1}
};

vector<vector<int>> O = {
        {1, 1},
        {1, 1}
};

vector<vector<int>> S = {
        {0, 1, 1},
        {1, 1, 0}
};

vector<vector<int>> T = {
        {0, 1, 0},
        {1, 1, 1}
};

vector<vector<int>> Z = {
        {1, 1, 0},
        {0, 1, 1}
};

// Check if block is within bounds and not colliding
bool isValidPosition(GameLogic &logic, const vector<vector<int>> &block, int x, int y, int boardWidth, int boardHeight) {
    for (int i = 0; i < block.size(); i++) {
        for (int j = 0; j < block[i].size(); j++) {
            if (block[i][j] != 0) {
                int newX = x + j;
                int newY = y + i;
                if (newX < 0 || newX >= boardWidth || newY >= boardHeight || (newY >= 0 && logic.board[newY][newX] != 0)) {
                    return false;
                }
            }
        }
    }
    return true;
}

// Rotate the block counterclockwise
vector<vector<int>> rotateBlockLeft(const vector<vector<int>>& block) {
    int rows = block.size();
    int cols = block[0].size();
    vector<vector<int>> rotatedBlock(cols, vector<int>(rows));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            rotatedBlock[cols - j - 1][i] = block[i][j];
        }
    }

    return rotatedBlock;
}

// Clear full rows
void clearFullRows(GameLogic& logic, int boardWidth, int boardHeight) {
    for (int i = boardHeight - 1; i >= 0; --i) {
        bool fullRow = true;
        for (int j = 0; j < boardWidth; ++j) {
            if (logic.board[i][j] == 0) {
                fullRow = false;
                break;
            }
        }

        if (fullRow) {
            // Clear the row
            for (int j = 0; j < boardWidth; ++j) {
                logic.board[i][j] = 0;
            }

            // Shift all rows above down by one
            for (int k = i; k > 0; --k) {
                for (int j = 0; j < boardWidth; ++j) {
                    logic.board[k][j] = logic.board[k - 1][j];
                }
            }

            // Clear the top row
            for (int j = 0; j < boardWidth; ++j) {
                logic.board[0][j] = 0;
            }

            // After clearing, move back one row to check the next
            i++;
        }
    }
}

// Set current block on the board
void fixBlockOnBoard(GameLogic &logic, const vector<vector<int>> &block, int x, int y, int type) {
    for (int i = 0; i < block.size(); i++) {
        for (int j = 0; j < block[i].size(); j++) {
            if (block[i][j] != 0) {
                logic.board[y + i][x + j] = type;
            }
        }
    }
}

// Spawn a new block
void spawnNewBlock(GameLogic &logic, vector<vector<int>> &currentBlock, int &blockX, int &blockY, int &currentBlockType, vector<int> &blockTypes, vector<vector<vector<int>>> &shapes, int boardWidth, int boardHeight) {
    int currentShapeIndex = rand() % shapes.size();
    currentBlock = shapes[currentShapeIndex];
    blockX = 3;
    blockY = 0;
    currentBlockType = blockTypes[currentShapeIndex];

    if (!isValidPosition(logic, currentBlock, blockX, blockY, boardWidth, boardHeight)) {
        cout << "Game over logic here." << endl;
        // Handle game over scenario
    }
}

int main() {
    // Game dimensions
    int boardWidth = 10, boardHeight = 20;  // 10x20 grid for the Tetris board
    int tileSize = 39; // Scaled down from original, adjust as needed
    int windowWidth = boardWidth * tileSize - 5, windowHeight = boardHeight * tileSize + 80;

    // Create the game window
    RenderWindow window(VideoMode(windowWidth, windowHeight), "Tetris");

    // Initialize game assets
    GameAssets assets;

    // Initialize game logic
    GameLogic logic(boardWidth, boardHeight);

    // Initialize Timer for speed control
    Timer timer;
    timer.start();
    float delay = 0.01; // Initial delay for the block to fall

    // Array of possible Tetrimino shapes
    vector<vector<vector<int>>> shapes = {I, J, L, O, S, T, Z};

    // Map shapes to block types/colors
    vector<int> blockTypes = {2, 3, 4, 5, 6, 7, 8}; // Map shapes to integers

    // Hold block variables
    vector<vector<int>> heldBlock;
    int heldBlockType = 0; // 0 means no block is held
    bool canHold = true;

    // Initialize the first block
    vector<vector<int>> currentBlock;
    int blockX, blockY, currentBlockType;
    spawnNewBlock(logic, currentBlock, blockX, blockY, currentBlockType, blockTypes, shapes, boardWidth, boardHeight);

    while (window.isOpen()) {
        // Handle events
        Event e;
        while (window.pollEvent(e)) {
            if (e.type == Event::Closed)
                window.close();

            if (e.type == Event::KeyPressed) {
                if (e.key.code == Keyboard::Left) {
                    int newX = blockX - 1;
                    if (isValidPosition(logic, currentBlock, newX, blockY, boardWidth, boardHeight)) {
                        blockX = newX;
                    }
                }
                if (e.key.code == Keyboard::Right) {
                    int newX = blockX + 1;
                    if (isValidPosition(logic, currentBlock, newX, blockY, boardWidth, boardHeight)) {
                        blockX = newX;
                    }
                }
                if (e.key.code == Keyboard::Space) {
                    // Drop the block to the bottom immediately
                    while (isValidPosition(logic, currentBlock, blockX, blockY + 1, boardWidth, boardHeight)) {
                        blockY += 1;
                    }
                    fixBlockOnBoard(logic, currentBlock, blockX, blockY, currentBlockType); // Fix block on the board before spawning a new one
                    clearFullRows(logic, boardWidth, boardHeight);
                    spawnNewBlock(logic, currentBlock, blockX, blockY, currentBlockType, blockTypes, shapes, boardWidth, boardHeight);
                    canHold = true; // Allow holding again after block falls
                }
                if (e.key.code == Keyboard::Z) {
                    auto rotatedBlock = rotateBlockLeft(currentBlock);
                    if (isValidPosition(logic, rotatedBlock, blockX, blockY, boardWidth, boardHeight)) {
                        currentBlock = rotatedBlock;
                    }
                }
                if (e.key.code == Keyboard::C && canHold) {
                    // Swap the current block with the held block
                    if (heldBlock.empty()) {
                        heldBlock = currentBlock;
                        heldBlockType = currentBlockType;
                        spawnNewBlock(logic, currentBlock, blockX, blockY, currentBlockType, blockTypes, shapes, boardWidth, boardHeight);
                    } else {
                        swap(currentBlock, heldBlock);
                        swap(currentBlockType, heldBlockType);
                        blockX = 3;
                        blockY = 0;
                        if (!isValidPosition(logic, currentBlock, blockX, blockY, boardWidth, boardHeight)) {
                            cout << "Swapped block position invalid, game over logic here if needed." << endl;
                            // Handle game over scenario
                        }
                    }
                    canHold = false; // Disable holding until the block falls
                }
            }
        }

        // Update block position over time
        if (timer.getElapsedTime() > delay) {
            int newY = blockY + 1;
            if (isValidPosition(logic, currentBlock, blockX, newY, boardWidth, boardHeight)) {
                blockY = newY;
            } else {
                fixBlockOnBoard(logic, currentBlock, blockX, blockY, currentBlockType); // Fix block on the board before spawning a new one
                clearFullRows(logic, boardWidth, boardHeight);
                spawnNewBlock(logic, currentBlock, blockX, blockY, currentBlockType, blockTypes, shapes, boardWidth, boardHeight);
                canHold = true; // Allow holding again after block falls
            }
            timer.start(); // Reset the timer
        }

        // Render everything
        window.clear(Color::Black);

        // Draw the board
        for (int i = 0; i < boardHeight; i++) {
            for (int j = 0; j < boardWidth; j++) {
                Sprite block = assets.tileSpriteEmpty;  // Start with the empty tile

                if (logic.board[i][j] != 0) {
                    if (logic.board[i][j] == 2) {
                        block = assets.tileSpriteCyan;    // I Block
                    } else if (logic.board[i][j] == 3) {
                        block = assets.tileSpriteBlue;    // J Block
                    } else if (logic.board[i][j] == 4) {
                        block = assets.tileSpriteOrange;  // L Block
                    } else if (logic.board[i][j] == 5) {
                        block = assets.tileSpriteYellow;  // O Block
                    } else if (logic.board[i][j] == 6) {
                        block = assets.tileSpriteGreen;   // S Block
                    } else if (logic.board[i][j] == 7) {
                        block = assets.tileSpriteRed;     // Z Block
                    } else if (logic.board[i][j] == 8) {
                        block = assets.tileSpritePurple;  // T Block
                    }
                }

                block.setPosition(j * tileSize, i * tileSize); // Set position adjusted for smaller block size
                window.draw(block);
                cout<<logic.board[i][j];
            }
            cout<<"\n";
        }


        // Draw the current block
        for (int i = 0; i < currentBlock.size(); i++) {
            for (int j = 0; j < currentBlock[i].size(); j++) {
                if (currentBlock[i][j] != 0) {
                    Sprite block;
                    if (currentBlockType == 2) {
                        block = assets.tileSpriteCyan;    // I Block
                    } else if (currentBlockType == 3) {
                        block = assets.tileSpriteBlue;    // J Block
                    } else if (currentBlockType == 4) {
                        block = assets.tileSpriteOrange;  // L Block
                    } else if (currentBlockType == 5) {
                        block = assets.tileSpriteYellow;  // O Block
                    } else if (currentBlockType == 6) {
                        block = assets.tileSpriteGreen;   // S Block
                    } else if (currentBlockType == 7) {
                        block = assets.tileSpriteRed;     // Z Block
                    } else if (currentBlockType == 8) {
                        block = assets.tileSpritePurple;  // T Block
                    }
                    block.setPosition((blockX + j) * tileSize, (blockY + i) * tileSize);
                    window.draw(block);
                }
            }
        }


        window.display();
    }

    return 0;
}
