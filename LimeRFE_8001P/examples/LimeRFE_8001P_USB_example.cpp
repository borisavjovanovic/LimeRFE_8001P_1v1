//#include <lime/LimeSuite.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <stdio.h>

#include "../LimeRFE_8001P.h"

int openPort(char* portName);
void closePort(int fd);

int main(int argc, char** argv)
{	
/*	
	if (argc != 2)
	{
		printf("Error: Wrong number of parameters\n");
		printf("Usage: limeRFE_USB_test <LimeRFE COM port>\n");
		printf("Example: limeRFE_USB_test COM3\n");
		exit(1);
	}

	//Open port
        limerfe_8001p_dev_t* limerfe_8001p = LimeRFE_8001P_Open(argv[1], nullptr);
*/
	//milans 221201 TMP TMP TMP TMP TMP
	//limerfe_8001p_dev_t* limerfe_8001p = LimeRFE_8001P_Open("COM4", nullptr);
	limerfe_8001p_dev_t* limerfe_8001p = LimeRFE_8001P_Open("/dev/ttyACM0", nullptr);

	if (limerfe_8001p == nullptr) {
		std::cout << "Error: failed to open device" << std::endl;
		return -1;
	}
	else {
		std::cout << "Port opened" << std::endl;
	}
/*
	//Configure LimeRFE to use channel HAM 2m channel in receive mode.
	//Transmit output is routed to TX/RX output. Notch is off. Attenuation is 0.
	LimeRFE_8001P_Configure(rfe, LimeRFE_8001P_CID_HAM_0145, LimeRFE_8001P_CID_HAM_0145, LimeRFE_8001P_PORT_1, LimeRFE_8001P_PORT_1, LimeRFE_8001P_MODE_RX, 
	LimeRFE_8001P_NOTCH_OFF, 0, 0, 0);
	//or simpler (by using default arguments)
	//RFE_Configure(NULL, fd, RFE_CID_HAM_0145);

	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	//Change mode to transmit
	LimeRFE_8001P_Mode(rfe, LimeRFE_8001P_MODE_TX);

	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
*/	

	//Reset LimeRFE
	LimeRFE_8001P_Reset(limerfe_8001p);

	limerfe_8001p_boardState state;
	int result;	
	result = LimeRFE_8001P_GetState(limerfe_8001p, &state);
//milans 221223
//	printf("state.DA1_EN = %d\n", state.DA1_EN);
//	state.DA1_EN = 1;
	printf("state.PDA1_EN = %d\n", state.PDA1_EN);
	state.PDA1_EN = 1;

    result = LimeRFE_8001P_SetState(limerfe_8001p, state);

	result = LimeRFE_8001P_GetState(limerfe_8001p, &state);
//milans 221223
//	printf("state.DA1_EN = %d\n", state.DA1_EN);
	printf("state.PDA1_EN = %d\n", state.PDA1_EN);
	
	//Close port
	LimeRFE_8001P_Close(limerfe_8001p);

	return 0;
}
