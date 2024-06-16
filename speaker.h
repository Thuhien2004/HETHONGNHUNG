#ifndef SPEAKER_H
#define SPEAKER_H

#include <stdint.h>

// �?nh nghia ch�n di?u khi?n loa
#define SPEAKER_PIN PIN_A2

// H�m b?t loa
void speaker_on() {
    output_high(SPEAKER_PIN);
}

// H�m t?t loa
void speaker_off() {
    output_low(SPEAKER_PIN);
}

// H�m ph�t �m thanh trong m?t kho?ng th?i gian
void play_sound(uint16_t duration_ms) {
    speaker_on();  // B?t loa
    delay_ms(duration_ms); // Ch? trong kho?ng th?i gian
    speaker_off(); // T?t loa
}

#endif /* SPEAKER_H */

