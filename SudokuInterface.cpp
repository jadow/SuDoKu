#include "SudokuInterface.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
	ViewHelper = new SudokuInterface();
    HMENU hMenu = SudokuInterface::createMenu();

    WNDCLASS wc = { };

    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;
	wc.hbrBackground = SudokuInterface::getBackGroundColour();


    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        CLASS_NAME,						// Window text
        (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX),            // Window style
        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, 
		ViewHelper->getWidth(), 
		ViewHelper->getHeight(),
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
            s_hFont = SudokuInterface::setFont(hdc);

			for(int i=0; i<ViewHelper->MaxHorizontal; i++)
			{
				for(int j=0; j<ViewHelper->MaxVertical; j++)
				{
					HWND hwndButton = CreateWindow( 
					L"BUTTON",  
					L"",     
					WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,  
					ViewHelper->getPosition(i), ViewHelper->getPosition(j), button_size, button_size,
					hwnd,     
					(HMENU)(IDC_BUTTON_0+(i+j*ViewHelper->MaxHorizontal)),       
					(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), 
					NULL);  

					if(s_hFont)
						SendMessage(hwndButton, WM_SETFONT, (WPARAM)s_hFont, (LPARAM)MAKELONG(TRUE, 0));

				}
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
					if(ViewHelper->model->trySolveBackTrack())
					{
						for(int i=0; i<ViewHelper->MaxHorizontal; i++)
						{
							for(int j=0; j<ViewHelper->MaxVertical; j++)
							{
								SendMessage(::GetDlgItem(hwnd, IDC_BUTTON_0+(i+j*ViewHelper->MaxHorizontal)), 
									WM_SETTEXT, 0, (LPARAM)ViewHelper->convertNumberWstring(ViewHelper->model->sudoku.getNumber(j,i)));
							}
						}	
					}
					return 0;
				}

			case IDC_CLEAR:
				{
					ViewHelper->model->clearAll();
					for(int i=0; i<ViewHelper->boxes; i++)
						SendMessage(GetDlgItem(hwnd, IDC_BUTTON_0+i), WM_SETTEXT, 0, (LPARAM)L"");

					return 0;
				}

			default: //buttons
				{
					int tempt = wParam - IDC_BUTTON_0;
					int y = tempt/ViewHelper->MaxHorizontal;
					int x = tempt%ViewHelper->MaxHorizontal;
					ViewHelper->model->incrementBox(y, x); 
					ViewHelper->updateButton(hwnd, wParam, y, x);

					return 0;
				}
			}
		}
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}