#ifndef _SUDOKU_INTERFACE_H_
#define _SUDOKU_INTERFACE_H_

#include <windows.h>
#include "SudokuController.h"
#include "resource.h"

#define MAX_SIZE	255
#define button_size	40
#define xOffset		6
#define yOffset		48
#define spacing		3

const wchar_t CLASS_NAME[]  = L"Sudoku";
const wchar_t* fontName = L"Croobie";
const long nFontSize = 30;
static HFONT s_hFont = NULL;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

class SudokuInterface 
{
public:
	Sudoku_Controller* model;
	HWND currentHWND;
	WPARAM currentWPARAM;

	int MaxVertical;
	int MaxHorizontal;
	int boxes;
	int MaxValue;
	int rootValue;
	
	void Init()
	{
		MaxVertical = model->sudoku.getVerticalMax();
		MaxHorizontal = model->sudoku.getHorizontalMax();
		boxes = MaxVertical * MaxHorizontal;
		MaxValue = model->sudoku.getMaxValue();
		rootValue = model->sudoku.getRootValue();
		currentHWND = NULL;
		currentWPARAM = NULL;
	}

	SudokuInterface()
	{
		model = new Sudoku_Controller;
		Init();
	}

	SudokuInterface(int size)
	{
		model = new Sudoku_Controller(size);
		Init();
	}

	static wchar_t* convertNumberWstring(int i)
	{
		wchar_t* tempt = new wchar_t[MAX_SIZE];
		wsprintf(tempt, L"%d", i);
		return tempt;
	}

	static HBRUSH getBackGroundColour()
	{
		return (HBRUSH)GetStockObject(BLACK_BRUSH);
	}

	static HMENU createMenu()
	{
		HMENU hMenu;
		hMenu = CreateMenu();
		AppendMenuW(hMenu, MF_STRING, IDC_SOLVE, L"&Solve");
		AppendMenuW(hMenu, MF_STRING, IDC_CLEAR, L"&Clear");
		return hMenu;
	}

	static HFONT setFont( HDC hdc)
	{
		LOGFONT logFont = {0};
		logFont.lfHeight = -MulDiv(nFontSize, GetDeviceCaps(hdc, LOGPIXELSY), 72);
		logFont.lfWeight = FW_BOLD;
		wcscpy(logFont.lfFaceName, fontName);
		return CreateFontIndirect(&logFont);
	}

	void updateButton(HWND hwnd, WPARAM wParam, int y, int x)
	{
		if(!model->sudoku.getNumber(y ,x))
			SendMessage(::GetDlgItem(hwnd, wParam), WM_SETTEXT, 0, (LPARAM)L"");				 
		else
			SendMessage(::GetDlgItem(hwnd, wParam), WM_SETTEXT, 0, (LPARAM)convertNumberWstring(model->sudoku.getNumber(y ,x)));
	}

	int getPosition(int i)
	{
		return i*button_size + ((i/3)+1)*spacing;
	}

	int getHeight()
	{
		return getPosition(model->sudoku.getVerticalMax())+yOffset;
	}

	int getWidth()
	{
		return getPosition(model->sudoku.getHorizontalMax())+xOffset;
	}
};

SudokuInterface* ViewHelper;



#endif //_SUDOKU_INTERFACE_H_