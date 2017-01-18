#ifndef _SUDOKU_CONTROLLER_HEADER_
#define _SUDOKU_CONTROLLER_HEADER_

#include "Sudoku.h"
#include <functional>

class Sudoku_Controller 
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
	static bool copyCell(Sudoku &destination, Sudoku target, int i, int j)
	{
		return destination.addNumber(i, j, target.getNumber(i, j));
	}
	static bool compareCell(Sudoku &destination, Sudoku target, int i, int j)
	{
		return (destination.getNumber(i, j) == target.getNumber(i, j));
	}
	static bool ForEachCell(Sudoku &destination, Sudoku target, bool(*callback)(Sudoku &destination, Sudoku target, int i, int j))
	{
		if(target.getHorizontalMax() != destination.getHorizontalMax() ||
			target.getVerticalMax() != destination.getVerticalMax() ||
			target.getMaxValue() != destination.getMaxValue())
		{
			return false;
		}
		
		for(int i=0; i<destination.getVerticalMax(); i++)
		{
			for(int j=0; j<destination.getHorizontalMax(); j++)
			{
					if(!callback(destination, target, i, j))
					return false;
			}
		}
		return true;
	}
	static bool copySudoku(Sudoku &destination, Sudoku target)
	{
		return ForEachCell(destination, target, &copyCell);
	}
	static bool compareSudoku(Sudoku destination, Sudoku target)
	{
		return ForEachCell(destination, target, &compareCell);
	}
	static bool addSudoku( std::vector<Sudoku> &destination, Sudoku target)
	{
		for(int i =0; i < destination.size(); i++)
		{
			if(compareSudoku(destination[i], target))
				return false;
		}
		Sudoku tempt(target.getMaxValue());
		if(!copySudoku(tempt, target))
			return false;

		destination.push_back(tempt);
		return true;
	}
		
public:
	Sudoku sudoku;
	std::vector<Sudoku> solutions;

	Sudoku_Controller();
	Sudoku_Controller(int size);
	bool trySolveBackTrack(int y=0, int x=0);
	void clearAll();
	void incrementBox(int y, int x);
	
	bool findAllBackTrack(int y=0, int x=0);
	void printAll();
};

#endif //_SUDOKU_CONTROLLER_HEADER_