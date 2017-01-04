#include "Sudoku.h"
#include <math.h>

section::section()
{
	solved = 0;
}

section::section(std::vector<int*> target)
{
	members=target;
	solved=0;
	for(int i=1; i<=target.size(); i++)
		solved+=i;
}

bool section::checkNumber(int num)
{
	for(int i=0; i<members.size(); i++)
	{
		if(num == *members[i])
			return false;
	}

	return true;
}

bool section::checkSolved()
{
	int total=0;
	for(int i=0; i<members.size(); i++)
		total+=*members[i];

	return (total == solved);
}

void Sudoku::init()
{
	sudoku.resize(y);
	for(int i=0; i<y; i++)
		sudoku[i].resize(x);
	
	initVertical();
	initHorizontal();
	initBoxes();
}

void Sudoku::initVertical()
{
	for(int i=0 ; i<y; i++)
	{
		std::vector<int *> tempt;
		for(int j=0 ; j<x; j++)
			tempt.push_back(&sudoku[i][j]);

		section column(tempt);
		vertical.push_back(column);
	}
}

void Sudoku::initHorizontal()
{
	for(int j=0 ; j<x; j++)
	{
		std::vector<int *> tempt;
		for(int i=0 ; i<y; i++)
			tempt.push_back(&sudoku[i][j]);

		section row(tempt);
		horizontal.push_back(row);
	}
}

void Sudoku::initBoxes()
{
	int baseX=0, baseY=0;
	for(int k=0 ; k<boxes; k++)
	{
		std::vector<int *> tempt;
		for(int i=0; i<sqrt_y; i++)
			for(int j=0 ; j<sqrt_x; j++)
				tempt.push_back(&sudoku[baseY+i][baseX+j]);

		section square(tempt);
		box.push_back(square);

		if((baseX+=sqrt_x) == x)
		{
			baseX=0;
			baseY+=sqrt_y;
		}
	}
}

bool Sudoku::valid_x(int x)
{
	return !(x<0 || x>this->x);
}
bool Sudoku::valid_y(int y)
{
	return !(y<0 || y>this->y);
}
bool Sudoku::valid_num(int num)
{
	return !(num<0 || num>this->x || num>this->y);
}

Sudoku::Sudoku(int size)
{
	double intpart;
	double sqrt_size=sqrt((double)size);
	//size should be a square number
	if(size<0 || modf(sqrt_size, &intpart))
	{
		size=9;
	}
	
	x=size;
	y=size;
	boxes=size;
	sqrt_x=sqrt_size;
	sqrt_y=sqrt_size;
	init();
}

Sudoku::Sudoku()
{
	x=9;
	y=9;
	boxes=9;
	sqrt_x=3;
	sqrt_y=3;
	init();
}

bool Sudoku::addNumber(int y, int x, int num)
{
	if(!valid_x(x) || !valid_y(y) || !valid_num(num))
		return false;

	if(vertical[y].checkNumber(num) && horizontal[x].checkNumber(num) 
		&& box[(y/sqrt_y)*sqrt_x+(x/sqrt_x)].checkNumber(num))
	{
		sudoku[y][x] = num;
		return true;
	}
	return false;
}

bool Sudoku::removeNumber(int y, int x)
{	
	if(!valid_x(x) || !valid_y(y))
		return false;
	
	sudoku[y][x]=0;
	return true;
}
int Sudoku::getNumber(int y, int x)
{
	return (!valid_x(x) || !valid_y(y)) ? 0 : sudoku[y][x];
}

int Sudoku::getHorizontalMax()
{
	return x;
}

int Sudoku::getVerticalMax()
{
	return y;
}

int Sudoku::getMaxValue()
{
	//for now
	return y;
}

bool Sudoku::checkSolved()
{
	for(int i=0; i<y; i++)
		if(!vertical[i].checkSolved())
			return false;
	
	for(int i=0; i<x; i++)
		if(!horizontal[i].checkSolved())
			return false;

	for(int i=0; i<boxes; i++)
		if(!box[i].checkSolved())
			return false;

	return true;
}
