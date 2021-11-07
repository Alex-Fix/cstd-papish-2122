#include <project.h>

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
    
// main constants
#define MAP_SIZE 10
    
// structures
struct battle_field {
	char hited_cells_count;
	char used_cells_count;
	char cells_statuses[MAP_SIZE][MAP_SIZE];
} field_a, field_b;

uint8 i2cReadBuffer[PACKET_SIZE];
uint8 i2cWriteBuffer[PACKET_SIZE];

char get_hited_cells_count(char field){
    if(field == FIELD_A) {
        return field_a.hited_cells_count;
    }
    else if(field == FIELD_B) {
        return field_b.hited_cells_count;
    }
    
    return -1;
}

void set_hited_cells_count(char field, char value) {
    if(field == FIELD_A) {
        field_a.hited_cells_count = value;
    }
    else if(field == FIELD_B) {
        field_b.hited_cells_count = value;
    }
}

char get_used_cells_count(char field){
    if(field == FIELD_A) {
        return field_a.used_cells_count;
    }
    else if(field == FIELD_B) {
        return field_b.used_cells_count;
    }
    
    return -1;
}

void set_used_cells_count(char field, char value) {
    if(field == FIELD_A) {
        field_a.used_cells_count = value;
    }
    else if(field == FIELD_B) {
        field_b.used_cells_count = value;
    }
}

char get_cell_status(char field, char row, char column){
    if(field == FIELD_A) {
        return field_a.cells_statuses[row][column];
    }
    else if(field == FIELD_B) {
        return field_b.cells_statuses[row][column];
    }
    
    return -1;
}

void set_cell_status(char field, char row, char column, char value) {
    if(field == FIELD_A) {
        field_a.cells_statuses[row][column] = value;
    }
    else if(field == FIELD_B) {
        field_b.cells_statuses[row][column] = value;
    }
}

void fake_data() {
    char index = 0;
    
    field_a.used_cells_count = index++;
    field_a.hited_cells_count = index++;
    
    for(int i = 0; i < MAP_SIZE; ++i) {
        for(int j = 0; j < MAP_SIZE; ++j) {
            field_a.cells_statuses[i][j] = index++;
        }
    }
    
    index = 127;
    
    field_b.used_cells_count = index--;
    field_b.hited_cells_count = index--;
    
    for(int i = 0; i < MAP_SIZE; ++i) {
        for(int j = 0; j < MAP_SIZE; ++j) {
            field_b.cells_statuses[i][j] = index--;
        }
    }
}

int main()
{
    CyGlobalIntEnable;
    
    I2CS_I2CSlaveInitReadBuf (i2cReadBuffer,  PACKET_SIZE);
    I2CS_I2CSlaveInitWriteBuf(i2cWriteBuffer, PACKET_SIZE);
    I2CS_Start();
    
    fake_data();
    
    for (;;)
    {
        if (0u != (I2CS_I2CSlaveStatus() & I2CS_I2C_SSTAT_WR_CMPLT))
        {
            if (PACKET_SIZE == I2CS_I2CSlaveGetWriteBufSize())
            {
                if (
                    (i2cWriteBuffer[PACKET_SOP_POS] == PACKET_SOP)
                    && (i2cWriteBuffer[PACKET_EOP_POS] == PACKET_EOP)
                )
                {
                    switch(i2cWriteBuffer[PACKET_CMD_POS]){
                    case CMD_GET_USED_CELLS_COUNT:
                        i2cReadBuffer[PACKET_D0_POS] = get_used_cells_count(i2cWriteBuffer[PACKET_D0_POS]);
                        break;
                    case CMD_SET_USED_CELLS_COUNT:
                        set_used_cells_count(i2cWriteBuffer[PACKET_D0_POS], i2cWriteBuffer[PACKET_D1_POS]);
                        break;
                    case CMD_GET_HITED_CELLS_COUNT:
                        i2cReadBuffer[PACKET_D0_POS] = get_hited_cells_count(i2cWriteBuffer[PACKET_D0_POS]);
                        break;
                    case CMD_SET_HITED_CELLS_COUNT:
                        set_hited_cells_count(i2cWriteBuffer[PACKET_D0_POS], i2cWriteBuffer[PACKET_D1_POS]);
                        break;
                    case CMD_GET_CELL_STATUS:
                        i2cReadBuffer[PACKET_D0_POS] = get_cell_status(i2cWriteBuffer[PACKET_D0_POS], i2cWriteBuffer[PACKET_D1_POS], i2cWriteBuffer[PACKET_D2_POS]);
                        break;
                    case CMD_SET_SELL_STATUS:
                        set_cell_status(i2cWriteBuffer[PACKET_D0_POS], i2cWriteBuffer[PACKET_D1_POS], i2cWriteBuffer[PACKET_D2_POS], i2cWriteBuffer[PACKET_D3_POS]);
                        break;
                }
                }
            }
            
            I2CS_I2CSlaveClearWriteBuf();
            (void) I2CS_I2CSlaveClearWriteStatus();
        }
        
        if (0u != (I2CS_I2CSlaveStatus() & I2CS_I2C_SSTAT_RD_CMPLT))
        {
            I2CS_I2CSlaveClearReadBuf();
            (void) I2CS_I2CSlaveClearReadStatus();
        }
    }
}