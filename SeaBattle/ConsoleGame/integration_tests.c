#include "acutest.h"
#include "communication.h"

void test_open_port_when_all_is_ok(void) {
    open_serial_port();

    TEST_CHECK(PORT != INVALID_HANDLE_VALUE);
}

void test_set_and_get_hited_cells_count_when_all_is_ok(void) {
    open_serial_port();
    TEST_CHECK(PORT != INVALID_HANDLE_VALUE);
    
    char player = 0;
    char hited_cells_count = 1;

    set_hited_cells_count(player, hited_cells_count);

    TEST_CHECK(get_hited_cells_count(player) == hited_cells_count);
}

void test_set_and_get_used_cells_count_when_all_is_ok(void) {
    open_serial_port();
    TEST_CHECK(PORT != INVALID_HANDLE_VALUE);
    
    char player = 0;
    char used_cells_count = 12;

    set_used_cells_count(player, used_cells_count);

    TEST_CHECK(get_used_cells_count(player) == used_cells_count);
}

void test_set_and_get_cell_status_when_all_is_ok(void) {
    open_serial_port();
    TEST_CHECK(PORT != INVALID_HANDLE_VALUE);
    
    char player = 0;
    char cell_status = 2;
    char cells[4][2] = { {0, 0}, {1, 1}, {2, 2}, {3, 3} };

    for(int i = 0; i < 4; ++i){
        set_cell_status(player, cells[i][0], cells[i][1], cell_status);
    }

    for(int i = 0; i < 4; ++i){
        TEST_CHECK(get_cell_status(player, cells[i][0], cells[i][1]) == cell_status);
    }
}

TEST_LIST = {
    { "open port when all is ok" , test_open_port_when_all_is_ok },
    { "set and get hited cells count when all is ok", test_set_and_get_hited_cells_count_when_all_is_ok },
    { "set and get used cells count when all is ok", test_set_and_get_used_cells_count_when_all_is_ok },
    { "set and get cell status when all is ok", test_set_and_get_cell_status_when_all_is_ok },
    { NULL, NULL }
};