#ifndef GAME_HEADER_FILE
#define GAME_HEADER_FILE

#include "communication.h"

// boolean
#define TRUE 1
#define FALSE 0

// main constants
#define MAP_SIZE 10
#define MAX_BATTLE_CELLS_USED_IN_GAME_COUNT 20
#define BATTLE_FIELD_A_FILENAME "battle_field_a.dat"
#define BATTLE_FIELD_B_FILENAME "battle_field_b.dat"

// battle cell states
#define BATTLE_CELL_STATUS_UNDEFINED 0
#define BATTLE_CELL_STATUS_USED_IN_GAME 1
#define BATTLE_CELL_STATUS_HITED 2
#define BATTLE_CELL_STATUS_MISSED 3

// global variables
#define ACTION_SIZE 5
char ACTION[ACTION_SIZE];
char QUIT;

void battle_field_constructor(char);
void init_battle_field_manualy(char, const char*);
void set_battle_field_cells_status(char, char);
void print_battle_field_cells(char, char);

// game functions
void main_menu();
void start_new_game();
void start_new_game_man_vs_man();
void start_game_man_vs_man();
void save_field(char*, char);
void load_field(char*, char);

// helper functions
void reset_globals();

#endif