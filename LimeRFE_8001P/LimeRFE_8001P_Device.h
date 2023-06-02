/*
 * File:   LimeRFE_8001P_Device.h
 * Author: ignas
 *
 * Created on September 4, 2019, 1:18 PM
 */

#ifndef LimeRFE_8001P_DEVICE_H
#define LimeRFE_8001P_DEVICE_H

#include "LimeRFE_8001P_constants.h"

class LimeRFE_8001P_Device
{
public:
    LimeRFE_8001P_Device(lms_device_t *d, LimeRFE_8001P_COM com);
    LimeRFE_8001P_Device(const LimeRFE_8001P_Device &) = delete;
    LimeRFE_8001P_Device &operator=(const LimeRFE_8001P_Device &) = delete;
    ~LimeRFE_8001P_Device();
    lms_device_t *sdrDevice;
    struct LimeRFE_8001P_COM com;

private:
    limerfe_8001p_boardState boardState;
};

#endif /* LimeRFE_8001P_DEVICE_H */
