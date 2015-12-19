// remote controlled actions, based on http://wp.josh.com/2014/05/01/a-platform-for-casual-encounters/

#include <Arduino.h>
#include <setjmp.h>
#include <ledStrip.h>

// This is the default baud rate for the serial link
#define LININOBAUD 250000
#define SERIALBAUD 115200

// Use the onboard LED
#define LED_PIN 13

#include "ledStrip.h"

// We to use this string to indicate where the command is inside the request string...
// Must match the command string sent by the HTML code
#define COMMAND_PREFIX "COMMAND="
#define COMMAND_PREFIX_LEN (sizeof(COMMAND_PREFIX)-1)

jmp_buf breakPoint;
typedef void (*commandFunction)();

void testInputRuntime();

int nombre_de_lampes;

void debut()
{
    nombre_de_lampes = 60;
    allumer(0,0);
}

void allumer(int lampe, int couleur)
{

  if (couleur == 0) {
    allumer(lampe, 0, 0, 0);
  } else {
    testInputRuntime();
    byte r, g, b;
    if (couleur <= 66) {
      r = 198 - couleur*3; g = couleur*3; b = 0;
    } else if (couleur <= 134) {
      couleur -= 66;
      r = 0; g = 198 - couleur*3; b = couleur*3;
    } else {
      couleur -= 134;
      r = couleur*3; g = 0; b = 198 - couleur*3;
    }
    allumer(lampe, r, g, b);
  }
}

void allumer(int lampe, int rouge, int vert, int bleu)
{
  testInputRuntime();
  if (lampe == 0) {
    for(int i = 0; i < nombre_de_lampes; i++) {
      stripSetRGB(i, rouge,vert,bleu);
      stripUpdate();
    }
  } else if (lampe >= 1 && lampe <= nombre_de_lampes) {
    stripSetRGB(lampe - 1, rouge,vert,bleu);
    stripUpdate();
  }
}

void commandZ() {
  for(int i = 0; i < 60; i++) {
    allumer(i+1, i*3);
  }
  delay(500);
  for(byte i = 1; i < 30; i++) {
    delay(25);
    allumer(i, 0);
    allumer(61-i, 0);
  }
}

commandFunction commands[] = {
  commandZ, // 0
  Gouttes,  // 1 : Christian
  Chenille, // 2 : Christian
  Antoine,  // 3
  Suzie,    // 4
  Laissa,   // 5
  Alice1,   // 6
  Alice2    // 7
};

#define NB_COMMANDS (sizeof(commands) / sizeof(commandFunction))

commandFunction nextCommand = 0;

bool prepareCommand( const char *commandString ) {
  // Use the first byte to specifiy action...

  // we look only at first char
  char cmd = commandString[0];
  // must be in ['0'..'9'] or ['a'..'z'] or ['A'..'Z']
  // reduce it to [0..36]
  if (cmd >= 'a') {
    cmd -= 'a' + 10;
  } else if (cmd >= 'A') {
    cmd -= 'A' + 10;
  } else {
    cmd -= '0';
  }

  if (cmd >= 0 && cmd < NB_COMMANDS) {
    nextCommand = commands[cmd];
    return true;
  }

  Serial.println("Unknown command");
  return false;
}

int readLine(Stream &s, char *buffer, int maxLen) {
  int len = 0;
  while (len < maxLen) {
    int c = s.read();
    if (c == -1 || c == '\n' || c == '\r') {
      *buffer = '\0';
      return len;
    }
    *buffer++ = c;
    len++;
  }
  return len;
}

bool testInput() {
  char commandBuffer[200];

  // Does this look like a command request?
  if (
#ifdef ARDUINO_AVR_YUN
  Serial
#else
  Serial.available()
#endif
      && readLine(Serial, commandBuffer, 200) > 2) {
    Serial.print("Serial ");Serial.println(commandBuffer);
    if (strncmp(commandBuffer, COMMAND_PREFIX, COMMAND_PREFIX_LEN) == 0) {
      return prepareCommand( commandBuffer + COMMAND_PREFIX_LEN);
    }
  }
#ifdef ARDUINO_AVR_YUN
  if (Serial1/*.available()*/ && readLine(Serial1, commandBuffer, 200) > 2) {
    Serial.print("Serial1 ");Serial.println(commandBuffer);
    if (strncmp(commandBuffer, COMMAND_PREFIX, COMMAND_PREFIX_LEN) == 0) {
      return prepareCommand( commandBuffer + COMMAND_PREFIX_LEN);
    }
  }
#endif

  return false;
}

unsigned long nextCall = 0;

void testInputRuntime() {
  if (millis() > nextCall) {
    nextCall = millis() + 1000;
    if (testInput()) {
      longjmp(breakPoint, 1);
    }
  }
}

void setup() {
  Serial.begin(SERIALBAUD); // open serial connection
#ifdef ARDUINO_AVR_YUN
  Serial1.begin(LININOBAUD); // open serial connection to Linino
#endif
  pinMode( LED_PIN, OUTPUT );

  stripInit(60, A0);
  stripUpdate(); // Initializes all to 'off'
  Serial.print("Ready ...");
}

void loop() {
  if (nextCommand == 0) {
    testInput();
  }
  commandFunction todo;
  if (nextCommand == 0) {
    todo = commands[random(0, NB_COMMANDS)];
  } else {
    todo = nextCommand;
  }
  nextCommand = 0;
  if (setjmp(breakPoint) == 0) {
    stripOff();
    todo();
    stripOff();
  }
}

