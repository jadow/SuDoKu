#include "Sudoku.h"

#include <stdio.h>

int main()
{
	Sudoku soduku;
	
	soduku.addNumber(0,0,2);
	soduku.addNumber(0,1,9);
	soduku.addNumber(0,2,5);
	soduku.addNumber(0,3,7);
	soduku.addNumber(0,4,4);
	soduku.addNumber(0,5,3);
	soduku.addNumber(0,6,8);
	soduku.addNumber(0,7,6);
	soduku.addNumber(0,8,1);
	
	soduku.addNumber(1,0,4);
	soduku.addNumber(1,1,3);
	soduku.addNumber(1,2,1);
	soduku.addNumber(1,3,8);
	soduku.addNumber(1,4,6);
	soduku.addNumber(1,5,5);
	soduku.addNumber(1,6,9);
	soduku.addNumber(1,7,2);
	soduku.addNumber(1,8,7);
	
	soduku.addNumber(2,0,8);
	soduku.addNumber(2,1,7);
	soduku.addNumber(2,2,6);
	soduku.addNumber(2,3,1);
	soduku.addNumber(2,4,9);
	soduku.addNumber(2,5,2);
	soduku.addNumber(2,6,5);
	soduku.addNumber(2,7,4);
	soduku.addNumber(2,8,3);

	soduku.addNumber(3,0,3);
	soduku.addNumber(3,1,8);
	soduku.addNumber(3,2,7);
	soduku.addNumber(3,3,4);
	soduku.addNumber(3,4,5);
	soduku.addNumber(3,5,9);
	soduku.addNumber(3,6,2);
	soduku.addNumber(3,7,1);
	soduku.addNumber(3,8,6);
	
	soduku.addNumber(4,0,6);
	soduku.addNumber(4,1,1);
	soduku.addNumber(4,2,2);
	soduku.addNumber(4,3,3);
	soduku.addNumber(4,4,8);
	soduku.addNumber(4,5,7);
	soduku.addNumber(4,6,4);
	soduku.addNumber(4,7,9);
	soduku.addNumber(4,8,5);
	
	soduku.addNumber(5,0,5);
	soduku.addNumber(5,1,4);
	soduku.addNumber(5,2,9);
	soduku.addNumber(5,3,2);
	soduku.addNumber(5,4,1);
	soduku.addNumber(5,5,6);
	soduku.addNumber(5,6,7);
	soduku.addNumber(5,7,3);
	soduku.addNumber(5,8,8);

	soduku.addNumber(6,0,7);
	soduku.addNumber(6,1,6);
	soduku.addNumber(6,2,3);
	soduku.addNumber(6,3,5);
	soduku.addNumber(6,4,2);
	soduku.addNumber(6,5,4);
	soduku.addNumber(6,6,1);
	soduku.addNumber(6,7,8);
	soduku.addNumber(6,8,9);
	
	soduku.addNumber(7,0,9);
	soduku.addNumber(7,1,2);
	soduku.addNumber(7,2,8);
	soduku.addNumber(7,3,6);
	soduku.addNumber(7,4,7);
	soduku.addNumber(7,5,1);
	soduku.addNumber(7,6,3);
	soduku.addNumber(7,7,5);
	soduku.addNumber(7,8,4);
	
	soduku.addNumber(8,0,1);
	soduku.addNumber(8,1,5);
	soduku.addNumber(8,2,4);
	soduku.addNumber(8,3,9);
	soduku.addNumber(8,4,3);
	soduku.addNumber(8,5,8);
	soduku.addNumber(8,6,6);
	soduku.addNumber(8,7,7);
	soduku.addNumber(8,8,2);

	soduku.printed();
	
	if(soduku.checkSolved())
		printf("solved\n");
	
	return 0;
}
