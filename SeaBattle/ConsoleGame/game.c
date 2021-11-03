#include "game.h"
#include <stdio.h>
#include <stdlib.h>

#define ACTION_SIZE 5
char ACTION[ACTION_SIZE] = { 0, 0, 0, 0, 0 };
char QUIT = FALSE;

void main_menu() {
	reset_globals();

	while (QUIT != TRUE) {
		printf("Choose action:\n");
		printf("\t1) New game\n");
		printf("\t2) Load game\n");
		printf("\t3) Quit\n");

		printf("Action: ");
		(void)gets_s(ACTION, ACTION_SIZE);
		(void)system("cls");

		switch (ACTION[0]) {
		case '1':
			start_new_game();
			break;
		case '2':
			break;
		case '3':
			QUIT = TRUE;
			break;
		default:
			printf("Invalid action: %s\n", ACTION);
		}
	}

	reset_globals();
}

void start_new_game() {
	reset_globals();

	while (QUIT != TRUE) {
		printf("Choose action:\n");
		printf("\t 1) Men vs Men\n");
		printf("\t 2) Men vs AI\n");
		printf("\t 3) AI vs AI\n");
		printf("\t 4) Quit\n");

		printf("Action: ");
		(void)gets_s(ACTION, ACTION_SIZE);
		(void)system("cls");

		switch (ACTION[0]) {
		case '1':
			start_new_game_man_vs_man();
			break;
		case '2':
			break;
		case '3':
			break;
		case '4':
			QUIT = TRUE;
			break;
		default:
			printf("Invalid action: %s\n", ACTION);
		}
	}

	reset_globals();
}

void start_new_game_man_vs_man() {
	struct battle_field field_a;
	battle_field_constructor(&field_a);
	struct battle_field field_b;
	battle_field_constructor(&field_b);

	reset_globals();
	
	while (QUIT != TRUE) {
		printf("Choose action:\n");
		printf("\t1) Fill battle field A\n");
		printf("\t2) Fill battle field B\n");
		printf("\t3) Start game\n");
		printf("\t4) Quit\n");

		printf("Action: ");
		(void)gets_s(ACTION, ACTION_SIZE);
		(void)system("cls");

		switch (ACTION[0])
		{
		case '1':
			init_battle_field_manualy(&field_a, "A");
			break;
		case '2':
			init_battle_field_manualy(&field_b, "B");
			break;
		case '3':
#ifndef TEST_MODE
			if (field_a.used_cells_count < MAX_BATTLE_CELLS_USED_IN_GAME_COUNT) {
				printf("Fill battle field A!\n");
			}
			else if (field_b.used_cells_count < MAX_BATTLE_CELLS_USED_IN_GAME_COUNT) {
				printf("Fill battle field B!\n");
			}
			else {
#endif
				set_battle_field_cells_is_empty_using_status(&field_a, BATTLE_CELL_STATUS_USED_IN_GAME);
				set_battle_field_cells_status(&field_a, BATTLE_CELL_STATUS_UNDEFINED);
				set_battle_field_cells_is_empty_using_status(&field_b, BATTLE_CELL_STATUS_USED_IN_GAME);
				set_battle_field_cells_status(&field_b, BATTLE_CELL_STATUS_UNDEFINED);
				start_game_man_vs_man(&field_a, &field_b);
#ifndef TEST_MODE
			}
#endif
			break;
		case '4':
			QUIT = TRUE;
			break;
		default:
			printf("Invalid action: %s\n", ACTION);
			break;
		}
	}

	reset_globals();
}

void init_battle_field_manualy(struct battle_field* field, const char* name) {
	reset_globals();

	char row = 0;
	char column = 0;
	char used_in_game = FALSE;
	
	while (QUIT != TRUE) {
		printf("Initialization Battle Field %s:\n", name);
		printf(
			"Max used cells in game: %d, used cells: %d, available: %d\n", 
			MAX_BATTLE_CELLS_USED_IN_GAME_COUNT, 
			field->used_cells_count, 
			MAX_BATTLE_CELLS_USED_IN_GAME_COUNT - field->used_cells_count
		);
		printf("Choose action:\n");
		printf("\t1) Mark as used/unused (enter {row}{column}{if used => 1 else 0} ~ 101)\n");
		printf("\tq) Quit from editor\n\n");

		print_battle_field_cells(field);

		printf("Action: ");
		(void)gets_s(ACTION, ACTION_SIZE);
		(void)system("cls");

		if (ACTION[0] == 'q') {
			QUIT = TRUE;
			continue;
		}
		
		row = ACTION[0] - 48;
		column = ACTION[1] - 48;
		used_in_game = ACTION[2] - 48;

		if (
			used_in_game 
			&& field->used_cells_count < MAX_BATTLE_CELLS_USED_IN_GAME_COUNT
			&& field->cells[row][column].status == BATTLE_CELL_STATUS_UNDEFINED
		) {
			field->cells[row][column].status = BATTLE_CELL_STATUS_USED_IN_GAME;
			++field->used_cells_count;
		}
		else if(
			!used_in_game 
			&& field->used_cells_count > 0
			&& field->cells[row][column].status == BATTLE_CELL_STATUS_USED_IN_GAME
		) {
			field->cells[row][column].status = BATTLE_CELL_STATUS_UNDEFINED;
			--field->used_cells_count;
		}
	}

	reset_globals();
}

void print_battle_field_cells(struct battle_field* field) {
	printf("\t ");
	for (int i = 0; i < MAP_SIZE; ++i) {
		printf(" %d ", i);
	}
	printf("\n");
	
	for (int i = 0; i < MAP_SIZE; ++i) {
		printf("\t%d", i);
		for (int j = 0; j < MAP_SIZE; ++j) {
			printf(" ");
			switch (field->cells[i][j].status) {
			case BATTLE_CELL_STATUS_UNDEFINED: 
				printf("*");
				break;
			case BATTLE_CELL_STATUS_USED_IN_GAME:
				printf("U");
				break;
			case BATTLE_CELL_STATUS_HITED:
				printf("X");
				break;
			}
			printf(" ");
		}
		printf("%d\n", i);
	}

	printf("\t ");
	for (int i = 0; i < MAP_SIZE; ++i) {
		printf(" %d ", i);
	}
	printf("\n\n");
}

void start_game_man_vs_man(struct battle_field* field_a, struct battle_field* field_b) {
	reset_globals();

	char player = 'A';
	char save_and_quit = FALSE;
	char row = 0;
	char column = 0;

	while (
		QUIT != TRUE 
		&& save_and_quit != TRUE
		&& field_a->hited_cells_count == 0 
		&& field_b->hited_cells_count == 0
	) {
		printf(
			"Player A hited %d, available %d. Player B hited %d, available %d\n",
			field_a->hited_cells_count,
			MAX_BATTLE_CELLS_USED_IN_GAME_COUNT - field_a->hited_cells_count,
			field_b->hited_cells_count,
			MAX_BATTLE_CELLS_USED_IN_GAME_COUNT - field_b->hited_cells_count
		);
		printf("Choose action:\n");
		printf("\t1) Fire (enter {row}{column} ~ 14)\n");
		printf("\ts) Save and quit\n");
		printf("\tq) Quit\n\n");

		printf("Battle field A\n\n");
		print_battle_field_cells(field_a);

		printf("Battle field B\n\n");
		print_battle_field_cells(field_b);

		printf("Action (Player %c): ", player);
		(void)gets_s(ACTION, ACTION_SIZE);
		(void)system("cls");

		if (ACTION[0] == 's') {
			save_and_quit = TRUE;
			continue;
		}
		if (ACTION[0] == 'q') {
			QUIT = TRUE;
			continue;
		}

		row = ACTION[0] - 48;
		column = ACTION[1] - 48;

		if (player == 'B') {
			if (
				field_a->cells[row][column].status == BATTLE_CELL_STATUS_HITED
				|| field_a->cells[row][column].status == BATTLE_CELL_STATUS_MISSED
			) {
				continue;
			}

			if (field_a->cells[row][column].is_empty == TRUE) {
				field_a->cells[row][column].status = BATTLE_CELL_STATUS_MISSED;
			}
			else {
				field_a->cells[row][column].status = BATTLE_CELL_STATUS_HITED;
				++field_a->hited_cells_count;
			}

			player = 'B';
		}
		else if (player == 'A') {
			if (
				field_b->cells[row][column].status == BATTLE_CELL_STATUS_HITED
				|| field_b->cells[row][column].status == BATTLE_CELL_STATUS_MISSED
				) {
				continue;
			}

			if (field_b->cells[row][column].is_empty == TRUE) {
				field_b->cells[row][column].status = BATTLE_CELL_STATUS_MISSED;
			}
			else {
				field_b->cells[row][column].status = BATTLE_CELL_STATUS_HITED;
				++field_b->hited_cells_count;
			}

			player = 'A';
		}
	}

	if (save_and_quit == TRUE) {
		save(BATTLE_FIELD_A_FILENAME, field_a);
		save(BATTLE_FIELD_B_FILENAME, field_b);
	}

	reset_globals();
}

void battle_field_constructor(struct battle_field* field) {
	field->hited_cells_count = 0;
	field->used_cells_count = 0;
	set_battle_field_cells_is_empty(field, TRUE);
	set_battle_field_cells_status(field, BATTLE_CELL_STATUS_UNDEFINED);
}

void set_battle_field_cells_status(struct battle_field* field, char status) {
	for (char i = 0; i < MAP_SIZE; ++i) {
		for (char j = 0; j < MAP_SIZE; ++j) {
			field->cells[i][j].status = status;
		}
	}
}

void set_battle_field_cells_is_empty(struct battle_field* field, char is_empty) {
	for (char i = 0; i < MAP_SIZE; ++i) {
		for (char j = 0; j < MAP_SIZE; ++j) {
			field->cells[i][j].is_empty = is_empty;
		}
	}
}

void set_battle_field_cells_is_empty_using_status(struct battle_field* field, char status) {
	for (char i = 0; i < MAP_SIZE; ++i) {
		for (char j = 0; j < MAP_SIZE; ++j) {
			field->cells[i][j].is_empty = field->cells[i][j].status == status ? TRUE : FALSE;
		}
	}
}

void reset_globals() {
	QUIT = FALSE;
	for (char i = 0; i < ACTION_SIZE; ++i) {
		ACTION[i] = 0;
	}
}

void save(char* filename, struct battle_field* field) {
	FILE* file = fopen(filename, "wb");
	int size = sizeof(struct battle_field);

	char* ch = (char*)field;
	for (int i = 0; i < size; ++i) {
		putc(*ch++, file);
	}

	fclose(file);
}

void load(char* filename, struct battle_field* field) {
	FILE* file = fopen(filename, "wb");
	int size = sizeof(struct battle_field);

	char* ch = (char*)field;
	int i;
	while ((i = getc(file)) != EOF) {
		*ch = i;
		++ch;
	}

	fclose(file);
}