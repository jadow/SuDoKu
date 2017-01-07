#include "SudokuSolver.h"

Sudoku_Solver::Sudoku_Solver():sudoku()
{
	//test code
	sudoku.addNumber(0,0,9);
	sudoku.addNumber(0,2,6);
	sudoku.addNumber(2,1,7);

	sudoku.addNumber(0,4,7);
	sudoku.addNumber(1,3,4);
	sudoku.addNumber(2,4,2);
	sudoku.addNumber(2,5,3);
	
	sudoku.addNumber(0,6,4);
	sudoku.addNumber(0,8,3);
	sudoku.addNumber(1,6,2);
	sudoku.addNumber(2,7,1);

	sudoku.addNumber(3,0,5);
	sudoku.addNumber(4,1,4);
	sudoku.addNumber(5,2,3);
	
	sudoku.addNumber(4,3,2);
	sudoku.addNumber(4,5,8);

	sudoku.addNumber(3,6,1);
	sudoku.addNumber(4,7,6);
	sudoku.addNumber(5,8,5);
	
	sudoku.addNumber(6,1,3);
	sudoku.addNumber(7,2,7);
	sudoku.addNumber(8,0,4);
	sudoku.addNumber(8,2,5);

	sudoku.addNumber(6,3,7);
	sudoku.addNumber(7,5,5);
	sudoku.addNumber(8,4,1);

	sudoku.addNumber(6,7,5);
	sudoku.addNumber(8,6,7);
	sudoku.addNumber(8,8,8);
}

Sudoku_Solver::Sudoku_Solver(int size):sudoku(size)
{

}

bool Sudoku_Solver::trySolveBackTrack(int y, int x)
{
	if(sudoku.checkSolved())
	{
		return true;
	}
	else if(!sudoku.getNumber(y,x))
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

bool Sudoku_Solver::findAllBackTrack(int y, int x)
{
	if(sudoku.checkSolved())
	{
		addSudoku(solutions, sudoku);
		return false;
	}
	else if(!sudoku.getNumber(y,x))
	{
		for(int i =1; i <= sudoku.getMaxValue(); i ++)
		{	
			if(!sudoku.addNumber(y, x, i))
				continue;
			
			int saveX=x, saveY=y;

			getNext(sudoku.getHorizontalMax(), y, x);
			if(findAllBackTrack( y, x))
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
		return findAllBackTrack( y, x);
    }    
}

void Sudoku_Solver::printAll()
{
	printf("\n%d solution(s)\n", solutions.size());
	for(int i =0 ; i < solutions.size(); i++)
	{
		printf("\nsolution #%d\n", (i+1));
		solutions[i].print();
	}
}