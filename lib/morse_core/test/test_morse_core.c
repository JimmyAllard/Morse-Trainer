#ifdef TEST

#include "unity.h"
#include "morse_core.h"

// Prototype of static function for test
char morse_core_decode_single(const char pattern[]);

// Official morse entry for test
typedef struct {
    char character;
    const char *pattern;
} test_morse_core_morse_entry;

// Official morse code for test
static const test_morse_core_morse_entry TEST_MORSE_CORE_CORE_TABLE[] = {
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
static const size_t TEST_MORSE_CORE_TABLE_SIZE = sizeof(TEST_MORSE_CORE_CORE_TABLE) / sizeof(TEST_MORSE_CORE_CORE_TABLE[0]);

extern MORSE_CORE_morse_code_t morse_code;


void setUp(void) {
    // Exécuté avant chaque test
}

void tearDown(void) {
    // Exécuté après chaque test
}

/* morse_core_decode_single */
void test_morse_core_decode_single(void) {
    for (int i = 0; i < TEST_MORSE_CORE_TABLE_SIZE; i++) {
        const char *pattern = TEST_MORSE_CORE_CORE_TABLE[i].pattern;
        char tested_character = TEST_MORSE_CORE_CORE_TABLE[i].character;
        char c = morse_core_decode_single(pattern);
        TEST_ASSERT_EQUAL_CHAR(tested_character, c);
    }
}

void test_morse_core_decode_single_undefined_pattern(void) {
    const char pattern;
    char c = morse_core_decode_single(&pattern);
    TEST_ASSERT_EQUAL_CHAR('0', c);
}

void test_morse_core_decode_single_null_pattern(void) {
    const char *pattern = NULL;
    char c = morse_core_decode_single(pattern);
    TEST_ASSERT_EQUAL_CHAR('0', c);
}

void test_morse_core_decode_single_empty_pattern(void) {
    const char *pattern = "";
    char c = morse_core_decode_single(pattern);
    TEST_ASSERT_EQUAL_CHAR('0', c);
}

/* morse_core_decode */
void test_morse_core_decode(void) {
    int patterns_size = 4;
    const char* patterns[] = {"-.-.", "....", ".-", ".-."};
    /*patterns[0] = "-.-.";
    patterns[1] = "....";
    patterns[2] = ".-";
    patterns[3] = ".-.";*/

    morse_core_success_t success = morse_core_decode(patterns, patterns_size);

    TEST_ASSERT_EQUAL_INT(MORSE_CORE_SUCCESS ,success);
}

#endif
