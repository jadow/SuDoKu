#include "SudokuSolver.h"
#include <stdio.h>

int main()
{
	Sudoku_Solver solver;
	solver.sudoku.print();
	solver.tryBackTrackSolve();
	solver.sudoku.print();
	return 0;
}
