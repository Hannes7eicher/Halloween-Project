#include "DFRobotDFPlayerMini.h"

// Use hardware serial interface (Serial1)
#define MP3_SERIAL Serial1

// Create the Player object
DFRobotDFPlayerMini player;

void setup() 
{
  Serial.begin(9600);    // For debug output
  MP3_SERIAL.begin(9600); // DFPlayer Mini expected baud rate
  
  if (player.begin(MP3_SERIAL)) 
  {
    Serial.println("OK");

    // Set volume to maximum (0 to 30).
    player.volume(5);  // 30 is very loud
  } 
  else 
  {
    Serial.println("Connecting to DFPlayer Mini failed!");
  }
}

void loop() 
{
  Serial.print("Playing #1 \t");
  player.play(1);
  delay(5000);
}