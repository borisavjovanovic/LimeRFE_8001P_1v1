/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   LimeRFE_8001P_Device.cpp
 * Author: ignas
 *
 * Created on September 4, 2019, 1:18 PM
 */

#include "LimeRFE_8001P_Device.h"
#include "LimeRFE_8001P_constants.h"
// #include "lms7_device.h"

LimeRFE_8001P_Device::LimeRFE_8001P_Device(lms_device_t *dev, LimeRFE_8001P_COM com) : sdrDevice(dev),
																  com(com)
{
	//	Cmd_GetConfig(dev, com, &boardState);
}

LimeRFE_8001P_Device::~LimeRFE_8001P_Device()
{
}