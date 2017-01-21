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

Sudoku_Controller* model;
HWND currentHWND = NULL;
WPARAM currentWPARAM = NULL;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

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

void updateButton(int y, int x)
{
	if(!model)
		return;
	WPARAM wParam = y*model->getHorizontalMax() + x + IDC_BUTTON_0;
	if(!model->getBoxValue(y ,x))
		SendMessage(::GetDlgItem(currentHWND, wParam), WM_SETTEXT, 0, (LPARAM)L"");				 
	else
		SendMessage(::GetDlgItem(currentHWND, wParam), WM_SETTEXT, 0, (LPARAM)convertNumberWstring(model->getBoxValue(y ,x)));

	Sleep(5);
}

int getOffset(int i)
{
	return (model) ? i*button_size + ((i/model->getRootValue())+1)*spacing : 0;
}

int getHeight()
{
	return (model) ? getOffset(model->getVerticalMax())+yOffset : 0;
}

int getWidth()
{
	return (model) ? getOffset(model->getHorizontalMax())+xOffset : 0;
}

int getVerticalPos(int i)
{
	return  (model) ? i/model->getHorizontalMax() : 0;
}

int getHorizontalPos(int i)
{
	return (model) ? i%model->getHorizontalMax() : 0;
}

#endif //_SUDOKU_INTERFACE_H_