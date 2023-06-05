#include "LimeRFE_8001P_constants.h"
// #include "lms7_device.h"
#include "LimeRFE_8001P_Device.h"
#include <cstdint>
// milans 220420
// #include "Logger.h"
#include "./LMS8001/API/lms8_device.h"
#include "./LMS8001/lms8001/lmsComms.h"
#include <iostream>

#define SERIAL_BAUDRATE 9600
// #define SERIAL_BAUDRATE 115200

/****************************************************************************
 *
 *   LimeLimeRFE_8001P API Functions
 *
 *****************************************************************************/
extern "C" API_EXPORT limerfe_8001p_dev_t *CALL_CONV LimeRFE_8001P_Open(const char *serialport, lms_device_t *dev)
{
    if (dev == nullptr && serialport == nullptr)
        return nullptr;

    int result;

    LimeRFE_8001P_COM com;
    // for unix
    // B.J. commented 24.11.2022
#ifdef __unix__
    com.fd = -1;
    com.hComm = -1; // B.J.
#endif
#ifndef __unix__
    com.hComm = 0;
#endif
    if (serialport != nullptr)
    {
        result = Limerfe_8001p_serialport_init(serialport, SERIAL_BAUDRATE, &com);
        if (result == -1)
            return nullptr;
        cout << "com.fd =" << com.fd << std::endl;            // B.J.
        cout << "com.hComm =" << (int)com.hComm << std::endl; // B.J.
        // milans 220421
        //		result = Cmd_Hello(com);
        //         if (result == LimeRFE_8001P_ERROR_COMM) {
        //             return nullptr;
        //         }
    }
    else
    {
        cout << "com.fd =" << com.fd << std::endl;            // B.J.
        cout << "com.hComm =" << (int)com.hComm << std::endl; // B.J.
        // Limerfe_8001p_Cmd_Hello(dev, com);
    }
    return new LimeRFE_8001P_Device(dev, com);
}

extern "C" API_EXPORT limerfe_8001p_dev_t *CALL_CONV LimeRFE_8001P_FindAndOpen(lms_device_t *dev)
{
    // if (dev == nullptr)
    //    return nullptr;

    bool gotPort = 0; // in case the port is not found
    char portName[100];

#ifdef _MSC_VER
    TCHAR lpTargetPath[5000]; // buffer to store the path of the COMPORTS
    DWORD test;
    for (int i = 0; i < 255; i++) // checking ports from COM0 to COM255
    {
        sprintf(portName, "COM%d", i);

        test = QueryDosDeviceA((LPCSTR)portName, (LPSTR)lpTargetPath, 5000);

        // Test the return value and error if any
        if (test != 0) // QueryDosDevice returns zero if it didn't find an object
        {
            i = 255;
            gotPort = 1;          
        }

        if (::GetLastError() == ERROR_INSUFFICIENT_BUFFER)
        {
            lpTargetPath[10000]; // in case the buffer got filled, increase size of the buffer.
            continue;
        }
    }
#endif // WIN

#ifdef __unix__
    // Maybe it would be better to follow this:
    // https://stackoverflow.com/questions/15342804/c-linux-detect-all-serial-ports
    // instead of trying to open port, as it is implemented now
    int fd;

    for (int i = 0; i < 255; i++)
    {
        // sprintf(portName, "/dev/ttyUSB%d", i);
        //  B.J. raspberry pico serial port has different label
        sprintf(portName, "/dev/ttyACM%d", i); //
        //cout << "port ="<< portName << std::endl;    
        //	    fd = open(portName, O_RDWR | O_NOCTTY | O_DELAY);
        fd = open(portName, O_RDWR | O_NOCTTY);
        if (fd != -1)
        {
            i = 255;
            gotPort = 1;
            //cout << "port ="<< portName << std::endl;            // B.J   
        }
    }
#endif // LINUX

    if (gotPort == 0) return nullptr;
    int result = 0;
    LimeRFE_8001P_COM com;
    // for unix
    // B.J. commented 24.11.2022
#ifdef __unix__
    com.fd = -1;
    com.hComm = -1; // B.J.
#endif
#ifndef __unix__
    com.hComm = 0;
#endif

    const char * serialport = (const char*) portName;
    
    if (serialport != nullptr)
    {
        result = Limerfe_8001p_serialport_init(serialport, SERIAL_BAUDRATE, &com);
        if (result == -1)
            return nullptr;
        
        cout << "port ="<< serialport << std::endl;            // B.J   
        cout << "com.fd =" << com.fd << std::endl;            // B.J.
        cout << "com.hComm =" << (int)com.hComm << std::endl; // B.J.
    }
    else
    {
        cout << "com.fd =" << com.fd << std::endl;            // B.J.
        cout << "com.hComm =" << (int)com.hComm << std::endl; // B.J.
        // Limerfe_8001p_Cmd_Hello(dev, com);
    }
    return new LimeRFE_8001P_Device(dev, com);
}

extern "C" API_EXPORT void CALL_CONV LimeRFE_8001P_Close(limerfe_8001p_dev_t *limerfe_8001p)
{
    if (!limerfe_8001p)
        return;
    auto *dev = static_cast<LimeRFE_8001P_Device *>(limerfe_8001p);
    if ((dev->com).fd >= 0)
        Limerfe_8001p_serialport_close(dev->com);
    delete dev;
}

extern "C" API_EXPORT int CALL_CONV LimeRFE_8001P_GetInfo(limerfe_8001p_dev_t *limerfe_8001p, unsigned char *cinfo)
{
    Limerfe_8001p_boardInfo info;
    int result = 0;
    if (!limerfe_8001p)
        return -1;
    auto *dev = static_cast<LimeRFE_8001P_Device *>(limerfe_8001p);
    result = Limerfe_8001p_Cmd_GetInfo(dev->sdrDevice, dev->com, &info);
    cinfo[0] = info.fw_ver;
    cinfo[1] = info.hw_ver;
    cinfo[2] = info.status1;
    cinfo[3] = info.status2;

    return result;
}

extern "C" API_EXPORT int LimeRFE_8001P_LoadConfig(limerfe_8001p_dev_t *limerfe_8001p, const char *filename)
{

    int result = 0;
    if (!limerfe_8001p)
        return -1;
    auto *dev = static_cast<LimeRFE_8001P_Device *>(limerfe_8001p);

    result = Limerfe_8001p_Cmd_LoadConfig(dev->sdrDevice, dev->com, filename);

    //        if (result == 0)
    //            dev->UpdateState();

    return result;
}

// B.J.
extern "C" API_EXPORT int LimeRFE_8001P_SaveConfig(limerfe_8001p_dev_t *limerfe_8001p, const char *filename) // limerfe_8001p_boardState state)
{

    int result = 0;
    if (!limerfe_8001p)
        return -1;
    auto *dev = static_cast<LimeRFE_8001P_Device *>(limerfe_8001p);

    result = Limerfe_8001p_Cmd_SaveConfig(dev->sdrDevice, dev->com, filename);
    return result;
}

extern "C" API_EXPORT int LimeRFE_8001P_Reset(limerfe_8001p_dev_t *limerfe_8001p)
{
    int result = 0;

    if (!limerfe_8001p)
        return -1;
    auto *dev = static_cast<LimeRFE_8001P_Device *>(limerfe_8001p);

    result = Limerfe_8001p_Cmd_Reset(dev->sdrDevice, dev->com);

    //        if (result == 0)
    //            dev->UpdateState();

    return result;
}

// milans 221128
extern "C" API_EXPORT int LimeRFE_8001P_LMS8_Enable(limerfe_8001p_dev_t *limerfe_8001p, int value)
{
    int result = 0;

    if (!limerfe_8001p)
        return -1;
    auto *dev = static_cast<LimeRFE_8001P_Device *>(limerfe_8001p);

    result = Limerfe_8001p_Cmd_lms8_Enable(dev->sdrDevice, dev->com, value);

    //        if (result == 0)
    //            dev->UpdateState();

    return result;
}

/*
extern "C" API_EXPORT int LimeRFE_8001P_Configure(limerfe_8001p_dev_t *limerfe_8001p, char channelIDRX, char channelIDTX, char portRX, char portTX, char mode, char notch, char attenuation, char enableSWR, char sourceSWR)
{
    limerfe_8001p_boardState state = {channelIDRX, channelIDTX, portRX, portTX, mode, notch, attenuation, enableSWR, sourceSWR};
    return LimeRFE_8001P_ConfigureState(limerfe_8001p, state);
}

extern "C" API_EXPORT int LimeRFE_8001P_ConfigureState(limerfe_8001p_dev_t *limerfe_8001p, limerfe_8001p_boardState state)
{
    int result = 0;
            if (!limerfe_8001p)
                return -1;
            auto* dev = static_cast<LimeRFE_8001P_Device*>(limerfe_8001p);

    //        dev->AutoFreq(state);

        result = Cmd_Configure(dev->sdrDevice, dev->com, state.channelIDRX, state.channelIDTX, state.selPortRX, state.selPortTX, state.mode, state.notchOnOff, state.attValue, state.enableSWR, state.sourceSWR);

            if (result == 0)
    //            dev->UpdateState(state);
    return result;
}
*/
// milans 221201
// This function may be useful... Implement it!
// Maybe there should be LimeRFE_8001P_GetState, and LimeRFE_8001P_SetState...
extern "C" API_EXPORT int LimeRFE_8001P_SetState(limerfe_8001p_dev_t *limerfe_8001p, limerfe_8001p_boardState state)
{
    int result = 0;

    if (!limerfe_8001p)
        return -1;
    auto *dev = static_cast<LimeRFE_8001P_Device *>(limerfe_8001p);

    result = Limerfe_8001p_Cmd_Configure(dev->sdrDevice, dev->com, state);

    return result;
}

extern "C" API_EXPORT int LimeRFE_8001P_GetState(limerfe_8001p_dev_t *limerfe_8001p, limerfe_8001p_boardState *state)
{
    int result = 0;

    if (!limerfe_8001p)
        return -1;
    auto *dev = static_cast<LimeRFE_8001P_Device *>(limerfe_8001p);

    result = Limerfe_8001p_Cmd_GetConfig(dev->sdrDevice, dev->com, state);

    return result;
}

extern "C" API_EXPORT int LimeRFE_8001P_ADF4002_Config(limerfe_8001p_dev_t *limerfe_8001p, double freq, int *rcount, int *ncount)
{
    int result = 0;

    if (!limerfe_8001p)
        return -1;
    auto *dev = static_cast<LimeRFE_8001P_Device *>(limerfe_8001p);

    result = Limerfe_8001p_ADF4002_config(dev->sdrDevice, dev->com, freq, *rcount, *ncount);
    return result;
}


/*
extern "C" API_EXPORT int LimeRFE_8001P_GetState(limerfe_8001p_dev_t *limerfe_8001p, limerfe_8001p_boardState *state)
{
    int result = 0;

    if (!limerfe_8001p)
        return -1;
    auto *dev = static_cast<LimeRFE_8001P_Device *>(limerfe_8001p);

    result = Limerfe_8001p_Cmd_GetConfig(dev->sdrDevice, dev->com, state);

    return result;
}
*/
/*
extern "C" API_EXPORT int LimeRFE_8001P_Mode(limerfe_8001p_dev_t *limerfe_8001p, int mode)
{
    int result = 0;

    if (!limerfe_8001p)
        return -1;
    auto *dev = static_cast<LimeRFE_8001P_Device *>(limerfe_8001p);

    result = Limerfe_8001p_Cmd_Mode(dev->sdrDevice, dev->com, mode);

    //        if (result == 0)
    //            dev->UpdateState(mode);
    return result;
}

extern "C" API_EXPORT int LimeRFE_8001P_ReadADC(limerfe_8001p_dev_t *limerfe_8001p, int adcID, int *value)
{
    if (!limerfe_8001p)
        return -1;
    auto *dev = static_cast<LimeRFE_8001P_Device *>(limerfe_8001p);

    return Limerfe_8001p_Cmd_ReadADC(dev->sdrDevice, dev->com, adcID, value);
}

extern "C" API_EXPORT int LimeRFE_8001P_ConfGPIO(limerfe_8001p_dev_t *limerfe_8001p, int gpioNum, int direction)
{
    if (!limerfe_8001p)
        return -1;
    auto *dev = static_cast<LimeRFE_8001P_Device *>(limerfe_8001p);

    return Limerfe_8001p_Cmd_ConfGPIO(dev->sdrDevice, dev->com, gpioNum, direction);
}

extern "C" API_EXPORT int LimeRFE_8001P_SetGPIO(limerfe_8001p_dev_t *limerfe_8001p, int gpioNum, int val)
{
    if (!limerfe_8001p)
        return -1;
    auto *dev = static_cast<LimeRFE_8001P_Device *>(limerfe_8001p);

    return Limerfe_8001p_Cmd_SetGPIO(dev->sdrDevice, dev->com, gpioNum, val);
}

extern "C" API_EXPORT int LimeRFE_8001P_GetGPIO(limerfe_8001p_dev_t *limerfe_8001p, int gpioNum, int *val)
{
    if (!limerfe_8001p)
        return -1;
    auto *dev = static_cast<LimeRFE_8001P_Device *>(limerfe_8001p);

    return Limerfe_8001p_Cmd_GetGPIO(dev->sdrDevice, dev->com, gpioNum, val);
}

API_EXPORT int CALL_CONV LimeRFE_8001P_AssignSDRChannels(limerfe_8001p_dev_t *limerfe_8001p, int rx, int tx)
{
    if (!limerfe_8001p)
        return -1;
    auto *dev = static_cast<LimeRFE_8001P_Device *>(limerfe_8001p);
    //    dev->SetChannels(rx, tx);
    return 0;
}

extern "C" API_EXPORT int LimeRFE_8001P_Fan(limerfe_8001p_dev_t *limerfe_8001p, int enable)
{
    if (!limerfe_8001p)
        return -1;
    auto *dev = static_cast<LimeRFE_8001P_Device *>(limerfe_8001p);

    return Limerfe_8001p_Cmd_Fan(dev->sdrDevice, dev->com, enable);
}

extern "C" API_EXPORT int LimeRFE_8001P_Diode(limerfe_8001p_dev_t *limerfe_8001p, int state)
{
    if (!limerfe_8001p)
        return -1;
    auto *dev = static_cast<LimeRFE_8001P_Device *>(limerfe_8001p);

    return Limerfe_8001p_Cmd_Diode(dev->sdrDevice, dev->com, state);
}

extern "C" API_EXPORT int LimeRFE_8001P_DiodeSPI(limerfe_8001p_dev_t *limerfe_8001p, int state)
{
    if (!limerfe_8001p)
        return -1;
    auto *dev = static_cast<LimeRFE_8001P_Device *>(limerfe_8001p);

    return Limerfe_8001p_Cmd_DiodeSPI(dev->sdrDevice, dev->com, state);
}
*/
extern "C" API_EXPORT int LimeRFE_8001P_SC1905_Enable(limerfe_8001p_dev_t *limerfe_8001p, uint8_t channel, uint8_t enable)
{
    if (!limerfe_8001p)
        return -1;
    auto *dev = static_cast<LimeRFE_8001P_Device *>(limerfe_8001p);

    limerfe_8001p_boardState state;
    int result = 0;

    result = LimeRFE_8001P_GetState(limerfe_8001p, &state);

    if (channel == 0)
    {
        if (enable == 1)
            state.SC1905_1_RESETn = 1;
        else
            state.SC1905_1_RESETn = 0;
    }
    else
    {
        if (enable == 1)
            state.SC1905_2_RESETn = 1;
        else
            state.SC1905_2_RESETn = 0;
    }
    result = LimeRFE_8001P_SetState(limerfe_8001p, state);
    return result;
}

extern "C" API_EXPORT int LimeRFE_8001P_Set_TX_Att(limerfe_8001p_dev_t *limerfe_8001p, uint8_t channel, float attenuation)
{
    if (!limerfe_8001p)
        return -1;
    auto *dev = static_cast<LimeRFE_8001P_Device *>(limerfe_8001p);

    limerfe_8001p_boardState state;
    int result = 0;

    uint8_t value = (uint8_t)(attenuation * 4.0);
    if (value > 127)
        value = 127;

    result = LimeRFE_8001P_GetState(limerfe_8001p, &state);

    if (channel == 0)
        state.TX1_ATT = value;
    else
        state.TX2_ATT = value;

    result = LimeRFE_8001P_SetState(limerfe_8001p, state);
    return result;
}

extern "C" API_EXPORT int LimeRFE_8001P_Set_ORX_Att(limerfe_8001p_dev_t *limerfe_8001p, uint8_t channel, float attenuation)
{
    if (!limerfe_8001p)
        return -1;
    auto *dev = static_cast<LimeRFE_8001P_Device *>(limerfe_8001p);

    limerfe_8001p_boardState state;
    int result = 0;

    uint8_t value = (uint8_t)(attenuation * 4.0);
    if (value > 127)
        value = 127;

    result = LimeRFE_8001P_GetState(limerfe_8001p, &state);

    if (channel == 0)
        state.ORX1_ATT = value;
    else
        state.ORX2_ATT = value;

    result = LimeRFE_8001P_SetState(limerfe_8001p, state);
    return result;
}

extern "C" API_EXPORT int LimeRFE_8001P_Get_TX_Att(limerfe_8001p_dev_t *limerfe_8001p, uint8_t channel, float *attenuation)
{
    if (!limerfe_8001p)
        return -1;
    auto *dev = static_cast<LimeRFE_8001P_Device *>(limerfe_8001p);

    limerfe_8001p_boardState state;
    int result = 0;

    uint8_t value = 0;
    result = LimeRFE_8001P_GetState(limerfe_8001p, &state);

    if (channel == 0)
        value = state.TX1_ATT;
    else
        value = state.TX2_ATT;
    if (value > 127)
        value = 127;

    *attenuation = ((float)(value)) / 4.0;

    return result;
}

extern "C" API_EXPORT int LimeRFE_8001P_Get_ORX_Att(limerfe_8001p_dev_t *limerfe_8001p, uint8_t channel, float *attenuation)
{
    if (!limerfe_8001p)
        return -1;
    auto *dev = static_cast<LimeRFE_8001P_Device *>(limerfe_8001p);

    limerfe_8001p_boardState state;
    int result = 0;

    uint8_t value = 0;
    result = LimeRFE_8001P_GetState(limerfe_8001p, &state);

    if (channel == 0)
        value = state.ORX1_ATT;
    else
        value = state.ORX2_ATT;
    if (value > 127)
        value = 127;

    *attenuation = ((float)(value)) / 4.0;
    return result;
}

extern "C" API_EXPORT int LimeRFE_8001P_SC1905_SPI_Message_Memory(limerfe_8001p_dev_t *limerfe_8001p, uint16_t address, uint8_t *val, bool isRead, int bytesNo, bool isEEPROM)
{
    if (!limerfe_8001p)
        return -1;
    auto *dev = static_cast<LimeRFE_8001P_Device *>(limerfe_8001p);

    return Limerfe_8001p_Cmd_SC1905_SPI_Message_Memory(dev->sdrDevice, dev->com, address, val, isRead, bytesNo, isEEPROM);
}

extern "C" API_EXPORT int LimeRFE_8001P_SC1905_SPI_Special_Command(limerfe_8001p_dev_t *limerfe_8001p, int command)
{
    if (!limerfe_8001p)
        return -1;
    auto *dev = static_cast<LimeRFE_8001P_Device *>(limerfe_8001p);

    return Limerfe_8001p_Cmd_SC1905_SPI_Special_Command(dev->sdrDevice, dev->com, command);
}

extern "C" API_EXPORT int LimeRFE_8001P_SC1905_Reset(limerfe_8001p_dev_t *limerfe_8001p)
{
    if (!limerfe_8001p)
        return -1;
    auto *dev = static_cast<LimeRFE_8001P_Device *>(limerfe_8001p);

    return Limerfe_8001p_Cmd_SC1905_Reset(dev->sdrDevice, dev->com);
}

extern "C" API_EXPORT int LimeRFE_8001P_SC1905_Apply_Frequency(limerfe_8001p_dev_t *limerfe_8001p, int freqRange, int minFreq, int maxFreq)
{
    if (!limerfe_8001p)
        return -1;
    auto *dev = static_cast<LimeRFE_8001P_Device *>(limerfe_8001p);

    return Limerfe_8001p_Cmd_SC1905_Apply_Frequency(dev->sdrDevice, dev->com, freqRange, minFreq, maxFreq);
}

extern "C" API_EXPORT int LimeRFE_8001P_SC1905_Set_Duty_Cycle_Feedback(limerfe_8001p_dev_t *limerfe_8001p, uint8_t Enabled)
{
    if (!limerfe_8001p)
        return -1;
    auto *dev = static_cast<LimeRFE_8001P_Device *>(limerfe_8001p);

    return Limerfe_8001p_Cmd_SC1905S_Set_Duty_Cycle_Feedback(dev->sdrDevice, dev->com, Enabled);
}

extern "C" API_EXPORT int LimeRFE_8001P_SC1905_Set_Adaptation_State(limerfe_8001p_dev_t *limerfe_8001p, uint8_t Running)
{
    if (!limerfe_8001p)
        return -1;
    auto *dev = static_cast<LimeRFE_8001P_Device *>(limerfe_8001p);

    return Limerfe_8001p_Cmd_SC1905S_Set_Adaptation_State(dev->sdrDevice, dev->com, Running);
}

extern "C" API_EXPORT int LimeRFE_8001P_SC1905_Set_Correction_Enable(limerfe_8001p_dev_t *limerfe_8001p, uint8_t Enabled)
{
    if (!limerfe_8001p)
        return -1;
    auto *dev = static_cast<LimeRFE_8001P_Device *>(limerfe_8001p);

    return Limerfe_8001p_Cmd_SC1905S_Set_Correction_Enable(dev->sdrDevice, dev->com, Enabled);
}

extern "C" API_EXPORT int LimeRFE_8001P_SC1905_Read_RFIN_AGC(limerfe_8001p_dev_t *limerfe_8001p, int *rfinAgc)
{
    if (!limerfe_8001p)
        return -1;
    auto *dev = static_cast<LimeRFE_8001P_Device *>(limerfe_8001p);

    return Limerfe_8001p_Cmd_SC1905S_Read_RFIN_AGC(dev->sdrDevice, dev->com, rfinAgc);
}

extern "C" API_EXPORT int LimeRFE_8001P_SC1905_Read_RFFB_AGC(limerfe_8001p_dev_t *limerfe_8001p, int *rffbAgc)
{
    if (!limerfe_8001p)
        return -1;
    auto *dev = static_cast<LimeRFE_8001P_Device *>(limerfe_8001p);

    return Limerfe_8001p_Cmd_SC1905S_Read_RFFB_AGC(dev->sdrDevice, dev->com, rffbAgc);
}

extern "C" API_EXPORT int LimeRFE_8001P_SC1905_Read_Center_Frequency(limerfe_8001p_dev_t *limerfe_8001p, float *centerFreq)
{
    if (!limerfe_8001p)
        return -1;
    auto *dev = static_cast<LimeRFE_8001P_Device *>(limerfe_8001p);

    return Limerfe_8001p_Cmd_SC1905S_Read_Center_Frequency(dev->sdrDevice, dev->com, centerFreq);
}

extern "C" API_EXPORT int LimeRFE_8001P_SC1905_Read_Signal_Bandwidth(limerfe_8001p_dev_t *limerfe_8001p, float *bandwidth)
{
    if (!limerfe_8001p)
        return -1;
    auto *dev = static_cast<LimeRFE_8001P_Device *>(limerfe_8001p);

    return Limerfe_8001p_Cmd_SC1905S_Read_Signal_Bandwidth(dev->sdrDevice, dev->com, bandwidth);
}

extern "C" API_EXPORT int LimeRFE_8001P_SC1905_Read_Error_Code(limerfe_8001p_dev_t *limerfe_8001p, char *stringValue)
{
    if (!limerfe_8001p)
        return -1;
    auto *dev = static_cast<LimeRFE_8001P_Device *>(limerfe_8001p);

    return Limerfe_8001p_Cmd_SC1905S_Read_Error_Code(dev->sdrDevice, dev->com, stringValue);
}

extern "C" API_EXPORT int LimeRFE_8001P_SC1905_Read_Warning_Code(limerfe_8001p_dev_t *limerfe_8001p, char *stringValue)
{
    if (!limerfe_8001p)
        return -1;
    auto *dev = static_cast<LimeRFE_8001P_Device *>(limerfe_8001p);

    return Limerfe_8001p_Cmd_SC1905S_Read_Warning_Code(dev->sdrDevice, dev->com, stringValue);
}

extern "C" API_EXPORT int LimeRFE_8001P_SC1905_GetStatus(limerfe_8001p_dev_t *limerfe_8001p, char *statusString)
{
    if (!limerfe_8001p)
        return -1;
    auto *dev = static_cast<LimeRFE_8001P_Device *>(limerfe_8001p);

    return Limerfe_8001p_Cmd_SC1905_GetStatus(dev->sdrDevice, dev->com, statusString);
}

extern "C" API_EXPORT int LimeRFE_8001P_Set_Config_Full(limerfe_8001p_dev_t *limerfe_8001p, uint8_t *state, int size)
{
    if (!limerfe_8001p)
        return -1;
    auto *dev = static_cast<LimeRFE_8001P_Device *>(limerfe_8001p);

    return Limerfe_8001p_Cmd_Set_Config_Full(dev->sdrDevice, dev->com, state, size);
}

extern "C" API_EXPORT int LimeRFE_8001P_Get_Config_Full(limerfe_8001p_dev_t *limerfe_8001p, uint8_t *state, int size)
{
    if (!limerfe_8001p)
        return -1;
    auto *dev = static_cast<LimeRFE_8001P_Device *>(limerfe_8001p);

    return Limerfe_8001p_Cmd_Get_Config_Full(dev->sdrDevice, dev->com, state, size);
}

extern "C" API_EXPORT int LimeRFE_8001P_LMS8_Open(limerfe_8001p_dev_t *limerfe_8001p, lms_device_t **device)
{
    if (device == nullptr)
    {
        //        lime::error("Device pointer cannot be NULL");
        return -1;
    }

    auto dev = LMS8_Device::CreateDevice();
    if (dev == nullptr)
    {
        //        lime::error("Unable to open device");
        return -1;
    }
    *device = dev;

    LMScomms *lms8controlPort = dev->GetConnection();

    LimeRFE_8001P_COM com = ((LimeRFE_8001P_Device *)limerfe_8001p)->com;

    lms8controlPort->InheritCOM(com.hComm);
    lms8controlPort->limerfe_8001p_do_mask = true;
    lms8controlPort->limerfe_8001p_cmd_mask = 0x80;

    return LMS_SUCCESS;
}

// milans 221130
extern "C" API_EXPORT int LimeRFE_8001P_Select_Channel(limerfe_8001p_dev_t *limerfe_8001p, int channel)
{
    int result = 0;

    if (!limerfe_8001p)
        return -1;
    auto *dev = static_cast<LimeRFE_8001P_Device *>(limerfe_8001p);

    result = Limerfe_8001p_Cmd_Select_Channel(dev->sdrDevice, dev->com, channel);

    //        if (result == 0)
    //            dev->UpdateState();

    return result;
}
// B.J.
extern "C" API_EXPORT int LimeRFE_8001P_SPI_write(limerfe_8001p_dev_t *limerfe_8001p, uint16_t maddress, uint16_t address, uint16_t data)
{
    if (!limerfe_8001p)
        return -1;
    auto *dev = static_cast<LimeRFE_8001P_Device *>(limerfe_8001p);
    return Limerfe_8001p_SPI_write(dev->sdrDevice, maddress, address, data);
}

extern "C" API_EXPORT int LimeRFE_8001P_SPI_read(limerfe_8001p_dev_t *limerfe_8001p, uint16_t maddress, uint16_t address, uint16_t *pData)
{
    if (!limerfe_8001p)
        return -1;
    auto *dev = static_cast<LimeRFE_8001P_Device *>(limerfe_8001p);
    return Limerfe_8001p_SPI_read(dev->sdrDevice, maddress, address, pData);
}

extern "C" API_EXPORT int LimeRFE_8001P_SPI_write_buffer(lms_device_t *limerfe_8001p, unsigned char *c, int size)
{
    if (!limerfe_8001p)
        return -1;
    auto *dev = static_cast<LimeRFE_8001P_Device *>(limerfe_8001p);
    return Limerfe_8001p_spi_write_buffer(dev->sdrDevice, c, size);
}

/*
extern "C" API_EXPORT int LimeRFE_8001P_SPI_read_buffer2(lms_device_t *limerfe_8001p, unsigned char *c, int size) {

    if (!limerfe_8001p)
        return -1;
    auto *dev = static_cast<LimeRFE_8001P_Device *>(limerfe_8001p);
    return Limerfe_8001p_spi_read_buffer2(dev->sdrDevice, c, size);
}
*/

extern "C" API_EXPORT int LimeRFE_8001P_SPI_read_buffer(lms_device_t *limerfe_8001p, unsigned char *c, int size)
{

    if (!limerfe_8001p)
        return -1;
    auto *dev = static_cast<LimeRFE_8001P_Device *>(limerfe_8001p);
    return Limerfe_8001p_spi_read_buffer(dev->sdrDevice, c, size);
}
