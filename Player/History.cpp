
#include "History.h"
#include "globals.h"
#include <iostream>

using namespace std;

History::History(int nRows, int nCols)
{
	if (nRows <= 0 || nCols <= 0 || nRows > MAXROWS || nCols > MAXCOLS)
	{
		cout << "***** History created with invalid size " << nRows << " by "
			<< nCols << "!" << endl;
		exit(1);
	}
	
	m_rows = nRows;
	m_cols = nCols;
	for (int i = 0; i < m_rows; i++)
		for (int j = 0; j < m_cols; j++)
			m_grid[i][j] = 0;                 // # of times player has stepped on coordinate = 0
}

bool History::record(int r, int c)             
{
	if (r <= 0 || r > m_rows || c <= 0 || c > m_cols) {
		return false;
	}
	else {
		m_grid[r - 1][c - 1] += 1;            // upper most row is 1 and left most column is 1, so -1
		return true;
	}
}

void History::display() const
{
	clearScreen();                                   // clears screen
	
	for (int i = 0; i < m_rows; i++) {
		for (int j = 0; j < m_cols; j++) {
			int times = m_grid[i][j];          // current # of times coordinate has been stepped on
			char n;                     // did not work without using the char n variable. was outputting 66 and 65 instead of B and A.
			if (times == 0) {
				n = '.';
			}
			if (times > 0 && times < 26) {
				n = 'A' + (times - 1);     // if times = 1, cout 'A' + 1 - 1 = 'A';  A++ = B; etc...
			}                             // cout << 'A' + (times - 1) was printing 66 and 65. had to use char variable.
			else if (times >= 26) {
				n = 'Z';
			}
			cout << n;
		}
		cout << endl;
	}
	cout << endl;
}