/**
  * @file LocalFile.cpp
  * @author Daniel Amodio
  * @date July 29, 2009
  * @class LocalFile
  *
  * 
  *
  */

#ifndef LOCALFILE_H
  
#include "LogType.h"
#include <stdio.h>

class LocalFile : public LogType
{
    public:
           /**
             * Constructor
             */
           LocalFile()
           {
               file=fopen("log.txt","a+");
               
           }
           
           /**
             * Destructor
             */
             // virtual?not?
           ~LocalFile()
           {
               log("\nSafe Exit");
               fclose(file);
           }
           
           /**
             * Accepts data to log
             */
           virtual void log(char* data)
           {
               fputs(data,file);
           }
           
           /**
             * Allow to use timers
             */
           virtual void step()
           {
               log("Step");  
           }
    private:
            /**
              * Variable to point to output file
              */
            FILE *file;
};

#define LOCALFILE_H
#endif
