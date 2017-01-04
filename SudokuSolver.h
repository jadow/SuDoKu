#ifndef _SUDOKU_SOLVER_HEADER_
#define _SUDOKU_SOLVER_HEADER_

#include "Sudoku.h"

class Sudoku_Solver 
{
private:	
	static void getNext(int max_x, int& y, int& x)
	{	
		if(++x == max_x)
		{
			x=0;
			y++;
		}
	}
	
public:
	Sudoku sudoku;
	
	Sudoku_Solver();
	Sudoku_Solver(int size);
	bool tryBackTrackSolve(int y=0, int x=0);
};

#endif //_SUDOKU_SOLVER_HEADER_