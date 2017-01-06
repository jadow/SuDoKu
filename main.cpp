#include "SudokuSolver.h"
#include <stdio.h>

int main()
{
	Sudoku_Solver solver;
	solver.sudoku.print();
	solver.trySolveBackTrack();
	solver.sudoku.print();
	return 0;
}
