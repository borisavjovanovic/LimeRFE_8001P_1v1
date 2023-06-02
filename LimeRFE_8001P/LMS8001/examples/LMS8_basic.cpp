/**
    @file   LMS8_basicRX.cpp
    @author Lime Microsystems (www.limemicro.com)
    @brief  basic LMS8001 API example
 */
#include "../lime/LMS8API.h"
#include <iostream>
#include <chrono>
#include <cstring>

using namespace std;

//Device structure, should be initialize to NULL
lms_device_t* device = NULL;

int error()
{
    if (device != NULL)
        LMS8_Close(device);
    exit(-1);
}

int main(int argc, char** argv)
{
    //Find devices
    int n;
    lms_info_str_t list[8]; //should be large enough to hold all detected devices
    if ((n = LMS8_GetDeviceList(list)) < 0) //NULL can be passed to only get number of devices
        error();

    cout << "Devices found: " << n << endl; //print number of devices
    if (n < 1)
        return -1;

    for (int i = 0; i < n; i++) {
        printf("Device %d: %s\n", i, list[i]);
    }

    //open the first device
    lms_info_str_t device_name;
    strcpy(device_name, list[0]);
    printf("Opening device: %s\n", device_name);
    if (LMS8_Open(&device, device_name, NULL))
        error();

    const lms_dev_info_t* info = LMS8_GetDeviceInfo(device);
    printf("Firmware: %s\n", info->firmwareVersion);
    printf("Harware: %s\n", info->hardwareVersion);
    printf("Protocol: %s\n", info->protocolVersion);

    //Test SPI
    uint16_t address = 0x0004;
    uint16_t value;
    LMS8_ReadLMSReg(device, 0x0004, &value);
    printf("Address: 0x%04x; Value: 0x%02x\n", address, value);
    value = 0x01;
    LMS8_WriteLMSReg(device, 0x0004, value);
    LMS8_ReadLMSReg(device, 0x0004, &value);
    printf("Address: 0x%04x; Value: 0x%02x\n", address, value);
    value = 0x00;
    LMS8_WriteLMSReg(device, 0x0004, value);
    LMS8_ReadLMSReg(device, 0x0004, &value);
    printf("Address: 0x%04x; Value: 0x%02x\n", address, value);

    int isLocked;

    isLocked = LMS8_Get_SPI_Reg_bits(device, PLL_LOCK);
    printf("Is Locked: %d\n", isLocked);

    printf("Tuning PLL...\n");

    int result = LMS8_PLL_Tune(device, 4.5);
    if(result != LMS_SUCCESS)
        printf("Error locking. Result: %d\n", result);

    isLocked = LMS8_Get_SPI_Reg_bits(device, PLL_LOCK);
    printf("Is Locked: %d\n", isLocked);

    //Close device
    LMS8_Close(device);

    return 0;
}