/**
 * @file lime/LMS8API.h
 *
 * @brief LMS8 API library
 */

#ifndef LMS8_API_H
#define LMS8_API_H

#include <stdint.h>
#include <stdlib.h>
#include "LMS8001_parameters.h"
#include "../lms8001/LMS8001_statuses.h"

#ifdef __cplusplus
extern "C" {
#else
/* stdbool.h is not applicable for C++ programs, as the language inherently
 * provides the bool type.
 *
 * Users of Visual Studio 2012 and earlier will need to supply a stdbool.h
 * implementation, as it is not included with the toolchain. Visual Studio 2013
 * onward supplies this header.
 */
#include <stdbool.h>
#endif

#if defined _WIN32 || defined __CYGWIN__
#   define CALL_CONV __cdecl
#   ifdef __GNUC__
#       define API_EXPORT __attribute__ ((dllexport))
#   else
#       define API_EXPORT __declspec(dllexport)
#   endif
#elif defined _DOXYGEN_ONLY_
    /** Marks an API routine to be made visible to the dynamic loader.
     *  This is OS and/or compiler-specific. */
#   define API_EXPORT
    /** Specifies calling convention, if necessary.
     *  This is OS and/or compiler-specific. */
#   define CALL_CONV
#else
#   define API_EXPORT __attribute__ ((visibility ("default")))
#   define CALL_CONV
#endif

///Floating point data type
typedef double float_type;

///convenience constant for good return code
static const int LMS_SUCCESS = 0;

/**
 * @defgroup FN_INIT    Initialization/deinitialization
 *
 * The functions in this section provide the ability to query available devices,
 * initialize them, and deinitialize them.
 * @{
 */

///LMS Device handle
typedef void lms_device_t;

///Convenience type for fixed length LMS Device information string
typedef char lms_info_str_t[256];

//API_EXPORT int CALL_CONV LMS8_Open(lms_device_t** device, const lms_info_str_t info, void* args);
API_EXPORT int CALL_CONV LMS8_Open(lms_device_t** device, const lms_info_str_t info = NULL, void* args = NULL);
API_EXPORT int CALL_CONV LMS8_Close(lms_device_t* device);
API_EXPORT int CALL_CONV LMS8_GetDeviceList(lms_info_str_t *dev_list);

API_EXPORT int CALL_CONV LMS8_ReadLMSReg(lms_device_t* device, uint32_t address, uint16_t* val);
API_EXPORT int CALL_CONV LMS8_WriteLMSReg(lms_device_t* device, uint32_t address, uint16_t val);

typedef struct
{
    char deviceName[32];            ///<The display name of the device
    char expansionName[32];         ///<The display name of the expansion card
    char firmwareVersion[16];       ///<The firmware version as a string
    char hardwareVersion[16];       ///<The hardware version as a string
    char protocolVersion[16];       ///<The protocol version as a string
    uint64_t boardSerialNumber;     ///<A unique board serial number
    char gatewareVersion[16];       ///<Gateware version as a string
    char gatewareTargetBoard[32];   ///<Which board should use this gateware
}lms_dev_info_t;

API_EXPORT const lms_dev_info_t* CALL_CONV LMS8_GetDeviceInfo(lms_device_t* device);

//milans 221130
//API_EXPORT int CALL_CONV LMS8_PLL_Tune(lms_device_t* device, double VCOFrequency_GHz, double refClock_MHz = 40.0, int FBDIV2 = 0, int INTMOD_EN = 0, int FF_MOD = 0);
//API_EXPORT int CALL_CONV LMS8_PLL_Tune(lms_device_t* device, double VCOFrequency_GHz, double refClock_MHz = 40.0);
API_EXPORT int CALL_CONV LMS8_PLL_Tune(lms_device_t* device, double VCOFrequency_GHz);

API_EXPORT int CALL_CONV LMS8_Get_SPI_Reg_bits(lms_device_t* device, const LMS8Parameter& param, uint8_t channel = 0, uint8_t PLLprofile = 0, liblms8_status* status = nullptr);

API_EXPORT int CALL_CONV LMS8_LoadConfig(lms_device_t* device, const char* filename);

API_EXPORT int CALL_CONV LMS8_PLL_Smart_Tune(lms_device_t* device, double LOFrequency_GHz, int generateIQ = 0, double loopBW_kHz = 300, double pm = 50, double bwef = 2);

API_EXPORT int CALL_CONV LMS8_Reset(lms_device_t* device);

/*
static const bool LMS_CH_TX = true;   ///<Convenience constants for TX selection
static const bool LMS_CH_RX = false;  ///<Convenience constants for RX selection

typedef char lms_name_t[16];

typedef struct
{
    float_type min;     ///<Minimum allowed value
    float_type max;     ///<Maximum allowed value
    float_type step;    ///<Minimum value step
}lms_range_t;

typedef enum
{
    LMS_TESTSIG_NONE=0,     ///<Disable test signals. Return to normal operation
    LMS_TESTSIG_NCODIV8,    ///<Test signal from NCO half scale
    LMS_TESTSIG_NCODIV4,    ///<Test signal from NCO half scale
    LMS_TESTSIG_NCODIV8F,   ///<Test signal from NCO full scale
    LMS_TESTSIG_NCODIV4F,   ///<Test signal from NCO full scale
    LMS_TESTSIG_DC          ///<DC test signal
}lms_testsig_t;

API_EXPORT int CALL_CONV LMS_Init(lms_device_t *device);

API_EXPORT int CALL_CONV LMS_GetNumChannels(lms_device_t *device, bool dir_tx);

API_EXPORT int CALL_CONV LMS_EnableChannel(lms_device_t *device, bool dir_tx,
                                           size_t chan, bool enabled);

API_EXPORT int CALL_CONV LMS_SetSampleRate(lms_device_t *device, float_type rate,
                                           size_t oversample);
API_EXPORT int CALL_CONV LMS_GetSampleRate(lms_device_t *device, bool dir_tx,
                           size_t chan, float_type *host_Hz, float_type *rf_Hz);
API_EXPORT int CALL_CONV LMS_GetSampleRateRange(lms_device_t *device, bool dir_tx,
                                                lms_range_t *range);
API_EXPORT int CALL_CONV LMS_SetLOFrequency(lms_device_t *device, bool dir_tx,
                                            size_t chan, float_type frequency);
API_EXPORT int CALL_CONV LMS_GetLOFrequency(lms_device_t *device, bool dir_tx,
                                            size_t chan, float_type *frequency);
API_EXPORT int CALL_CONV LMS_GetLOFrequencyRange(lms_device_t *device, bool dir_tx,
                                                 lms_range_t *range);
///Enumeration of RF ports
enum
{
    LMS_PATH_NONE = 0, ///<No active path (RX or TX)
    LMS_PATH_LNAH = 1, ///<RX LNA_H port
    LMS_PATH_LNAL = 2, ///<RX LNA_L port
    LMS_PATH_LNAW = 3, ///<RX LNA_W port
    LMS_PATH_TX1 = 1,  ///<TX port 1
    LMS_PATH_TX2 = 2,   ///<TX port 2
    LMS_PATH_AUTO = 255, ///<Automatically select port (if supported)
};
API_EXPORT int CALL_CONV LMS_GetAntennaList(lms_device_t *dev, bool dir_tx, 
                                            size_t chan, lms_name_t *list);
API_EXPORT int CALL_CONV LMS_SetAntenna(lms_device_t *dev, bool dir_tx,
                                        size_t chan, size_t index);
API_EXPORT int CALL_CONV LMS_GetAntenna(lms_device_t *dev, bool dir_tx,
                                        size_t chan);
API_EXPORT int CALL_CONV LMS_GetAntennaBW(lms_device_t *dev, bool dir_tx,
                                 size_t chan, size_t index, lms_range_t *range);
API_EXPORT int CALL_CONV LMS_SetNormalizedGain(lms_device_t *device, bool dir_tx,
                                               size_t chan,float_type gain);
API_EXPORT int CALL_CONV LMS_SetGaindB(lms_device_t *device, bool dir_tx,
                                        size_t chan, unsigned gain);
API_EXPORT int CALL_CONV LMS_GetNormalizedGain(lms_device_t *device, bool dir_tx,
                                                size_t chan, float_type *gain);
API_EXPORT int CALL_CONV LMS_GetGaindB(lms_device_t *device, bool dir_tx,
                                                size_t chan, unsigned *gain);
API_EXPORT int CALL_CONV LMS_SetLPFBW(lms_device_t *device, bool dir_tx,
                                             size_t chan, float_type bandwidth);
API_EXPORT int CALL_CONV LMS_GetLPFBW(lms_device_t *device, bool dir_tx,
                                            size_t chan, float_type *bandwidth);
API_EXPORT int CALL_CONV LMS_GetLPFBWRange(lms_device_t *device, bool dir_tx,
                                            lms_range_t *range);
API_EXPORT int CALL_CONV LMS_SetLPF(lms_device_t *device, bool dir_tx,
                                    size_t chan, bool enable);
API_EXPORT int CALL_CONV LMS_SetGFIRLPF(lms_device_t *device, bool dir_tx,
                               size_t chan, bool enabled, float_type bandwidth);
API_EXPORT int CALL_CONV LMS_Calibrate(lms_device_t *device, bool dir_tx,
                                        size_t chan, double bw, unsigned flags);
API_EXPORT int CALL_CONV LMS_LoadConfig(lms_device_t *device, const char *filename);

API_EXPORT int CALL_CONV LMS_SaveConfig(lms_device_t *device, const char *filename);

API_EXPORT int CALL_CONV LMS_SetTestSignal(lms_device_t *device, bool dir_tx,
                    size_t chan, lms_testsig_t sig, int16_t dc_i, int16_t dc_q);
API_EXPORT int CALL_CONV LMS_GetTestSignal(lms_device_t *device, bool dir_tx,
                                               size_t chan, lms_testsig_t *sig);
API_EXPORT int CALL_CONV LMS_GetChipTemperature(lms_device_t *dev, size_t ind,
                                                float_type *temp);
///Enumeration of LMS7 GFIRS
typedef enum
{
    LMS_GFIR1 = 0,
    LMS_GFIR2,
    LMS_GFIR3
}lms_gfir_t;

///Number of NCO frequency/phase offset values
static const int LMS_NCO_VAL_COUNT = 16;

API_EXPORT int CALL_CONV LMS_SetSampleRateDir(lms_device_t *device, bool dir_tx,
                                            float_type rate, size_t oversample);
API_EXPORT int CALL_CONV LMS_SetNCOFrequency(lms_device_t *device, bool dir_tx,
                     size_t chan, const float_type *freq, float_type pho);
API_EXPORT int CALL_CONV LMS_GetNCOFrequency(lms_device_t *device, bool dir_tx,
                          size_t chan, float_type *freq, float_type *pho);
API_EXPORT int CALL_CONV LMS_SetNCOPhase(lms_device_t *device, bool dir_tx,
                   size_t chan, const float_type *phases, float_type fcw);
API_EXPORT int CALL_CONV LMS_GetNCOPhase(lms_device_t *device, bool dir_tx,
                            size_t chan, float_type *phases, float_type *fcw);
API_EXPORT int CALL_CONV LMS_SetNCOIndex(lms_device_t *device, bool dir_tx,
                                    size_t chan, int index, bool downconv);
API_EXPORT int CALL_CONV LMS_GetNCOIndex(lms_device_t *device, bool dir_tx,
                                        size_t chan);
API_EXPORT int CALL_CONV LMS_SetGFIRCoeff(lms_device_t * device, bool dir_tx,
             size_t chan, lms_gfir_t filt, const float_type* coef,size_t count);
API_EXPORT int CALL_CONV LMS_GetGFIRCoeff(lms_device_t * device, bool dir_tx,
                                size_t chan, lms_gfir_t filt, float_type* coef);
API_EXPORT int CALL_CONV LMS_SetGFIR(lms_device_t * device, bool dir_tx,
                                    size_t chan, lms_gfir_t filt, bool enabled);
API_EXPORT int CALL_CONV LMS_EnableCache(lms_device_t *dev, bool enable);

API_EXPORT int CALL_CONV LMS_Reset(lms_device_t *device);

API_EXPORT int CALL_CONV LMS_ReadLMSReg(lms_device_t *device, uint32_t address,
                                        uint16_t *val);
API_EXPORT int CALL_CONV LMS_WriteLMSReg(lms_device_t *device, uint32_t address,
                                        uint16_t val);
API_EXPORT int CALL_CONV LMS_ReadParam(lms_device_t *device,
                                     struct LMS7Parameter param, uint16_t *val);
API_EXPORT int CALL_CONV LMS_WriteParam(lms_device_t *device,
                                      struct LMS7Parameter param, uint16_t val);
API_EXPORT int CALL_CONV LMS_ReadFPGAReg(lms_device_t *device, uint32_t address,
                                        uint16_t *val);
API_EXPORT int CALL_CONV LMS_WriteFPGAReg(lms_device_t *device, uint32_t address,
                                        uint16_t val);
///Runtime VCTCXO DAC trim value. Does not persist over power-cycle
#define BOARD_PARAM_DAC     0
///The value of board temperature sensor (if present), read-only.
#define BOARD_PARAM_TEMP    1

API_EXPORT int CALL_CONV LMS_ReadCustomBoardParam(lms_device_t *device,
                                 uint8_t id, float_type *val, lms_name_t units);
API_EXPORT int CALL_CONV LMS_WriteCustomBoardParam(lms_device_t *device,
                            uint8_t id, float_type val, const lms_name_t units);
///Chip reference clock
#define LMS_CLOCK_REF    0x0000
///RX LO clock
#define LMS_CLOCK_SXR    0x0001
///TX LO clock
#define LMS_CLOCK_SXT    0x0002
///CGEN clock
#define LMS_CLOCK_CGEN   0x0003
///RXTSP reference clock (read-only)
#define LMS_CLOCK_RXTSP  0x0004
///TXTSP reference clock (read-only)
#define LMS_CLOCK_TXTSP  0x0005

#define LMS_CLOCK_EXTREF 0x0006

API_EXPORT int CALL_CONV LMS_GetClockFreq(lms_device_t *dev, size_t clk_id,
                                         float_type *freq);
API_EXPORT int CALL_CONV LMS_SetClockFreq(lms_device_t *dev, size_t clk_id,
                                         float_type freq);
API_EXPORT int CALL_CONV LMS_VCTCXOWrite(lms_device_t * dev, uint16_t val);

API_EXPORT int CALL_CONV LMS_VCTCXORead(lms_device_t * dev, uint16_t *val);

API_EXPORT int CALL_CONV LMS_Synchronize(lms_device_t *dev, bool toChip);

API_EXPORT int CALL_CONV LMS_GPIORead(lms_device_t *dev, uint8_t* buffer, size_t len);

API_EXPORT int CALL_CONV LMS_GPIOWrite(lms_device_t *dev, const uint8_t* buffer, size_t len);

API_EXPORT int CALL_CONV LMS_GPIODirRead(lms_device_t *dev, uint8_t* buffer, size_t len);

API_EXPORT int CALL_CONV LMS_GPIODirWrite(lms_device_t *dev, const uint8_t* buffer, size_t len);

typedef struct
{
    uint64_t timestamp;
    bool waitForTimestamp;
    bool flushPartialPacket;
}lms_stream_meta_t;

///Attempt to align channel phases in MIMO mode (supported only for Rx channels)
#define LMS_ALIGN_CH_PHASE (1<<16)
typedef struct
{
    size_t handle;
    bool isTx;
    uint32_t channel;
    uint32_t fifoSize;
    float throughputVsLatency;
    enum
    {
        LMS_FMT_F32=0,    ///<32-bit floating point
        LMS_FMT_I16,      ///<16-bit integers
        LMS_FMT_I12       ///<12-bit integers stored in 16-bit variables
    }dataFmt;
    enum
    {
        LMS_LINK_FMT_DEFAULT=0, ///<12-bit integers stored in 16-bit variables 
                                /// when dataFmt=LMS_FMT_I12, 16-bit otherwise
        LMS_LINK_FMT_I16,       ///<16-bit integers
        LMS_LINK_FMT_I12        ///<12-bit integers
    }linkFmt;
}lms_stream_t;

typedef struct
{
    bool active;
    uint32_t fifoFilledCount;
    uint32_t fifoSize;
    uint32_t underrun;
    uint32_t overrun;
    uint32_t droppedPackets;
    float_type sampleRate;
    float_type linkRate;
    uint64_t timestamp;
} lms_stream_status_t;

API_EXPORT int CALL_CONV LMS_SetupStream(lms_device_t *device, lms_stream_t *stream);

API_EXPORT int CALL_CONV LMS_DestroyStream(lms_device_t *dev, lms_stream_t *stream);

API_EXPORT int CALL_CONV LMS_StartStream(lms_stream_t *stream);

API_EXPORT int CALL_CONV LMS_StopStream(lms_stream_t *stream);

API_EXPORT int CALL_CONV LMS_RecvStream(lms_stream_t *stream, void *samples,
             size_t sample_count, lms_stream_meta_t *meta, unsigned timeout_ms);
API_EXPORT int CALL_CONV LMS_GetStreamStatus(lms_stream_t *stream, lms_stream_status_t* status);

API_EXPORT int CALL_CONV LMS_SendStream(lms_stream_t *stream,
                            const void *samples,size_t sample_count,
                            const lms_stream_meta_t *meta, unsigned timeout_ms);
API_EXPORT int CALL_CONV LMS_UploadWFM(lms_device_t *device, const void **samples,
                                uint8_t chCount, size_t sample_count, int format);
API_EXPORT int CALL_CONV LMS_EnableTxWFM(lms_device_t *device, unsigned chan, bool active);

API_EXPORT int CALL_CONV LMS_GetProgramModes(lms_device_t *device, lms_name_t *list);

typedef bool (*lms_prog_callback_t)(int bsent, int btotal, const char* progressMsg);

API_EXPORT int CALL_CONV LMS_Program(lms_device_t *device, const char *data,
                size_t size, const lms_name_t mode, lms_prog_callback_t callback);
typedef struct
{
    char deviceName[32];            ///<The display name of the device
    char expansionName[32];         ///<The display name of the expansion card
    char firmwareVersion[16];       ///<The firmware version as a string
    char hardwareVersion[16];       ///<The hardware version as a string
    char protocolVersion[16];       ///<The protocol version as a string
    uint64_t boardSerialNumber;     ///<A unique board serial number
    char gatewareVersion[16];       ///<Gateware version as a string
    char gatewareTargetBoard[32];   ///<Which board should use this gateware
}lms_dev_info_t;

API_EXPORT const lms_dev_info_t* CALL_CONV LMS_GetDeviceInfo(lms_device_t *device);

API_EXPORT const char* LMS_GetLibraryVersion(void);

API_EXPORT const char * CALL_CONV LMS_GetLastErrorMessage(void);

#define LMS_LOG_CRITICAL 0
#define LMS_LOG_ERROR    1
#define LMS_LOG_WARNING  2
#define LMS_LOG_INFO     3
#define LMS_LOG_DEBUG    4

typedef void (*LMS_LogHandler)(int lvl, const char *msg);

API_EXPORT void LMS_RegisterLogHandler(LMS_LogHandler handler);
*/

#ifdef __cplusplus
} //extern "C"
#endif

#endif //LMS8_API_H
