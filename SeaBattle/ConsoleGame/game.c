#include "game.h"

void main_menu() {
	reset_globals();

	open_serial_port();

	while (QUIT != TRUE) {
		printf("Choose action:\n");
		printf("\t1) New game\n");
		printf("\t2) Quit\n");

		printf("Action: ");
		(void)gets_s(ACTION, ACTION_SIZE);
		(void)system("cls");

		switch (ACTION[0]) {
		case '1':
			start_new_game();
			break;
		case '2':
			QUIT = TRUE;
			break;
		default:
			printf("Invalid action: %s\n", ACTION);
		}
	}

	CloseHandle(PORT);

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
	reset_globals();

	battle_field_constructor(FIELD_A);
	battle_field_constructor(FIELD_B);

	while (QUIT != TRUE) {
		printf("Choose action:\n");
		printf("\t1) Fill battle field A\n");
		printf("\t2) Fill battle field B\n");
		printf("\t3) Load\n");
		printf("\t4) Start game\n");
		printf("\t5) Quit\n");

		printf("Action: ");
		(void)gets_s(ACTION, ACTION_SIZE);
		(void)system("cls");

		switch (ACTION[0])
		{
		case '1':
			init_battle_field_manualy(FIELD_A, "A");
			break;
		case '2':
			init_battle_field_manualy(FIELD_B, "B");
			break;
		case '3':
			load_field(BATTLE_FIELD_A_FILENAME, FIELD_A);
			load_field(BATTLE_FIELD_B_FILENAME, FIELD_B);
			printf("Successfully loaded\n");
			break;
		case '4':
			if (get_used_cells_count(FIELD_A) < MAX_BATTLE_CELLS_USED_IN_GAME_COUNT) {
				printf("Fill battle field A!\n");
			}
			else if (get_used_cells_count(FIELD_B) < MAX_BATTLE_CELLS_USED_IN_GAME_COUNT) {
				printf("Fill battle field B!\n");
			}
			else {
				start_game_man_vs_man();
			}
			break;
		case '5':
			QUIT = TRUE;
			break;
		default:
			printf("Invalid action: %s\n", ACTION);
			break;
		}
	}

	reset_globals();
}

void init_battle_field_manualy(char field, const char* name) {
	reset_globals();

	char row = 0;
	char column = 0;
	char used_in_game = FALSE;
	
	while (QUIT != TRUE) {
		printf("Initialization Battle Field %s:\n", name);
		printf(
			"Max used cells in game: %d, used cells: %d, available: %d\n",
			MAX_BATTLE_CELLS_USED_IN_GAME_COUNT,
			get_used_cells_count(field),
			MAX_BATTLE_CELLS_USED_IN_GAME_COUNT - get_used_cells_count(field)
		);
		printf("Choose action:\n");
		printf("\t1) Mark as used/unused (enter {row}{column}{if used => 1 else 0} ~ 101)\n");
		printf("\tq) Quit from editor\n\n");

		print_battle_field_cells(field, TRUE);

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
			&& get_used_cells_count(field) < MAX_BATTLE_CELLS_USED_IN_GAME_COUNT
			&& get_cell_status(field, row, column) == BATTLE_CELL_STATUS_UNDEFINED
		) {
			get_cell_status(field, row, column, BATTLE_CELL_STATUS_USED_IN_GAME);
			set_used_cells_count(field, get_used_cells_count(field) + 1);
		}
		else if(
			!used_in_game 
			&& get_used_cells_count(field) > 0
			&& get_cell_status(field, row, column) == BATTLE_CELL_STATUS_USED_IN_GAME
		) {
			get_cell_status(field, row, column, BATTLE_CELL_STATUS_UNDEFINED);
			set_used_cells_count(field, get_used_cells_count(field) - 1);
		}
	}

	reset_globals();
}

void print_battle_field_cells(char field, char is_editor) {
	printf("\t ");
	for (int i = 0; i < MAP_SIZE; ++i) {
		printf(" %d ", i);
	}
	printf("\n");
	
	for (int i = 0; i < MAP_SIZE; ++i) {
		printf("\t%d", i);
		for (int j = 0; j < MAP_SIZE; ++j) {
			printf(" ");
			switch (get_cell_status(field, i, j)) {
			case BATTLE_CELL_STATUS_UNDEFINED: 
				printf("*");
				break;
			case BATTLE_CELL_STATUS_USED_IN_GAME:
				if (is_editor == TRUE) {
					printf("U");
				}
				else {
					printf("*");
				}
				break;
			case BATTLE_CELL_STATUS_HITED:
				printf("H");
				break;
			case BATTLE_CELL_STATUS_MISSED:
				printf("M");
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

void start_game_man_vs_man() {
	reset_globals();

	char player = 'A';
	char save_and_quit = FALSE;
	char row = 0;
	char column = 0;

	while (
		QUIT != TRUE 
		&& save_and_quit != TRUE
		&& get_hited_cells_count(FIELD_A) < MAX_BATTLE_CELLS_USED_IN_GAME_COUNT
		&& get_hited_cells_count(FIELD_B) < MAX_BATTLE_CELLS_USED_IN_GAME_COUNT
	) {
		printf(
			"Player A hited %d, available %d. Player B hited %d, available %d\n",
			get_hited_cells_count(FIELD_A),
			MAX_BATTLE_CELLS_USED_IN_GAME_COUNT - get_hited_cells_count(FIELD_A),
			get_hited_cells_count(FIELD_B),
			MAX_BATTLE_CELLS_USED_IN_GAME_COUNT - get_hited_cells_count(FIELD_B)
		);
		printf("Choose action:\n");
		printf("\t1) Fire (enter {row}{column} ~ 14)\n");
		printf("\ts) Save and quit\n");
		printf("\tq) Quit\n\n");

		printf("Battle field A\n\n");
		print_battle_field_cells(FIELD_A, FALSE);

		printf("Battle field B\n\n");
		print_battle_field_cells(FIELD_B, FALSE);

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
				get_cell_status(FIELD_A, row, column) == BATTLE_CELL_STATUS_HITED
				|| get_cell_status(FIELD_A, row, column) == BATTLE_CELL_STATUS_MISSED
			) {
				continue;
			}

			if (get_cell_status(FIELD_A, row, column) != BATTLE_CELL_STATUS_USED_IN_GAME) {
				set_cell_status(FIELD_A, row, column, BATTLE_CELL_STATUS_MISSED);
				player = 'A';
			}
			else {
				set_cell_status(FIELD_A, row, column, BATTLE_CELL_STATUS_HITED);
				set_hited_cells_count(FIELD_A, get_hited_cells_count(FIELD_A) + 1);
			}
		}
		else if (player == 'A') {
			if (
				get_cell_status(FIELD_B, row, column) == BATTLE_CELL_STATUS_HITED
				|| get_cell_status(FIELD_B, row, column) == BATTLE_CELL_STATUS_MISSED
				) {
				continue;
			}

			if (get_cell_status(FIELD_B, row, column) != BATTLE_CELL_STATUS_USED_IN_GAME) {
				set_cell_status(FIELD_B, row, column, BATTLE_CELL_STATUS_MISSED);
				player = 'B';
			}
			else {
				set_cell_status(FIELD_B, row, column, BATTLE_CELL_STATUS_HITED);
				set_hited_cells_count(FIELD_B, get_hited_cells_count(FIELD_B) + 1);
			}
		}
	}

	if (save_and_quit == TRUE) {
		save_field(BATTLE_FIELD_A_FILENAME, FIELD_A);
		save_field(BATTLE_FIELD_B_FILENAME, FIELD_B);
	}

	if (get_hited_cells_count(FIELD_B) == MAX_BATTLE_CELLS_USED_IN_GAME_COUNT) {
		printf("Player A wins!!!\n");
	}
	if (get_hited_cells_count(FIELD_A) == MAX_BATTLE_CELLS_USED_IN_GAME_COUNT) {
		printf("Player B wins!!!\n");
	}

	reset_globals();
}

void battle_field_constructor(char field) {
	set_used_cells_count(field, 0);
	set_hited_cells_count(field, 0);
	set_battle_field_cells_status(field, BATTLE_CELL_STATUS_UNDEFINED);
}

void set_battle_field_cells_status(char field, char status) {
	for (char i = 0; i < MAP_SIZE; ++i) {
		for (char j = 0; j < MAP_SIZE; ++j) {
			set_cell_status(field, i, j, status);
		}
	}
}

void reset_globals() {
	QUIT = FALSE;
	for (char i = 0; i < ACTION_SIZE; ++i) {
		ACTION[i] = 0;
	}
}

void save_field(char* filename, struct battle_field* field) {
	FILE* file = fopen(filename, "wb");

	putc(get_used_cells_count(field), file);
	putc(get_hited_cells_count(field), file);

	for (char row = 0; row < MAP_SIZE; ++row) {
		for (char column = 0; column < MAP_SIZE; ++column) {
			putc(get_cell_status(field, row, column), file);
		}
	}

	fclose(file);
}

void load_field(char* filename, char field) {
	FILE* file = fopen(filename, "rb");
	
	set_used_cells_count(field, getc(file));
	set_hited_cells_count(field, getc(file));

	for (char row = 0; row < MAP_SIZE; ++row) {
		for (char column = 0; column < MAP_SIZE; ++column) {
			set_cell_status(field, row, column, getc(file));
		}
	}

	fclose(file);
}