//
//  main.cpp
//  Project4
//
//  Created by Tuan Dao on 10/20/15.
//  Copyright © 2015 Tuan Dao. All rights reserved.
//

#include <iostream>
#include <vector>
#include <stdlib.h> // exit()
#include "d_matrix.h"
#include "d_except.h"
#include "board.hpp"
#include "sortHelper.h"

using namespace std;

int main()
{
    int numCalls = 0, numBoards = 0, sum = 0, numEx = 0;
    vector<int> callDB;
    
    string filename = "sudoku.txt";
    ifstream fin;
    fin.open(filename.c_str());
    if (!fin) {
        cerr << "Cannot open " << filename << endl;
        exit(1);
    }
    
    while (fin && fin.peek() != 'Z') {
        numBoards++;
        numCalls = 0;
        board sudoku(fin);
        cout << "-------------------------------\n";
        cout << "Board #" << numBoards << ":\n";
        sudoku.print();
        sudoku.solve(numCalls);
        cout << "Solution: " << endl;
        sudoku.print();
        cout << "Number of recursive calls: " << numCalls << endl;
        sum += numCalls;
        if (numCalls > 50000) numEx++;
        callDB.push_back(numCalls);
    }
    
    quicksort(callDB);
    cout << "-------------------------------\n";
    cout << "Number of boards solved: " << numBoards << endl;
    cout << "Average number of calls: " << sum/numBoards << endl;
    cout << "Median number of calls: " << callDB[numBoards/2] << endl;
    cout << "Number of boards that exceed 50k calls: " << numEx << endl;
}
