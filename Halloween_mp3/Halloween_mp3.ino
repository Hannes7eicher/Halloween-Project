#include "thingProperties.h"
#include "DFRobotDFPlayerMini.h"
#include <Modulino.h>

#define MP3_SERIAL Serial1

ModulinoPixels leds;
ModulinoDistance distance;
DFRobotDFPlayerMini player;

int idleBrightness = 50;       // Constant brightness when idle
int animationBrightness = 255; // Maximum brightness for the animation
bool hasPlayed = false;        // Flag to track if the sound has played
unsigned long soundStartTime = 0; // To track when the sound starts
unsigned long eyeStartTime = 0; // To track when the pulsing starts
bool pulsing = false;          // Flag to track if the eyes are currently pulsing

// Timing intervals
const unsigned long soundDuration = 5000; // Duration of the sound in milliseconds
const unsigned long checkInterval = 100; // Interval for checking the distance sensor
const unsigned long pulseInterval = 5;   // Interval for changing the brightness during the pulse

unsigned long lastCheckTime = 0;
unsigned long lastPlayTime = 0; // to track when `hasPlayed` was last set

int brightnessDirection = 5;    // Variable to track whether brightness is increasing or decreasing
int currentBrightness = 50;     // Ensure initial brightness matches idle brightness

// Function to set "angry eyes" pattern
void angryEyes(ModulinoColor color, int brightness) {
  // Assuming pixels 0-3 form one "eye" and 4-7 form the other "eye"
  for (int i = 0; i < 4; i++) {
    setPixel(i, color, brightness);   // Set the first eye
    setPixel(i + 4, color, brightness); // Set the second eye
  }
  leds.show();
}

void setPixel(int pixel, ModulinoColor color, int brightness) {
  leds.set(pixel, color, brightness);
}

// Play the specified track
void scarePeople(unsigned long currentTime) {
  hasPlayed = true;                    // Set the flag so it doesn't play again immediately
  lastPlayTime = currentTime;          // Record the time when it was last played
  soundStartTime = currentTime;        // Record the time when the sound starts
  eyeStartTime = currentTime;          // Record the time when the pulsing starts
  pulsing = true;                      // Start pulsing the eyes
  player.play(laugh_sound);            // Play the specified track
  people_scared++;                     // Update count of scared people
  Serial.println("Laughter track and pulsing started");
}

void setup() {
  Serial.begin(9600);
  MP3_SERIAL.begin(9600); // DFPlayer Mini expected baud rate

  delay(1500);
  initProperties(); // Initialize properties for ArduinoIoTCloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();

  Modulino.begin();
  distance.begin();
  leds.begin();

  if (player.begin(MP3_SERIAL)) {
    Serial.println("OK");
    player.volume(30);
  } else {
    Serial.println("Connecting to DFPlayer Mini failed!");
  }

  // Set eyes to idle brightness when starting
  angryEyes(RED, idleBrightness);
}

void loop() {
  ArduinoCloud.update();
  
  unsigned long currentTime = millis();

  // Check distance sensor periodically
  if (currentTime - lastCheckTime >= checkInterval) {
    lastCheckTime = currentTime;

    if (distance.available()) {
      int measure = distance.get();
      Serial.println(measure);

      // Play animation only if within the range or if triggered by cloud, and not already played recently
      if ((measure > 0 && measure < 100 && !hasPlayed) || (laugh_trigger && !hasPlayed)) {
        scarePeople(currentTime);

        // Reset the trigger after activation, notify the cloud
        laugh_trigger = false;
      }
    } else {
      Serial.println("Distance sensor not available");
    }
  }

  // Reset the flag based on timer
  if (hasPlayed && currentTime - lastPlayTime >= 5000) { // Reset after 5 seconds
    hasPlayed = false;
    Serial.println("Flag hasPlayed reset after 5 seconds");
  }

  // Check if pulsing is active
  if (pulsing) {
    // Check if the sound should stop
    if (currentTime - soundStartTime >= soundDuration) {
      pulsing = false;  // Stop pulsing after sound finishes
      Serial.println("Pulsing stopped after sound duration");
    }
    
    // Handle the pulsing effect non-blocking
    if (currentTime - eyeStartTime >= pulseInterval) {
      eyeStartTime = currentTime;  // Reset the eye timing for the next pulse
      
      currentBrightness += brightnessDirection;  // Adjust brightness
      if (currentBrightness <= 0 || currentBrightness >= animationBrightness) {
        brightnessDirection = -brightnessDirection;  // Reverse direction at boundaries
      }
      
      angryEyes(RED, currentBrightness);  // Apply the brightness
      Serial.println("Pulsing brightness adjusted: " + String(currentBrightness));
    }
  } else if (currentBrightness != idleBrightness) {
    // Ensure that the eyes stay at idle brightness when not pulsing
    currentBrightness = idleBrightness;
    angryEyes(RED, idleBrightness);
    Serial.println("Set eyes to idle brightness");
  }
}

// Cloud Variable Update Callback
void onLaughTriggerChange() {
  Serial.println("Laugh trigger activated via Cloud");
  scarePeople(millis()); // Pass current time and use laugh_sound
}

void onLaughingChange()  {}
void onLaughChange()  {}
void onAnimationChange()  {}
void onLaughSoundChange()  {}