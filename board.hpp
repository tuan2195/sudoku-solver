//
//  board.hpp
//  Project4
//
//  Created by Tuan Dao on 10/23/15.
//  Copyright © 2015 Tuan Dao. All rights reserved.
//

#ifndef board_hpp
#define board_hpp

#include <stdio.h>
#include <fstream>
#include "d_matrix.h"

typedef int ValueType; // The type of the value in a cell
const int Blank = -1;  // Indicates that a cell is blank

const int SquareSize = 3;  //  The number of cells in a small square
//  (usually 3).  The board has
//  SquareSize^2 rows and SquareSize^2
//  columns.

const int BoardSize = SquareSize * SquareSize;

const int MinValue = 1;
const int MaxValue = 9;

//int numSolutions = 0;

typedef int ValueType; // The type of the value in a cell

class board
// Stores the entire Sudoku board
{
public:
    board();
    board(string);
    board(int);
    board(ifstream&);
    void clear();
    void initialize(ifstream &fin);
    void print();
    bool isBlank(int, int);
    ValueType getCell(int, int);
    void setCell(int i, int j, ValueType val);
    void clearCell(int i,int j);
    void updateConflict(int y, int x);
    void updateConflicts(void);
    bool isSolved(void);
    void updateDB(void);
    bool causeConflict(int y, int x, ValueType val);
    void printConflict(int y, int x);
    void printConflicts(void);
    int numPossibles(int y, int x);
    bool solve(int &numCalls);
private:
    
    // The following matrices go from 1 to BoardSize in each
    // dimension.  I.e. they are each (BoardSize+1) X (BoardSize+1)
    
    matrix<ValueType> value, conflict, inRow, inCol, inSq;
};
#endif /* board_hpp */
