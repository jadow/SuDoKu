#include "SudokuSolver.h"

Sudoku_Solver::Sudoku_Solver():sudoku()
{
	sudoku.addNumber(0,0,5);
	sudoku.addNumber(0,1,3);
	sudoku.addNumber(1,0,6);
	sudoku.addNumber(2,1,9);
	sudoku.addNumber(2,2,8);

	sudoku.addNumber(0,4,7);
	sudoku.addNumber(1,3,1);
	sudoku.addNumber(1,4,9);
	sudoku.addNumber(1,5,5);

	sudoku.addNumber(2,7,6);

	sudoku.addNumber(3,0,8);
	sudoku.addNumber(4,0,4);
	sudoku.addNumber(5,0,7);
	
	sudoku.addNumber(3,4,6);
	sudoku.addNumber(4,3,8);
	sudoku.addNumber(4,5,3);
	sudoku.addNumber(5,4,2);

	sudoku.addNumber(3,8,3);
	sudoku.addNumber(4,8,1);
	sudoku.addNumber(5,8,6);

	sudoku.addNumber(6,1,6);

	sudoku.addNumber(7,3,4);
	sudoku.addNumber(7,4,1);
	sudoku.addNumber(7,5,9);
	sudoku.addNumber(8,4,8);

	sudoku.addNumber(6,6,2);
	sudoku.addNumber(6,7,8);
	sudoku.addNumber(7,8,5);
	sudoku.addNumber(8,7,7);
	sudoku.addNumber(8,8,9);
}

Sudoku_Solver::Sudoku_Solver(int size):sudoku(size)
{

}
bool Sudoku_Solver::findOne(Sudoku sudoku)
{
	addSudoku(solutions, sudoku);
	return true;
}

bool Sudoku_Solver::findAll(Sudoku sudoku)
{
	addSudoku(solutions, sudoku);
	return false;
}

bool Sudoku_Solver::recurveBackTrack(std::function<bool(Sudoku)> callback, int y, int x)
{
	if(sudoku.checkSolved())
	{
		return callback(sudoku); 
	}
	
	if(!sudoku.getNumber(y,x))
	{
		for(int i =1; i <= sudoku.getMaxValue(); i ++)
		{	
			if(!sudoku.addNumber(y, x, i))
				continue;
			
			int saveX=x, saveY=y;

			getNext(sudoku.getHorizontalMax(), y, x);
			if(trySolveBackTrack( y, x))
				return true;
					
			x=saveX;
			y=saveY;

			sudoku.removeNumber(y, x);	
		}
		return false;
	}
	else    
	{
		getNext(sudoku.getHorizontalMax(), y, x);
		return trySolveBackTrack( y, x);
    }    
}

bool Sudoku_Solver::trySolveBackTrack(int y, int x)
{
	return recurveBackTrack(std::bind(&Sudoku_Solver::findOne, this, sudoku), y, x);
}

bool Sudoku_Solver::findAllBackTrack(int y, int x)
{
 	return recurveBackTrack(std::bind(&Sudoku_Solver::findAll, this, sudoku), y, x);
}