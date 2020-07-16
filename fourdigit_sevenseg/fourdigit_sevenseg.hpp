#ifndef FOURDIGIT_SEVENSEG_HPP_
#define FOURDIGIT_SEVENSEG_HPP_

#ifdef ARDUINO
#include <Arduino.h>
#endif

#include <avr/io.h>

namespace fourdigit_sevenseg {
                                      /* 1  2  3  4 */
const uint8_t DEFAULT_DIGIT_PINS[4]  = { 0, 1, 2, 3 };
                                      /* a  b  c  d  e  f  g */
const uint8_t DEFAULT_NUMBER_PINS[7] = { 4, 5, 6, 7, 8, 9, 10 };
const uint8_t DEFAULT_DOT_PIN        = 11;
const bool    NUMBER_TABLE[11][7]    = {
    /* a  b  c  d  e  f  g */
    { 1, 1, 1, 1, 1, 1, 0 },  // 0
    { 0, 1, 1, 0, 0, 0, 0 },  // 1
    { 1, 1, 0, 1, 1, 0, 1 },  // 2
    { 1, 1, 1, 1, 0, 0, 1 },  // 3
    { 0, 1, 1, 0, 0, 1, 1 },  // 4
    { 1, 0, 1, 1, 0, 1, 1 },  // 5
    { 1, 0, 1, 1, 1, 1, 1 },  // 6
    { 1, 1, 1, 0, 0, 0, 0 },  // 7
    { 1, 1, 1, 1, 1, 1, 1 },  // 8
    { 1, 1, 1, 1, 0, 1, 1 },  // 9
    { 0, 0, 0, 0, 0, 0, 1 },  // -
};

// const bool CATHOD_NUMBER_TABLE[11][7] = {
   /* a  b  c  d  e  f  g */
    // { 0, 0, 0, 0, 0, 0, 1 },  // 0
    // { 1, 0, 0, 1, 1, 1, 1 },  // 1
    // { 0, 0, 1, 0, 0, 1, 0 },  // 2
    // { 0, 0, 0, 0, 1, 1, 0 },  // 3
    // { 1, 0, 0, 1, 1, 0, 0 },  // 4
    // { 0, 1, 0, 0, 1, 0, 0 },  // 5
    // { 0, 1, 0, 0, 0, 0, 0 },  // 6
    // { 0, 0, 0, 1, 1, 1, 1 },  // 7
    // { 0, 0, 0, 0, 0, 0, 0 },  // 8
    // { 0, 0, 0, 0, 1, 0, 0 },  // 9
    // { 1, 1, 1, 1, 1, 1, 0 },  // -
// };

class FourDigitSevenSeg {
   private:
    const uint8_t* DIGIT_PINS_;
    const uint8_t* NUMBER_PINS_;
    const uint8_t  DOT_PIN_;
    const uint8_t   DOT_POS_;
    const bool     FILL_ZERO_;
    const bool     IS_COMMON_ANODE_;

    int16_t max_value_;
    int16_t min_value_;
    float   value_;
    bool    is_static_dot_;

   public:
    FourDigitSevenSeg(const uint8_t* d_pins = DEFAULT_DIGIT_PINS,
                      const uint8_t* n_pins = DEFAULT_NUMBER_PINS, const uint8_t& d_pin = 11, const uint8_t& d_pos = 2,
                      const bool& f_zero = false, const bool& is_ca = true,const bool& enable_minus = true);
    void init();
    void setValue(const float&);
    void updateDigit(const uint8_t&);
    void resetDigit();
    void updateNumber(const uint8_t&, bool dot = false);
    void resetNumber();
    void displayNumber(const uint8_t&, const uint8_t&, const bool& dot = false);
    void displayMinus(const uint8_t&);
    void display();
    void display(const float&);
};
}  // namespace fourdigit_sevenseg
#endif  // FOURDIGIT_SEVENSEG_HPP_
