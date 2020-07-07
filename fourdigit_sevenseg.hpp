#ifndef FOURDIGIT_SEVENSEG_HPP_
#define FOURDIGIT_SEVENSEG_HPP_

#include <Arduino.h>
#include <avr/io.h>

class FourDigitSevenSeg {
   private:
    const uint8_t* PINS;
   public:
    FourDigitSevenSeg();
    FourDigitSevenSeg(uint8_t*);
    FourDigitSevenSeg(const uint8_t*, const uint8_t&);
    void print(float);
}

#endif  // 4DIGIT_7SEG_HPP_
