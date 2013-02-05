// SerialTest4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>


int _tmain(int argc, _TCHAR* argv[])
{

   Serial ser;
   if (!ser.openPort(TEXT("COM3")))
      exit(-1);

   if (!ser.go('h', 'i'))
      OutputDebugString(TEXT("Failed to send"));

   ser.closePort();

   return 0;
}

