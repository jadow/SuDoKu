#include "SudokuInterface.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
	model = new Sudoku_Controller();
    HMENU hMenu = createMenu();

    WNDCLASS wc = { };

    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;
	wc.hbrBackground = getBackGroundColour();

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        CLASS_NAME,						// Window text
        (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX),            // Window style
        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, 
		getWidth(), 
		getHeight(),
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
            s_hFont = setFont(hdc);

			for(int i=0; i<model->totalBoxes(); i++)
			{
				HWND hwndButton = CreateWindow( 
				L"BUTTON",  
				L"",     
				WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,  
				getOffset(getHorizontalPos(i)), getOffset(getVerticalPos(i)), 
				button_size, button_size,
				hwnd, 
				(HMENU)(IDC_BUTTON_0+i),       
				(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), 
				NULL);  

				if(s_hFont)
					SendMessage(hwndButton, WM_SETFONT, (WPARAM)s_hFont, (LPARAM)MAKELONG(TRUE, 0));
			}

            EndPaint(hwnd, &ps);
        }
        return 0;

	case WM_COMMAND:
		{
			switch (LOWORD(wParam)) 
			{
			case IDC_SOLVE:
				{
					currentHWND = hwnd;
					if(model->trySolveBackTrack(updateButton))
						/*for(int i=0; i<model->totalBoxes(); i++)
								SendMessage(GetDlgItem(hwnd, IDC_BUTTON_0+i), WM_SETTEXT, 0, 
								(LPARAM)convertNumberWstring(model->getBoxValue(getHorizontalPos(i), getVerticalPos(i))));*/

					return 0;
				}

			case IDC_CLEAR:
				{
					model->clearAll();
					for(int i=0; i<model->totalBoxes(); i++)
						SendMessage(GetDlgItem(hwnd, IDC_BUTTON_0+i), WM_SETTEXT, 0, (LPARAM)L"");

					return 0;
				}

			default: //buttons
				{
					int y = getVerticalPos(wParam - IDC_BUTTON_0);
					int x = getHorizontalPos(wParam - IDC_BUTTON_0);
					model->incrementBox(y, x); 
					currentHWND = hwnd;
					updateButton(y, x);

					return 0;
				}
			}
		}
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}