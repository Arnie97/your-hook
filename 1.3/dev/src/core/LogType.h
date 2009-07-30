/**
  * @file LogType.h
  * @author Daniel Amodio
  * @date July 22, 2009
  * @class LogType
  *
  * The LogType class will be a pure virtual (abstract) class
  * to use as a base for different log types (LOCAL_FILE, DEBUG, etc)
  * The constructor and destructor will be used for startup and shutdown code
  * and the log() function will handle any logged data
  */
#ifndef LOGTYPE_H

/**
  * Definition to handle names of log types
  */
typedef int LogTypeName;

/**
  * Names for different ways to log data
  */
enum
{
      DEBUG,
      LOCAL_FILE
};

class LogType
{
public:
       
       /**
         * Method that will add data to the log
         * @param data Data to add to the log
         */
       virtual void log(char* data) = 0;
       
       /**
         * Method to allow log types to utilize timers
         */
       virtual void step() = 0;
       
private:

};


#define LOGTYPE_H
#endif
