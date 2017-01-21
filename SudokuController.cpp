#include "SudokuController.h"

Sudoku_Controller::Sudoku_Controller():sudoku()
{
	//init code
}

Sudoku_Controller::Sudoku_Controller(int size):sudoku(size)
{

}

	
int Sudoku_Controller::getVerticalMax()
{
	return sudoku.getVerticalMax();
}
int Sudoku_Controller::getHorizontalMax()
{
	return sudoku.getHorizontalMax();
}
int Sudoku_Controller::totalBoxes()
{
	return sudoku.getHorizontalMax()*sudoku.getVerticalMax();
}
int Sudoku_Controller::getMaxValue()
{
	return sudoku.getMaxValue();
}
int Sudoku_Controller::getRootValue()
{
	return sudoku.getRootValue();
}

int Sudoku_Controller::getBoxValue(int y, int x)
{
	return sudoku.getNumber(y, x);
}

bool Sudoku_Controller::trySolveBackTrack(int y, int x)
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


bool Sudoku_Controller::trySolveBackTrack(void(*callback)(int y, int x), int y, int x)
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
			
			callback(y, x);

			int saveX=x, saveY=y;

			getNext(sudoku.getHorizontalMax(), y, x);
			if(trySolveBackTrack(callback, y, x))
				return true;
					
			x=saveX;
			y=saveY;

			sudoku.removeNumber(y, x);	
			callback(y, x);
		}
		return false;
	}
	else    
	{
		getNext(sudoku.getHorizontalMax(), y, x);
		return trySolveBackTrack(callback, y, x);
    }    
}
void Sudoku_Controller::clearAll()
{
	for(int i=0; i<sudoku.getHorizontalMax(); i++)
		for(int j=0; j<sudoku.getVerticalMax(); j++)
			sudoku.removeNumber(j,i);
	
}

void Sudoku_Controller::incrementBox(int y, int x)
{
	int tempt = sudoku.getNumber(y,x);
	while(!sudoku.addNumber(y, x, ++tempt))
		if(tempt >= sudoku.getMaxValue())
			tempt= -1;
}

bool Sudoku_Controller::findAllBackTrack(int y, int x)
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