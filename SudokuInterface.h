#ifndef _SUDOKU_INTERFACE_H_
#define _SUDOKU_INTERFACE_H_

#include <windows.h>
#include "SudokuController.h"

#define button_size	40
#define xOffset		6
#define yOffset		48

Sudoku_Controller* model;
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

#endif //_SUDOKU_INTERFACE_H_