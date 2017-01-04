#include "Sudoku.h"

#include <stdio.h>

void getNext(int max_x, int& y, int& x)
{
	if(++x == max_x)
	{
		x=0;
		y++;
	}
}

bool tryBackTrackSolve(Sudoku& target, int y=0, int x=0)
{
	if(target.checkSolved())
	{
		return true;
	}
	else if(!target.getNumber(y,x))
	{
		//assuming that sudoku is square
		for(int i =1; i <= target.getMaxValue(); i ++)
		{
			
			if(!target.addNumber(y, x, i))
				continue;
			
			int saveX=x, saveY=y;

			getNext(target.getHorizontalMax(), y, x);
			if(tryBackTrackSolve(target, y, x))
				return true;
					
			x=saveX;
			y=saveY;

			target.removeNumber(y, x);	
		}
		return false;
	}
	else    
	{
		getNext(target.getHorizontalMax(), y, x);
		return tryBackTrackSolve(target, y, x);
    }    
}

int main()
{
	Sudoku sudoku;

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

	sudoku.print();
	tryBackTrackSolve(sudoku);
	sudoku.print();
	return 0;
}
