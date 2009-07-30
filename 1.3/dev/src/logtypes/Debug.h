/**
  * @file Debug.cpp
  * @author Daniel Amodio
  * @date July 27, 2009
  * @class Debug
  *
  * Basic logging to screen, for debugging purposes
  *
  */

#ifndef DEBUG_H
  
#include "LogType.h"
#include <iostream>

class Debug : public LogType
{
    public:
           /**
             * Constructor
             */
           //Debug();
           
           /**
             * Destructor
             */
           //virtual ~Debug();
           
           /**
             * Accepts data to log
             */
           virtual void log(char* data)
           {
               std::cout << data;
           }
           
           /**
             * Allow to use timers
             */
           virtual void step()
           {
               log("Step");  
           }
    private:
};

#define DEBUG_H
#endif
