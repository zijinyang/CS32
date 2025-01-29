#include "History.h"
#include "globals.h"
#include <iostream>
using namespace std;


History::History(int nRows, int nCols){
    m_nRows = nRows;
    m_nCols = nCols;
    for(int r = 0; r < nRows; r++){
        for(int c = 0; c < nCols; c++){
            m_hits[r][c] = '.';
        }
    }
}

bool History::record(int r, int c){
    if(r < 1 || r > m_nRows || c < 1 || c > m_nCols)
        return false;
    char& hit = m_hits[r-1][c-1]; 
    if( hit == '.')
        hit = 'A'; 
    else if (hit == 'Z');
    else
        hit++;
    return true;
}

void History::display() const{
    clearScreen();
    for(int r = 0; r < m_nRows; r++){
        for(int c = 0; c < m_nCols; c++){
            cout << m_hits[r][c]; 
        }
        cout << endl;
    }
    cout << endl;
}