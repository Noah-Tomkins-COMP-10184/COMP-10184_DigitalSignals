/**
 * I, Noah Tomkins, 0000790079 certify that this material is my original work.
 * No other person's work has been used without due acknowledgement.
 */

#include <Arduino.h>

/**
 * Debounce code referenced from:
 * https://forum.arduino.cc/t/using-momentary-push-button-as-toggle/214213/3
 * Post #5 by user: tf68
 */

const uint32_t debounceTime = 5;
const bool switchOn  = false;
const bool switchOff = true;

bool lastState   = switchOff;
bool newState    = switchOff;
bool toggleState = false;

void setup() {
  Serial.begin(115200);

  pinMode(D5, INPUT_PULLUP);
  pinMode(D4, OUTPUT);

  analogWriteRange(1023);
}

void loop() {
    int potValue = analogRead(A0);
    newState = digitalRead(D5);

    if (lastState != newState) {
        delay(debounceTime);
        lastState = newState;

        if (newState == switchOn && toggleState == false)
            toggleState = true;
        else if (newState == switchOn && toggleState == true)
            toggleState = false;
    }

    if (toggleState)
        analogWrite(D4, potValue);
    else
        digitalWrite(D4, 1); // 1 seems to be off, don't know why but it works

    Serial.println("toggleState: " + String(toggleState));
}