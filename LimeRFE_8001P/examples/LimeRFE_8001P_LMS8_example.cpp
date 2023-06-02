//#include <lime/LimeSuite.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <stdio.h>

#include "../LimeRFE_8001P.h"
#include "../LMS8001/lime/LMS8API.h"

int openPort(char* portName);
void closePort(int fd);

//Device structure, should be initialize to NULL
limerfe_8001p_dev_t* limerfe_8001p = NULL;
lms_device_t* lms8_device = NULL;

int error()
{
    if (lms8_device != NULL)
        LMS8_Close(lms8_device);
    if (limerfe_8001p != NULL)
        LimeRFE_8001P_Close(limerfe_8001p);
    exit(-1);
}

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		printf("Error: Wrong number of parameters\n");
		printf("Usage: limelimerfe_8001p_USB_test <Limelimerfe_8001p COM port>\n");
		printf("Example: limelimerfe_8001p_USB_test COM3\n");
		exit(1);
	}
	//Open port
    //limerfe_8001p = LimeRFE_8001P_Open(argv[1], nullptr);
    limerfe_8001p = LimeRFE_8001P_Open("/dev/ttyACM0", nullptr);

	if (limerfe_8001p == nullptr) {
		std::cout << "Error: failed to open device" << std::endl;
		return -1;
	}
	else {
		std::cout << "Port opened" << std::endl;
	}

	unsigned char cinfo[4];
    int result;

//	LIMElimerfe_8001p_GetInfo(fd, cinfo);
	LimeRFE_8001P_GetInfo(limerfe_8001p, cinfo);

	printf("Firmware version: %d\n", (int)cinfo[2]);
	printf("Hardware version: %#x\n", (int)cinfo[3]);

    LimeRFE_8001P_Reset(limerfe_8001p);

    printf("Enable LMS8001...\n");
    LimeRFE_8001P_LMS8_Enable(limerfe_8001p, 1);

    if (LimeRFE_8001P_LMS8_Open(limerfe_8001p, &lms8_device))
        error();

    printf("Selecting channel 1\n");
    result = LimeRFE_8001P_Select_Channel(limerfe_8001p, LimeRFE_8001P_CH1);

    const lms_dev_info_t* info = LMS8_GetDeviceInfo(lms8_device);
    printf("Firmware: %s\n", info->firmwareVersion);
    printf("Harware: %s\n", info->hardwareVersion);
    printf("Protocol: %s\n", info->protocolVersion);

    //Test SPI
    uint16_t address = 0x0004;
    uint16_t value;
    if(LMS8_ReadLMSReg(lms8_device, 0x0004, &value) != LMS_SUCCESS)
        error();
    printf("Address: 0x%04x; Value: 0x%02x\n", address, value);
    value = 0x01;
    if(LMS8_WriteLMSReg(lms8_device, 0x0004, value) != LMS_SUCCESS)
        error();
    LMS8_ReadLMSReg(lms8_device, 0x0004, &value);
    printf("Address: 0x%04x; Value: 0x%02x\n", address, value);
    value = 0x00;
    LMS8_WriteLMSReg(lms8_device, 0x0004, value);
    LMS8_ReadLMSReg(lms8_device, 0x0004, &value);
    printf("Address: 0x%04x; Value: 0x%02x\n", address, value);

    printf("Resetting...\n");
    result = LMS8_Reset(lms8_device);
    if (result != LMS_SUCCESS)
        printf("Error resetting.\n");
    printf("Finished\n");
    
    
    printf("Loading state...\n");
    result = LMS8_LoadConfig(lms8_device, "Conf_LMS8001.ini");
    if (result != LMS_SUCCESS)
        printf("Error loading state.\n");
    printf("Finished\n");
    
    int isLocked;

    isLocked = LMS8_Get_SPI_Reg_bits(lms8_device, PLL_LOCK);
    printf("Is Locked: %d\n", isLocked);

    printf("Tuning PLL...\n");

    result = LMS8_PLL_Tune(lms8_device, 4.5);
    if (result != LMS_SUCCESS)
        printf("Error locking. Result: %d\n", result);

    isLocked = LMS8_Get_SPI_Reg_bits(lms8_device, PLL_LOCK);
    printf("Is Locked: %d\n", isLocked);

    printf("Resetting...\n");
    result = LMS8_Reset(lms8_device);
    if (result != LMS_SUCCESS)
        printf("Error resetting.\n");
    printf("Finished\n");

    isLocked = LMS8_Get_SPI_Reg_bits(lms8_device, PLL_LOCK);
    printf("Is Locked: %d\n", isLocked);
    
    printf("Smart Tuning PLL...\n");

    result = LMS8_PLL_Smart_Tune(lms8_device, 5.5);
    if (result != LMS_SUCCESS)
        printf("Error locking. Result: %d\n", result);

    isLocked = LMS8_Get_SPI_Reg_bits(lms8_device, PLL_LOCK);
    printf("Is Locked: %d\n", isLocked);
    
    printf("Selecting channel 2\n");
    result = LimeRFE_8001P_Select_Channel(limerfe_8001p, LimeRFE_8001P_CH2);

    printf("Resetting...\n");
    result = LMS8_Reset(lms8_device);
    if (result != LMS_SUCCESS)
        printf("Error resetting.\n");
    printf("Finished\n");

    isLocked = LMS8_Get_SPI_Reg_bits(lms8_device, PLL_LOCK);
    printf("Is Locked: %d\n", isLocked);

    printf("Smart Tuning PLL...\n");

    result = LMS8_PLL_Smart_Tune(lms8_device, 3.5);
    if (result != LMS_SUCCESS)
        printf("Error locking. Result: %d\n", result);

    isLocked = LMS8_Get_SPI_Reg_bits(lms8_device, PLL_LOCK);
    printf("Is Locked: %d\n", isLocked);

//    printf("Disabling LMS8001...\n");
//    LimeRFE_8001P_LMS8_Enable(limerfe_8001p, 0);

    //Close device
    LMS8_Close(lms8_device);

	//Close port
   	LimeRFE_8001P_Close(limerfe_8001p);

	return 0;
}
