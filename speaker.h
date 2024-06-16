#ifndef SPEAKER_H
#define SPEAKER_H

#include <stdint.h>

// Ð?nh nghia chân di?u khi?n loa
#define SPEAKER_PIN PIN_A2

// Hàm b?t loa
void speaker_on() {
    output_high(SPEAKER_PIN);
}

// Hàm t?t loa
void speaker_off() {
    output_low(SPEAKER_PIN);
}

// Hàm phát âm thanh trong m?t kho?ng th?i gian
void play_sound(uint16_t duration_ms) {
    speaker_on();  // B?t loa
    delay_ms(duration_ms); // Ch? trong kho?ng th?i gian
    speaker_off(); // T?t loa
}

#endif /* SPEAKER_H */

