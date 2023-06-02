/**
    @file ConnectionManager.h
    @author Lime Microsystems (www.limemicro.com)
    @brief Class for managing connection to devices
*/

#ifndef LMS_CONNECTION_MANAGER_H
#define LMS_CONNECTION_MANAGER_H

#include "./IConnection.h"
#include <map>

// milans 220614
#ifndef __unix__
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#include "./../../LimeSuite.h" // B.J.
//#include "lime/lms7_device.h"

class ConnectionManager
{
public:
    struct DeviceInfo
    {
        std::string name;
        lms8_IConnection::eConnectionType port;
        int portIndex;
    };

     lms_device_t* lmsControlSDR;  // B.J. connection to the LimeSDR board

    ConnectionManager();
    ~ConnectionManager();
    bool IsOpen();
    bool Open();
    int Open(unsigned i);
    void Close();
    int RefreshDeviceList();
    int GetOpenedIndex();
    std::vector<std::string> GetDeviceList() { return mDeviceList; };

    int Write(const unsigned char *buffer, int length, int timeout_ms = 0);
    int Read(unsigned char *buffer, int length, int timeout_ms = 0);

    int WriteStream(const char *buffer, int length);
    int ReadStream(char *buffer, int length, unsigned int timeout_ms);

    int BeginDataReading(char *buffer, long length);
    int WaitForReading(int contextHandle, unsigned int timeout_ms);
    int FinishDataReading(char *buffer, long &length, int contextHandle);
    void AbortReading();

    int BeginDataSending(const char *buffer, long length);
    int WaitForSending(int contextHandle, unsigned int timeout_ms);
    int FinishDataSending(const char *buffer, long &length, int contextHandle);
    void AbortSending();

     // B.J.
    void InitializeSDR(lms_device_t *lms);
    int SPI_write(lms_device_t *lms, uint16_t maddress, uint16_t address, uint16_t data);
    int SPI_read(lms_device_t *lms, uint16_t maddress, uint16_t address, uint16_t *data);
    int SPI_write_buffer(lms_device_t *lms, const unsigned char *c, int size);
    int SPI_read_buffer(lms_device_t *lms, unsigned char *c, int size);
    void ConvertToAscii(uint8_t ch, uint8_t *pX10, uint8_t *pX1);

    // milans 220614
#ifndef __unix__
    void InheritCOM(HANDLE handle);
#else
    // B.J. -- unix support
    void InheritCOM(int handle);
#endif

protected:
    bool mLogData;
    /// Port used for communication.
    lms8_IConnection *activeControlPort;
    std::vector<DeviceInfo> mDevices;
    std::vector<std::string> mDeviceList;
    int mOpenedDevice;
    std::map<lms8_IConnection::eConnectionType, lms8_IConnection *> m_connections;
};

#endif // LMS_CONNECTION_MANAGER_H
