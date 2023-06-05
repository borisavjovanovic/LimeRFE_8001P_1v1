#ifndef __limeLimeRFE_8001P_constants__
#define __limeLimeRFE_8001P_constants__

#include "LimeRFE_8001P.h"

#include <fcntl.h> // File control definitions
#include "LimeSuite.h"
using namespace std;
#include <string.h>
#include <math.h>

#ifdef _MSC_VER
#include <tchar.h>

#define O_NOCTTY 0
#define IXANY 0x00000800 /* any char will restart after stop */

#include <winsock2.h>
#endif // WIN

#ifdef __unix__
#include <unistd.h>
#include <termios.h> /* POSIX terminal control definitions */
#include <sys/ioctl.h>
#include <getopt.h>

// tchar.h
typedef char TCHAR;

#endif // LINUX

typedef struct LimeRFE_8001P_COM
{
#ifndef __unix__
	HANDLE hComm;
#else
	int hComm; // B.J. add com port file descriptor for unix
#endif
	int fd;
} LimeRFE_8001P_COM;

#define LimeRFE_8001P_I2C 0
#define LimeRFE_8001P_USB 1

#define LimeRFE_8001P_BUFFER_SIZE 16
#define LimeRFE_8001P_BUFFER_SIZE_MODE 2

// test
#define LimeRFE_8001P_CMD_LED_ONOFF 0xFF

#define GPIO_SCL 6
#define GPIO_SDA 7

#define LimeRFE_8001P_I2C_FSCL 100E3 // Approx. SCL frequency - ???

#define LimeRFE_8001P_CMD_HELLO 0x00

// CTRL
#define LimeRFE_8001P_CMD_MODE 0xd1
#define LimeRFE_8001P_CMD_CONFIG 0xd2
#define LimeRFE_8001P_CMD_MODE_FULL 0xd3
// #define LimeRFE_8001P_CMD_CONFIG_FULL             0xd4

#define LimeRFE_8001P_CMD_READ_ADC1 0xa1
#define LimeRFE_8001P_CMD_READ_ADC2 0xa2
#define LimeRFE_8001P_CMD_READ_TEMP 0xa3

#define LimeRFE_8001P_CMD_CONFGPIO45 0xb1
#define LimeRFE_8001P_CMD_SETGPIO45 0xb2
#define LimeRFE_8001P_CMD_GETGPIO45 0xb3

#define LimeRFE_8001P_CMD_FAN 0xc1

// General CTRL
// milans 220614
// #define LimeRFE_8001P_CMD_GET_INFO                0xe1
#define LimeRFE_8001P_CMD_GET_INFO 0x11
// milans 220624
#define LimeRFE_8001P_CMD_SET_CONFIG_FULL 0x12
#define LimeRFE_8001P_CMD_GET_CONFIG_FULL 0x13
// milans 220714
#define LimeRFE_8001P_CMD_RESET           0x14
//milans 221128
#define LimeRFE_8001P_CMD_LMS8_ENABLE     0x15
#define LimeRFE_8001P_CMD_SELECT_CHANNEL  0x16

// #define LimeRFE_8001P_CMD_RESET                   0xe2
//#define LimeRFE_8001P_CMD_GET_CONFIG 0xe3
// #define LimeRFE_8001P_CMD_GET_CONFIG_FULL         0xe4
//#define LimeRFE_8001P_CMD_I2C_MASTER 0xe5

// milans 220429
// #define LimeRFE_8001P_CMD_DIODE                   0xf1
//#define LimeRFE_8001P_CMD_DIODE 0x71
// milans 220506
// #define LimeRFE_8001P_CMD_DIODESPI                0xf2
//#define LimeRFE_8001P_CMD_DIODESPI 0x72

// SC1905 Control
// #define LimeRFE_8001P_CMD_SC1905_SPI_MESSAGE_MEMORY  0x91
// #define LimeRFE_8001P_CMD_SC1905_RESET               0x92
// #define LimeRFE_8001P_CMD_SC1905_SPI_SPECIAL_COMMAND 0x93
// #define LimeRFE_8001P_CMD_SC1905_SPI_EEPROM          0x94

#define LimeRFE_8001P_CMD_SC1905_SPI_MESSAGE_MEMORY 0x61
#define LimeRFE_8001P_CMD_SC1905_RESET 0x62
#define LimeRFE_8001P_CMD_SC1905_SPI_SPECIAL_COMMAND 0x63
#define LimeRFE_8001P_CMD_SC1905_SPI_EEPROM 0x64

#define LimeRFE_8001P_DISABLE 0
#define LimeRFE_8001P_ENABLE 1

#define LimeRFE_8001P_OFF 0
#define LimeRFE_8001P_ON 1

#define LimeRFE_8001P_MAX_HELLO_ATTEMPTS 10

#define LimeRFE_8001P_TIME_BETWEEN_HELLO_MS 200

#define LimeRFE_8001P_TYPE_INDEX_WB 0
#define LimeRFE_8001P_TYPE_INDEX_HAM 1
#define LimeRFE_8001P_TYPE_INDEX_CELL 2
#define LimeRFE_8001P_TYPE_INDEX_COUNT 3

#define LimeRFE_8001P_CHANNEL_INDEX_WB_1000 0
#define LimeRFE_8001P_CHANNEL_INDEX_WB_4000 1
#define LimeRFE_8001P_CHANNEL_INDEX_WB_COUNT 2

#define LimeRFE_8001P_CHANNEL_INDEX_HAM_0030 0
#define LimeRFE_8001P_CHANNEL_INDEX_HAM_0070 1
#define LimeRFE_8001P_CHANNEL_INDEX_HAM_0145 2
#define LimeRFE_8001P_CHANNEL_INDEX_HAM_0220 3
#define LimeRFE_8001P_CHANNEL_INDEX_HAM_0435 4
#define LimeRFE_8001P_CHANNEL_INDEX_HAM_0920 5
#define LimeRFE_8001P_CHANNEL_INDEX_HAM_1280 6
#define LimeRFE_8001P_CHANNEL_INDEX_HAM_2400 7
#define LimeRFE_8001P_CHANNEL_INDEX_HAM_3500 8
#define LimeRFE_8001P_CHANNEL_INDEX_HAM_COUNT 9

#define LimeRFE_8001P_CHANNEL_INDEX_CELL_BAND01 0
#define LimeRFE_8001P_CHANNEL_INDEX_CELL_BAND02 1
#define LimeRFE_8001P_CHANNEL_INDEX_CELL_BAND03 2
#define LimeRFE_8001P_CHANNEL_INDEX_CELL_BAND07 3
#define LimeRFE_8001P_CHANNEL_INDEX_CELL_BAND38 4
#define LimeRFE_8001P_CHANNEL_INDEX_CELL_COUNT 5

#define LimeRFE_8001P_PORT_1_NAME "TX/RX (J3)"		   // J3 - TX/RX
#define LimeRFE_8001P_PORT_2_NAME "TX (J4)"		   // J4 - TX
#define LimeRFE_8001P_PORT_3_NAME "30 MHz TX/RX (J5)" // J5 - 30 MHz TX/RX

#define LimeRFE_8001P_TXRX_VALUE_RX 0
#define LimeRFE_8001P_TXRX_VALUE_TX 1

#define LimeRFE_8001P_NOTCH_DEFAULT 0

#define LimeRFE_8001P_NOTCH_BIT_OFF 1
#define LimeRFE_8001P_NOTCH_BIT_ON 0

#define LimeRFE_8001P_NOTCH_BYTE 8
#define LimeRFE_8001P_NOTCH_BIT 0
#define LimeRFE_8001P_ATTEN_BYTE 12
#define LimeRFE_8001P_ATTEN_BIT 0 // LSB bit - Attenuation is 3-bit value
#define LimeRFE_8001P_PORTTX_BYTE 11
#define LimeRFE_8001P_PORTTX_BIT 5

#define LimeRFE_8001P_MODE_RX 0
#define LimeRFE_8001P_MODE_TX 1
#define LimeRFE_8001P_MODE_NONE 2
#define LimeRFE_8001P_MODE_TXRX 3

#define LimeRFE_8001P_MCU_BYTE_PA_EN_BIT 0
#define LimeRFE_8001P_MCU_BYTE_LNA_EN_BIT 1
#define LimeRFE_8001P_MCU_BYTE_TXRX0_BIT 2
#define LimeRFE_8001P_MCU_BYTE_TXRX1_BIT 3
#define LimeRFE_8001P_MCU_BYTE_RELAY_BIT 4

#define LimeRFE_8001P_CHANNEL_RX 0
#define LimeRFE_8001P_CHANNEL_TX 1

typedef struct
{
	unsigned char status1;
	unsigned char status2;
	unsigned char fw_ver;
	unsigned char hw_ver;
} Limerfe_8001p_boardInfo;

struct Limerfe_8001p_guiState
{
	double powerCellCorr;
	double powerCorr;
	double rlCorr;
};

#if __cplusplus
extern "C"
{
#endif

	int Limerfe_8001p_write_buffer_fd(LimeRFE_8001P_COM com, unsigned char *c, int size);
	int Limerfe_8001p_read_buffer_fd(LimeRFE_8001P_COM com, unsigned char *data, int size);
	int Limerfe_8001p_write_buffer(lms_device_t *dev, LimeRFE_8001P_COM com, unsigned char *data, int size);
	int Limerfe_8001p_read_buffer(lms_device_t *dev, LimeRFE_8001P_COM com, unsigned char *data, int size);

	//int Limerfe_8001p_spi_read_buffer2(lms_device_t *lms, unsigned char *c, int size);
	int Limerfe_8001p_spi_read_buffer(lms_device_t *lms, unsigned char *c, int size);  // B.J.
	int Limerfe_8001p_spi_write_buffer(lms_device_t *lms, unsigned char *c, int size);
	


	int Limerfe_8001p_my_read(LimeRFE_8001P_COM com, char *buffer, int count);
	int Limerfe_8001p_my_write(LimeRFE_8001P_COM com, char *buffer, int count);
	int Limerfe_8001p_serialport_write(LimeRFE_8001P_COM com, const char *str, int len);
	int Limerfe_8001p_serialport_read(LimeRFE_8001P_COM com, char *buff, int len);
	int Limerfe_8001p_serialport_init(const char *serialport, int baud, LimeRFE_8001P_COM *com);
	int Limerfe_8001p_serialport_close(LimeRFE_8001P_COM com);
	int Limerfe_8001p_Cmd_GetInfo(lms_device_t *dev, LimeRFE_8001P_COM com, Limerfe_8001p_boardInfo *info);
	int Limerfe_8001p_Cmd_GetConfig(lms_device_t *dev, LimeRFE_8001P_COM com, limerfe_8001p_boardState *state);
	int Limerfe_8001p_Cmd_Hello(lms_device_t *dev, LimeRFE_8001P_COM com);
	int Limerfe_8001p_Cmd_LoadConfig(lms_device_t *dev, LimeRFE_8001P_COM com, const char *filename);
	int Limerfe_8001p_Cmd_SaveConfig(lms_device_t *dev, LimeRFE_8001P_COM com, const char *filename);
	int Limerfe_8001p_Cmd_Reset(lms_device_t *dev, LimeRFE_8001P_COM com);
//milans 221128
	int Limerfe_8001p_Cmd_lms8_Enable(lms_device_t* dev, LimeRFE_8001P_COM com, uint8_t value);
//milans 221130
	int Limerfe_8001p_Cmd_Select_Channel(lms_device_t* dev, LimeRFE_8001P_COM com, uint8_t channel);
	//	int Limerfe_8001p_Cmd_ConfigureState(lms_device_t* dev, LimeRFE_8001P_COM com, limerfe_8001p_boardState state);
	//	int Limerfe_8001p_Cmd_Configure(lms_device_t *dev, LimeRFE_8001P_COM com, int channelIDRX, int channelIDTX = -1, int selPortRX = 0, int selPortTX = 0, int mode = 0, int notch = 0, int attenuation = 0, int enableSWR = 0, int sourceSWR = 0);
	int Limerfe_8001p_Cmd_Configure(lms_device_t *dev, LimeRFE_8001P_COM com, limerfe_8001p_boardState state);
//	int Limerfe_8001p_Cmd_Mode(lms_device_t *dev, LimeRFE_8001P_COM com, int mode);
//	int Limerfe_8001p_Cmd_ReadADC(lms_device_t *dev, LimeRFE_8001P_COM com, int adcID, int *value);
//	int Limerfe_8001p_Cmd_Cmd(lms_device_t *dev, LimeRFE_8001P_COM com, unsigned char *buf);
//	int Limerfe_8001p_Cmd_ConfGPIO(lms_device_t *dev, LimeRFE_8001P_COM com, int gpioNum, int direction);
//	int Limerfe_8001p_Cmd_SetGPIO(lms_device_t *dev, LimeRFE_8001P_COM com, int gpioNum, int val);
//	int Limerfe_8001p_Cmd_GetGPIO(lms_device_t *dev, LimeRFE_8001P_COM com, int gpioNum, int *val);
//	int Limerfe_8001p_Cmd_Fan(lms_device_t *dev, LimeRFE_8001P_COM com, int enable);

	// milans 220429
//	int Limerfe_8001p_Cmd_Diode(lms_device_t *dev, LimeRFE_8001P_COM com, int state);
	// milans 220506
//	int Limerfe_8001p_Cmd_DiodeSPI(lms_device_t *dev, LimeRFE_8001P_COM com, int state);
	// milans 220520
	int Limerfe_8001p_Cmd_SC1905_SPI_Message_Memory(lms_device_t *dev, LimeRFE_8001P_COM com, uint16_t address, uint8_t *val, bool isRead, int bytesNo, bool isEEPROM = false);
	// milans 220526
	int Limerfe_8001p_Cmd_SC1905_Reset(lms_device_t *dev, LimeRFE_8001P_COM com);
	// milans 220527
	int Limerfe_8001p_Cmd_SC1905_Apply_Frequency(lms_device_t *dev, LimeRFE_8001P_COM com, int freqRange, int minFreq, int maxFreq);
	
	// B.J.
	int Limerfe_8001p_Cmd_SC1905S_Set_Duty_Cycle_Feedback(lms_device_t *dev, LimeRFE_8001P_COM com, uint8_t Enabled);
	int Limerfe_8001p_Cmd_SC1905S_Set_Adaptation_State(lms_device_t *dev, LimeRFE_8001P_COM com, uint8_t Running);
	int Limerfe_8001p_Cmd_SC1905S_Set_Correction_Enable(lms_device_t *dev, LimeRFE_8001P_COM com, uint8_t Enabled);
	int Limerfe_8001p_Cmd_SC1905S_Read_RFIN_AGC(lms_device_t *dev, LimeRFE_8001P_COM com, int * rfinAgc);
	int Limerfe_8001p_Cmd_SC1905S_Read_RFFB_AGC(lms_device_t *dev, LimeRFE_8001P_COM com, int * rffbAgc);
	int Limerfe_8001p_Cmd_SC1905S_Read_Center_Frequency(lms_device_t *dev, LimeRFE_8001P_COM com, float * centerFreq);
	int Limerfe_8001p_Cmd_SC1905S_Read_Signal_Bandwidth(lms_device_t *dev, LimeRFE_8001P_COM com, float * bandwidth);
	int Limerfe_8001p_Cmd_SC1905S_Read_Error_Code(lms_device_t *dev, LimeRFE_8001P_COM com, char * stringValue);
	int Limerfe_8001p_Cmd_SC1905S_Read_Warning_Code(lms_device_t *dev, LimeRFE_8001P_COM com, char * stringValue);
	int Limerfe_8001p_Cmd_SC1905_GetStatus(lms_device_t *dev, LimeRFE_8001P_COM com, char * statusString);

	// milans 220530
	int Limerfe_8001p_Cmd_SC1905_SPI_Special_Command(lms_device_t *dev, LimeRFE_8001P_COM com, int command);
	// milans 220624
	int Limerfe_8001p_Cmd_Set_Config_Full(lms_device_t *dev, LimeRFE_8001P_COM com, uint8_t *state, int size);
	// milans 220715
	int Limerfe_8001p_Cmd_Get_Config_Full(lms_device_t *dev, LimeRFE_8001P_COM com, uint8_t *state, int size);

	//	int ReadConfig(const char *filename, limerfe_8001p_boardState *stateBoard, guiState *stateGUI);
	int Limerfe_8001p_ReadConfig(const char *filename, limerfe_8001p_boardState *stateBoard);

	// milans 220722
	//	int Limerfe_8001p_SaveConfig(const char *filename, limerfe_8001p_boardState state, guiState stateGUI);
	int Limerfe_8001p_WriteConfig(const char *filename, limerfe_8001p_boardState state);

	/************************************************************************
	 * I2C Functions
	 *************************************************************************/
/*
	void Limerfe_8001p_mySleep(double sleepms);
	void Limerfe_8001p_i2c_dly(void);
	int Limerfe_8001p_i2c_setVal(lms_device_t *lms, int bitGPIO, int value);
	int Limerfe_8001p_i2c_getVal(lms_device_t *lms, int bitGPIO);
	int Limerfe_8001p_i2c_start(lms_device_t *lms);
	int Limerfe_8001p_i2c_stop(lms_device_t *lms);
	int Limerfe_8001p_i2c_rx(lms_device_t *lms, char ack, unsigned char *d);
	int Limerfe_8001p_i2c_tx(lms_device_t *lms, unsigned char d);
	int Limerfe_8001p_i2c_write_buffer(lms_device_t *lms, unsigned char *c, int size);
	int Limerfe_8001p_i2c_read_buffer(lms_device_t *lms, unsigned char *c, int size);
*/
//B.J.
int Limerfe_8001p_SPI_write(lms_device_t *lms, uint16_t maddress, uint16_t address, uint16_t data);
int Limerfe_8001p_SPI_read(lms_device_t *lms, uint16_t maddress, uint16_t address, uint16_t *data);
int Limerfe_8001p_ADF4002_config(lms_device_t *lms, LimeRFE_8001P_COM com, double freq, int & rcount,	int & ncount);

#if __cplusplus
}
#endif

#endif // __limeLimeRFE_8001P_constants__
