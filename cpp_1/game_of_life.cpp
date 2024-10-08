#include <iostream>
#include <vector>

class GameOfLife {
private:
    int rows, cols;
    bool** currentGrid;  // Pointer to a 2D grid (dynamic array of bools)
    bool** nextGrid;

    // Private Constructor for Singleton Pattern
    GameOfLife(int r, int c) : rows(r), cols(c) {
        currentGrid = new bool*[rows];
        nextGrid = new bool*[rows];
        for (int i = 0; i < rows; ++i) {
            currentGrid[i] = new bool[cols]{false};
            nextGrid[i] = new bool[cols]{false};
        }
    }

    // Destructor to release dynamically allocated memory
    ~GameOfLife() {
        for (int i = 0; i < rows; ++i) {
            delete[] currentGrid[i];
            delete[] nextGrid[i];
        }
        delete[] currentGrid;
        delete[] nextGrid;
    }

    // Singleton instance
    static GameOfLife* instance;

public:
    // Static method to get the single instance
    static GameOfLife* getInstance(int r = 10, int c = 10) {
        if (instance == nullptr) {
            instance = new GameOfLife(r, c);
        }
        return instance;
    }

    // Method to initialize the grid with a pattern
    void initialize(std::vector<std::pair<int, int>>& liveCells) {
        for (auto& cell : liveCells) {
            currentGrid[cell.first][cell.second] = true;
        }
    }

    // Method to print the grid
    void printGrid() {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                std::cout << (currentGrid[i][j] ? "O " : ". ");
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    // Method to update the grid using pointers and references
    void updateGrid() {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                int liveNeighbors = countLiveNeighbors(i, j);
                if (currentGrid[i][j]) {
                    // Rule 1: Any live cell with fewer than 2 or more than 3 live neighbors dies
                    nextGrid[i][j] = (liveNeighbors == 2 || liveNeighbors == 3);
                } else {
                    // Rule 2: Any dead cell with exactly 3 live neighbors becomes a live cell
                    nextGrid[i][j] = (liveNeighbors == 3);
                }
            }
        }

        // Swap the grids for the next iteration
        std::swap(currentGrid, nextGrid);
    }

private:
    // Helper function to count live neighbors using references
    int countLiveNeighbors(int row, int col) {
        int liveNeighbors = 0;
        for (int i = row - 1; i <= row + 1; ++i) {
            for (int j = col - 1; j <= col + 1; ++j) {
                if (i >= 0 && i < rows && j >= 0 && j < cols && (i != row || j != col)) {
                    if (currentGrid[i][j]) {
                        ++liveNeighbors;
                    }
                }
            }
        }
        return liveNeighbors;
    }
};

// Initialize Singleton instance
GameOfLife* GameOfLife::instance = nullptr;

int main() {
    int rows = 10;
    int cols = 10;
    
    // Singleton pattern ensures only one instance of the game
    GameOfLife* game = GameOfLife::getInstance(rows, cols);

    // Initial pattern (Glider)
    std::vector<std::pair<int, int>> liveCells = {
        {1, 2}, {2, 3}, {3, 1}, {3, 2}, {3, 3}
    };

    game->initialize(liveCells);
    std::cout << "Initial State: \n";
    game->printGrid();

    // Simulate 10 generations
    for (int i = 0; i < 10; ++i) {
        game->updateGrid();
        std::cout << "Generation " << i + 1 << ":\n";
        game->printGrid();
    }

    return 0;
}
