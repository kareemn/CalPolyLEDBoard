#include "text.h"
#include "display.h"

#define BUFFER_SIZE  1024
#define POLL_INTERVAL   10     // 100ms
#define RECV_TIMEOUT    50    // 500ms

#define ASSERT_RECV_BYTE(b) if(b<0) return 0

void setup()
{
   // Serial3 was dropping bytes randomly at any higher baud rates
   Serial3.begin(1200);
   Serial.begin(57600);
   initializeDisplay();
	
   unsigned long nextUpdate = 0;
   char pollByte = 'F';
	while(1)
	{
      if (ticks >= nextUpdate)
      {
         Serial3.write(pollByte); // send poll
         nextUpdate = ticks + POLL_INTERVAL;
      }
      
      // check for incoming data
      if (Serial3.available())
      {
         if (readIncomingMessage())
         {
            // message updated successfully
            pollByte = 'U';
         }
         else
         {
            // error updating
            pollByte = 'F';
         }
      }
	}
}

// will perform a blocking read on Serial3 with a timeout
int serial3ReadTimeout()
{
   int startTime = ticks;
   while (ticks-startTime < RECV_TIMEOUT)
   {
      if (Serial3.available())
      {
         return Serial3.read();
      }
   }
   return -1;
}

static char currentMsg[BUFFER_SIZE];
int readIncomingMessage()
{
	char prevMsg[BUFFER_SIZE];
	int index = 0;
   
   // get the start byte
   int startByte = serial3ReadTimeout();
   ASSERT_RECV_BYTE(startByte);
   
   if (startByte == 0x0c) // new message
   {
      // copy current message into prevMsg and clear currentMsg
      for (index = 0; index < BUFFER_SIZE; index++)
      {
         prevMsg[index] = currentMsg[index];
         currentMsg[index] = 0;
      }
      index = 0;
   
      // get transition byte
      int transition = serial3ReadTimeout();
      ASSERT_RECV_BYTE(transition);
   
      // get length byte
      int length = serial3ReadTimeout();
      ASSERT_RECV_BYTE(length);
      
      // read the message
      int isDuplicate = 1;
      uint8_t crc = 0;
      while (1)
      {
         int c = serial3ReadTimeout();
         ASSERT_RECV_BYTE(c);
         crc ^= c;
         currentMsg[index] = c;
         if (currentMsg[index] != prevMsg[index])
            // not duplicate message
            isDuplicate = 0;
         if (!c)
            // stop byte
            break;
         index++;
      }
      
      // get crc byte
      int sentCRC = serial3ReadTimeout();
      ASSERT_RECV_BYTE(sentCRC);
      
      Serial.print(length);
      Serial.print(" ");
      Serial.println(index);
      
      if (index != length)
         return 0;
      
      // got the same message, don't do anything
      if (isDuplicate)
         return 1;
      
      Serial.print("Index: ");
      Serial.println(index-1);
      Serial.print("Prev: ");
      Serial.println(prevMsg);
      Serial.print("Current: ");
      Serial.println(currentMsg);
      
      if (transition == 202)
      {
         transitionRight(1, 2, prevMsg);
         transitionRight(-320, 2, currentMsg);
         delay(100);
      }
      else if (transition == 203)
      {
         transitionLeft(1, 2, prevMsg);
         transitionLeft(321, 2, currentMsg);
         delay(100);
      }
      else if (transition == 201)
      {
         transitionUp(1, 2, prevMsg);
         delay(100);
         transitionUp(1, 33, currentMsg);
         delay(100);
      }
      else
      {
         // no transtion
         clearDisplay();
         writeDisplay(1, 2, currentMsg);
      }
   }
   else if (startByte == 0x0e)
   {
      // new offset for previous message
      
      // get offset byte twice (for error checking)
      int offset1 = serial3ReadTimeout();
      ASSERT_RECV_BYTE(offset1);
      int offset2 = serial3ReadTimeout();
      ASSERT_RECV_BYTE(offset2);
      if (offset1 != offset2)
         return 1;
      
      clearDisplay();
      writeDisplay(1, 2+(offset1*2), prevMsg);
   }
   else if (startByte == 0xFE)
   {
      // turn dislay off
      displayOff();
   }
   else if (startByte == 0xFF)
   {
      // turn dislay on
      displayOn();
   }
   return 1;
}

// will never enter this function, but must be defined
// we just do everyting in setup()
void loop() {}