/* Serial.cpp
 * Class for communication between computer and Xiphos board.
 *
 */
#include "StdAfx.h"
#include "Serial.h"

/* Pass in com port. ex- "COM2"
 * Note: when calling openPort, wrap the name string in the TEXT() macro
 * ex- openPort(TEXT("COM2"));
 * Returns true if port successfully opened
 */
bool Serial::openPort(LPCWSTR name) {

	// opens connection
	port = CreateFile(name, GENERIC_WRITE, 0, 0, OPEN_EXISTING,
	 FILE_ATTRIBUTE_NORMAL, 0);
   
   // error checking
	if (port == INVALID_HANDLE_VALUE) 
      return false;

   // create port setting struct
   DCB dcb = {0};
   dcb.DCBlength = sizeof(DCB);

   // error checking
   if (!GetCommState(port, &dcb))
       return false;

   // define port settings
   dcb.BaudRate = CBR_57600;
   dcb.ByteSize = 8;
   dcb.StopBits = ONESTOPBIT;
   dcb.Parity = NOPARITY;
  
   // more error checking
   if (!SetCommState(port, &dcb)) 
      return false;
  
   return true;
}

bool Serial::go(float x, float z) {

   uint8_t xx, zz;
   xx = (uint8_t)127.5*(x+1);
   zz = (uint8_t)63.75*z;

   // 43 = start code for xiphos
   char buf[4] = {43, xx, zz, '\0'};
   DWORD byteRd = 0;

   if (!WriteFile(port, buf, 4, &byteRd, NULL))
      return false;
   return true;
}

bool Serial::stop() {

   // 11 = stop code for xiphos
   char buf[2] = {11, '\0'};
   DWORD byteRd = 0;

   if (!WriteFile(port, buf, 2, &byteRd, NULL))
      return false;
   return true;
}

void Serial::closePort() {
   CloseHandle(port);
}