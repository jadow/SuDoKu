#include <windows.h>
#include "SudokuController.h"

#define button_size	40
#define xOffset		6
#define yOffset		48

Sudoku_Controller* model;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
	model = new Sudoku_Controller;

    // Register the window class.
    const wchar_t CLASS_NAME[]  = L"Sudoku";
    
    WNDCLASS wc = { };

    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window.

    HMENU hMenubar;
    HMENU hMenu;

    hMenu = CreateMenu();

    AppendMenuW(hMenu, MF_STRING, 0, L"&Solve");
    AppendMenuW(hMenu, MF_STRING, 1, L"&Clear");

    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        L"Learn to Program Windows",    // Window text
        (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX),            // Window style
        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, 
		button_size*model->sudoku.getHorizontalMax()+xOffset, 
		button_size*model->sudoku.getVerticalMax()+yOffset,
        NULL,       // Parent window    
        hMenu,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
        );

    if (hwnd == NULL)
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    // Run the message loop.

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_CREATE:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

			for(int i=0; i<model->sudoku.getHorizontalMax(); i++)
			{
				for(int j=0; j<model->sudoku.getVerticalMax(); j++)
				{
					HWND hwndButton = CreateWindow( 
					L"BUTTON",  // Predefined class; Unicode assumed 
					L"",      // Button text 
					WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
					(button_size*i), (button_size*j), button_size, button_size,
					hwnd,     // Parent window
					NULL,       // No menu.
					(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), 
					NULL);      // Pointer not needed.
				}
			}

            EndPaint(hwnd, &ps);
        }
        return 0;

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}