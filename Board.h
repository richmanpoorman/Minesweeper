#ifndef BOARD_H_
#define BOARD_H_

#include <vector>
class Board {
private:
    // Each individual cell
    struct Cell {
        bool isMine;
        bool isSeen;
        int  number;
    };

    // Sets up the cell
    Cell makeCell(bool isMine);

    // Represents the board
    std::vector<std::vector<Cell>> board; 
    
    // The set up
    int difficulty = 1;
    int numMines;

    // makes the board for the set up
    void makeBoard(const int seed);
public:
    
        /* CONSTRUCTORS */
    // Default Constructor
    Board();

    // Deconstructor
    ~Board();

    // Seeded Board
    Board(std::vector<std::vector<Cell>> givenBoard); 

        /* BOARD FUNCTIONS */
    // Select the cell on the board
    void selectCell(int x, int y);

    // Redoes the board when starting
    void resetBoard();
    void resetBoard(std::vector<std::vector<Cell>> givenBoard);

    // When there is a victory, return true
    bool isWin();

};

#endif