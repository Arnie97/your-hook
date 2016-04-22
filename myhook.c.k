#include <stdbool.h>
#include <stdio.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <mmsystem.h>
#define play(file) PlaySound(file ".wav", NULL, SND_FILENAME | SND_ASYNC)

static bool scroll_toggled


int click(bool right_click, unsigned times):
    INPUT mouse_up = {
        .type = INPUT_MOUSE,
        .mi.dwFlags = right_click? MOUSEEVENTF_RIGHTUP: MOUSEEVENTF_LEFTUP
    }, mouse_down = {
        .type = INPUT_MOUSE,
        .mi.dwFlags = right_click? MOUSEEVENTF_RIGHTDOWN: MOUSEEVENTF_LEFTDOWN
    }
    for int i = 0; i < times; i++:
        SendInput(1, &mouse_down, sizeof mouse_down)
        SendInput(1, &mouse_up, sizeof mouse_up)


LRESULT CALLBACK LowLevelMouseProc(int nCode, WPARAM wParam, LPARAM lParam):
    static bool working
    if (
        // Prevent recursion
        !working &&
        // Scroll lock is enabled
        scroll_toggled &&
        // Mouse is being clicked
        (wParam == WM_LBUTTONUP || wParam == WM_RBUTTONUP)
    ):
        puts(wParam == WM_RBUTTONUP? "[R]": "[L]"), play("gcrafire")

        // Set the recursion flag
        working = true
        // 30 clicks in total, including the original one
        click(wParam == WM_RBUTTONUP, 30 - 1)
        working = false

    return CallNextHookEx(NULL, nCode, wParam, lParam)


LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam):
    if (
        // Scroll lock was pressed, and is being released
        wParam == WM_KEYUP &&
        ((KBDLLHOOKSTRUCT *)lParam)->vkCode == VK_SCROLL &&

        // And the status of scroll lock is changed
        scroll_toggled != GetKeyState(VK_SCROLL) & 0x0001
    ):
        scroll_toggled = !scroll_toggled

        // Scroll lock is being turned on
        if scroll_toggled:
            puts("Who's your daddy"), play("iseased")

        // Scroll lock is being turned off
        else:
            puts("Happy birthday"), play("icraata")

    return CallNextHookEx(NULL, nCode, wParam, lParam)


int main(void):
    // Retrieve the applications instance
    HINSTANCE app_instance = GetModuleHandle(NULL)

    // Set global hooks to capture keystrokes and mouse clicks
    HHOOK mouse_hook = SetWindowsHookEx(
        WH_MOUSE_LL, LowLevelMouseProc, app_instance, 0
    ), keyboard_hook = SetWindowsHookEx(
        WH_KEYBOARD_LL, LowLevelKeyboardProc, app_instance, 0
    )
    puts("Conscript reporting"), play("iconsec")

    // Message loop
    MSG msg
    while GetMessage(&msg, NULL, 0, 0) > 0:
        TranslateMessage(&msg)
        DispatchMessage(&msg)

    // Remove hooks and exit
    UnhookWindowsHookEx(mouse_hook)
    UnhookWindowsHookEx(keyboard_hook)
    return 0
