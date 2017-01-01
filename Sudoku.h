#ifndef _SUDOKU_HEADER_
#include <vector>

class section
{
	std::vector<int*> members;
	int solved;
public:
	section(std::vector<int*> target);
	section();
	bool checkNumber(int num);
	bool checkSolved();
};

class Sudoku 
{
private:
	std::vector<std::vector<int> > sudoku;

	std::vector<section> vertical;
	std::vector<section> horizontal;
	std::vector<section> box;

	int x, y, boxes, sqrt_x, sqrt_y;

	void init();
	void initVertical();
	void initHorizontal();
	void initBoxes();

	bool valid_x(int x);
	bool valid_y(int y);
	bool valid_num(int num);

public:
	Sudoku(int size);		//size * size
	Sudoku();				//9 * 9

	bool addNumber(int y, int x, int num);
	bool removeNumber(int y, int x);
	int getNumber(int y, int x);
	int getHorizontalMax();
	int getVerticalMax();
	bool checkSolved();

	void printed();
};

#define _SUDOKU_HEADER_
#endif //_SUDOKU_HEADER_

