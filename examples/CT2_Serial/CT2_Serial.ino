// Arduino Current Transformer Library
// https://github.com/JChristensen/CurrentTransformer
// Copyright (C) 2018 by Jack Christensen and licensed under
// GNU GPL v3.0, https://www.gnu.org/licenses/gpl.html
//
// Example sketch to read two current transformers every five seconds
// and print the measurements to Serial.
// Tested with TA17L-03 current transformers (10A max), Arduino Uno,
// Arduino v1.8.5.

#include <CurrentTransformer.h>             // https://github.com/JChristensen/CurrentTransformer
#include <Streaming.h>                      // http://arduiniana.org/libraries/streaming/

const float ctRatio(1000);                  // current transformer winding ratio
const float rBurden(200);                   // current transformer burden resistor value
const float vcc(5.120);                     // adjust to actual value for best accuracy
const uint32_t MS_BETWEEN_SAMPLES(5000);    // milliseconds
const int32_t BAUD_RATE(115200);

CurrentTransformer ct0(A0, ctRatio, rBurden, vcc);
CurrentTransformer ct1(A1, ctRatio, rBurden, vcc);

void setup()
{
    delay(1000);
    Serial.begin(BAUD_RATE);
    ct0.begin();
}

void loop()
{
    uint32_t msStart = millis();
    float i0 = ct0.read();
    float i1 = ct1.read();
    Serial << millis() << F("  ") << _FLOAT(i0, 3) << F(" A  ") << _FLOAT(i1, 3) << F(" A\n");
    while (millis() - msStart < MS_BETWEEN_SAMPLES);  // wait to start next measurement
}

