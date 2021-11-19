#include "acutest.h"
#include "game.h"

void test_reset_globals_isnt_empty(void) {
    QUIT = TRUE;
    for(int i = 0; i < ACTION_SIZE; ++i){
        ACTION[i] = (char)i;
    }

    reset_globals();

    TEST_CHECK(QUIT == FALSE);
    for(int i = 0; i < ACTION_SIZE; ++i){
        TEST_CHECK(ACTION[i] == FALSE);
    }
}

void test_reset_globals_is_empty(void) {
    QUIT = FALSE;
    for(int i = 0; i < ACTION_SIZE; ++i){
        ACTION[i] = 0;
    }

    reset_globals();

    TEST_CHECK(QUIT == FALSE);
    for(int i = 0; i < ACTION_SIZE; ++i){
        TEST_CHECK(ACTION[i] == FALSE);
    }
}

TEST_LIST = {
    { "reset globals when globals isnt`t empty", test_reset_globals_isnt_empty },
    { "reset globals when globals is empty", test_reset_globals_is_empty },
    { NULL, NULL }
};