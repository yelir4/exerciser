/*
    main.cpp
    exerciser
    g++ main.cpp -o exerciser -DUNICODE -lgdi32
*/

// there's limitations with other implementations i've seen...
// or at least i couldn't get it figured out on my end or in making more customizations
// so the way that i can imagine implementing it now is such that i treat this file as the main file
// as WinMain acts as a main function ...
// that's okay though i can link other .cpp, .h files to this, no problem
// i know how to do that ... rather effectively i may even say

// include the workout.h header file (and subsequently the windows api)
#include "workout.h"

// mwah mwah beautiful you
using namespace exerciser;

// declare windows procedure
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

// declare window handles for subwindows
// textField and button
HWND textField, button;
HWND textBox;

// note the strings passed in include a null empty character
// example if the box says "hello world" and your max is 5
// then you will have "hell" with a \0 attached obviously
const int maxChars = 10;
wchar_t textSaved[maxChars];
int gwtstat;

// define class name and window title
const wchar_t* szClassName = L"exericser"; // wide char* because dealing with winapi / note the 'L'
const wchar_t* szTitleName = L"window";


// main function as defined by WINAPI
int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nCmdShow)
{
    HWND hwnd;              // define window handle
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
    wincl.hbrBackground = CreateSolidBrush(RGB(120,120,192)); // = (HBRUSH) COLOR_BACKGROUND;

    // register window class as defined above, quit program if failure
    if(!RegisterClassEx (&wincl))
    {
        return 0;
    }

    // window styles documentation
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

    // show the window "hwnd" that we just defined
    ShowWindow (hwnd, nCmdShow);

    // while there are messages to process
    while (GetMessage (&messages, NULL, 0, 0))
    {
        // translate virtual key messages into character messages
        TranslateMessage(&messages);
        // send message to WindowProcedure
        DispatchMessage(&messages);
    }

    // the program return value is 0, given by PostQuitMessage (0)
    return messages.wParam;
}

// message handler of program
// called by the windows function DispatchMessage()
// actions in programs go here (create buttons, elements)
// braces inside switches are optional but they allow you to declare local variables within the switch
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // switch for the message passed by window handle "hwnd"
    switch (message)
    {
        // case: on creation of main window "hwnd"
        case WM_CREATE:
        {
            // initialize text field window handle (declared at top of document)
            textField = CreateWindow(
                                    L"STATIC", // keyword static class, note the L
                                    L"wowww i love it", // text goes into the box
                                    WS_VISIBLE | WS_CHILD | WS_BORDER | WS_SIZEBOX, // WS_VISIBLE makes this window immediately visible
                                    20, // position x, y
                                    20,
                                    60, // width, height
                                    40,
                                    hwnd, // parent window (hwnd in this case, because that window passed the message)
                                    NULL, // hMenu
                                    NULL, // hInstance
                                    NULL // lpParam
                                );

            // initialize button window handle (as declared at top of document)
            button = CreateWindow(
                                    L"BUTTON", // keyword button class
                                    L"click me", // text goes into the button
                                    WS_VISIBLE | WS_CHILD | WS_BORDER,
                                    50,
                                    50,
                                    500,
                                    25,
                                    hwnd,
                                    (HMENU) 1,  // button parameter (typecasts 1 to HMENU)
                                    NULL,
                                    NULL
                                );

            textBox = CreateWindow(
                                    L"EDIT", // keyword textBox class
                                    L"changable text bosx",
                                    WS_VISIBLE | WS_CHILD | WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL, // es_multiline fixes scrolling and makes it sclolable
                                    100, // box dimensions
                                    300,
                                    200,
                                    100,
                                    hwnd, // parent
                                    NULL,
                                    NULL,
                                    NULL
                                );
            
            break;
        }
        
        // case: message is a COMMAND or any other action (ex: button press)
        case WM_COMMAND:
        {
            // low order words
            switch(LOWORD(wParam))
            {
                // any unique number, corresponds to BUTTON PARAMETER as seen above
                // in this case "CASE 1" because above button parameter is 1
                case 1:
                {
                    // currently doesn't work because it's not registered in the volume mixer ?
                    ::MessageBeep(MB_OK);
                    
                    // this is how a standard message box would work, should i want one
                    // parent, text inside, title text, ok button (documentation somewhere)
                    //::MessageBox(hwnd, L"Button was clicked", L"yip", MB_OK);

                    // change textField's window text
                    // note we can change textField here because it's scope is outside this function (see top of document)
                    SetWindowText (textField, L"its good practice not to download and run people's\
                                                programs on the internet. lucky for you i am not smart\
                                                enough to figure out how to hack and kil your computer");

                    // gwtstat holds the number of characters copied by GetWindowText
                    // 0 if error (nothing was copy / couldnt be copied)
                    // otherwise returns number of characters copied
                    // GetWindowText, takes maxChars of characters from the text box and saves it into "textBox"
                    // maybe it will have to be maxChars-1? will have to see ...
                    gwtstat = GetWindowText (textBox, textSaved, maxChars);


                    rep penssi(textSaved, 100);

                    // see if we edid this rights
                    // this is also a good way to see if things i do work
                    ::MessageBox(hwnd, textSaved, textSaved, MB_OK);

                    // SetWindowPos documentation
                    // https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-setwindowpos
                    // change textField's window position
                    SetWindowPos (textField, HWND_TOP, 20,20,500,200, SWP_SHOWWINDOW);
                    break;
                }
                case 2:
                    PostQuitMessage (0);
            }
            break;
        }

        // case: closing window (x button pressed)
        case WM_DESTROY:
        {
            PostQuitMessage (0);        // send WM_QUIT to message queue (closes window, ends process)
            break;
        }

        // case: window closed in some other unknown way (task manager or through alt-tab)
        case WM_CLOSE:
        {
            PostQuitMessage (0);
            break;
        }

        // case: returning default windows procedure
        // dedicated to messages that we don't deal with
        default:
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
