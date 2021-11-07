#include "communication.h"

void print_error(const char* context) {
    DWORD error_code = GetLastError();
    char buffer[256];
    DWORD size = FormatMessageA(
        FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_MAX_WIDTH_MASK,
        NULL, error_code, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
        buffer, sizeof(buffer), NULL);
    if (size == 0) { buffer[0] = 0; }
    fprintf(stderr, "%s: %s\n", context, buffer);
}

void open_serial_port() {
    HANDLE port = CreateFileA(DEVICE, GENERIC_READ | GENERIC_WRITE, 0, NULL,
        OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (port == INVALID_HANDLE_VALUE)
    {
        print_error(DEVICE);
        PORT = INVALID_HANDLE_VALUE;
        return;
    }

    BOOL success = FlushFileBuffers(port);
    if (!success)
    {
        print_error("Failed to flush serial port");
        CloseHandle(port);
        PORT = INVALID_HANDLE_VALUE;
        return;
    }

    COMMTIMEOUTS timeouts = { 0 };
    timeouts.ReadIntervalTimeout = 0;
    timeouts.ReadTotalTimeoutConstant = 100;
    timeouts.ReadTotalTimeoutMultiplier = 0;
    timeouts.WriteTotalTimeoutConstant = 100;
    timeouts.WriteTotalTimeoutMultiplier = 0;

    success = SetCommTimeouts(port, &timeouts);
    if (!success)
    {
        print_error("Failed to set serial timeouts");
        CloseHandle(port);
        PORT = INVALID_HANDLE_VALUE;
        return;
    }

    DCB state = { 0 };
    state.DCBlength = sizeof(DCB);
    state.BaudRate = BOUD_RATE;
    state.ByteSize = 8;
    state.Parity = NOPARITY;
    state.StopBits = ONESTOPBIT;
    success = SetCommState(port, &state);
    if (!success)
    {
        print_error("Failed to set serial settings");
        CloseHandle(port);
        PORT = INVALID_HANDLE_VALUE;
    }

    PORT = port;
}

void write_port() {
    DWORD written;
    BOOL success = WriteFile(PORT, WRITE_BUFFER, PACKET_SIZE, &written, NULL);
    if (!success)
    {
        print_error("Failed to write to port");
        return;
    }
    if (written != PACKET_SIZE)
    {
        print_error("Failed to write all bytes to port");
    }
}

void read_port() {
    DWORD received;
    BOOL success = ReadFile(PORT, READ_BUFFER, PACKET_SIZE, &received, NULL);
    if (!success)
    {
        print_error("Failed to read from port");
    }
}

char get_hited_cells_count(char field) {
    WRITE_BUFFER[PACKET_SOP_POS] = PACKET_SOP;
    WRITE_BUFFER[PACKET_CMD_POS] = CMD_GET_HITED_CELLS_COUNT;
    WRITE_BUFFER[PACKET_D0_POS] = field;
    WRITE_BUFFER[PACKET_D1_POS] = 0;
    WRITE_BUFFER[PACKET_D2_POS] = 0;
    WRITE_BUFFER[PACKET_D3_POS] = 0;
    WRITE_BUFFER[PACKET_EOP_POS] = PACKET_EOP;

    write_port();
    read_port();

    return READ_BUFFER[PACKET_D0_POS];
}

void set_hited_cells_count(char field, char value) {
    WRITE_BUFFER[PACKET_SOP_POS] = PACKET_SOP;
    WRITE_BUFFER[PACKET_CMD_POS] = CMD_SET_HITED_CELLS_COUNT;
    WRITE_BUFFER[PACKET_D0_POS] = field;
    WRITE_BUFFER[PACKET_D1_POS] = value;
    WRITE_BUFFER[PACKET_D2_POS] = 0;
    WRITE_BUFFER[PACKET_D3_POS] = 0;
    WRITE_BUFFER[PACKET_EOP_POS] = PACKET_EOP;

    write_port();
}

char get_used_cells_count(char field) {
    WRITE_BUFFER[PACKET_SOP_POS] = PACKET_SOP;
    WRITE_BUFFER[PACKET_CMD_POS] = CMD_GET_USED_CELLS_COUNT;
    WRITE_BUFFER[PACKET_D0_POS] = field;
    WRITE_BUFFER[PACKET_D1_POS] = 0;
    WRITE_BUFFER[PACKET_D2_POS] = 0;
    WRITE_BUFFER[PACKET_D3_POS] = 0;
    WRITE_BUFFER[PACKET_EOP_POS] = PACKET_EOP;

    write_port();
    read_port();

    return READ_BUFFER[PACKET_D0_POS];
}

void set_used_cells_count(char field, char value) {
    WRITE_BUFFER[PACKET_SOP_POS] = PACKET_SOP;
    WRITE_BUFFER[PACKET_CMD_POS] = CMD_SET_USED_CELLS_COUNT;
    WRITE_BUFFER[PACKET_D0_POS] = field;
    WRITE_BUFFER[PACKET_D1_POS] = value;
    WRITE_BUFFER[PACKET_D2_POS] = 0;
    WRITE_BUFFER[PACKET_D3_POS] = 0;
    WRITE_BUFFER[PACKET_EOP_POS] = PACKET_EOP;

    write_port();
}

char get_cell_status(char field, char row, char column) {
    WRITE_BUFFER[PACKET_SOP_POS] = PACKET_SOP;
    WRITE_BUFFER[PACKET_CMD_POS] = CMD_GET_CELL_STATUS;
    WRITE_BUFFER[PACKET_D0_POS] = field;
    WRITE_BUFFER[PACKET_D1_POS] = row;
    WRITE_BUFFER[PACKET_D2_POS] = column;
    WRITE_BUFFER[PACKET_D3_POS] = 0;
    WRITE_BUFFER[PACKET_EOP_POS] = PACKET_EOP;

    write_port();
    read_port();

    return READ_BUFFER[PACKET_D0_POS];
}

void set_cell_status(char field, char row, char column, char value) {
    WRITE_BUFFER[PACKET_SOP_POS] = PACKET_SOP;
    WRITE_BUFFER[PACKET_CMD_POS] = CMD_SET_SELL_STATUS;
    WRITE_BUFFER[PACKET_D0_POS] = field;
    WRITE_BUFFER[PACKET_D1_POS] = row;
    WRITE_BUFFER[PACKET_D2_POS] = column;
    WRITE_BUFFER[PACKET_D3_POS] = value;
    WRITE_BUFFER[PACKET_EOP_POS] = PACKET_EOP;

    write_port();
}
