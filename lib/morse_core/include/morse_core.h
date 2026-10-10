#ifndef MORSE_CORE_H
#define MORSE_CORE_H

typedef enum {
    MORSE_CORE_SUCCESS,
    MORSE_CORE_ERROR,
    MORSE_CORE_UNKNOWN
} morse_core_success_t;

typedef struct MORSE_CORE_morse_code MORSE_CORE_morse_code_t;

typedef struct {
    morse_core_success_t success;
    char* value;
} morse_core_packet_t;

morse_core_success_t morse_core_decode(const char* patterns[], int patterns_size);
const char *morse_core_encode(char *string);

#endif
