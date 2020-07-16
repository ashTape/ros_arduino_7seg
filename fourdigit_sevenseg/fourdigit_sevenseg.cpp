#include "fourdigit_sevenseg.hpp"
namespace fourdigit_sevenseg {
FourDigitSevenSeg::FourDigitSevenSeg(const uint8_t* d_pins, const uint8_t* n_pins, const uint8_t& d_pin,
                                     const uint8_t& d_pos, const bool& f_zero, const bool& is_ano,
                                     const bool& enable_minus)
    : DIGIT_PINS_(d_pins)
    , NUMBER_PINS_(n_pins)
    , DOT_PIN_(d_pin)
    , DOT_POS_(d_pos)
    , FILL_ZERO_(f_zero)
    , IS_COMMON_ANODE_(is_ano) {
    if (enable_minus) {
        if (DOT_POS_ >= 1 && DOT_POS_ <= 2) {
            is_static_dot_ = true;
            max_value_     = round(pow(10 ,DOT_POS_ + 1));
            min_value_     = -1 * round(pow(10,DOT_POS_));
        } else {
            is_static_dot_ = false;
            max_value_     = 10000;
            min_value_     = -1000;
        }
    } else {
        if (DOT_POS_ >= 0 && DOT_POS_ <= 2) {
            is_static_dot_ = true;
            max_value_     = round(pow(10 ,DOT_POS_ + 1));
            min_value_     = 0;
        } else {
            is_static_dot_ = false;
            max_value_     = 10000;
            min_value_     = 0;
        }
        min_value_ = 0;
    }
}

void FourDigitSevenSeg::init() {
    for (uint8_t i{ 0 }; i < 4; ++i) pinMode(DIGIT_PINS_[i], OUTPUT);
    for (uint8_t i{ 0 }; i < 7; ++i) pinMode(NUMBER_PINS_[i], OUTPUT);
    pinMode(DOT_PIN_, OUTPUT);
    resetNumber();
}

void FourDigitSevenSeg::setValue(const float& value) { value_ = value; }

void FourDigitSevenSeg::updateDigit(const uint8_t& digit) {
    for (uint8_t i{ 0 }; i < 4; ++i) {
        if (i == digit)
            digitalWrite(DIGIT_PINS_[i], IS_COMMON_ANODE_);
        else
            digitalWrite(DIGIT_PINS_[i], !IS_COMMON_ANODE_);
    }
    delay(1);
}

void FourDigitSevenSeg::resetDigit() {
    for (uint8_t i{ 0 }; i < 4; ++i) digitalWrite(DIGIT_PINS_[i], IS_COMMON_ANODE_);
}

void FourDigitSevenSeg::updateNumber(const uint8_t& num, bool dot) {
    for (uint8_t i{ 0 }; i < 7; i++) digitalWrite(NUMBER_PINS_[i], NUMBER_TABLE[num][i] ^ IS_COMMON_ANODE_);
    digitalWrite(DOT_PIN_, dot ^ IS_COMMON_ANODE_);
}

void FourDigitSevenSeg::resetNumber() {
    for (uint8_t i{ 0 }; i < 7; i++) digitalWrite(NUMBER_PINS_[i], !IS_COMMON_ANODE_);
    digitalWrite(DOT_PIN_, !IS_COMMON_ANODE_);
}

void FourDigitSevenSeg::displayNumber(const uint8_t& digit, const uint8_t& num, const bool& dot) {
    // resetDigit();
    // resetNumber();
    updateNumber(num, dot);
    updateDigit(digit);
}

void FourDigitSevenSeg::displayMinus(const uint8_t& digit) {
    displayNumber(digit, 10);  // Call DISPLAY_NUMBER_TABLE[10]
}

void FourDigitSevenSeg::display() {
    /* Error Handle*/
    if (value_ >= max_value_) {
        /* Display "9.9.9.9." when called with the invalid positive value */
        for (uint8_t i{ 0 }; i < 4; ++i) displayNumber(i, 9, true);
        return;
    } else if (value_ < min_value_) {
        /* Display "-9.9.9." when called with the invalid negative value */
        displayMinus(0);
        for (uint8_t i{ 1 }; i < 4; ++i) displayNumber(i, 9, true);
        return;
    }

    // uint16_t v_tmp = static_cast<uint16_t>(abs(value_ * (float)pow(10, 3 - DOT_POS_)));
    uint16_t v_tmp = round(abs(value_ * pow(10, 3 - DOT_POS_)));
    uint16_t v_rmd{ 0 };  // Reminder

    if (value_ >= 0) {
        /* Positive Number */
        if (is_static_dot_) {
            for (uint8_t i{ 3 }; i == 0; --i) {
                if (v_tmp >= 10) {
                    v_rmd = v_tmp % 10;
                    displayNumber(i, v_rmd, i == DOT_POS_);
                    v_tmp = (v_tmp - v_rmd) / 10;
                    // Serial.println(value_);
                    // Serial.println(v_tmp);
                    // Serial.println(v_rmd);
                } else {
                    displayNumber(i, v_tmp, i == DOT_POS_);
                }

                // } else if (v_tmp != 0) {
                //     displayNumber(i, 2, i == DOT_POS_);
                //     v_tmp = 0;
                // }
                // } else if (i <= DOT_POS_) {
                //     displayNumber(i, 0, i == DOT_POS_);
                // } else if (FILL_ZERO_) {
                //     displayNumber(i, 0, false);
                // } else {
                //     return;
                // }
            }
        }
    } else {
        // /* Negative Number */
        // if (is_static_dot_) {
        //     for (uint8_t i{ 0 }; i < 3; ++i) {
        //         if (v_tmp >= 10) {
        //             v_rmd = v_tmp % 10;
        //             v_tmp = (v_tmp - v_rmd) / 10;
        //             // Serial.print("v_rmd: ");
        //             // Serial.println(v_rmd);
        //             // Serial.print("v_tmp: ");
        //             // Serial.println(v_tmp);
        //             displayNumber(i, v_rmd, i == DOT_POS_);
        //         } else if (v_tmp != 0) {
        //             displayNumber(i, v_tmp, i == DOT_POS_);
        //             // v_tmp = 0;
        //         } else if (i <= DOT_POS_) {
        //             displayNumber(i, 0, i == DOT_POS_);
        //         } else if (FILL_ZERO_) {
        //             displayNumber(i, 0, false);
        //         } else {
        //             return;
        //         }
        //     }
        // }
        // displayMinus(3);
        return;
    }
}

void FourDigitSevenSeg::display(const float& val) {
    setValue(val);
    display();
}
}  // namespace fourdigit_sevenseg
