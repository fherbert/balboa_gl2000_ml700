#include <stdio.h>
#include <stdint.h>
#include <string.h>

uint8_t calculateCRC(uint8_t *data,uint8_t dataLength)
{
  unsigned long crc;
  int i, bit;

  crc = data[0];
  for ( i = 0 ; i < dataLength ; i++ ) {
    crc ^= data[i];
    for ( bit = 0 ; bit < 8 ; bit++ ) {
      if ( (crc & 0x80) != 0 ) {
        crc <<= 1;
        crc ^= 0x7;
      } else {
        crc <<= 1;
      }
    }
  }
  return crc ^ 0;
}

// Define the size of the prefix, command, and CRC arrays
#define START_SIZE 2
#define ID_SIZE 3
#define COMMAND_SIZE 3
#define CRC_SIZE 1
#define CRC_CALC_SIZE (START_SIZE + ID_SIZE + COMMAND_SIZE)
#define TOTAL_COMMAND_SIZE (START_SIZE + ID_SIZE + COMMAND_SIZE + CRC_SIZE)

const uint8_t FB_PREFIX[START_SIZE]   = {0xFB,0x06};
const uint8_t PANEL_ID[ID_SIZE]  = {0x64,0xD4,0x06};

// Enum to represent the possible commands
typedef enum {
    COMMAND_EMPTY,
    COMMAND_UP,
    COMMAND_DOWN
} CommandType;

// Function to set the command based on the enum
void setCommand(uint8_t* command, CommandType cmd) {
    uint8_t data[3];
    switch (cmd) {
    case COMMAND_EMPTY:
        data[0] = 0x00;
        data[1] = 0x00;
        data[2] = 0xFF;
        break;
    case COMMAND_UP:
        data[0] = 0x00;
        data[1] = 0x01;
        data[2] = 0xFE;
        break;
    case COMMAND_DOWN:
        data[0] = 0x00;
        data[1] = 0x02;
        data[2] = 0xFD;
        break;
    default:
        // Handle invalid choice
        printf("Invalid choice. Using empty command.\n");
        data[0] = 0x00;
        data[1] = 0x00;
        data[2] = 0xFF;
        break;
    }
    memcpy(command, data, 3);
}

void sendCommand(CommandType cmd) {
    uint8_t command[TOTAL_COMMAND_SIZE];
    memcpy(command, FB_PREFIX, START_SIZE);
    memcpy(command + START_SIZE, PANEL_ID, ID_SIZE);
    setCommand(command + START_SIZE + ID_SIZE, cmd);
    uint8_t crc = calculateCRC(command, CRC_CALC_SIZE);
    memcpy(command + CRC_CALC_SIZE, &crc, CRC_SIZE);
    printf("Message: ");
    for (int i = 0; i < TOTAL_COMMAND_SIZE; i++) {
        printf("0x%02X ", command[i]);
    }
    printf("\n");
}

int main() {
    int userInput;
    printf("Select a command:\n (0): Empty\n (1): Up\n (2): Down\n");
    scanf("%d", &userInput);
    sendCommand((CommandType)userInput);
    return 0;
}
