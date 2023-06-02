/**
    @file ConnectionManager.cpp
    @author Lime Microsystems (www.limemicro.com)
    @brief Implementation of various connection types to devices
*/

#include "ConnectionManager.h"
#include "ConnectionCOM.h"
#include "./../../../LimeRFE_8001P_constants.h"

#ifdef ENABLE_USB_CONNECTION
#include "ConnectionUSB.h"
#endif
#ifdef ENABLE_SPI_CONNECTION
#include "ConnectionSPI.h"
#endif

#include <sstream>
#include <iomanip>
#include <iostream>

#include <thread>
// #include "lime/lms7_device.h"

#define MADDRESS 170 * 32
#define MADDRESS2 171 * 32

/** @brief Creates connection interfaces
 */
ConnectionManager::ConnectionManager() : activeControlPort(NULL)
{
    mLogData = false;
    mOpenedDevice = -1;
    lmsControlSDR = nullptr; // B.J.

    m_connections[lms8_IConnection::COM_PORT] = new ConnectionCOM();
#ifdef ENABLE_USB_CONNECTION
    m_connections[lms8_IConnection::USB_PORT] = new ConnectionUSB();
#endif
#ifdef ENABLE_SPI_CONNECTION
    m_connections[lms8_IConnection::SPI_PORT] = new ConnectionSPI();
#endif
}

/** @brief Destroys connection interfaces
 */
ConnectionManager::~ConnectionManager()
{
    for (auto iter = m_connections.begin(); iter != m_connections.end(); ++iter)
    {
        delete iter->second;
    }
}

/** @brief Checks if connection to device is opened
    @return True if device is connected
*/
bool ConnectionManager::IsOpen()
{
    // if ((activeControlPort->IsOpen()) || (lmsControlSDR != nullptr))
    // return true;
    // else return false;    
    return activeControlPort ? activeControlPort->IsOpen() : false;
}

/** @brief Opens connection to first available device
    @return True if connected to device
*/
bool ConnectionManager::Open()
{
    return Open(0);
}

/** @brief Connects to selected device
    @param i device index from device list
    @return 1:Success, 0:failure
*/
int ConnectionManager::Open(unsigned i)
{
    if (i >= mDevices.size())
        return 0;

    if (activeControlPort)
        activeControlPort->Close();
    switch (mDevices[i].port)
    {
     case lms8_IConnection::COM_PORT:
        activeControlPort = m_connections[lms8_IConnection::COM_PORT];
        break;
    case lms8_IConnection::USB_PORT:
        activeControlPort = m_connections[lms8_IConnection::USB_PORT];
        break;
    case lms8_IConnection::SPI_PORT:
        activeControlPort = m_connections[lms8_IConnection::SPI_PORT];
        break;
    default:
        return 0;
    }
    mOpenedDevice = -1;
    if (i < mDevices.size())
    {
        if (activeControlPort->Open(mDevices[i].portIndex))
        {
            mOpenedDevice = i;
            return 1;
        }
    }
    return 0;
}

/** @brief Closes connection to device
 */
void ConnectionManager::Close()
{
    if (activeControlPort)
    {
        activeControlPort->Close();
        // Notify(LMS_Message(MSG_BOARD_DISCONNECTED, "", 0, 0));
    }
    mOpenedDevice = -1;
}

/** @brief Finds all currently connected devices and forms device list
    @return number of devices found
*/
int ConnectionManager::RefreshDeviceList()
{
    mDeviceList.clear();
    mDevices.clear();
    DeviceInfo dev;
    for (auto iter = m_connections.begin(); iter != m_connections.end(); ++iter)
    {
        vector<string> names;
        lms8_IConnection *port = iter->second;
        if (port->RefreshDeviceList() > 0)
        {
            names = port->GetDeviceNames();
            for (unsigned i = 0; i < names.size(); ++i)
            {
                dev.name = names[i];
                dev.port = iter->first;
                dev.portIndex = i;
                mDevices.push_back(dev);
            }
        }
    }
    for (unsigned i = 0; i < mDevices.size(); ++i)
        mDeviceList.push_back(mDevices[i].name);
    return mDevices.size();
}

/** @brief Returns currently opened connection index
 */
int ConnectionManager::GetOpenedIndex()
{
    return mOpenedDevice;
}

/** @brief Writes given data to currently opened connection
    @param buffer outcomming data buffer
    @param length bytes to write
    @param timeout_ms timeout in milliseconds
    @return number of bytes written, on failure negative values
*/
int ConnectionManager::Write(const unsigned char *buffer, const int length, int timeout_ms)
{
    if (activeControlPort)
    {

        // B.J. debug
        /*
        cout << "COM Write ";  // B.J.
        uint8_t X10, X1 = 0x00;
        for (int i=0; i<length; i++) {
            ConvertToAscii(buffer[i], &X10, &X1);
            cout << X10 << X1;
        }
        cout << std::endl;
        */

        int bytesTransferred = activeControlPort->Write(buffer, length, timeout_ms);

#ifndef NDEBUG
        if (mLogData)
        {
            stringstream ss;
            ss << "WR(" << (bytesTransferred >= 0 ? bytesTransferred : 0) << "): ";
            ss << std::hex << std::setfill('0');
            int repeatedZeros = 0;
            for (int i = length - 1; i >= 0; --i)
                if (buffer[i] == 0)
                    ++repeatedZeros;
                else
                    break;
            if (repeatedZeros == 1)
                repeatedZeros = 0;
            repeatedZeros = repeatedZeros - (repeatedZeros & 0x1);
            for (int i = 0; i < length - repeatedZeros; ++i)
                // casting to short to print as numbers
                ss << " " << std::setw(2) << (unsigned short)buffer[i];
            if (repeatedZeros > 1)
                ss << " (00 x " << std::dec << repeatedZeros << " times)";
            cout << ss.str() << endl;
        }
#endif
        return bytesTransferred;
    }
    else if (lmsControlSDR != nullptr)
    {

        int bytesTransferred = SPI_write_buffer(lmsControlSDR, buffer, length);
        // std::this_thread::sleep_for(std::chrono::microseconds(500));
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        // B.J. debug
        /*
        cout << "SPI Write ";  // B.J.
        uint8_t X10, X1 = 0x00;
        for (int i=0; i<length; i++) {
            ConvertToAscii(buffer[i], &X10, &X1);
            cout << X10 << X1;
        }
        cout << std::endl;
        */

        return bytesTransferred;
    }
    return -1;
}

void ConnectionManager::ConvertToAscii(uint8_t ch, uint8_t *pX10, uint8_t *pX1)
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

/** @brief Receives data from currently opened connection
    @param buffer incomming data buffer, must be big enough for length bytes
    @param length bytes to read
    @param timeout_ms timeout in milliseconds
    @return number of bytes received
*/
int ConnectionManager::Read(unsigned char *buffer, int length, int timeout_ms)
{

    // printf("Read\n");
    if (activeControlPort)
    {

        int bytesTransferred = activeControlPort->Read(buffer, length, timeout_ms);
        /*
        cout << "COM Read " << std::endl;  // B.J.
        uint8_t X10, X1 = 0x00;
        for (int i=0; i<length; i++) {
            ConvertToAscii(buffer[i], &X10, &X1);
            cout << X10 << X1;
        }
        cout << std::endl;
        */

#ifndef NDEBUG
        if (mLogData)
        {
            stringstream ss;
            ss << "RD(" << (bytesTransferred >= 0 ? bytesTransferred : 0) << "): ";
            ss << std::hex << std::setfill('0');
            int repeatedZeros = 0;
            for (int i = length - 1; i >= 0; --i)
                if (buffer[i] == 0)
                    ++repeatedZeros;
                else
                    break;
            if (repeatedZeros == 2)
                repeatedZeros = 0;
            repeatedZeros = repeatedZeros - (repeatedZeros & 0x1);
            for (int i = 0; i < length - repeatedZeros; ++i)
                // casting to short to print as numbers
                ss << " " << std::setw(2) << (unsigned short)buffer[i];
            if (repeatedZeros > 2)
                ss << " (00 x " << std::dec << repeatedZeros << " times)";
            cout << ss.str() << endl;
        }
#endif
        return bytesTransferred;
    }
    else if (lmsControlSDR != nullptr)
    {

        // std::this_thread::sleep_for(std::chrono::milliseconds(timeout_ms));
        int bytesTransferred = SPI_read_buffer(lmsControlSDR, buffer, length);
        // std::this_thread::sleep_for(std::chrono::milliseconds(timeout_ms));

        /*
        cout << "SPI Read " << std::endl;  // B.J.
        uint8_t X10, X1 = 0x00;
        for (int i=0; i<length; i++) {
            ConvertToAscii(buffer[i], &X10, &X1);
            cout << X10 << X1;
        }
        cout << std::endl;
        */
        return bytesTransferred;
    }
    return -1;
}

int ConnectionManager::WriteStream(const char *buffer, int length)
{
    return 0;
}

int ConnectionManager::ReadStream(char *buffer, int length, unsigned int timeout_ms)
{
    /*int handle = activeControlPort->BeginDataReading(buffer, length);
    activeControlPort->WaitForReading(handle, timeout_ms);
    long received = length;
    activeControlPort->FinishDataReading(buffer, received, handle);
    return received;
    */
    long len = length;
    int status = activeControlPort->ReadDataBlocking(buffer, len, 0);
    return len;
}

int ConnectionManager::BeginDataReading(char *buffer, long length)
{
    return activeControlPort->BeginDataReading(buffer, length);
}
/**
@brief Blocks until data is received or set number of milliseconds have passed.
@param contextHandle handle returned by BeginDataReading()
@param timeout_ms number of milliseconds to wait
@return 1-data received, 0-data not received
*/
int ConnectionManager::WaitForReading(int contextHandle, unsigned int timeout_ms)
{
    return activeControlPort->WaitForReading(contextHandle, timeout_ms);
}
/**
@brief Finished asynchronous data reading.
@param buffer where to put received data
@param length number of bytes to read, will be changed to actual number of bytes received
@param contextHandle context handle returned by BeginDataReading()
@return received data length
*/
int ConnectionManager::FinishDataReading(char *buffer, long &length, int contextHandle)
{
    return activeControlPort->FinishDataReading(buffer, length, contextHandle);
}

/**
@brief Aborts reading operations
*/
void ConnectionManager::AbortReading()
{
    activeControlPort->AbortReading();
}

/**
@brief Start asynchronous data sending.
@param buffer data buffer to be sent
@param length number of bytes to send.
@return context handle
*/
int ConnectionManager::BeginDataSending(const char *buffer, long length)
{
    return activeControlPort->BeginDataSending(buffer, length);
}
/**
@brief Blocks until data is sent or set number of miliseconds have passed.
@param contextHandle handle returned by BeginDataReading()
@param timeout_ms number of miliseconds to wait
@return 1-data sent, 0-data not sent
*/
int ConnectionManager::WaitForSending(int contextHandle, unsigned int timeout_ms)
{
    return activeControlPort->WaitForSending(contextHandle, timeout_ms);
}
/**
@brief Finished asynchronous data sending.
@param buffer where to put received data
@param length number of bytes to send, will be changed to actual number of bytes sent
@param contextHandle context handle returned by BeginDataReading()
@return sent data length
*/
int ConnectionManager::FinishDataSending(const char *buffer, long &length, int contextHandle)
{
    return activeControlPort->FinishDataSending(buffer, length, contextHandle);
}

/**
@brief Aborts sending operations
*/
void ConnectionManager::AbortSending()
{
    activeControlPort->AbortSending();
}

#ifndef __unix__
void ConnectionManager::InheritCOM(HANDLE handle)
{
    activeControlPort = m_connections[lms8_IConnection::COM_PORT];
    ConnectionCOM *tmp = (ConnectionCOM *)activeControlPort;
    tmp->inheritedCOM = true;
    tmp->InheritHCOMM(handle);
}
#else
// B.J. -- unix support
void ConnectionManager::InheritCOM(int handle)
{
    activeControlPort = m_connections[lms8_IConnection::COM_PORT];
    ConnectionCOM *tmp = (ConnectionCOM *)activeControlPort;
    tmp->inheritedCOM = true;
    tmp->InheritHCOMM(handle);
}
#endif

// B.J.
void ConnectionManager::InitializeSDR(lms_device_t *lms)
{
    lmsControlSDR = lms;
}

int ConnectionManager::SPI_write(lms_device_t *lms, uint16_t maddress, uint16_t address, uint16_t data)
{
    int ret = 0;
    ret = Limerfe_8001p_SPI_write(lms, maddress, address, data);
    return ret;
}

int ConnectionManager::SPI_read(lms_device_t *lms, uint16_t maddress, uint16_t address, uint16_t *data)
{
    int ret = 0;
    uint16_t regValue = 0x0000;
    ret = Limerfe_8001p_SPI_read(lms, maddress, address, &regValue);
    *data = regValue;
    return ret;
}

int ConnectionManager::SPI_write_buffer(lms_device_t *lms, const unsigned char *c, int size)
{

    Limerfe_8001p_spi_write_buffer(lms, (unsigned char *)c, size);
    // std::this_thread::sleep_for(std::chrono::milliseconds(100));

    /*
    // size is 16 or 64. Units - bytes
    uint16_t maddress = MADDRESS;
    uint16_t maddress2 = MADDRESS2;
    uint16_t data = 0;
    for (int i = 0; i < size / 2; i++) // transfer data
    {
        data = (uint16_t)(c[2 * i + 1]);
        data = data << 8;
        data += (uint16_t)(c[2 * i]);
        SPI_write(lms, maddress, i, data);
    }
    SPI_write(lms, maddress2, 0, 0x0001); // start the Do_command()
    //
    */

    return size;
}

int ConnectionManager::SPI_read_buffer(lms_device_t *lms, unsigned char *c, int size)
{

    // Limerfe_8001p_spi_read_buffer2(lms, c, size);
    // B.J.
    Limerfe_8001p_spi_read_buffer(lms, c, size);
    return size;

    /*
    uint16_t maddress = MADDRESS;
    uint16_t maddress2 = MADDRESS2;
    uint16_t data = 0;
    bool m_bfound = false;
    int ret = 0;
    int i = 0;
    int numtry = 0;
    while ((i < 10) && (!m_bfound))
    {

        SPI_read(lms, maddress2, 0, &data);
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
        numtry = i;
        ret = ((data & 0xFF00) >> 8);  // number of bytes returned
        for (i = 0; i < size / 2; i++)
        {
            SPI_read(lms, maddress, i, &data);
            c[2 * i + 1] = (uint8_t)(data >> 8);
            c[2 * i] = (uint8_t)(data & 0x00FF);
        }
    }
    else {
        ret = 0;
        numtry = 10;
    }
    return ret;
    */
}
// end B.J.