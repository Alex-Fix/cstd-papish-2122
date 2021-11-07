#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#define _CRT_SECURE_NO_WARNINGS

// includes
#include <stdio.h>
#include <stdint.h>
#include <Windows.h>

// buffer and packet size
#define PACKET_SIZE 7

// package positions
#define PACKET_SOP_POS 0
#define PACKET_CMD_POS 1
#define PACKET_D0_POS 2
#define PACKET_D1_POS 3
#define PACKET_D2_POS 4
#define PACKET_D3_POS 5
#define PACKET_EOP_POS 6

// start and end of packet markers
#define PACKET_SOP 0xFC
#define PACKET_EOP 0xFE

// command statuses
#define CMD_STATUS_DONE 0xFD
#define CMD_STATUS_FAIL 0xFF

// commands
#define CMD_GET_HITED_CELLS_COUNT 0
#define CMD_SET_HITED_CELLS_COUNT 1
#define CMD_GET_USED_CELLS_COUNT 2
#define CMD_SET_USED_CELLS_COUNT 3
#define CMD_GET_CELL_STATUS 4
#define CMD_SET_SELL_STATUS 5

// fields
#define FIELD_A 0
#define FIELD_B 1

// helper defines
#define DEVICE "\\\\.\\COM5"
#define BOUD_RATE 9600

// global variables
HANDLE PORT;
uint8_t WRITE_BUFFER[PACKET_SIZE];
uint8_t READ_BUFFER[PACKET_SIZE];

// functions
char get_hited_cells_count(char);
void set_hited_cells_count(char, char);
char get_used_cells_count(char);
void set_used_cells_count(char, char);
char get_cell_status(char, char, char);
void set_cell_status(char, char, char, char);

// helper functions
void print_error(const char*);
void open_serial_port();
void write_port();
void read_port();

#endif