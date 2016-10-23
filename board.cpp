//
//  board.cpp
//  Project4
//
//  Created by Tuan Dao on 10/23/15.
//  Copyright © 2015 Tuan Dao. All rights reserved.
//

#include <stdlib.h> // exit()
#include "board.hpp"

ostream &operator<<(ostream &ostr, vector<int> &v)
// Overloaded output operator for vector class.
{
    for (size_t i = 0; i < v.size(); i++)
        ostr << v[i] << " ";
    ostr << endl;
    return ostr;
}

board::board(string fileName)
: value(BoardSize+1, BoardSize+1),
conflict((BoardSize+1)*(BoardSize+1), BoardSize+1),
inRow(BoardSize+1, 10), inCol(BoardSize+1, 10), inSq(BoardSize+1, 10)
{
    clear();
    ifstream fin;
    fin.open(fileName.c_str());
    if (!fin)
    {
        cerr << "Cannot open " << fileName << endl;
        exit(1);
    }
    initialize(fin);
}

board::board(ifstream& fin)
: value(BoardSize+1, BoardSize+1),
conflict((BoardSize+1)*(BoardSize+1), BoardSize+1),
inRow(BoardSize+1, 10), inCol(BoardSize+1, 10), inSq(BoardSize+1, 10)
{
    initialize(fin);
}

board::board()
: value(BoardSize+1, BoardSize+1),
conflict((BoardSize+1)*(BoardSize+1), BoardSize+1),
inRow(BoardSize+1, 10), inCol(BoardSize+1, 10), inSq(BoardSize+1, 10)
// Board constructor
{
    clear();
}

board::board(int sqSize)
: value(BoardSize+1, BoardSize+1),
conflict((BoardSize+1)*(BoardSize+1), BoardSize+1),
inRow(BoardSize+1, 10), inCol(BoardSize+1, 10), inSq(BoardSize+1, 10)
{
    board();
    clear();
}

void board::clear()
// Clear the entire board.
{
    for (int i = 1; i < BoardSize; i++) {
        for (int j = 1; j < BoardSize; j++) {
            value[i][j] = Blank;
        }
    }
}

void board::setCell(int i,int j, ValueType val)
// set cell i,j to val and update conflicts
{
    value[i][j] = val;
}

void board::clearCell(int i,int j)
{
    setCell(i, j, Blank);
}

void board::initialize(ifstream &fin)
// Read a Sudoku board from the input file.
{
    char ch;
    
    clear();
    for (int i = 1; i <= BoardSize; i++)
        for (int j = 1; j <= BoardSize; j++)
        {
            fin >> ch;
            // If the read char is not Blank
            if (ch != '.') setCell(i,j,ch-'0');   // Convert char to int
            else setCell(i, j, Blank);            // Else set to blank
        }
    
    updateConflicts();
}

int squareIndex(int y, int x)
{
    if (y < 1 || y > BoardSize || x < 1 || x > BoardSize)
        throw rangeError("bad value in squareIndex");
    return SquareSize * ((y-1)/SquareSize) + (x-1)/SquareSize + 1;
}

int cellIndex(int y, int x)
{
    return x + (y-1)*BoardSize;
}

void board::updateDB(void)
{
    ValueType temp;
    for (int i = 1 ; i <= BoardSize; i++) {
        inRow[i].clear();
        inCol[i].clear();
        inSq[i].clear();
    }
    
    for (int y = 1; y <= BoardSize; y++) {
        for (int x = 1; x <= BoardSize; x++) {
            if (!isBlank(y, x)) {
                temp = getCell(y, x);
                inRow[y].push_back(temp);
                inCol[x].push_back(temp);
                inSq[squareIndex(y, x)].push_back(temp);
            }
        }
    }
}

bool board::causeConflict(int y, int x, ValueType val)
{
    int z = squareIndex(y, x);
    int sizeX = (int)inCol[x].size();
    int sizeY = (int)inRow[y].size();
    int sizeZ = (int)inSq[z].size();
    
    for (int idx = 0; idx < sizeX; idx++)
        if (val == inCol[x][idx])
            return 1;
    
    for (int idy = 0; idy < sizeY; idy++)
        if (val == inRow[y][idy])
            return 1;
    
    for (int idz = 0; idz < sizeZ; idz++)
        if (val == inSq[z][idz])
            return 1;
    
    return 0;
}

void board::updateConflict(int y, int x)
{
    int index = cellIndex(y, x);
    conflict[index].clear();
    
    for (int val = 1; val <= BoardSize; val++) {
        if (!causeConflict(y, x, val)) {
            conflict[index].push_back(val);
        }
    }

}

int board::numPossibles(int y, int x)
{
    return (int)conflict[cellIndex(y, x)].size();
}

void board::printConflict(int y, int x)
{
    int index = cellIndex(y, x);
    int size = (int)conflict[index].size();
    cout << "Possible values for square [" << y << "," << x << "]: ";
    for (int k = 0; k < size; k++) {
        if (conflict[index][k] != Blank) {
            cout << conflict[index][k] << " ";
        }
    }
    cout << endl;
}


void board::updateConflicts(void)
{
    updateDB();
    for (int i = 1; i <= BoardSize; i++)
        for (int j = 1; j <= BoardSize; j++)
            if (isBlank(i, j))
                updateConflict(i, j);
}

void board::printConflicts(void)
{
    updateConflicts();
    for (int i = 1; i <= BoardSize; i++)
        for (int j = 1; j <= BoardSize; j++)
            if (isBlank(i, j))
                printConflict(i, j);
}

ValueType board::getCell(int i, int j)
// Returns the value stored in a cell.  Throws an exception
// if bad values are passed.
{
    if (i >= 1 && i <= BoardSize && j >= 1 && j <= BoardSize)
        return value[i][j];
    else
        throw rangeError("bad value in getCell");
    return Blank;
}


bool board::isBlank(int i, int j)
// Returns true if cell i,j is blank, and false otherwise.
{
    if (i < 1 || i > BoardSize || j < 1 || j > BoardSize)
        throw rangeError("bad value in setCell");
    if (value[i][j] == Blank) {
        return 1;
    } else return 0;
}

void board::print()
// Prints the current board.
{
    for (int i = 1; i <= BoardSize; i++)
    {
        if ((i-1) % SquareSize == 0)
        {
            cout << " -";
            for (int j = 1; j <= BoardSize; j++)
                cout << "---";
            cout << "-";
            cout << endl;
        }
        for (int j = 1; j <= BoardSize; j++)
        {
            if ((j-1) % SquareSize == 0)
                cout << "|";
            if (!isBlank(i,j))
                cout << " " << getCell(i,j) << " ";
            else
                cout << "   ";
        }
        cout << "|";
        cout << endl;
    }
    
    cout << " -";
    for (int j = 1; j <= BoardSize; j++)
        cout << "---";
    cout << "-";
    cout << endl;
}

bool board::isSolved(void)
{
    for (int i = 1; i <= BoardSize; i++)
        for (int j = 1; j <= BoardSize; j++)
            if (isBlank(i, j)) return 0;
    return 1;
}

bool board::solve(int &numCalls)
{
    //----------BRANCH 1----------
    
    if (isSolved()) return 1;
    
    //----------BRANCH 2----------
    
    numCalls++;
    updateConflicts();
    
    int X = 0, Y = 0, nPos = 100;
    
    for (int i = 1; i <= BoardSize; i++)
        for (int j = 1; j <= BoardSize; j++)
            if (isBlank(i, j))
                if (numPossibles(i, j) <= nPos) {
                    Y = i;
                    X = j;
                    nPos = numPossibles(i, j);
                }

    int index = cellIndex(Y, X);
    
    for (int i = 0; i < nPos; i++) {
        setCell(Y, X, conflict[index][i]);
        if (solve(numCalls)) {
            return 1;
        }
        else clearCell(Y, X);
    }
    
    //----------BRANCH 3----------
    
    return 0;
}
