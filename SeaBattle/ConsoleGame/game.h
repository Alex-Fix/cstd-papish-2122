#ifndef GAME_HEADER_FILE
#define GAME_HEADER_FILE

#define _CRT_SECURE_NO_WARNINGS

// boolean
#define TRUE 1
#define FALSE 0

// main constants
#define MAP_SIZE 10
#define MAX_BATTLE_CELLS_USED_IN_GAME_COUNT 20

// battle cell states
#define BATTLE_CELL_STATUS_UNDEFINED 0
#define BATTLE_CELL_STATUS_USED_IN_GAME 1
#define BATTLE_CELL_STATUS_HITED 2

// structures
struct battle_cell {
	char is_empty;
	char status;
};

struct battle_field {
	char hited_cells_count;
	char unhited_cells_count;
	char used_cells_count;
	struct battle_cell cells[MAP_SIZE][MAP_SIZE];
};

void battle_field_constructor(struct battle_field*);
void init_battle_field_manualy(struct battle_field*, const char* name);
void set_battle_field_cells_status(struct battle_field*, char);
void set_battle_field_cells_is_empty(struct battle_field*, char);
void print_battle_field_cells(struct battle_field*);
void set_battle_field_cells_is_empty_using_status(struct battle_field*, char);

// game functions
void main_menu();
void start_new_game();
void start_new_game_man_vs_man();
void start_game_man_vs_man(struct battle_field*, struct battle_field*);

// helper functions

#endif