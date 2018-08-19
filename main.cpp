#pragma hdrstop
#pragma argsused

#ifdef _WIN32
#include <tchar.h>
#else
  typedef char _TCHAR;
  #define _tmain main
#endif

#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <string>
#include <ctime>
#include "boost/date_time/gregorian/gregorian.hpp"

void print_usage(char *progname)
{
  std::string prog = std::string(progname);
  prog = prog.substr( prog.find_last_of("\\") + 1);

  std::cout << "Usage: " << prog << " [+-]days" << "\n";
  std::cout << "example: \"" << prog << " -10\" will set the date to current datem minus 10 days." << "\n";
}

int _tmain(int argc, _TCHAR* argv[])
{

  if (argc < 2)
  {
    print_usage(argv[0]);
    return 0;
  }

  int days_to_change = 0;

  try
  {
   days_to_change  = std::abs( std::stoi(argv[1]) );
  }
  catch (...)
  {
    std::cout << "invalid integer value: [" << argv[1] << "]\n";
    print_usage(argv[0]);
    return 0;
  }

  //time_t today = time(NULL);
  //tm tm_today = {};
  //tm_today = *localtime(&today);
  //boost::gregorian::day_iterator dayIt( boost::gregorian::date_from_tm(tm_today), days_to_change );
  boost::gregorian::day_iterator dayIt( boost::gregorian::day_clock::local_day(), days_to_change );

  std::cout << "Current date: " << boost::gregorian::to_iso_string(*dayIt) << "\n";
  if (argv[1][0] == '-')
    --dayIt;
  else
    ++dayIt;


  SYSTEMTIME winSysTime;
  GetSystemTime(&winSysTime);

  winSysTime.wYear = dayIt->year();
  winSysTime.wMonth = dayIt->month();
  winSysTime.wDay = dayIt->day();

  if ( SetSystemTime(&winSysTime) != 0)
  {
    std::cout << "New date: " << boost::gregorian::to_iso_string(*dayIt) << "\n";
  }
  else
  {
    std::cout << "Could not change date! Do you have admin rights?" << "\n";
  }

  return 0;
}
