/********************************************************************/
/*                                                                  */
/*                                                                  */
/*                                                                  */
/********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "morse_core.h"

// Trick to test static functions with Ceedling
#ifndef TEST
#define STATIC static
#else 
#define STATIC
#endif

typedef struct {
    char character;
    const char *pattern;
} MORSE_CORE_morse_entry_t;

struct MORSE_CORE_morse_code {
    char* characters;
    char *patterns[50]; // TODO Set max LEN
};

STATIC const MORSE_CORE_morse_entry_t MORSE_CORE_TABLE[] = {
    {'A', ".-"}, {'B', "-..."}, {'C', "-.-."}, {'D', "-.."},
    {'E', "."}, {'F', "..-."}, {'G', "--."}, {'H', "...."},
    {'I', ".."}, {'J', ".---"}, {'K', "-.-"}, {'L', ".-.."},
    {'M', "--"}, {'N', "-."}, {'O', "---"}, {'P', ".--."},
    {'Q', "--.-"}, {'R', ".-."}, {'S', "..."}, {'T', "-"},
    {'U', "..-"}, {'V', "...-"}, {'W', ".--"}, {'X', "-..-"},
    {'Y', "-.--"}, {'Z', "--.."},
    {'0', "-----"}, {'1', ".----"}, {'2', "..---"}, {'3', "...--"},
    {'4', "....-"}, {'5', "....."}, {'6', "-...."}, {'7', "--..."},
    {'8', "---.."}, {'9', "----."}
};

STATIC const size_t MORSE_CORE_TABLE_SIZE = sizeof(MORSE_CORE_TABLE) / sizeof(MORSE_CORE_TABLE[0]);

STATIC MORSE_CORE_morse_code_t morse_code = {0};

morse_core_success_t morse_core_init(void) {
    // TODO: Init ?
}

MORSE_CORE_morse_code_t* morse_core_get_handle(void) {
    return &morse_code;
}

// To decode a single morse code
// return the character associate with code 
STATIC char morse_core_decode_single(const char pattern[]) {
    // Validate the pointer exist
    if (!pattern || pattern == NULL) {
        return '0';
    }

    // Initiate as '0', if pattern is not recognized, function returns '0'
    char letter = '0';
    // Find the pattern
    for (int i = 0; i < MORSE_CORE_TABLE_SIZE; i++) {
        if (strcmp(MORSE_CORE_TABLE[i].pattern, pattern) == 0) {
            letter = MORSE_CORE_TABLE[i].character;
        }
    }

    return letter;
}

morse_core_success_t morse_core_decode(const char* patterns[], int patterns_size) {
    // Validate the pointer exist
    if (!patterns || patterns == NULL) {
        return MORSE_CORE_ERROR;
    }
    // Validate patterns_size
    if (patterns_size <= 0) {
        memset(morse_code.characters, 0, sizeof(morse_code.characters));
        memset(morse_code.patterns, 0, sizeof(morse_code.patterns));
        return MORSE_CORE_ERROR;
    }

    for (int i = 0; i < patterns_size; i++) {
        char letter = morse_core_decode_single(patterns[i]);
    }

    return MORSE_CORE_SUCCESS;
}

