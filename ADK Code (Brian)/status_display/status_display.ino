#include "display.h"
#include "text.h"

#define MAX_MESSAGES          50
#define MESSAGE_LEN           200
#define EVENTS_TIMEOUT        20
#define OFFICEHOURS_TIMEOUT   30

// bytes we may receive from the phone
#define SWIPE_UP        201
#define SWIPE_RIGHT     202
#define SWIPE_LEFT      203

typedef struct {
   char messages[MAX_MESSAGES][MESSAGE_LEN];
   int current;
   int total;
   int timeout;
} DisplayState;
static DisplayState events;
static DisplayState officeHours;
static DisplayState *state;
static int waiting_for_ACK = 0;
static int transition = 0;


void sendCurrentMessage()
{
   if (!state->total)
      // nothing to send
      return;
   clearBox(0, 24, 31, 31); // clear the line
   chprintf(0, 24, "%d/%d", state->current+1, state->total);
   
   int len = 0;
   char *msg = state->messages[state->current];
   while (msg[len]) len++; // get msg len
   len++; // include null byte

   Serial3.write(0x0c);
   Serial3.write(transition);
   Serial3.write(len-1);
   
   uint8_t crc = 0;
   int i;
   for (i = 0; i < len; i++)
   {
      crc ^= msg[i];
      Serial3.write(msg[i]);
   }
   Serial3.write(crc);
}

void sendOffset(int offset)
{
   Serial3.write(0x0e);
   // write offset twice for error checking
   Serial3.write(offset);
   Serial3.write(offset);
}

void swipeLeft()
{
   state->current++;
   if (state->current >= state->total)
      state->current = 0;
   transition = 203;
   elapsed_seconds = 0;
}

void swipeRight()
{
   state->current--;
   if (state->current < 0)
      state->current = state->total-1;
   transition = 202;
   elapsed_seconds = 0;
}

void swipeUp()
{
   // switch the state
   if (state == &events)
      state = &officeHours;
   else if (state == &officeHours)
      state = &events;

   // transition to first message of new state
   state->current = 0;
   transition = 201;
   elapsed_seconds = 0;
}

void setup() {
   initializeDisplay();

   drawLogo();
   Serial.begin(57600);
   Serial1.begin(9600);
   Serial3.begin(1200); // Serial3 was dropping bytes randomly at any higher baud rates
   Serial2.begin(9600);
   Serial3.write(0x0c);
   Serial3.write(0x01);
   Serial3.write(0x17);
   
   events.current = 0;
   events.total = 0;
   events.timeout = EVENTS_TIMEOUT;
   officeHours.current = 0;
   officeHours.total = 0;
   officeHours.timeout = OFFICEHOURS_TIMEOUT;
   state = &events;
   
   int offset = -1;
   int prev_elapsed_seconds = 0;
   int msgChanged = 0;
   while (1)
   {
      // check for new data from desktop application
      if (checkSerial2())
      {
         msgChanged = 1;
      }
      
      // check for polls from main display
      int start_time = elapsed_seconds;
      if (Serial3.available())
      {
         char c = Serial3.read();
         Serial.print("Changed?: ");
         Serial.print(msgChanged);
         Serial.print("  Offset:");
         Serial.print(offset);
         Serial.print("  Byte:");
         Serial.println(c);
         if (c == 'F' || msgChanged)
         {
            sendCurrentMessage();
            msgChanged = 0;
         }
         else if (c == 'U' && offset >= 0)
         {
            sendOffset(offset);
            offset = -1;
         }
      }
      elapsed_seconds = start_time;
      
      // check for new data from the phone
      if (Serial1.available())
      {
         int byte = Serial1.read();
         Serial.print("New Serial1 Data: ");
         Serial.println(byte);
         offset = -1;
         switch (byte)
         {
         case SWIPE_UP:
            swipeUp();
            msgChanged = 1;
            break;
         case SWIPE_LEFT:
            swipeLeft();
            msgChanged = 1;
            break;
         case SWIPE_RIGHT:
            swipeRight();
            msgChanged = 1;
            break;
         case 0xFE:
            displayOff();
            Serial3.write(0xFE);
            break;
         case 0xFF:
            displayOn();
            Serial3.write(0xFF);
            break;
         default:
            offset = byte;
            break;
         }
      }
      
      // show elapsed seconds if it's not already shown
      if (elapsed_seconds != prev_elapsed_seconds)
      {
         clearBox(0, 16, 31, 23); // clear the line
         chprintf(0, 16, "%d", elapsed_seconds);
         prev_elapsed_seconds = elapsed_seconds;
      }
      
      // check if the current message has timed out
      if (elapsed_seconds >= state->timeout)
      {
         msgChanged = 1;
         if (state == &events)
         {
            // go to the next message
            swipeLeft();
         }
         else if (state == &officeHours)
         {
            // go back to events mode
            swipeUp();
         }
      }
   }
}

int type = 0;
int char_count = 0;
DisplayState *updateState = NULL;
int checkSerial2()
{
   char c;
   int retVal = 0;
   while (Serial2.available() > 0)
   {
      c = Serial2.read();
      if (c == -1)
      {
         // error, do nothing
      }
      else if (!updateState)
      {
         // start byte
         if (c == 'O')
            updateState = &officeHours;
         else if (c == 'E')
            updateState = &events;
         else
            break;
         updateState->total = 0;
         char_count = 0;
      }
      else if (c == 0)
      {
         updateState->messages[updateState->total++][char_count++] = 0;
         char_count = 0;
      }
      else if (c == 0x17) 
      {
         // stop byte
         state = &events;
         state->current = 0;
         updateState = NULL;
         elapsed_seconds = 0;
         retVal = 1;
      }
      else
      {
         updateState->messages[updateState->total][char_count++] = c;
      }
   }
   return retVal;
}

// will never enter this function, but must be defined
// we just do everyting in setup()
void loop() {}