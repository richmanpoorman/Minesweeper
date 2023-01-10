#include <vector>   // For vector
#include <stdlib.h> // For rand
#include <ciso646>  // For the alternate tokens
#include "Board.h"

using namespace std;

// Sets up the cell
Board::Cell Board::makeCell() {
    Board::Cell cell;
    cell.isMine = false;
    cell.isSeen = false;
    cell.number = 0;
    return cell;
}

// makes the board for the set up
void Board::makeBoard(std::vector<std::vector<Cell>> &givenBoard) {
    board = givenBoard;
}
void Board::makeBoard() {
    // Use the difficulty to decide the size
    int x = difficulty == 0 ? 8 : difficulty == 1 ? 16 : 30;
    int y = difficulty == 0 ? 8 : 16;
    
    numMines = x * y / 5;
    board = vector<vector<Cell>> (x, vector<Cell> (y, makeCell()));
    // Randomly places the mines
    for (int i = 0; i < numMines; i++) {
        int randX = rand() % x, randY = rand() % y;
        while (board[randX][randY].isMine) {
            randX = rand() % x;
            randY = rand() % y;
        }
        board[randX][randY].isMine = true;
    }
    
    // Updates the numbers surrounding the mines
    for (int r = 0; r < x; r++) {
        for (int c = 0; c < y; c++) {
            // Skip Mines
            if (board[r][c].isMine) { 
                board[r][c].number = 10;
                continue; 
            }

            // Check surrounding cells
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    if (r + i < 0 or r + i >= x) continue;
                    if (c + j < 0 or c + j >= y) continue;
                    if (board[r + i][c + j].isMine) board[r][c].number++;
                }
            }
        }
    }
}

    /* CONSTRUCTORS */
// Default Constructor
Board::Board() {
    numChecked = 0;
    makeBoard();
}

// Deconstructor
Board::~Board() {
    // Use the default; no pointers
}

// Seeded Board
Board::Board(std::vector<std::vector<Cell>> &givenBoard) {
    numChecked = 0;
    makeBoard(givenBoard);
}

    /* BOARD FUNCTIONS */
// Select the cell on the board
bool Board::selectCell(int x, int y) {
    if (x < 0 or x >= board.size() or y < 0 or y >= board[x].size() or board[x][y].isSeen) return;
    if (board[x][y].isMine) return false;
    board[x][y].isSeen = true;
    numChecked++;
    if (board[x][y].number == 0) {
        for (int i = -1; i <= 1; i++) for (int j = -1; j <= 1; j++) 
            selectCell(x + i, y + j);
    }
    return true;
}

// Redoes the board when starting
void Board::resetBoard() {
    makeBoard();
}
void Board::resetBoard(std::vector<std::vector<Cell>> &givenBoard) {
    makeBoard(givenBoard);
}

// When there is a victory, return true
bool Board::isWin() {
    return numChecked == board.size() * board[0].size() - numMines;
}
