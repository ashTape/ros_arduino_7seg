#include "fourdigit_sevenseg.hpp"

uint8_t digit_pins[4]   = { 11, 2, 0, 5 };
uint8_t number_pins[7]  = { 4, 1, 7, 9, 10, 3, 6 };
uint8_t dot_pin         = 8;
uint8_t dot_pos         = 1;
bool    fill_zero       = true;
bool    is_common_anode = true;
bool    enable_minus    = true;

fourdigit_sevenseg::FourDigitSevenSeg fdss(digit_pins, number_pins, dot_pin, dot_pos, fill_zero, is_common_anode,
                                           enable_minus);

void setup() {
    fdss.init();
    for (int i{ 0 }; i < 4; ++i) digitalWrite(digit_pins[i], HIGH);
    fdss.updateNumber(8, true);
    delay(1000);
    // Serial.begin(57600);
}

void loop() {
    // float value = -9.87;
    // while (value < 10) {
    //     value += 0.01;
    //     fdss.display(value);
    // }
    float value{ 1 };
    int   i{ 0 };
    // while (i < 20000) {
        fdss.display(value);
        // i++;
    // }

    // if (value == 9)
    //     value = 0;
    // else
    //     ++value;
}
