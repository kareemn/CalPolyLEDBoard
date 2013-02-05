/* Serial.h
 *
 * Class for communication between computer and Xiphos board.
 * NOTE: Ensure the line '#include "Serial.h"' is added to stdafx.h
 */

#include <Windows.h>
#include <stdint.h>

class Serial {

private:
   HANDLE port;

public:
   bool openPort(LPCWSTR name);
   bool go(float x, float z); 
   bool stop();
   void closePort();
};