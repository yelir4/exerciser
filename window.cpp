/*
    main.cpp
    exerciser
    g++ main.cpp -o exerciser -DUNICODE
*/
#ifndef WINDOW_CPP
#define WINDOW_CPP

#include <windows.h>

// declare windows procedure
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

HWND textField;

// name class name
const wchar_t* szClassName = L"exericser"; // wide char* because dealing with winapi / note the 'L'
const wchar_t* szTitleName = L"window";


int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nCmdShow)
{
    HWND hwnd;              // window handle
    MSG messages;           // here messages for the application are saved
    WNDCLASSEX wincl;       // datastructure for the windowclass

    // window structure
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;    // function called by windows
    wincl.style = CS_DBLCLKS;               // catch doule clicks
    wincl.cbSize = sizeof (WNDCLASSEX);

    // use default icon, mouse pointer
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;  // no menu
    wincl.cbClsExtra = 0;       // no extra bytes after the window class
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    // register window class as defined above, quit program if failure
    if(!RegisterClassEx (&wincl))
    {
        return 0;
    }

    // window styles
    // https://learn.microsoft.com/en-us/windows/win32/winmsg/window-styles
    // WS_MINIMIZEBOX - ability to minimize window
    // WS_SYSMENU - no resizing window
    hwnd = CreateWindowEx (
        0,                      // extended possibilities for variation
        szClassName,            // class name
        szTitleName,            // title text
                                // window style
        WS_SYSMENU,
        CW_USEDEFAULT,          // windows decides the position (CW_USEDEFAULT)
        CW_USEDEFAULT,          // where the window ends up on the screen
        500,                    // program width, height in pixels
        500,
        HWND_DESKTOP,           // window is child-window to desktop
        NULL,                   // no menu
        hThisInstance,          // program instance handler
        NULL                    // no window creation data
        );

    ShowWindow (hwnd, nCmdShow);


    while (GetMessage (&messages, NULL, 0, 0))
    {
        // translate virtual key messages into character messages
        TranslateMessage(&messages);
        // send message to WindowProcedure
        DispatchMessage(&messages);
    }

    // the program return value is 0- the value that PostQuitMessage() gave
    return messages.wParam;
}

// message handler of program
// called by the windows function DispatchMessage()
// actions in programs go here (create buttons, elements)
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    const wchar_t* classy = L"STATIC"; // must be named static to work
    const wchar_t* blah2 = L"hi there"; // text that goes into the box

    switch (message) // handle message passed by hwnd
    {
        case WM_CREATE: // called when window is created
            textField = CreateWindow(
                                        classy,
                                        blah2,
                                        WS_VISIBLE | WS_CHILD | WS_BORDER | WS_SIZEBOX,
                                        20, // position x, y
                                        20,
                                        60, // width, height
                                        40,
                                        hwnd, // parent window (hWnd passed in by the function in this case)
                                        NULL, // hMenu
                                        NULL, // hInstance
                                        NULL // lpParam
                                    );
            break;
        case WM_DESTROY:                // window is destroyed (x button) (want to quit the application)
            PostQuitMessage (0);        // send WM_QUIT to message queue
            break;
        default:
            // return the default windows procedure
            // handles stuff that we have not defined here
            // probably other cases once we add stuff here
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}

#endif