//#include <lime/LimeSuite.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <stdio.h>
#include <unistd.h>

#include "../LimeRFE_8001P.h"
#include "../LMS8001/lime/LMS8API.h"

int openPort(char* portName);
void closePort(int fd);

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
	//limerfe_8001p_boardState state;
	int result = 0;	
    int isLocked = 0;

    // SC1905 variables
    int rfinAgc = 0;
    int rffbAgc = 0;
    float centerFreq = 0.0;
    float bandwidth = 0.0;
    char stringValue[100];
    
    int rcount = 0; 
    int ncount = 0;
 
    limerfe_8001p = LimeRFE_8001P_Open("/dev/ttyACM0", nullptr);
    //limerfe_8001p = LimeRFE_8001P_FindAndOpen(nullptr);

	if (limerfe_8001p == nullptr) {
		std::cout << "Error: failed to open device" << std::endl;
		return -1;
	}
	else {
		std::cout << "Port opened" << std::endl;
	}

	printf("Resetting LimeRFE_8001P board ...\n");
    LimeRFE_8001P_Reset(limerfe_8001p);
    
    printf("Loading LimeRFE_8001P board ini file ...\n");
    LimeRFE_8001P_LoadConfig(limerfe_8001p, "Config_LimeRFE_8001P.ini");

    printf("Selecting channel 1\n");
    result = LimeRFE_8001P_Select_Channel(limerfe_8001p, LimeRFE_8001P_CH1);

    printf("Enable LMS8001...\n");
    LimeRFE_8001P_LMS8_Enable(limerfe_8001p, 1);

    if (LimeRFE_8001P_LMS8_Open(limerfe_8001p, &lms8_device))
        error();

    printf("Resetting LMS8001...\n");
    result = LMS8_Reset(lms8_device);
    if (result != LMS_SUCCESS)
        printf("Error resetting.\n");
    printf("Finished\n");
    
    printf("Loading LMS8001 state...\n");
    result = LMS8_LoadConfig(lms8_device, "Config_LMS8001.ini");
    if (result != LMS_SUCCESS)
        printf("Error loading state.\n");
    printf("Finished\n");

    // uncomment this if tou change ADF4002 configuration, put desired ext.ref.frequency
    
    // result = LimeRFE_8001P_ADF4002_Config(limerfe_8001p, 30.72e6, &rcount, &ncount);
    // printf("ADF4002 tune: rcount=%d, ncount=%d\n", rcount, ncount);  // to check
    // sleep(1); // important delay
    
    printf("Smart Tuning PLL...\n");

    result = LMS8_PLL_Smart_Tune(lms8_device, 4.9);
    if (result != LMS_SUCCESS)
        printf("Error locking. Result: %d\n", result);

    isLocked = LMS8_Get_SPI_Reg_bits(lms8_device, PLL_LOCK);
    printf("Is Locked: %d\n", isLocked);
    
    printf("Enable SC1905...\n");
    LimeRFE_8001P_SC1905_Enable(limerfe_8001p, LimeRFE_8001P_CH1, 1); // Enable=1; Disable=0
	
    sleep(2); // important delay
    printf("Finished\n");

    //result = LimeRFE_8001P_SC1905_Apply_Frequency(limerfe_8001p, 7, 1950, 2050);
    result = LimeRFE_8001P_SC1905_Set_Duty_Cycle_Feedback(limerfe_8001p, 1);  // On=1/Off=0
    result = LimeRFE_8001P_SC1905_Set_Adaptation_State(limerfe_8001p, 1); //Running=1/Frozen=0
    result = LimeRFE_8001P_SC1905_Set_Correction_Enable(limerfe_8001p, 1); // FW Control=1/Disabled=0
   
    result = LimeRFE_8001P_SC1905_Read_RFIN_AGC(limerfe_8001p, &rfinAgc);
    printf("SC1905 rfinAgc = %d\n", rfinAgc);
   
    result = LimeRFE_8001P_SC1905_Read_RFFB_AGC(limerfe_8001p, &rffbAgc);
    printf("SC1905 rffbAgc = %d\n", rffbAgc);

    result = LimeRFE_8001P_SC1905_Read_Center_Frequency(limerfe_8001p, &centerFreq);
    printf("SC1905 centerFreq = %f\n", centerFreq);

    result = LimeRFE_8001P_SC1905_Read_Signal_Bandwidth(limerfe_8001p, &bandwidth);
    printf("SC1905 bandwidth = %f\n", bandwidth);
   
    result = LimeRFE_8001P_SC1905_Read_Error_Code(limerfe_8001p, stringValue);
    printf("SC1905 Error code = %s\n", stringValue);

    result = LimeRFE_8001P_SC1905_Read_Warning_Code(limerfe_8001p, stringValue);
    printf("SC1905 Warning code = %s\n", stringValue);

    float attenuation = 0.0;
    result = LimeRFE_8001P_Get_TX_Att(limerfe_8001p, LimeRFE_8001P_CH1, &attenuation);
    printf("TX1 att. = %8.3f\n", attenuation);

    attenuation += 0.25;
    result = LimeRFE_8001P_Set_TX_Att(limerfe_8001p, LimeRFE_8001P_CH1, attenuation);

    result = LimeRFE_8001P_Get_TX_Att(limerfe_8001p, LimeRFE_8001P_CH1, &attenuation);
    printf("TX1 att. = %8.3f\n", attenuation);

    attenuation = 0.0;
    result = LimeRFE_8001P_Get_ORX_Att(limerfe_8001p, LimeRFE_8001P_CH1, &attenuation);
    printf("ORX1 att. = %8.3f\n", attenuation);

    attenuation += 0.25;
    result = LimeRFE_8001P_Set_ORX_Att(limerfe_8001p, LimeRFE_8001P_CH1, attenuation);
    
    result = LimeRFE_8001P_Get_ORX_Att(limerfe_8001p, LimeRFE_8001P_CH1, &attenuation);
    printf("ORX1 att. = %8.3f\n", attenuation);

    sleep(15);
	

    printf("Disable SC1905...\n");
    LimeRFE_8001P_SC1905_Enable(limerfe_8001p, LimeRFE_8001P_CH1, 0); // Enable=1; Disable=0
    sleep(1);
    printf("Disable LMS8001...\n");
    LimeRFE_8001P_LMS8_Enable(limerfe_8001p, 0);


   //Close device
    LMS8_Close(lms8_device);

    //Close port
	LimeRFE_8001P_Close(limerfe_8001p);
	return 0;
}
