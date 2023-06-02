#include "LimeRFE_8001P_constants.h"
#include "INI.h"
#include <chrono>

// B.J. commented 24.11.2022
// remove comment when SPI connection is used
/// #include "lime/lms7_device.h"

#include <iostream>

// B.J. commented 24.11.2022
#include <thread>
// #include "LimeSuite.h"

#define MADDRESS 170 * 32
#define MADDRESS2 171 * 32
/*********************************************************************************************
 * USB Communication
 **********************************************************************************************/

int Limerfe_8001p_my_read(LimeRFE_8001P_COM com, char *buffer, int count)
{
	int result;
#ifdef __unix__
	result = read(com.fd, buffer, count);
#else
	int rc = 0;
	int ret;

	DWORD rc_dw = 0;
	ret = ReadFile(com.hComm, buffer, count, &rc_dw, NULL);
	rc = rc_dw;

	result = (ret == 0) ? -1 : rc;

#endif // LINUX
	return result;
}

int Limerfe_8001p_my_write(LimeRFE_8001P_COM com, char *buffer, int count)
{
	int result;
#ifdef __unix__
	result = write(com.fd, buffer, count);
#else
	int rc = 0;
	int ret;

	DWORD rc_dw = 0;
	ret = WriteFile(com.hComm, buffer, count, &rc_dw, NULL);
	rc = rc_dw;

	result = (ret == 0) ? -1 : rc;

#endif // LINUX
	return result;
}

int Limerfe_8001p_serialport_write(LimeRFE_8001P_COM com, const char *str, int len)
{
	char *cstr = (char *)str;
	return Limerfe_8001p_my_write(com, cstr, len);
}

int Limerfe_8001p_serialport_read(LimeRFE_8001P_COM com, char *buff, int len)
{
	int n = Limerfe_8001p_my_read(com, buff, len);
	return n;
}

// takes the string name of the serial port (e.g. "/dev/tty.usbserial","COM1")
// and a baud rate (bps) and connects to that port at that speed and 8N1.
// opens the port in fully raw mode so you can send binary data.
// returns valid fd, or -1 on error
int Limerfe_8001p_serialport_init(const char *serialport, int baud, LimeRFE_8001P_COM *com)
{

	char *cserialport = (char *)serialport;

	int result = 0;
#ifdef __unix__

	struct termios toptions;

	int fd = open(cserialport, O_RDWR | O_NOCTTY);
	if (fd == -1)
		return -1;

	com->fd = fd;

	int res;

	res = tcgetattr(com->fd, &toptions);

	if (res < 0)
	{
		perror("init_serialport: Couldn't get term attributes");
		return -1;
	}

	speed_t brate = baud; // let you override switch below if needed
	switch (baud)
	{
	case 4800:
		brate = B4800;
		break;
	case 9600:
		brate = B9600;
		break;
		// if you want these speeds, uncomment these and set #defines if Linux
		// #ifndef OSNAME_LINUX
		//    case 14400:  brate=B14400;  break;
		// #endif
	case 19200:
		brate = B19200;
		break;
		// #ifndef OSNAME_LINUX
		//     case 28800:  brate=B28800;  break;
		// #endif
		// case 28800:  brate=B28800;  break;
	case 38400:
		brate = B38400;
		break;
	case 57600:
		brate = B57600;
		break;
	case 115200:
		brate = B115200;
		break;
	}
	cfsetispeed(&toptions, brate);
	cfsetospeed(&toptions, brate);

	// 8N1
	toptions.c_cflag &= ~PARENB;
	toptions.c_cflag &= ~CSTOPB;
	toptions.c_cflag &= ~CSIZE;
	toptions.c_cflag |= CS8;
	// no flow control
	toptions.c_cflag &= ~CRTSCTS;
	toptions.c_cflag |= CREAD | CLOCAL;					 // turn on READ & ignore ctrl lines
	toptions.c_iflag &= ~(IXON | IXOFF | IXANY);		 // turn off s/w flow ctrl
	toptions.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // make raw
	toptions.c_oflag &= ~OPOST;							 // make raw
														 // see: http://unixwiz.net/techtips/termios-vmin-vtime.html
	toptions.c_cc[VMIN] = 0;
	toptions.c_cc[VTIME] = 20;

	res = tcsetattr(com->fd, TCSANOW, &toptions);

	if (res < 0)
	{
		perror("init_serialport: Couldn't set term attributes");
		return -1;
	}

	// for unix
	com->hComm = com->fd; // B.J.

#else
	HANDLE hComm;
	char *port;

	if (strlen(serialport) < 4)
		return -1;

	// COMxx/COMxxx
	if (strlen(serialport) > 4)
	{
		port = (char *)calloc(1, sizeof(char) * strlen("\\\\.\\COM100") + 1);
		strncat(port, "\\\\.\\", strlen("\\\\.\\"));
	}
	// COMx
	else
	{
		port = (char *)calloc(1, sizeof(char) * 5);
	}
	strncat(port, serialport, strlen(serialport));

	// #ifdef _UNICODE
	//	wchar_t wport[20];
	//	mbstowcs(wport, port, strlen(port) + 1);//Plus null
	//
	//	hComm = CreateFileW(wport, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	// #else
	//	hComm = CreateFileA(port, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	// #endif

	// milans 220421 TMP TMP TMP TMP!!!!!!
	hComm = CreateFileA(port, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

	free(port);

	if (hComm == INVALID_HANDLE_VALUE)
	{
		result = -1;
	}

	DCB dcbSerialParams = {0}; // Initializing DCB structure
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

	//	After that retrieve the current settings of the serial port using the GetCommState() function.
	bool status = GetCommState(hComm, &dcbSerialParams);

	//	and set the values for Baud rate, Byte size, Number of start / Stop bits etc.
	dcbSerialParams.BaudRate = CBR_9600;   // Setting BaudRate = 9600
	dcbSerialParams.ByteSize = 8;		   // Setting ByteSize = 8
	dcbSerialParams.StopBits = ONESTOPBIT; // Setting StopBits = 1
	dcbSerialParams.Parity = NOPARITY;	   // Setting Parity = None

	// milans 220421
	dcbSerialParams.fDtrControl = DTR_CONTROL_ENABLE;
	//	dcbSerialParams.fDtrControl = DTR_CONTROL_DISABLE;  //Disable DTR, because in Windows each time the port opens the Arduino is reset
	SetCommState(hComm, &dcbSerialParams);

	// milans 220421
	PurgeComm(hComm, PURGE_RXCLEAR | PURGE_TXCLEAR);

	// Set timeouts
	COMMTIMEOUTS timeouts = {0};
	timeouts.ReadIntervalTimeout = 50;		   // in milliseconds
	timeouts.ReadTotalTimeoutConstant = 50;	   // in milliseconds
	timeouts.ReadTotalTimeoutMultiplier = 10;  // in milliseconds
	timeouts.WriteTotalTimeoutConstant = 50;   // in milliseconds
	timeouts.WriteTotalTimeoutMultiplier = 10; // in milliseconds

	if (!SetCommTimeouts(hComm, &timeouts))
	{
		return -1;
	}

	com->hComm = hComm;
	com->fd = 0;					  // Set to a value greater than -1, so the direct USB connection can be checked by if(com.fd >= 0)

#endif // LINUX

	return 0;
}

int Limerfe_8001p_serialport_close(LimeRFE_8001P_COM com)
{
	int result;
#ifdef __unix__
	result = close(com.fd);
#else
	int ret = CloseHandle(com.hComm); // Closing the Serial Port
	result = (ret != 0) ? 0 : -1;

#endif // LINUX
	return result;
}

int Limerfe_8001p_spi_write_buffer(lms_device_t *lms, unsigned char *c, int size);
int Limerfe_8001p_spi_read_buffer(lms_device_t *lms, unsigned char *c, int size);
void ConvertToAscii(uint8_t ch, uint8_t *pX10, uint8_t *pX1);

int Limerfe_8001p_write_buffer(lms_device_t *dev, LimeRFE_8001P_COM com, unsigned char *data, int size)
{
	if (com.fd >= 0)
	{ // prioritize direct connection
		return Limerfe_8001p_write_buffer_fd(com, data, size);
	}
	else if (dev != NULL)
	{
		// B.J.
		// return Limerfe_8001p_i2c_write_buffer(dev, data, size);
		return Limerfe_8001p_spi_write_buffer(dev, data, size);
	}
	return -1; // error: both dev and fd are invalid
}

int Limerfe_8001p_write_buffer_fd(LimeRFE_8001P_COM com, unsigned char *c, int size)
{
	int actual_length;
	actual_length = Limerfe_8001p_serialport_write(com, (char *)c, size);
	if (actual_length != size)
	{
		return -1;
	}
	return 0;
}

int Limerfe_8001p_read_buffer(lms_device_t *dev, LimeRFE_8001P_COM com, unsigned char *data, int size)
{
	if (com.fd >= 0)
	{ // prioritize direct connection
		return Limerfe_8001p_read_buffer_fd(com, data, size);
	}
	else if (dev != NULL)
	{
		// B.J.
		// return Limerfe_8001p_i2c_read_buffer(dev, data, size);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));

		// B.J.  it must be at least 100ms delay because of SC1905
		return Limerfe_8001p_spi_read_buffer(dev, data, size);
	}
	return -1; // error: both dev and fd are invalid
}

int Limerfe_8001p_read_buffer_fd(LimeRFE_8001P_COM com, unsigned char *data, int size)
{
	memset(data, 0, size);
	int received = 0;
	auto t1 = std::chrono::high_resolution_clock::now();
	do
	{
		int count = Limerfe_8001p_serialport_read(com, (char *)data + received, size - received);
		if (count > 0)
			received += count;
		if (received >= size)
			break;
	} while (std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - t1).count() < 1.0); // timeout
	return received;
}

//******* Command Definitions *******
#define sbi(p, n) ((p) |= (1UL << (n)))
#define cbi(p, n) ((p) &= ~(1 << (n)))

void setStateBit(uint8_t *state, int byte, int bit, int value)
{
	if (value == 0)
		cbi(state[byte], bit);
	else
		sbi(state[byte], bit);
}

int getStateBit(uint8_t *state, int byte, int bit)
{
	int result;

	result = (state[byte] >> bit) & 0x01;

	return result;
}

int Limerfe_8001p_Cmd_GetInfo(lms_device_t *dev, LimeRFE_8001P_COM com, Limerfe_8001p_boardInfo *info)
{
	unsigned char buf[LimeRFE_8001P_BUFFER_SIZE];
	int len;

	memset(buf, 0, LimeRFE_8001P_BUFFER_SIZE);

	buf[0] = LimeRFE_8001P_CMD_GET_INFO;
	if (Limerfe_8001p_write_buffer(dev, com, buf, LimeRFE_8001P_BUFFER_SIZE) != 0)
		return LimeRFE_8001P_ERROR_COMM;
	len = Limerfe_8001p_read_buffer(dev, com, buf, LimeRFE_8001P_BUFFER_SIZE);
	if (len != LimeRFE_8001P_BUFFER_SIZE)
		return (LimeRFE_8001P_ERROR_COMM);

	info->fw_ver = buf[1];	// FW_VER
	info->hw_ver = buf[2];	// HW_VER
	info->status1 = buf[3]; // Status
	info->status2 = buf[4]; // Status

	return LimeRFE_8001P_SUCCESS;
}

// int Limerfe_8001p_ReadConfig(const char *filename, limerfe_8001p_boardState *stateBoard, guiState *stateGUI) {
int Limerfe_8001p_ReadConfig(const char *filename, limerfe_8001p_boardState *stateBoard)
{
	typedef INI<string, string, string> ini_t;
	ini_t parser(filename, true);

	//	if (parser.select("LimeLimeRFE_8001P_Board_Settings") == false)
	if (parser.select("LimeRFE_8001P_Board_Settings") == false)
		return LimeRFE_8001P_ERROR_CONF_FILE;
	/*
		stateBoard->channelIDRX = parser.get("channelIDRX", 0);
		stateBoard->channelIDTX = parser.get("channelIDTX", 0);
		stateBoard->selPortRX = parser.get("selPortRX", 0);
		stateBoard->selPortTX = parser.get("selPortTX", 0);
		stateBoard->notchOnOff = parser.get("notchOnOff", 0);
		stateBoard->mode = parser.get("mode", 0);
		stateBoard->attValue = parser.get("attValue", 0);
		stateBoard->enableSWR = parser.get("enableSWR", 0);
		stateBoard->sourceSWR = parser.get("sourceSWR", 0);

		if (parser.select("LimeLimeRFE_8001P_GUI_Settings")) {
			stateGUI->powerCellCorr = parser.get("CellularPowerCorrection", 0);
			stateGUI->powerCorr = parser.get("PowerCorrection", 0);
			stateGUI->rlCorr = parser.get("GammaCorrection", 0);
		}
	*/
	stateBoard->SPI_2_MCU_DIR_OUT_in = parser.get("SPI_2_MCU_DIR_OUT_in", 0);
	stateBoard->LMS8001_1_SSENn = parser.get("LMS8001_1_SSENn", 0);
	stateBoard->LMS8001_2_SSENn = parser.get("LMS8001_2_SSENn", 0);
	stateBoard->EXT_PLL_SSENn = parser.get("EXT_PLL_SSENn", 0);
	stateBoard->LMS8001_1_RESETn = parser.get("LMS8001_1_RESETn", 0);
	stateBoard->LMS8001_2_RESETn = parser.get("LMS8001_2_RESETn", 0);
	stateBoard->SC1905_1_SSENn = parser.get("SC1905_1_SSENn", 0);
	stateBoard->SC1905_2_SSENn = parser.get("SC1905_2_SSENn", 0);
	// milans 221223
	//	stateBoard->GPIO_SEL_A_LMS8001 = parser.get("GPIO_SEL_A_LMS8001", 0);
	stateBoard->SC1905_1_RESETn = parser.get("SC1905_1_RESETn", 0);
	stateBoard->SC1905_2_RESETn = parser.get("SC1905_2_RESETn", 0);
	stateBoard->BP_AMP1 = parser.get("BP_AMP1", 0);
	stateBoard->SD_AMP1 = parser.get("SD_AMP1", 0);
	stateBoard->BP_AMP2 = parser.get("BP_AMP2", 0);
	stateBoard->SD_AMP2 = parser.get("SD_AMP2", 0);
	// milans 221223
	//	stateBoard->PA1_A_EN = parser.get("PA1_A_EN", 0);
	//	stateBoard->PA1_B_EN = parser.get("PA1_B_EN", 0);
	//	stateBoard->PA2_A_EN = parser.get("PA2_A_EN", 0);
	//	stateBoard->PA2_B_EN = parser.get("PA2_B_EN", 0);
	stateBoard->DA1_A_EN = parser.get("DA1_A_EN", 0);
	stateBoard->DA1_B_EN = parser.get("DA1_B_EN", 0);
	stateBoard->DA2_A_EN = parser.get("DA2_A_EN", 0);
	stateBoard->DA2_B_EN = parser.get("DA2_B_EN", 0);

	stateBoard->LNA1_EN = parser.get("LNA1_EN", 0);
	stateBoard->LNA2_EN = parser.get("LNA2_EN", 0);
	// milans 221223
	//	stateBoard->DA1_EN = parser.get("DA1_EN", 0);
	//	stateBoard->DA2_EN = parser.get("DA2_EN", 0);
	//	stateBoard->PA1_A_B_CTRL = parser.get("PA1_A_B_CTRL", 0);
	//	stateBoard->PA2_A_B_CTRL = parser.get("PA2_A_B_CTRL", 0);
	//	stateBoard->PA1_CPL_ATT = parser.get("PA1_CPL_ATT", 0);
	//	stateBoard->PA2_CPL_ATT = parser.get("PA2_CPL_ATT", 0);
	stateBoard->PDA1_EN = parser.get("PDA1_EN", 0);
	stateBoard->PDA2_EN = parser.get("PDA2_EN", 0);
	stateBoard->DA1_A_B_CTRL = parser.get("DA1_A_B_CTRL", 0);
	stateBoard->DA2_A_B_CTRL = parser.get("DA2_A_B_CTRL", 0);
	stateBoard->ORX1_ATT = parser.get("ORX1_ATT", 0);
	stateBoard->ORX2_ATT = parser.get("ORX2_ATT", 0);

	// milans 221223
	stateBoard->TX1_ATT = parser.get("TX1_ATT", 0);
	stateBoard->TX2_ATT = parser.get("TX2_ATT", 0);

	stateBoard->TXRX_1 = parser.get("TXRX_1", 0);
	stateBoard->TXRX_2 = parser.get("TXRX_2", 0);

	return LimeRFE_8001P_SUCCESS;
}

// milans 220722
// int Limerfe_8001p_SaveConfig(const char *filename, limerfe_8001p_boardState state, guiState stateGUI) {
int Limerfe_8001p_WriteConfig(const char *filename, limerfe_8001p_boardState state)
{
	FILE *fout;
	fout = fopen(filename, "w");

	if (fout == NULL)
	{
		fclose(fout);
		return 1;
	}

	fprintf(fout, "[LimeRFE_8001P_Board_Settings]\n");

	fprintf(fout, "SPI_2_MCU_DIR_OUT_in=%d\n", state.SPI_2_MCU_DIR_OUT_in);
	fprintf(fout, "LMS8001_1_SSENn=%d\n", state.LMS8001_1_SSENn);
	fprintf(fout, "LMS8001_2_SSENn=%d\n", state.LMS8001_2_SSENn);
	fprintf(fout, "EXT_PLL_SSENn=%d\n", state.EXT_PLL_SSENn);
	fprintf(fout, "LMS8001_1_RESETn=%d\n", state.LMS8001_1_RESETn);
	fprintf(fout, "LMS8001_2_RESETn=%d\n", state.LMS8001_2_RESETn);
	fprintf(fout, "SC1905_1_SSENn=%d\n", state.SC1905_1_SSENn);
	fprintf(fout, "SC1905_2_SSENn=%d\n", state.SC1905_2_SSENn);
	// milans 22123
	//	fprintf(fout, "GPIO_SEL_A_LMS8001=%d\n", state.GPIO_SEL_A_LMS8001);	
	fprintf(fout, "SC1905_1_RESETn=%d\n", state.SC1905_1_RESETn);
	fprintf(fout, "SC1905_2_RESETn=%d\n", state.SC1905_2_RESETn);
	fprintf(fout, "BP_AMP1=%d\n", state.BP_AMP1);
	fprintf(fout, "SD_AMP1=%d\n", state.SD_AMP1);
	fprintf(fout, "BP_AMP2=%d\n", state.BP_AMP2);
	fprintf(fout, "SD_AMP2=%d\n", state.SD_AMP2);
	// milans 22123
	//	fprintf(fout, "PA1_A_EN=%d\n", state.PA1_A_EN);
	//	fprintf(fout, "PA1_B_EN=%d\n", state.PA1_B_EN);
	//	fprintf(fout, "PA2_A_EN=%d\n", state.PA2_A_EN);
	//	fprintf(fout, "PA2_B_EN=%d\n", state.PA2_B_EN);
	fprintf(fout, "DA1_A_EN=%d\n", state.DA1_A_EN);
	fprintf(fout, "DA1_B_EN=%d\n", state.DA1_B_EN);
	fprintf(fout, "DA2_A_EN=%d\n", state.DA2_A_EN);
	fprintf(fout, "DA2_B_EN=%d\n", state.DA2_B_EN);

	fprintf(fout, "LNA1_EN=%d\n", state.LNA1_EN);
	fprintf(fout, "LNA2_EN=%d\n", state.LNA2_EN);
	// milans 221223
	//	fprintf(fout, "DA1_EN=%d\n", state.DA1_EN);
	//	fprintf(fout, "DA2_EN=%d\n", state.DA2_EN);
	//	fprintf(fout, "PA1_A_B_CTRL=%d\n", state.PA1_A_B_CTRL);
	//	fprintf(fout, "PA2_A_B_CTRL=%d\n", state.PA2_A_B_CTRL);
	//	fprintf(fout, "PA1_CPL_ATT=%d\n", state.PA1_CPL_ATT);
	//	fprintf(fout, "PA2_CPL_ATT=%d\n", state.PA2_CPL_ATT);
	fprintf(fout, "PDA1_EN=%d\n", state.PDA1_EN);
	fprintf(fout, "PDA2_EN=%d\n", state.PDA2_EN);
	fprintf(fout, "DA1_A_B_CTRL=%d\n", state.DA1_A_B_CTRL);
	fprintf(fout, "DA2_A_B_CTRL=%d\n", state.DA2_A_B_CTRL);
	fprintf(fout, "ORX1_ATT=%d\n", state.ORX1_ATT);
	fprintf(fout, "ORX2_ATT=%d\n", state.ORX2_ATT);

	// milans 221223
	fprintf(fout, "TX1_ATT=%d\n", state.TX1_ATT);
	fprintf(fout, "TX2_ATT=%d\n", state.TX2_ATT);

	fprintf(fout, "TXRX_1=%d\n", state.TXRX_1);
	fprintf(fout, "TXRX_2=%d\n", state.TXRX_2);

	fclose(fout);
	return 0;
}

// milans 221201
// ovdi!!!
int Limerfe_8001p_Cmd_GetConfig(lms_device_t *dev, LimeRFE_8001P_COM com, limerfe_8001p_boardState *boardState)
{
	unsigned char buf[LimeRFE_8001P_BUFFER_SIZE];
	int len;

	memset(buf, 0, LimeRFE_8001P_BUFFER_SIZE);

	int result = Limerfe_8001p_Cmd_Get_Config_Full(dev, com, buf, LimeRFE_8001P_BUFFER_SIZE);

	/*
		buf[0] = LimeRFE_8001P_CMD_GET_CONFIG;
		if (Limerfe_8001p_write_buffer(dev, com, buf, LimeRFE_8001P_BUFFER_SIZE) != 0)
			return LimeRFE_8001P_ERROR_COMM;
		len = Limerfe_8001p_read_buffer(dev, com, buf, LimeRFE_8001P_BUFFER_SIZE);
		if (len == -1)
			return (LimeRFE_8001P_ERROR_COMM);
	*/
	uint8_t *state = buf;

	//	uint8_t state[STATE_SIZE];
	//	memset(state, 0, STATE_SIZE);
	//	int getStateBit(uint8_t * state, int byte, int bit)

	boardState->SPI_2_MCU_DIR_OUT_in = getStateBit(state, SPI_2_MCU_DIR_OUT_in_BYTE, SPI_2_MCU_DIR_OUT_in_BIT);
	boardState->LMS8001_1_SSENn = getStateBit(state, LMS8001_1_SSENn_BYTE, LMS8001_1_SSENn_BIT);
	boardState->LMS8001_2_SSENn = getStateBit(state, LMS8001_2_SSENn_BYTE, LMS8001_2_SSENn_BIT);
	boardState->EXT_PLL_SSENn = getStateBit(state, EXT_PLL_SSENn_BYTE, EXT_PLL_SSENn_BIT);
	boardState->LMS8001_1_RESETn = getStateBit(state, LMS8001_1_RESETn_BYTE, LMS8001_1_RESETn_BIT);
	boardState->LMS8001_2_RESETn = getStateBit(state, LMS8001_2_RESETn_BYTE, LMS8001_2_RESETn_BIT);
	boardState->SC1905_1_SSENn = getStateBit(state, SC1905_1_SSENn_BYTE, SC1905_1_SSENn_BIT);
	boardState->SC1905_2_SSENn = getStateBit(state, SC1905_2_SSENn_BYTE, SC1905_2_SSENn_BIT);
	// milans 221223
	//	boardState->GPIO_SEL_A_LMS8001 = getStateBit(state, GPIO_SEL_A_LMS8001_BYTE, GPIO_SEL_A_LMS8001_BIT);
	boardState->SC1905_1_RESETn = getStateBit(state, SC1905_1_RESETn_BYTE, SC1905_1_RESETn_BIT);
	boardState->SC1905_2_RESETn = getStateBit(state, SC1905_2_RESETn_BYTE, SC1905_2_RESETn_BIT);
	boardState->BP_AMP1 = getStateBit(state, BYPASS_AMP1_BYTE, BYPASS_AMP1_BIT);
	boardState->SD_AMP1 = getStateBit(state, DISABLE_AMP1_BYTE, DISABLE_AMP1_BIT);
	boardState->BP_AMP2 = getStateBit(state, BYPASS_AMP2_BYTE, BYPASS_AMP2_BIT);
	boardState->SD_AMP2 = getStateBit(state, DISABLE_AMP2_BYTE, DISABLE_AMP2_BIT);
	// milans 22123
	//	boardState->PA1_A_EN = getStateBit(state, PA1_A_EN_BYTE, PA1_A_EN_BIT);
	//	boardState->PA1_B_EN = getStateBit(state, PA1_B_EN_BYTE, PA1_B_EN_BIT);
	//	boardState->PA2_A_EN = getStateBit(state, PA2_A_EN_BYTE, PA2_A_EN_BIT);
	//	boardState->PA2_B_EN = getStateBit(state, PA2_B_EN_BYTE, PA2_B_EN_BIT);
	boardState->DA1_A_EN = getStateBit(state, DA1_A_EN_BYTE, DA1_A_EN_BIT);
	boardState->DA1_B_EN = getStateBit(state, DA1_B_EN_BYTE, DA1_B_EN_BIT);
	boardState->DA2_A_EN = getStateBit(state, DA2_A_EN_BYTE, DA2_A_EN_BIT);
	boardState->DA2_B_EN = getStateBit(state, DA2_B_EN_BYTE, DA2_B_EN_BIT);

	boardState->LNA1_EN = getStateBit(state, LNA1_EN_BYTE, LNA1_EN_BIT);
	boardState->LNA2_EN = getStateBit(state, LNA2_EN_BYTE, LNA2_EN_BIT);
	// milans 221223
	//	boardState->DA1_EN = getStateBit(state, DA1_EN_BYTE, DA1_EN_BIT);
	//	boardState->DA2_EN = getStateBit(state, DA2_EN_BYTE, DA2_EN_BIT);
	//	boardState->PA1_A_B_CTRL = getStateBit(state, PA1_A_B_CTRL_BYTE, PA1_A_B_CTRL_BIT);
	//	boardState->PA2_A_B_CTRL = getStateBit(state, PA2_A_B_CTRL_BYTE, PA2_A_B_CTRL_BIT);
	boardState->PDA1_EN = getStateBit(state, PDA1_EN_BYTE, PDA1_EN_BIT);
	boardState->PDA2_EN = getStateBit(state, PDA2_EN_BYTE, PDA2_EN_BIT);
	boardState->DA1_A_B_CTRL = getStateBit(state, DA1_A_B_CTRL_BYTE, DA1_A_B_CTRL_BIT);
	boardState->DA2_A_B_CTRL = getStateBit(state, DA2_A_B_CTRL_BYTE, DA2_A_B_CTRL_BIT);

	// milans 221223
	//	boardState->PA1_CPL_ATT =
	boardState->ORX1_ATT =
		//		pow(2, 0) * getStateBit(state, PA1_CPL_D0_BYTE, PA1_CPL_D0_BIT) +
		//		pow(2, 1) * getStateBit(state, PA1_CPL_D1_BYTE, PA1_CPL_D1_BIT) +
		//		pow(2, 2) * getStateBit(state, PA1_CPL_D2_BYTE, PA1_CPL_D2_BIT) +
		//		pow(2, 3) * getStateBit(state, PA1_CPL_D3_BYTE, PA1_CPL_D3_BIT) +
		//		pow(2, 4) * getStateBit(state, PA1_CPL_D4_BYTE, PA1_CPL_D4_BIT) +
		//		pow(2, 5) * getStateBit(state, PA1_CPL_D5_BYTE, PA1_CPL_D5_BIT) +
		//		pow(2, 6) * getStateBit(state, PA1_CPL_D6_BYTE, PA1_CPL_D6_BIT);
		pow(2, 0) * getStateBit(state, ORX1_ATT_D0_BYTE, ORX1_ATT_D0_BIT) +
		pow(2, 1) * getStateBit(state, ORX1_ATT_D1_BYTE, ORX1_ATT_D1_BIT) +
		pow(2, 2) * getStateBit(state, ORX1_ATT_D2_BYTE, ORX1_ATT_D2_BIT) +
		pow(2, 3) * getStateBit(state, ORX1_ATT_D3_BYTE, ORX1_ATT_D3_BIT) +
		pow(2, 4) * getStateBit(state, ORX1_ATT_D4_BYTE, ORX1_ATT_D4_BIT) +
		pow(2, 5) * getStateBit(state, ORX1_ATT_D5_BYTE, ORX1_ATT_D5_BIT) +
		pow(2, 6) * getStateBit(state, ORX1_ATT_D6_BYTE, ORX1_ATT_D6_BIT);

	// milans 221223
	//	boardState->PA2_CPL_ATT =
	boardState->ORX2_ATT =
		//		pow(2, 0) * getStateBit(state, PA2_CPL_D0_BYTE, PA2_CPL_D0_BIT) +
		//		pow(2, 1) * getStateBit(state, PA2_CPL_D1_BYTE, PA2_CPL_D1_BIT) +
		//		pow(2, 2) * getStateBit(state, PA2_CPL_D2_BYTE, PA2_CPL_D2_BIT) +
		//		pow(2, 3) * getStateBit(state, PA2_CPL_D3_BYTE, PA2_CPL_D3_BIT) +
		//		pow(2, 4) * getStateBit(state, PA2_CPL_D4_BYTE, PA2_CPL_D4_BIT) +
		//		pow(2, 5) * getStateBit(state, PA2_CPL_D5_BYTE, PA2_CPL_D5_BIT) +
		//		pow(2, 6) * getStateBit(state, PA2_CPL_D6_BYTE, PA2_CPL_D6_BIT);
		pow(2, 0) * getStateBit(state, ORX2_ATT_D0_BYTE, ORX2_ATT_D0_BIT) +
		pow(2, 1) * getStateBit(state, ORX2_ATT_D1_BYTE, ORX2_ATT_D1_BIT) +
		pow(2, 2) * getStateBit(state, ORX2_ATT_D2_BYTE, ORX2_ATT_D2_BIT) +
		pow(2, 3) * getStateBit(state, ORX2_ATT_D3_BYTE, ORX2_ATT_D3_BIT) +
		pow(2, 4) * getStateBit(state, ORX2_ATT_D4_BYTE, ORX2_ATT_D4_BIT) +
		pow(2, 5) * getStateBit(state, ORX2_ATT_D5_BYTE, ORX2_ATT_D5_BIT) +
		pow(2, 6) * getStateBit(state, ORX2_ATT_D6_BYTE, ORX2_ATT_D6_BIT);

	// B.J.
	boardState->TX1_ATT =
		pow(2, 0) * getStateBit(state, TX1_ATT_D0_BYTE, TX1_ATT_D0_BIT) +
		pow(2, 1) * getStateBit(state, TX1_ATT_D1_BYTE, TX1_ATT_D1_BIT) +
		pow(2, 2) * getStateBit(state, TX1_ATT_D2_BYTE, TX1_ATT_D2_BIT) +
		pow(2, 3) * getStateBit(state, TX1_ATT_D3_BYTE, TX1_ATT_D3_BIT) +
		pow(2, 4) * getStateBit(state, TX1_ATT_D4_BYTE, TX1_ATT_D4_BIT) +
		pow(2, 5) * getStateBit(state, TX1_ATT_D5_BYTE, TX1_ATT_D5_BIT) +
		pow(2, 6) * getStateBit(state, TX1_ATT_D6_BYTE, TX1_ATT_D6_BIT);

	// B.J.
	boardState->TX2_ATT =
		pow(2, 0) * getStateBit(state, TX2_ATT_D0_BYTE, TX2_ATT_D0_BIT) +
		pow(2, 1) * getStateBit(state, TX2_ATT_D1_BYTE, TX2_ATT_D1_BIT) +
		pow(2, 2) * getStateBit(state, TX2_ATT_D2_BYTE, TX2_ATT_D2_BIT) +
		pow(2, 3) * getStateBit(state, TX2_ATT_D3_BYTE, TX2_ATT_D3_BIT) +
		pow(2, 4) * getStateBit(state, TX2_ATT_D4_BYTE, TX2_ATT_D4_BIT) +
		pow(2, 5) * getStateBit(state, TX2_ATT_D5_BYTE, TX2_ATT_D5_BIT) +
		pow(2, 6) * getStateBit(state, TX2_ATT_D6_BYTE, TX2_ATT_D6_BIT);	

	boardState->TXRX_1 = getStateBit(state, MCU_BYTE, MCU_TXRX_1_BIT);
	boardState->TXRX_2 = getStateBit(state, MCU_BYTE, MCU_TXRX_2_BIT);

	boardState->ActiveChannel = getStateBit(state, MISC_BYTE, MISC_CHANNEL_BIT);

	//	setStateBit(state, MISC_BYTE, MISC_CHANNEL_BIT, cmbChannel->GetSelection());

	//	int result = LimeRFE_8001P_Set_Config_Full(limerfe_8001p, state, STATE_SIZE);
	//	return Limerfe_8001p_Cmd_Set_Config_Full(dev, com, state, STATE_SIZE);
	//	if (result != LimeRFE_8001P_SUCCESS) {
	//		PrintError(result);
	//		return;
	//	}
	/*
		state->channelIDRX = buf[1];
		state->channelIDTX = buf[2];

		state->selPortRX = buf[3];
		state->selPortTX = buf[4];

		state->mode = buf[5];

		state->notchOnOff = buf[6];
		state->attValue = buf[7];

		state->enableSWR = buf[8];
		state->sourceSWR = buf[9];
	*/
	return result;
}

void Limerfe_8001p_mySleep(int sleepms)
{
#ifdef __unix__
	usleep(sleepms * 1000); // usleep takes sleep time in us (1 millionth of a second)
#endif
#ifdef _WIN32
	Sleep(sleepms);
#endif
}

int Limerfe_8001p_Cmd_Hello(lms_device_t *dev, LimeRFE_8001P_COM com)
{
	int result = 0;
	unsigned char buf[1];
	int len;

	buf[0] = LimeRFE_8001P_CMD_HELLO;

	int attempts = 0;
	bool connected = false;

	while (!connected && (attempts < LimeRFE_8001P_MAX_HELLO_ATTEMPTS))
	{
		Limerfe_8001p_write_buffer(dev, com, buf, 1);
		Limerfe_8001p_mySleep(LimeRFE_8001P_TIME_BETWEEN_HELLO_MS);
#ifdef __unix__
		len = Limerfe_8001p_read_buffer(dev, com, buf, 1);
#else
		DWORD dwlen;
		ReadFile(com.hComm, buf, 1, &dwlen, NULL);
		len = dwlen;
#endif
		if ((len == 1) && (buf[0] == LimeRFE_8001P_CMD_HELLO))
			connected = true;
		attempts++;
	}

	result = (connected) ? 0 : LimeRFE_8001P_ERROR_COMM;
	return result;
}

int Limerfe_8001p_Cmd_LoadConfig(lms_device_t *dev, LimeRFE_8001P_COM com, const char *filename)
{
	int result = 0;

	limerfe_8001p_boardState state;
	//	guiState stateGUI;
	//	result = Limerfe_8001p_ReadConfig(filename, &state, &stateGUI);
	result = Limerfe_8001p_ReadConfig(filename, &state);
	if (result != 0)
		return result;

	result = Limerfe_8001p_Cmd_Configure(dev, com, state);
	//	result = Limerfe_8001p_Cmd_Configure(dev, com, state.channelIDRX, state.channelIDTX, state.selPortRX, state.selPortTX, state.mode, state.notchOnOff, state.attValue, state.enableSWR, state.sourceSWR);

	return result;
}


// B.J.
int Limerfe_8001p_Cmd_SaveConfig(lms_device_t *dev, LimeRFE_8001P_COM com, const char *filename)
{
	int result = 0;

	limerfe_8001p_boardState state;

	result = Limerfe_8001p_Cmd_GetConfig(dev, com, &state);
	
	if (result != 0)
		return result;

	Limerfe_8001p_WriteConfig(filename, state);
	return result;
}

int Limerfe_8001p_Cmd_Reset(lms_device_t *dev, LimeRFE_8001P_COM com)
{
	int result = 0;
	unsigned char buf[LimeRFE_8001P_BUFFER_SIZE];
	int len;

	memset(buf, 0, LimeRFE_8001P_BUFFER_SIZE);

	buf[0] = LimeRFE_8001P_CMD_RESET;

	if (Limerfe_8001p_write_buffer(dev, com, buf, LimeRFE_8001P_BUFFER_SIZE) != 0)
		return LimeRFE_8001P_ERROR_COMM;
	len = Limerfe_8001p_read_buffer(dev, com, buf, LimeRFE_8001P_BUFFER_SIZE);
	if (len == -1)
		return (LimeRFE_8001P_ERROR_COMM);

	return result;
}

// milans 221128
int Limerfe_8001p_Cmd_lms8_Enable(lms_device_t *dev, LimeRFE_8001P_COM com, uint8_t value)
{
	int result = 0;
	unsigned char buf[LimeRFE_8001P_BUFFER_SIZE];
	int len;

	memset(buf, 0, LimeRFE_8001P_BUFFER_SIZE);

	buf[0] = LimeRFE_8001P_CMD_LMS8_ENABLE;
	buf[1] = value;

	if (Limerfe_8001p_write_buffer(dev, com, buf, LimeRFE_8001P_BUFFER_SIZE) != 0)
		return LimeRFE_8001P_ERROR_COMM;
	len = Limerfe_8001p_read_buffer(dev, com, buf, LimeRFE_8001P_BUFFER_SIZE);
	if (len == -1)
		return (LimeRFE_8001P_ERROR_COMM);

	return result;
}

// milans 221130
int Limerfe_8001p_Cmd_Select_Channel(lms_device_t *dev, LimeRFE_8001P_COM com, uint8_t channel)
{
	int result = 0;
	unsigned char buf[LimeRFE_8001P_BUFFER_SIZE];
	int len;

	memset(buf, 0, LimeRFE_8001P_BUFFER_SIZE);

	buf[0] = LimeRFE_8001P_CMD_SELECT_CHANNEL;
	buf[1] = channel;

	if (Limerfe_8001p_write_buffer(dev, com, buf, LimeRFE_8001P_BUFFER_SIZE) != 0)
		return LimeRFE_8001P_ERROR_COMM;
	len = Limerfe_8001p_read_buffer(dev, com, buf, LimeRFE_8001P_BUFFER_SIZE);
	if (len == -1)
		return (LimeRFE_8001P_ERROR_COMM);

	return result;
}

/*
int Limerfe_8001p_Cmd_ConfigureState(lms_device_t* dev, LimeRFE_8001P_COM com, limerfe_8001p_boardState state)
{
	return Limerfe_8001p_Cmd_Configure(dev, com, state.channelIDRX, state.channelIDTX, state.selPortRX, state.selPortTX, state.mode, state.notchOnOff, state.attValue, state.enableSWR, state.sourceSWR);
}
*/

int Limerfe_8001p_Cmd_Configure(lms_device_t *dev, LimeRFE_8001P_COM com, limerfe_8001p_boardState boardState)
{
	uint8_t state[STATE_SIZE];

	memset(state, 0, STATE_SIZE);

	setStateBit(state, SPI_2_MCU_DIR_OUT_in_BYTE, SPI_2_MCU_DIR_OUT_in_BIT, boardState.SPI_2_MCU_DIR_OUT_in);
	setStateBit(state, LMS8001_1_SSENn_BYTE, LMS8001_1_SSENn_BIT, boardState.LMS8001_1_SSENn);
	setStateBit(state, LMS8001_2_SSENn_BYTE, LMS8001_2_SSENn_BIT, boardState.LMS8001_2_SSENn);
	setStateBit(state, EXT_PLL_SSENn_BYTE, EXT_PLL_SSENn_BIT, boardState.EXT_PLL_SSENn);
	setStateBit(state, LMS8001_1_RESETn_BYTE, LMS8001_1_RESETn_BIT, boardState.LMS8001_1_RESETn);
	setStateBit(state, LMS8001_2_RESETn_BYTE, LMS8001_2_RESETn_BIT, boardState.LMS8001_2_RESETn);
	setStateBit(state, SC1905_1_SSENn_BYTE, SC1905_1_SSENn_BIT, boardState.SC1905_1_SSENn);
	setStateBit(state, SC1905_2_SSENn_BYTE, SC1905_2_SSENn_BIT, boardState.SC1905_2_SSENn);
	// milans 221223
	//	setStateBit(state, GPIO_SEL_A_LMS8001_BYTE, GPIO_SEL_A_LMS8001_BIT, boardState.GPIO_SEL_A_LMS8001);
	setStateBit(state, SC1905_1_RESETn_BYTE, SC1905_1_RESETn_BIT, boardState.SC1905_1_RESETn);
	setStateBit(state, SC1905_2_RESETn_BYTE, SC1905_2_RESETn_BIT, boardState.SC1905_2_RESETn);
	setStateBit(state, BYPASS_AMP1_BYTE, BYPASS_AMP1_BIT, boardState.BP_AMP1);
	setStateBit(state, DISABLE_AMP1_BYTE, DISABLE_AMP1_BIT, boardState.SD_AMP1);
	setStateBit(state, BYPASS_AMP2_BYTE, BYPASS_AMP2_BIT, boardState.BP_AMP2);
	setStateBit(state, DISABLE_AMP2_BYTE, DISABLE_AMP2_BIT, boardState.SD_AMP2);
	// milans 221223
	//	setStateBit(state, PA1_A_EN_BYTE, PA1_A_EN_BIT, boardState.PA1_A_EN);
	//	setStateBit(state, PA1_B_EN_BYTE, PA1_B_EN_BIT, boardState.PA1_B_EN);
	//	setStateBit(state, PA2_A_EN_BYTE, PA2_A_EN_BIT, boardState.PA2_A_EN);
	//	setStateBit(state, PA2_B_EN_BYTE, PA2_B_EN_BIT, boardState.PA2_B_EN);
	setStateBit(state, DA1_A_EN_BYTE, DA1_A_EN_BIT, boardState.DA1_A_EN);
	setStateBit(state, DA1_B_EN_BYTE, DA1_B_EN_BIT, boardState.DA1_B_EN);
	setStateBit(state, DA2_A_EN_BYTE, DA2_A_EN_BIT, boardState.DA2_A_EN);
	setStateBit(state, DA2_B_EN_BYTE, DA2_B_EN_BIT, boardState.DA2_B_EN);

	setStateBit(state, LNA1_EN_BYTE, LNA1_EN_BIT, boardState.LNA1_EN);
	setStateBit(state, LNA2_EN_BYTE, LNA2_EN_BIT, boardState.LNA2_EN);
	// milans 221223
	//	setStateBit(state, DA1_EN_BYTE, DA1_EN_BIT, boardState.DA1_EN);
	//	setStateBit(state, DA2_EN_BYTE, DA2_EN_BIT, boardState.DA2_EN);
	//	setStateBit(state, PA1_A_B_CTRL_BYTE, PA1_A_B_CTRL_BIT, boardState.PA1_A_B_CTRL);
	//	setStateBit(state, PA2_A_B_CTRL_BYTE, PA2_A_B_CTRL_BIT, boardState.PA2_A_B_CTRL);
	setStateBit(state, PDA1_EN_BYTE, PDA1_EN_BIT, boardState.PDA1_EN);
	setStateBit(state, PDA2_EN_BYTE, PDA2_EN_BIT, boardState.PDA2_EN);
	setStateBit(state, DA1_A_B_CTRL_BYTE, DA1_A_B_CTRL_BIT, boardState.DA1_A_B_CTRL);
	setStateBit(state, DA2_A_B_CTRL_BYTE, DA2_A_B_CTRL_BIT, boardState.DA2_A_B_CTRL);

	int selection = 0;
	int selectionBits[7];
	memset(selectionBits, 0, 7 * sizeof(selectionBits[0]));

	// milans 221223
	//	selection = boardState.PA1_CPL_ATT;
	selection = boardState.ORX1_ATT;

	for (int i = 0; selection > 0; i++)
	{
		selectionBits[i] = selection % 2;
		selection = selection / 2;
	}

	// milans 221223
	//	setStateBit(state, PA1_CPL_D0_BYTE, PA1_CPL_D0_BIT, selectionBits[0]);
	//	setStateBit(state, PA1_CPL_D1_BYTE, PA1_CPL_D1_BIT, selectionBits[1]);
	//	setStateBit(state, PA1_CPL_D2_BYTE, PA1_CPL_D2_BIT, selectionBits[2]);
	//	setStateBit(state, PA1_CPL_D3_BYTE, PA1_CPL_D3_BIT, selectionBits[3]);
	//	setStateBit(state, PA1_CPL_D4_BYTE, PA1_CPL_D4_BIT, selectionBits[4]);
	//	setStateBit(state, PA1_CPL_D5_BYTE, PA1_CPL_D5_BIT, selectionBits[5]);
	//	setStateBit(state, PA1_CPL_D6_BYTE, PA1_CPL_D6_BIT, selectionBits[6]);
	setStateBit(state, ORX1_ATT_D0_BYTE, ORX1_ATT_D0_BIT, selectionBits[0]);
	setStateBit(state, ORX1_ATT_D1_BYTE, ORX1_ATT_D1_BIT, selectionBits[1]);
	setStateBit(state, ORX1_ATT_D2_BYTE, ORX1_ATT_D2_BIT, selectionBits[2]);
	setStateBit(state, ORX1_ATT_D3_BYTE, ORX1_ATT_D3_BIT, selectionBits[3]);
	setStateBit(state, ORX1_ATT_D4_BYTE, ORX1_ATT_D4_BIT, selectionBits[4]);
	setStateBit(state, ORX1_ATT_D5_BYTE, ORX1_ATT_D5_BIT, selectionBits[5]);
	setStateBit(state, ORX1_ATT_D6_BYTE, ORX1_ATT_D6_BIT, selectionBits[6]);

	// milans 221223
	//	selection = boardState.PA2_CPL_ATT;
	selection = boardState.ORX2_ATT;

	memset(selectionBits, 0, 7 * sizeof(selectionBits[0]));

	for (int i = 0; selection > 0; i++)
	{
		selectionBits[i] = selection % 2;
		selection = selection / 2;
	}

	// milans 22123
	//	setStateBit(state, PA2_CPL_D0_BYTE, PA2_CPL_D0_BIT, selectionBits[0]);
	//	setStateBit(state, PA2_CPL_D1_BYTE, PA2_CPL_D1_BIT, selectionBits[1]);
	//	setStateBit(state, PA2_CPL_D2_BYTE, PA2_CPL_D2_BIT, selectionBits[2]);
	//	setStateBit(state, PA2_CPL_D3_BYTE, PA2_CPL_D3_BIT, selectionBits[3]);
	//	setStateBit(state, PA2_CPL_D4_BYTE, PA2_CPL_D4_BIT, selectionBits[4]);
	//	setStateBit(state, PA2_CPL_D5_BYTE, PA2_CPL_D5_BIT, selectionBits[5]);
	//	setStateBit(state, PA2_CPL_D6_BYTE, PA2_CPL_D6_BIT, selectionBits[6]);
	setStateBit(state, ORX2_ATT_D0_BYTE, ORX2_ATT_D0_BIT, selectionBits[0]);
	setStateBit(state, ORX2_ATT_D1_BYTE, ORX2_ATT_D1_BIT, selectionBits[1]);
	setStateBit(state, ORX2_ATT_D2_BYTE, ORX2_ATT_D2_BIT, selectionBits[2]);
	setStateBit(state, ORX2_ATT_D3_BYTE, ORX2_ATT_D3_BIT, selectionBits[3]);
	setStateBit(state, ORX2_ATT_D4_BYTE, ORX2_ATT_D4_BIT, selectionBits[4]);
	setStateBit(state, ORX2_ATT_D5_BYTE, ORX2_ATT_D5_BIT, selectionBits[5]);
	setStateBit(state, ORX2_ATT_D6_BYTE, ORX2_ATT_D6_BIT, selectionBits[6]);


	// B.J.
	selection = boardState.TX1_ATT;

	memset(selectionBits, 0, 7 * sizeof(selectionBits[0]));

	for (int i = 0; selection > 0; i++)
	{
		selectionBits[i] = selection % 2;
		selection = selection / 2;
	}

	setStateBit(state, TX1_ATT_D0_BYTE, TX1_ATT_D0_BIT, selectionBits[0]);
	setStateBit(state, TX1_ATT_D1_BYTE, TX1_ATT_D1_BIT, selectionBits[1]);
	setStateBit(state, TX1_ATT_D2_BYTE, TX1_ATT_D2_BIT, selectionBits[2]);
	setStateBit(state, TX1_ATT_D3_BYTE, TX1_ATT_D3_BIT, selectionBits[3]);
	setStateBit(state, TX1_ATT_D4_BYTE, TX1_ATT_D4_BIT, selectionBits[4]);
	setStateBit(state, TX1_ATT_D5_BYTE, TX1_ATT_D5_BIT, selectionBits[5]);
	setStateBit(state, TX1_ATT_D6_BYTE, TX1_ATT_D6_BIT, selectionBits[6]);

	selection = boardState.TX2_ATT;

	memset(selectionBits, 0, 7 * sizeof(selectionBits[0]));

	for (int i = 0; selection > 0; i++)
	{
		selectionBits[i] = selection % 2;
		selection = selection / 2;
	}

	setStateBit(state, TX2_ATT_D0_BYTE, TX2_ATT_D0_BIT, selectionBits[0]);
	setStateBit(state, TX2_ATT_D1_BYTE, TX2_ATT_D1_BIT, selectionBits[1]);
	setStateBit(state, TX2_ATT_D2_BYTE, TX2_ATT_D2_BIT, selectionBits[2]);
	setStateBit(state, TX2_ATT_D3_BYTE, TX2_ATT_D3_BIT, selectionBits[3]);
	setStateBit(state, TX2_ATT_D4_BYTE, TX2_ATT_D4_BIT, selectionBits[4]);
	setStateBit(state, TX2_ATT_D5_BYTE, TX2_ATT_D5_BIT, selectionBits[5]);
	setStateBit(state, TX2_ATT_D6_BYTE, TX2_ATT_D6_BIT, selectionBits[6]);


	//	setStateBit(state, CHAIN_SIZE, MCU_BYTE_TXRX_1_BIT, cbTXRX_1->GetValue());
	//	setStateBit(state, CHAIN_SIZE, MCU_BYTE_TXRX_2_BIT, cbTXRX_2->GetValue());
	setStateBit(state, MCU_BYTE, MCU_TXRX_1_BIT, boardState.TXRX_1);
	setStateBit(state, MCU_BYTE, MCU_TXRX_2_BIT, boardState.TXRX_2);

	// milans 221201
	//	setStateBit(state, MISC_BYTE, MISC_CHANNEL_BIT, cmbChannel->GetSelection());
	setStateBit(state, MISC_BYTE, MISC_CHANNEL_BIT, boardState.ActiveChannel);

	//	int result = LimeRFE_8001P_Set_Config_Full(limerfe_8001p, state, STATE_SIZE);
	return Limerfe_8001p_Cmd_Set_Config_Full(dev, com, state, STATE_SIZE);
	//	if (result != LimeRFE_8001P_SUCCESS) {
	//		PrintError(result);
	//		return;
	//	}
}

/*
int Limerfe_8001p_Cmd_Configure(lms_device_t *dev, LimeRFE_8001P_COM com, int channelIDRX, int channelIDTX, int selPortRX, int selPortTX, int mode, int notch, int attenuation, int enableSWR, int sourceSWR) {

	int result = 0;

	if (channelIDTX == -1)
		channelIDTX = channelIDRX;

	unsigned char buf[LimeRFE_8001P_BUFFER_SIZE];
	int len;

	memset(buf, 0, LimeRFE_8001P_BUFFER_SIZE);

	buf[0] = LimeRFE_8001P_CMD_CONFIG;

	buf[1] = channelIDRX;
	buf[2] = channelIDTX;

	buf[3] = selPortRX;
	buf[4] = selPortTX;

	buf[5] = mode;

	buf[6] = notch;

	buf[7] = attenuation;

	buf[8] = enableSWR;
	buf[9] = sourceSWR;

	if (Limerfe_8001p_write_buffer(dev, com, buf, LimeRFE_8001P_BUFFER_SIZE) != 0)
		return LimeRFE_8001P_ERROR_COMM;
	len = Limerfe_8001p_read_buffer(dev, com, buf, LimeRFE_8001P_BUFFER_SIZE);
	if (len == -1)
		return(LimeRFE_8001P_ERROR_COMM);

	result = buf[1]; // buf[0] is the command, buf[1] is the result
	return result;
}


int Limerfe_8001p_Cmd_Mode(lms_device_t *dev, LimeRFE_8001P_COM com, int mode)
{
	int result = 0;

	unsigned char buf[LimeRFE_8001P_BUFFER_SIZE_MODE];
	int len;

	memset(buf, 0, LimeRFE_8001P_BUFFER_SIZE_MODE);

	buf[0] = LimeRFE_8001P_CMD_MODE;

	buf[1] = mode;

	if (Limerfe_8001p_write_buffer(dev, com, buf, LimeRFE_8001P_BUFFER_SIZE_MODE) != 0)
		return LimeRFE_8001P_ERROR_COMM;
	len = Limerfe_8001p_read_buffer(dev, com, buf, LimeRFE_8001P_BUFFER_SIZE_MODE);
	if (len == -1)
		return (LimeRFE_8001P_ERROR_COMM);

	result = buf[1]; // buf[0] is the command, buf[1] is the result
	return result;
}

int Limerfe_8001p_Cmd_ReadADC(lms_device_t *dev, LimeRFE_8001P_COM com, int adcID, int *value)
{
	int result = LimeRFE_8001P_SUCCESS;
	unsigned char buf[LimeRFE_8001P_BUFFER_SIZE];
	int len;

	memset(buf, 0, LimeRFE_8001P_BUFFER_SIZE);

	if (adcID == LimeRFE_8001P_ADC1)
		buf[0] = LimeRFE_8001P_CMD_READ_ADC1;
	else
		buf[0] = LimeRFE_8001P_CMD_READ_ADC2;

	if (Limerfe_8001p_write_buffer(dev, com, buf, LimeRFE_8001P_BUFFER_SIZE) != 0)
		return LimeRFE_8001P_ERROR_COMM;
	len = Limerfe_8001p_read_buffer(dev, com, buf, LimeRFE_8001P_BUFFER_SIZE);
	if (len == -1)
	{
		*value = 0;
		return (LimeRFE_8001P_ERROR_COMM);
	}

	*value = buf[2] * pow(2, 8) + buf[1];

	return result;
}

int Limerfe_8001p_Cmd_Cmd(lms_device_t *dev, LimeRFE_8001P_COM com, unsigned char *buf)
{
	int result = 0;
	int len;

	if (Limerfe_8001p_write_buffer(dev, com, buf, LimeRFE_8001P_BUFFER_SIZE) != 0)
		return LimeRFE_8001P_ERROR_COMM;
	len = Limerfe_8001p_read_buffer(dev, com, buf, LimeRFE_8001P_BUFFER_SIZE);
	if (len == -1)
		return (LimeRFE_8001P_ERROR_COMM);

	return result;
}

int Limerfe_8001p_Cmd_ConfGPIO(lms_device_t *dev, LimeRFE_8001P_COM com, int gpioNum, int direction)
{
	if ((gpioNum != LimeRFE_8001P_GPIO4) & (gpioNum != LimeRFE_8001P_GPIO5))
		return LimeRFE_8001P_ERROR_GPIO_PIN;

	int result = 0;
	unsigned char buf[LimeRFE_8001P_BUFFER_SIZE];
	int len;
	memset(buf, 0, LimeRFE_8001P_BUFFER_SIZE);

	buf[0] = LimeRFE_8001P_CMD_CONFGPIO45;
	buf[1] = gpioNum;
	buf[2] = direction;

	if (Limerfe_8001p_write_buffer(dev, com, buf, LimeRFE_8001P_BUFFER_SIZE) != 0)
		return LimeRFE_8001P_ERROR_COMM;
	len = Limerfe_8001p_read_buffer(dev, com, buf, LimeRFE_8001P_BUFFER_SIZE);
	if (len == -1)
		return (LimeRFE_8001P_ERROR_COMM);

	return result;
}

int Limerfe_8001p_Cmd_SetGPIO(lms_device_t *dev, LimeRFE_8001P_COM com, int gpioNum, int val)
{
	if ((gpioNum != LimeRFE_8001P_GPIO4) & (gpioNum != LimeRFE_8001P_GPIO5))
		return LimeRFE_8001P_ERROR_GPIO_PIN;

	int result = 0;
	unsigned char buf[LimeRFE_8001P_BUFFER_SIZE];
	int len;
	memset(buf, 0, LimeRFE_8001P_BUFFER_SIZE);

	buf[0] = LimeRFE_8001P_CMD_SETGPIO45;
	buf[1] = gpioNum;
	buf[2] = val;

	if (Limerfe_8001p_write_buffer(dev, com, buf, LimeRFE_8001P_BUFFER_SIZE) != 0)
		return LimeRFE_8001P_ERROR_COMM;
	len = Limerfe_8001p_read_buffer(dev, com, buf, LimeRFE_8001P_BUFFER_SIZE);
	if (len == -1)
		return (LimeRFE_8001P_ERROR_COMM);

	return result;
}

int Limerfe_8001p_Cmd_GetGPIO(lms_device_t *dev, LimeRFE_8001P_COM com, int gpioNum, int *val)
{
	if ((gpioNum != LimeRFE_8001P_GPIO4) & (gpioNum != LimeRFE_8001P_GPIO5))
		return LimeRFE_8001P_ERROR_GPIO_PIN;

	int result = 0;
	unsigned char buf[LimeRFE_8001P_BUFFER_SIZE];
	int len;
	memset(buf, 0, LimeRFE_8001P_BUFFER_SIZE);

	buf[0] = LimeRFE_8001P_CMD_GETGPIO45;
	buf[1] = gpioNum;

	if (Limerfe_8001p_write_buffer(dev, com, buf, LimeRFE_8001P_BUFFER_SIZE) != 0)
		return LimeRFE_8001P_ERROR_COMM;
	len = Limerfe_8001p_read_buffer(dev, com, buf, LimeRFE_8001P_BUFFER_SIZE);
	if (len == -1)
		return (LimeRFE_8001P_ERROR_COMM);

	*val = buf[1];

	return result;
}
*/
/******************************************************************************
 * I2C Communications
 *******************************************************************************/
/*
void Limerfe_8001p_mySleep(double sleepms)
{
#ifdef __unix__
	usleep(sleepms * 1000); // usleep takes sleep time in us (1 millionth of a second)
#endif
#ifdef _WIN32
	Sleep(sleepms);
#endif
}

void Limerfe_8001p_i2c_dly(void)
{
	double sleepms = 0.5 * 1 / LimeRFE_8001P_I2C_FSCL * 1000; // for example 0.5 * period - Check this!!!
	Limerfe_8001p_mySleep(sleepms);
}

int Limerfe_8001p_i2c_setVal(lms_device_t *lms, int bitGPIO, int value)
{
		uint8_t gpio_dir = 0;
		int direction;
		if (LMS_GPIODirRead(lms, &gpio_dir, 1) != 0)
			return -1;
		// Direction: 1-output, 0-input
		// If writting 0, then output => direction = 1
		// If writting 1, then input (high Z, and pull-up will do the trick) => direction = 0
		(value == 1) ? direction = 0 : direction = 1;

		(direction == 1) ? gpio_dir |= (1 << (bitGPIO)) : gpio_dir &= ~(1 << (bitGPIO));

		if (LMS_GPIODirWrite(lms, &gpio_dir, 1) != 0)
			return -1;

		uint8_t gpio_val = 0;
		if (LMS_GPIORead(lms, &gpio_val, 1) != 0)
			return -1;

		(value == 1) ? gpio_val |= (1 << (bitGPIO)) : gpio_val &= ~(1 << (bitGPIO));

		if (LMS_GPIOWrite(lms, &gpio_val, 1) != 0)
			return -1;

		Limerfe_8001p_i2c_dly();
	return 0;
}

int Limerfe_8001p_i2c_getVal(lms_device_t *lms, int bitGPIO)
{
		uint8_t gpio_val = 0;
		if (LMS_GPIORead(lms, &gpio_val, 1) != 0)
			return -1;

		int result = 0;

		result = gpio_val & (1 << (bitGPIO));

		return result;
}

int Limerfe_8001p_i2c_start(lms_device_t *lms)
{
	if (Limerfe_8001p_i2c_setVal(lms, GPIO_SDA, 1) != 0)
		return -1;
	Limerfe_8001p_i2c_setVal(lms, GPIO_SCL, 1);
	Limerfe_8001p_i2c_setVal(lms, GPIO_SDA, 0);
	Limerfe_8001p_i2c_setVal(lms, GPIO_SCL, 0);
	return 0;
}

int Limerfe_8001p_i2c_stop(lms_device_t *lms)
{
	if (Limerfe_8001p_i2c_setVal(lms, GPIO_SDA, 0) != 0)
		return -1;
	Limerfe_8001p_i2c_setVal(lms, GPIO_SCL, 1);
	Limerfe_8001p_i2c_setVal(lms, GPIO_SDA, 1);
	return 0;
}

int Limerfe_8001p_i2c_rx(lms_device_t *lms, char ack, unsigned char *d)
{
	char x = 0;

	Limerfe_8001p_i2c_setVal(lms, GPIO_SDA, 1);
	for (x = 0; x < 8; x++)
	{
		(*d) <<= 1;

		int attempt = 0;
		do
		{
			Limerfe_8001p_i2c_setVal(lms, GPIO_SCL, 1);
			attempt++;
			if (attempt > 100)
			{ // Is this limit OK?
				return LimeRFE_8001P_ERROR_COMM;
			}
		} while (Limerfe_8001p_i2c_getVal(lms, GPIO_SCL) == 0); // wait for any SCL clock stretching
		Limerfe_8001p_i2c_dly();
		if (Limerfe_8001p_i2c_getVal(lms, GPIO_SDA))
			(*d) |= 1;
		Limerfe_8001p_i2c_setVal(lms, GPIO_SCL, 0);
	}
	if (ack)
		Limerfe_8001p_i2c_setVal(lms, GPIO_SDA, 0);
	else
		Limerfe_8001p_i2c_setVal(lms, GPIO_SDA, 1);
	Limerfe_8001p_i2c_setVal(lms, GPIO_SCL, 1);
	Limerfe_8001p_i2c_dly(); // send (N)ACK bit
	Limerfe_8001p_i2c_setVal(lms, GPIO_SCL, 0);
	Limerfe_8001p_i2c_setVal(lms, GPIO_SDA, 1);
	//	return d;
	return LimeRFE_8001P_SUCCESS;
}

int Limerfe_8001p_i2c_tx(lms_device_t *lms, unsigned char d)
{
	char x;
	int b;

	for (x = 8; x; x--)
	{
		if (d & 0x80)
			Limerfe_8001p_i2c_setVal(lms, GPIO_SDA, 1);
		else
			Limerfe_8001p_i2c_setVal(lms, GPIO_SDA, 0);
		Limerfe_8001p_i2c_setVal(lms, GPIO_SCL, 1);
		d <<= 1;
		Limerfe_8001p_i2c_setVal(lms, GPIO_SCL, 0);
	}
	Limerfe_8001p_i2c_setVal(lms, GPIO_SDA, 1);
	Limerfe_8001p_i2c_setVal(lms, GPIO_SCL, 1);
	Limerfe_8001p_i2c_dly();
	b = Limerfe_8001p_i2c_getVal(lms, GPIO_SDA); // possible ACK bit
	Limerfe_8001p_i2c_setVal(lms, GPIO_SCL, 0);
	return b;
}

int Limerfe_8001p_i2c_write_buffer(lms_device_t *lms, unsigned char *c, int size)
{
	unsigned char addressI2C = LimeRFE_8001P_I2C_ADDRESS;
	unsigned char addressByte = addressI2C << 1;
	unsigned char addressByteW = addressByte & ~1;

	if (Limerfe_8001p_i2c_start(lms) != 0) // send start sequence
		return -1;
	Limerfe_8001p_i2c_tx(lms, addressByteW); // I2C address with R/W bit clear

	for (int i = 0; i < size; i++)
	{
		Limerfe_8001p_i2c_tx(lms, c[i]);
	}

	Limerfe_8001p_i2c_stop(lms); // send stop sequence

	return 0;
}

int Limerfe_8001p_i2c_read_buffer(lms_device_t *lms, unsigned char *c, int size)
{
	unsigned char addressI2C = LimeRFE_8001P_I2C_ADDRESS;
	unsigned char addressByte = addressI2C << 1;
	unsigned char addressByteR = addressByte | 1;

	Limerfe_8001p_i2c_start(lms);			  // send a restart sequence
	Limerfe_8001p_i2c_tx(lms, addressByteR); // I2C address with R/W bit set

	int i;
	for (i = 0; i < size; i++)
	{
		char ack = 1;
		if (i == (size - 1))
			ack = 0;
		int res = Limerfe_8001p_i2c_rx(lms, ack, &(c[i]));
		if (res != LimeRFE_8001P_SUCCESS)
			return LimeRFE_8001P_ERROR_COMM;
	}
	Limerfe_8001p_i2c_stop(lms); // send stop sequence
	return i;
}

int Limerfe_8001p_Cmd_Fan(lms_device_t *dev, LimeRFE_8001P_COM com, int enable)
{
	int result = 0;

	unsigned char buf[LimeRFE_8001P_BUFFER_SIZE_MODE];
	int len;

	memset(buf, 0, LimeRFE_8001P_BUFFER_SIZE_MODE);

	buf[0] = LimeRFE_8001P_CMD_FAN;

	buf[1] = enable;

	if (Limerfe_8001p_write_buffer(dev, com, buf, LimeRFE_8001P_BUFFER_SIZE_MODE) != 0)
		return LimeRFE_8001P_ERROR_COMM;
	len = Limerfe_8001p_read_buffer(dev, com, buf, LimeRFE_8001P_BUFFER_SIZE_MODE);
	if (len == -1)
		return (LimeRFE_8001P_ERROR_COMM);

	//	result = buf[1]; // buf[0] is the command, buf[1] is the result
	return result;
}

int Limerfe_8001p_Cmd_Diode(lms_device_t *dev, LimeRFE_8001P_COM com, int state)
{
	int result = 0;

	unsigned char buf[LimeRFE_8001P_BUFFER_SIZE];
	int len;

	memset(buf, 0, LimeRFE_8001P_BUFFER_SIZE);

	buf[0] = LimeRFE_8001P_CMD_DIODE;

	buf[1] = state;

	if (Limerfe_8001p_write_buffer(dev, com, buf, LimeRFE_8001P_BUFFER_SIZE) != 0)
		return LimeRFE_8001P_ERROR_COMM;
	len = Limerfe_8001p_read_buffer(dev, com, buf, LimeRFE_8001P_BUFFER_SIZE);
	if (len == -1)
		return (LimeRFE_8001P_ERROR_COMM);

	//	result = buf[1]; // buf[0] is the command, buf[1] is the result
	return result;
}

int Limerfe_8001p_Cmd_DiodeSPI(lms_device_t *dev, LimeRFE_8001P_COM com, int state)
{
	int result = 0;

	unsigned char buf[LimeRFE_8001P_BUFFER_SIZE];
	int len;

	memset(buf, 0, LimeRFE_8001P_BUFFER_SIZE);

	buf[0] = LimeRFE_8001P_CMD_DIODESPI;

	buf[1] = state;

	if (Limerfe_8001p_write_buffer(dev, com, buf, LimeRFE_8001P_BUFFER_SIZE) != 0)
		return LimeRFE_8001P_ERROR_COMM;
	len = Limerfe_8001p_read_buffer(dev, com, buf, LimeRFE_8001P_BUFFER_SIZE);
	if (len == -1)
		return (LimeRFE_8001P_ERROR_COMM);

	//	result = buf[1]; // buf[0] is the command, buf[1] is the result
	return result;
}
*/
int Limerfe_8001p_Cmd_SC1905_SPI_Message_Memory(lms_device_t *dev, LimeRFE_8001P_COM com, uint16_t address, uint8_t *val, bool isRead, int bytesNo, bool isEEPROM)
{
	//	int result = LimeRFE_8001P_SUCCESS;

	unsigned char buf[LimeRFE_8001P_BUFFER_SIZE];
	int len;

	memset(buf, 0, LimeRFE_8001P_BUFFER_SIZE);

	buf[0] = LimeRFE_8001P_CMD_SC1905_SPI_MESSAGE_MEMORY;

	buf[1] = (isRead) ? 1 : 0;
	buf[2] = (address >> 8) & 0xff;
	buf[3] = address & 0xff;
	buf[4] = bytesNo;
	if (!isRead)
	{
		buf[5] = *val;
		if (bytesNo == 2)
			buf[6] = *(val + 1);
	}
	// milans 220729
	//	buf[7] = (isEEPROM) ? 1 : 0;
	if (isEEPROM)
		buf[7] = 1;
	else
		buf[7] = 0;

	if (Limerfe_8001p_write_buffer(dev, com, buf, LimeRFE_8001P_BUFFER_SIZE) != 0)
		return LimeRFE_8001P_ERROR_COMM;

	//	Limerfe_8001p_mySleep(2000);

	len = Limerfe_8001p_read_buffer(dev, com, buf, LimeRFE_8001P_BUFFER_SIZE);
	if (len == -1)
		return (LimeRFE_8001P_ERROR_COMM);

	if (isRead)
		if (bytesNo == 1)
		{
			*val = buf[1];
		}
		else
		{
			val[0] = buf[1];
			val[1] = buf[2];
		}

	//	return result;
	return (int)buf[0];
}

int Limerfe_8001p_Cmd_SC1905_SPI_Special_Command(lms_device_t *dev, LimeRFE_8001P_COM com, int command)
{
	int result = LimeRFE_8001P_SUCCESS;

	unsigned char buf[LimeRFE_8001P_BUFFER_SIZE];
	unsigned char reply[5];
	int len;

	memset(buf, 0, LimeRFE_8001P_BUFFER_SIZE);

	buf[0] = LimeRFE_8001P_CMD_SC1905_SPI_SPECIAL_COMMAND;

	buf[1] = 0x10;
	buf[3] = 0x00;
	buf[4] = 0x00;

	reply[1] = 0x90;
	reply[3] = 0x00;
	reply[4] = 0x00;

	switch (command)
	{
	case LimeRFE_8001P_SC1905_COMMAND_CLEAR_WARNING:
		buf[2] = 0x03;
		reply[2] = 0x03;
		break;
	case LimeRFE_8001P_SC1905_COMMAND_ACTIVATE_OUTPUTS:
		buf[2] = 0x04;
		reply[2] = 0x04;
		break;
	case LimeRFE_8001P_SC1905_COMMAND_WRITE_MAXPWRCALPARAM_A:
		buf[2] = 0xf5;
		reply[2] = 0xf5;
		break;
	case LimeRFE_8001P_SC1905_COMMAND_WRITE_MAXPWRCALPARAM_B:
		buf[2] = 0xf6;
		reply[2] = 0xf6;
		break;
	case LimeRFE_8001P_SC1905_COMMAND_CLEAR_MAXPWRCALPARAM_A:
		buf[2] = 0xf3;
		reply[2] = 0xf3;
		break;
	case LimeRFE_8001P_SC1905_COMMAND_CLEAR_MAXPWRCALPARAM_B:
		buf[2] = 0xf4;
		reply[2] = 0xf4;
		break;
	default:
		return LimeRFE_8001P_ERROR_SC1905_SPECIAL_MESSAGE_UNKNOWN;
	}

	if (Limerfe_8001p_write_buffer(dev, com, buf, LimeRFE_8001P_BUFFER_SIZE) != 0)
		return LimeRFE_8001P_ERROR_COMM;

	//	Limerfe_8001p_mySleep(2000);

	len = Limerfe_8001p_read_buffer(dev, com, buf, LimeRFE_8001P_BUFFER_SIZE);
	if (len == -1)
		return (LimeRFE_8001P_ERROR_COMM);

	if (!((buf[1] == reply[1]) && (buf[2] == reply[2]) && (buf[3] == reply[3]) && (buf[4] == reply[4])))
	{
		result = LimeRFE_8001P_ERROR_SC1905_SPECIAL_MESSAGE_WRONG_REPLY;
	}
	//	return result;
	return result;
}

int Limerfe_8001p_Cmd_SC1905_Reset(lms_device_t *dev, LimeRFE_8001P_COM com)
{
	int result = LimeRFE_8001P_SUCCESS;

	unsigned char buf[LimeRFE_8001P_BUFFER_SIZE];
	int len;

	memset(buf, 0, LimeRFE_8001P_BUFFER_SIZE);

	buf[0] = LimeRFE_8001P_CMD_SC1905_RESET;

	if (Limerfe_8001p_write_buffer(dev, com, buf, LimeRFE_8001P_BUFFER_SIZE) != 0)
		return LimeRFE_8001P_ERROR_COMM;
	len = Limerfe_8001p_read_buffer(dev, com, buf, LimeRFE_8001P_BUFFER_SIZE);
	if (len == -1)
		return (LimeRFE_8001P_ERROR_COMM);

	return result;
}

int Limerfe_8001p_Cmd_SC1905_Apply_Frequency(lms_device_t *dev, LimeRFE_8001P_COM com, int freqRange, int minFreq, int maxFreq)
{
	int result = LimeRFE_8001P_SUCCESS;

	uint16_t address;
	uint8_t val[2] = {0x00, 0x00};

	address = 0x010;
	val[0] = freqRange;
	result = Limerfe_8001p_Cmd_SC1905_SPI_Message_Memory(dev, com, address, val, false, 1);
	if (result != LimeRFE_8001P_SUCCESS)
		return result;

	address = 0x011;
	uint16_t minFreqValue = 2 * minFreq;
	val[0] = (minFreqValue >> 8) & 0xff;
	val[1] = minFreqValue & 0xff;
	result = Limerfe_8001p_Cmd_SC1905_SPI_Message_Memory(dev, com, address, val, false, 2);
	if (result != LimeRFE_8001P_SUCCESS)
		return result;

	address = 0x013;
	uint16_t maxFreqValue = 2 * maxFreq;
	val[0] = (maxFreqValue >> 8) & 0xff;
	val[1] = maxFreqValue & 0xff;
	result = Limerfe_8001p_Cmd_SC1905_SPI_Message_Memory(dev, com, address, val, false, 2);

	return result;
}

int Limerfe_8001p_Cmd_SC1905S_Set_Duty_Cycle_Feedback(lms_device_t *dev, LimeRFE_8001P_COM com, uint8_t Enabled)
{
	int result = LimeRFE_8001P_SUCCESS;
	uint16_t address;
	uint8_t val[2] = {0x00, 0x00};
	val[0] = (Enabled & 0x01);
	address = 0x017;
	result = Limerfe_8001p_Cmd_SC1905_SPI_Message_Memory(dev, com, address, val, false, 1);
	return result;
}

int Limerfe_8001p_Cmd_SC1905S_Set_Adaptation_State(lms_device_t *dev, LimeRFE_8001P_COM com, uint8_t Running)
{
	int result = LimeRFE_8001P_SUCCESS;
	uint16_t address;
	uint8_t val[2] = {0x00, 0x00};
	val[0] =(Running & 0x01);
	address = 0x023;
	result = Limerfe_8001p_Cmd_SC1905_SPI_Message_Memory(dev, com, address, val, false, 1);
	return result;
}

int Limerfe_8001p_Cmd_SC1905S_Set_Correction_Enable(lms_device_t *dev, LimeRFE_8001P_COM com, uint8_t Enabled)
{
	int result = LimeRFE_8001P_SUCCESS;
	uint16_t address;
	uint8_t val[2] = {0x00, 0x00};
	val[0] = (Enabled & 0x01);
	address = 0x008;
	result = Limerfe_8001p_Cmd_SC1905_SPI_Message_Memory(dev, com,  address, val, false, 1);

	// SC1905 SPI PRogramming Guide, page 17
	// "After changing Output Mode, send the "Activate Outputs" messages toi be effective. See Table 2."
	result = Limerfe_8001p_Cmd_SC1905_SPI_Special_Command(dev, com, LimeRFE_8001P_SC1905_COMMAND_ACTIVATE_OUTPUTS);
	return result;
}

// Read RFIN AGC
int Limerfe_8001p_Cmd_SC1905S_Read_RFIN_AGC(lms_device_t *dev, LimeRFE_8001P_COM com, int * rfinAgc) {
    
	int result = LimeRFE_8001P_SUCCESS;
	uint16_t address;
	uint8_t val[2] = {0x00, 0x00};
	
	address = 0x23C;
	result = Limerfe_8001p_Cmd_SC1905_SPI_Message_Memory(dev, com, address, val, true, 1);
	*rfinAgc = val[0];
	return result;
}	

// Read RFFB AGC
int Limerfe_8001p_Cmd_SC1905S_Read_RFFB_AGC(lms_device_t *dev, LimeRFE_8001P_COM com, int * rffbAgc) {
    
	int result = LimeRFE_8001P_SUCCESS;
	uint16_t address;
	uint8_t val[2] = {0x00, 0x00};

	address = 0x9C4;
	result = Limerfe_8001p_Cmd_SC1905_SPI_Message_Memory(dev, com, address, val, true, 1);
	*rffbAgc = val[0];
	return result;
}	

// Read Center Frequency
int Limerfe_8001p_Cmd_SC1905S_Read_Center_Frequency(lms_device_t *dev, LimeRFE_8001P_COM com, float * centerFreq) {

    int result = LimeRFE_8001P_SUCCESS;
	uint16_t address;
	uint8_t val[2] = {0x00, 0x00};

	address = 0x01A;
	result = Limerfe_8001p_Cmd_SC1905_SPI_Message_Memory(dev, com, address, val, true, 2);

	*centerFreq = (val[0] * 100 + val[1]) / 2;
	return result;
}	

// Read Signal Bandwidth (24dBc BW)
int Limerfe_8001p_Cmd_SC1905S_Read_Signal_Bandwidth(lms_device_t *dev, LimeRFE_8001P_COM com, float * bandwidth) {

    int result = LimeRFE_8001P_SUCCESS;
	uint16_t address;
	uint8_t val[2] = {0x00, 0x00};

	address = 0x018;
	result = Limerfe_8001p_Cmd_SC1905_SPI_Message_Memory(dev, com, address, val, true, 2);

	*bandwidth = (val[0] * 100 + val[1]) / 2;
	return result;
}


// Read Error Code & Generate Error Message
int Limerfe_8001p_Cmd_SC1905S_Read_Error_Code(lms_device_t *dev, LimeRFE_8001P_COM com, char * stringValue) {
	
	int result = LimeRFE_8001P_SUCCESS;
	uint16_t address;
	uint8_t val[2] = {0x00, 0x00};

	address = 0x006;
	result = Limerfe_8001p_Cmd_SC1905_SPI_Message_Memory(dev, com, address, val, true, 2);

	int errorCode = val[0];
	switch (errorCode)
	{
	case 0:
		sprintf(stringValue, "No Error");
		break;
	case 3:
		sprintf(stringValue, "EEPROM Corrupted");
		break;
	case 5:
		sprintf(stringValue, "Center Frequency outside the Defined Frequencvy Range");
		break;
	case 13:
		sprintf(stringValue, "Wrong CLK Setting");
		break;
	default:
		sprintf(stringValue, "Internal Chip Error");
	}	
	return result;
}


// Read Warning Code & Generate Warning Message
int Limerfe_8001p_Cmd_SC1905S_Read_Warning_Code(lms_device_t *dev, LimeRFE_8001P_COM com, char * stringValue) {
	
	int result = LimeRFE_8001P_SUCCESS;
	uint16_t address;
	uint8_t val[2] = {0x00, 0x00};

	address = 0x007;
	result = Limerfe_8001p_Cmd_SC1905_SPI_Message_Memory(dev, com, address, val, true, 2);

	int warningCode = val[0];
	switch (warningCode)
	{
	case 0:
		sprintf(stringValue, "No Warning");
		break;
	case 44:
	case 48:
		sprintf(stringValue, "Center Frequency Too Low");
		break;
	case 62:
		sprintf(stringValue, "IC Temperature Outside Allowed Range");
		break;
	default:
		sprintf(stringValue, "Internal Warning");
	}
	return result;
}

int Limerfe_8001p_Cmd_SC1905_GetStatus(lms_device_t *dev, LimeRFE_8001P_COM com, char * statusString)
{
	int result = LimeRFE_8001P_SUCCESS;
	uint16_t address;
	uint8_t val[2];

	address = 0x005;
	result = Limerfe_8001p_Cmd_SC1905_SPI_Message_Memory(dev, com, address, val, true, 1);
	int status = val[0];

	switch (status)
	{
	case 0:
		sprintf(statusString, "INIT");
		break;
	case 1:
		sprintf(statusString, "FSA");
		break;
	case 3:
		sprintf(statusString, "TRACK");
		break;
	case 6:
		sprintf(statusString, "CAL");
		break;
	case 9:
		sprintf(statusString, "PDET");
		break;
	default:
		sprintf(statusString, "Unknown");
	}
	
	return result;
}


int Limerfe_8001p_Cmd_Set_Config_Full(lms_device_t *dev, LimeRFE_8001P_COM com, uint8_t *state, int size)
{
	int result = LimeRFE_8001P_SUCCESS;

	unsigned char buf[LimeRFE_8001P_BUFFER_SIZE];
	int len;

	memset(buf, 0, LimeRFE_8001P_BUFFER_SIZE);

	buf[0] = LimeRFE_8001P_CMD_SET_CONFIG_FULL;

	memcpy(buf + 1, state, size);

	if (Limerfe_8001p_write_buffer(dev, com, buf, LimeRFE_8001P_BUFFER_SIZE) != 0)
		return LimeRFE_8001P_ERROR_COMM;
	len = Limerfe_8001p_read_buffer(dev, com, buf, LimeRFE_8001P_BUFFER_SIZE);
	if (len == -1)
		return (LimeRFE_8001P_ERROR_COMM);

	return result;
}

int Limerfe_8001p_Cmd_Get_Config_Full(lms_device_t *dev, LimeRFE_8001P_COM com, uint8_t *state, int size)
{
	int result = LimeRFE_8001P_SUCCESS;

	unsigned char buf[LimeRFE_8001P_BUFFER_SIZE];
	int len;

	memset(buf, 0, LimeRFE_8001P_BUFFER_SIZE);

	buf[0] = LimeRFE_8001P_CMD_GET_CONFIG_FULL;

	if (Limerfe_8001p_write_buffer(dev, com, buf, LimeRFE_8001P_BUFFER_SIZE) != 0)
		return LimeRFE_8001P_ERROR_COMM;
	len = Limerfe_8001p_read_buffer(dev, com, buf, LimeRFE_8001P_BUFFER_SIZE);
	if (len == -1)
		return (LimeRFE_8001P_ERROR_COMM);

	memcpy(state, buf + 1, size);

	return result;
}

// B.J. commented 24.11.2022
// dummy declarations
// these functions are part of LimeSute API
// remove when SPI connection is used

int LMS_ReadEXTBRDReg(lms_device_t *device, uint32_t address, uint16_t *val)
{
	return 0;
}
int LMS_ReadEXTBRD(lms_device_t *device, uint32_t *address, uint32_t *data, unsigned cnt)
{
	return 0;
}
int LMS_WriteEXTBRDReg(lms_device_t *device, uint32_t address, uint16_t val)
{
	return 0;
}
int LMS_WriteEXTBRD(lms_device_t *device, uint32_t *address, uint32_t *data, unsigned cnt)
{
	return 0;
}

// B.J.
int Limerfe_8001p_SPI_write(lms_device_t *lms, uint16_t maddress, uint16_t address, uint16_t data)
{
	uint16_t addr = address + maddress;
	int ret = 0;
	if (LMS_WriteEXTBRDReg(lms, addr, data) != 0)
		ret = -1;
	return ret;
}

int Limerfe_8001p_SPI_read(lms_device_t *lms, uint16_t maddress, uint16_t address, uint16_t *data)
{
	uint16_t addr = address + maddress;
	int ret = 0;
	uint16_t regValue = 0x0000;
	for (int k = 0; k < 6; k++)
		LMS_ReadEXTBRDReg(lms, addr, &regValue);
	*data = regValue;
	return ret;
}

/*
int Limerfe_8001p_spi_write_buffer(lms_device_t *lms, unsigned char *c, int size)
{
	uint16_t maddress = MADDRESS;
	uint16_t maddress2 = MADDRESS2;
	uint16_t data = 0;
	for (int i = 0; i < (size / 2); i++)
	{
		data = 0;
		data = (uint16_t)(c[2 * i + 1]);
		data = data << 8;
		data += (uint16_t)(c[2 * i]);
		Limerfe_8001p_SPI_write(lms, maddress, i, data);
	}
	Limerfe_8001p_SPI_write(lms, maddress2, 0, 0x0001); /
	return 0;
}
*/

int Limerfe_8001p_spi_write_buffer(lms_device_t *lms, unsigned char *c, int size)
{
	// size is 16 or 64. Units - bytes
	uint16_t maddress = MADDRESS;
	uint16_t maddress2 = MADDRESS2;
	uint32_t data[64];
	uint32_t addr[64];
	int i = 0;

	for (i = 0; i < (size / 2); i++) // transfer data
	{
		addr[i] = maddress + i;
		data[i] = 0;
		data[i] = (uint16_t)(c[2 * i + 1]);
		data[i] = data[i] << 8;
		data[i] += (uint16_t)(c[2 * i]);
	}
	addr[size / 2] = maddress2;
	data[size / 2] = 0x0001;
	LMS_WriteEXTBRD(lms, addr, data, (unsigned int)(size / 2) + 1);
	/*
		cout << "SPI Write ";  // B.J.
		uint8_t X10, X1 = 0x00;
		for (int j=0; j < size; j++) {
			ConvertToAscii(c[j], &X10, &X1);
			cout << X10 << X1 <<" ";
		}
		cout << "01" << "00" <<" ";
		cout << std::endl;
	*/
	// std::this_thread::sleep_for(std::chrono::milliseconds(1));
	return 0;
}

/*
int Limerfe_8001p_spi_read_buffer(lms_device_t *lms, unsigned char *c, int size)
{
	uint16_t maddress = MADDRESS;
	uint16_t maddress2 = MADDRESS2;
	uint16_t data = 0;
	bool m_bfound = false;
	int ret = 0;
	int i = 0;

	while ((i < 10) && (!m_bfound))
	{

		Limerfe_8001p_SPI_read(lms, maddress2, 0, &data);
		if ((data & 0x00FF) == 0x0000)
			m_bfound = true;
		else
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
			i++;
		}
	}
	if (m_bfound)
	{
		ret = ((data & 0xFF00) >> 8); // number of bytes returned
		for (i = 0; i < (size / 2); i++)
		{
			Limerfe_8001p_SPI_read(lms, maddress, i, &data);
			c[2 * i + 1] = (uint8_t)(data >> 8);
			c[2 * i] = (uint8_t)(data & 0x00FF);
			// return size;
		}
	}
	else
		ret = 0;
	return size;
}
*/

/*
int Limerfe_8001p_spi_read_buffer2(lms_device_t *lms, unsigned char *c, int size)
{
	uint16_t maddress = MADDRESS;
	uint16_t maddress2 = MADDRESS2;
	uint16_t data = 0;
	bool m_bfound = false;
	int ret = 0;
	int i = 0;

	uint32_t addr[64];
	uint32_t dataa[64];
	uint8_t cx[64 * 2];

	for (i = 0; i < (size / 2); i++)
	{
		addr[i] = i + maddress;
		dataa[i] = 0;
	}

	addr[i] = maddress;
	dataa[i] = 0;
	i++;

	addr[i] = maddress;
	dataa[i] = 0;
	i++;

	for (i = 0; i < 64 * 2; i++)
		cx[i] = 0x00;

	m_bfound = true;
	if (m_bfound)
	{
		LMS_ReadEXTBRD(lms, addr, dataa, (unsigned int)(size / 2) + 2);
		for (int i = 0; i < (size / 2) + 2; i++)
		{
			cx[2 * i + 1] = (uint8_t)(dataa[i] >> 8);
			cx[2 * i] = (uint8_t)(dataa[i] & 0x00FF);
		}

		for (i = 0; i < size; i++)
			c[i] = cx[i + 8];
	}
	else
		ret = 0;
	return size;
}
*/

void ConvertToAscii(uint8_t ch, uint8_t *pX10, uint8_t *pX1)
{

	uint8_t X10, X1 = 0;

	X10 = ((ch & 0xF0) >> 4);
	X1 = (ch & 0x0F);

	if (X10 > 9)
		X10 = X10 + 0x37; // A-F
	else
		X10 = X10 + 0x30; // 0-9

	if (X1 > 9)
		X1 = X1 + 0x37;
	else
		X1 = X1 + 0x30;

	*pX10 = X10;
	*pX1 = X1;
}

int Limerfe_8001p_spi_read_buffer(lms_device_t *lms, unsigned char *c, int size)
{
	uint16_t maddress = MADDRESS;
	uint16_t maddress2 = MADDRESS2;
	bool m_bfound = false;
	int ret = 0;
	int i = 0;
	int k = 0;

	uint32_t addr[64];
	uint32_t dataa[64];
	uint8_t cx[128];

	for (i = 0; i < 64; i++)
	{
		cx[2 * i] = 0x00;
		cx[2 * i + 1] = 0x00;
		addr[i] = 0;
		dataa[i] = 0;
	}

	k = 0;
	addr[k] = maddress2;
	k++;

	for (i = 0; i < (size / 2); i++)
	{
		addr[k] = i + maddress;
		k++;
	}
	// dummy read
	for (i = 0; i < 10; i++)
	{
		addr[k] = maddress + (size / 2) - 1; // the last one
		k++;
	}

	LMS_ReadEXTBRD(lms, addr, dataa, k);

	for (i = 0; i < k; i++)
	{
		cx[2 * i + 1] = (uint8_t)(dataa[i] >> 8);
		cx[2 * i] = (uint8_t)(dataa[i] & 0x00FF);
	}
	/*
		cout << "SPI Read ";  // B.J.
		uint8_t X10, X1 = 0x00;
		for (int j=0; j < 2*k; j++) {
			ConvertToAscii(cx[j], &X10, &X1);
			cout << X10 << X1 <<" ";
		}
		cout << std::endl;
	*/

	m_bfound = false;
	i = 0;
	while ((!m_bfound) && (i < 2 * k))
	{
		if (cx[i] == 0xAA)
			m_bfound = true;
		i = i + 2;
	}

	if ((m_bfound) && ((i + size) <= 2 * k))
	{
		for (int j = 0; j < size; j++)
			c[j] = cx[i + j];
		return size;
	}
	else
	{
		for (int j = 0; j < size; j++)
			c[j] = 0x00;
		return -1;
	}
}
// end B.J.
