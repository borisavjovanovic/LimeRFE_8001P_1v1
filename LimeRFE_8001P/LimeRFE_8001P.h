/**
 * @file limeLimeRFE_8001P/limeLimeRFE_8001P.h
 *
 * @brief LimeLimeRFE_8001P API functions
 *
 * Copyright (C) 2016 Lime Microsystems
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __limeLimeRFE_8001P__
#define __limeLimeRFE_8001P__

// milans 220420
// #include "LimeSuite.h"
#include "LimeSuite.h"
#include <cstdint>

#define LimeRFE_8001P_CH1 0
#define LimeRFE_8001P_CH2 1

/// LimeLimeRFE_8001P I2C address
#define LimeRFE_8001P_I2C_ADDRESS 0x51

/// LimeLimeRFE_8001P Channel IDs
/*
#define LimeRFE_8001P_CID_WB_1000 0
#define LimeRFE_8001P_CID_WB_4000 1
#define LimeRFE_8001P_CID_HAM_0030 2
#define LimeRFE_8001P_CID_HAM_0145 3
#define LimeRFE_8001P_CID_HAM_0435 4
#define LimeRFE_8001P_CID_HAM_1280 5
#define LimeRFE_8001P_CID_HAM_2400 6
#define LimeRFE_8001P_CID_HAM_3500 7
#define LimeRFE_8001P_CID_CELL_BAND01 8
#define LimeRFE_8001P_CID_CELL_BAND02 9
#define LimeRFE_8001P_CID_CELL_BAND03 10
#define LimeRFE_8001P_CID_CELL_BAND07 11
#define LimeRFE_8001P_CID_CELL_BAND38 12
#define LimeRFE_8001P_CID_COUNT 13
#define LimeRFE_8001P_CID_AUTO (-2)
*/
/*
#define LimeRFE_8001P_CID_WB_1000 1
#define LimeRFE_8001P_CID_WB_4000 2
#define LimeRFE_8001P_CID_HAM_0030 3
#define LimeRFE_8001P_CID_HAM_0070 4
#define LimeRFE_8001P_CID_HAM_0145 5
#define LimeRFE_8001P_CID_HAM_0220 6
#define LimeRFE_8001P_CID_HAM_0435 7
#define LimeRFE_8001P_CID_HAM_0920 8
#define LimeRFE_8001P_CID_HAM_1280 9
#define LimeRFE_8001P_CID_HAM_2400 10
#define LimeRFE_8001P_CID_HAM_3500 11
#define LimeRFE_8001P_CID_CELL_BAND01 12
#define LimeRFE_8001P_CID_CELL_BAND02 13
#define LimeRFE_8001P_CID_CELL_BAND03 14
#define LimeRFE_8001P_CID_CELL_BAND07 15
#define LimeRFE_8001P_CID_CELL_BAND38 16
#define LimeRFE_8001P_CID_AUTO (-2)
#define LimeRFE_8001P_CID_NOT_SELECTED 100
*/
/// LimeLimeRFE_8001P Ports
//#define LimeRFE_8001P_PORT_1 1 ///< Connector J3 - 'TX/RX'
//#define LimeRFE_8001P_PORT_2 2 ///< Connector J4 - 'TX'
//#define LimeRFE_8001P_PORT_3 3 ///< Connector J5 - '30 MHz TX/RX'

/// LimeLimeRFE_8001P convenience constants for notch on/off control
//#define LimeRFE_8001P_NOTCH_OFF 0
//#define LimeRFE_8001P_NOTCH_ON 1

/// LimeLimeRFE_8001P Modes
//#define LimeRFE_8001P_MODE_RX 0   ///< RX - Enabled; TX - Disabled
//#define LimeRFE_8001P_MODE_TX 1   ///< RX - Disabled; TX - Enabled
//#define LimeRFE_8001P_MODE_NONE 2 ///< RX - Disabled; TX - Disabled
//#define LimeRFE_8001P_MODE_TXRX 3 ///< RX - Enabled; TX - Enabled

/// LimeLimeRFE_8001P ADC constants
//#define LimeRFE_8001P_ADC1 0		///< ADC #1, this ADC value is proportional to output power in dB.
//#define LimeRFE_8001P_ADC2 1		///< ADC #2, this ADC value is proportional to reflection coefficient in dB.
//#define LimeRFE_8001P_ADC_VREF 5.0 ///< ADC referent voltage
//#define LimeRFE_8001P_ADC_BITS 10	///< ADC resolution

/// LimeLimeRFE_8001P error codes
#define LimeRFE_8001P_SUCCESS 0
#define LimeRFE_8001P_ERROR_COMM_SYNC -4 ///< Error synchronizing communication
#define LimeRFE_8001P_ERROR_GPIO_PIN -3  ///< Non-configurable GPIO pin specified. Only pins 4 and 5 are configurable.
#define LimeRFE_8001P_ERROR_CONF_FILE -2 ///< Problem with .ini configuration file
#define LimeRFE_8001P_ERROR_COMM -1	  ///< Communication error

// milans - Delete these old codes, I kept them temporarily to be able to compile
#define LimeRFE_8001P_ERROR_TX_CONN 0xF1			   ///< Wrong TX connector - not possible to route TX of the selecrted channel to the specified port
#define LimeRFE_8001P_ERROR_RX_CONN 0xF2			   ///< Wrong RX connector - not possible to route RX of the selecrted channel to the specified port
#define LimeRFE_8001P_ERROR_RXTX_SAME_CONN 0xF3	   ///< Mode TXRX not allowed - when the same port is selected for RX and TX, it is not allowed to use mode RX & TX
#define LimeRFE_8001P_ERROR_CELL_WRONG_MODE 0xF4	   ///< Wrong mode for cellular channel - Cellular FDD bands (1, 2, 3, and 7) are only allowed mode RX & TX, while TDD band 38 is allowed only RX or TX mode
#define LimeRFE_8001P_ERROR_CELL_TX_NOT_EQUAL_RX 0xF5 ///< Cellular channels must be the same both for RX and TX
#define LimeRFE_8001P_ERROR_WRONG_CHANNEL_CODE 0xF6   ///< Requested channel code is wrong

#define LimeRFE_8001P_ERROR_SC1905_RSR 1 ///< RSR problem: Either the initial value was wrong, or the timeout has occured
#define LimeRFE_8001P_ERROR_SC1905_CHK 2 ///< RSR CHKblem: Checksum value does not match the Message Reply Buffer value
#define LimeRFE_8001P_ERROR_SC1905_EEPROM_BUSY 3
#define LimeRFE_8001P_ERROR_SC1905_EEPROM_LOCKED 4
#define LimeRFE_8001P_ERROR_SC1905_EEPROM_UNLOCKED 5
// milans 220530
#define LimeRFE_8001P_ERROR_SC1905_SPECIAL_MESSAGE_UNKNOWN 0xa1	 ///< SC1905 Special Message unknown or not implemented
#define LimeRFE_8001P_ERROR_SC1905_SPECIAL_MESSAGE_WRONG_REPLY 0xa2 ///< SC1905 provided wrong reply to Special Message
#define LimeRFE_8001P_ERROR_SC1905_MAXPWRCLEARONGOING_TOO_LONG 0xa3 ///< SC1905 provided wrong reply to Special Message

#define LimeRFE_8001P_SC1905_MAXPWRCLEARONGOING_ATTEMPTS 20 ///< Max number of attempts to read the MaxPWRClearOnGOing flag until value 0x00 is returned

/// LimeLimeRFE_8001P configurable GPIO pins
#define LimeRFE_8001P_GPIO4 4
#define LimeRFE_8001P_GPIO5 5

/// LimeLimeRFE_8001P configurable GPIO pins direction
#define LimeRFE_8001P_GPIO_DIR_OUT 0 ///< Output
#define LimeRFE_8001P_GPIO_DIR_IN 1  ///< Input

/// LimeLimeRFE_8001P SWR subsystem enable
#define LimeRFE_8001P_SWR_DISABLE 0 ///< Disable
#define LimeRFE_8001P_SWR_ENABLE 1	 ///< Enable

/// LimeLimeRFE_8001P SWR subsystem source
#define LimeRFE_8001P_SWR_SRC_EXT 0  ///< External - SWR signals are supplied to the connectors J18 for forward and J17 for forward signal. To be supplied from the external coupler.
#define LimeRFE_8001P_SWR_SRC_CELL 1 ///< Cellular - Power Meter signal is provided internally from the cellular TX amplifier outputs.

#define LimeRFE_8001P_SC1905_COMMAND_CLEAR_WARNING 0
#define LimeRFE_8001P_SC1905_COMMAND_ACTIVATE_OUTPUTS 1
#define LimeRFE_8001P_SC1905_COMMAND_WRITE_MAXPWRCALPARAM_A 2
#define LimeRFE_8001P_SC1905_COMMAND_WRITE_MAXPWRCALPARAM_B 3
#define LimeRFE_8001P_SC1905_COMMAND_CLEAR_MAXPWRCALPARAM_A 4
#define LimeRFE_8001P_SC1905_COMMAND_CLEAR_MAXPWRCALPARAM_B 5
// Add additional commands if needed

#define LimeRFE_8001P_SC1905_FREQUENCY_A 0
#define LimeRFE_8001P_SC1905_FREQUENCY_B 1

/*************************************************************************************/
/*************************************************************************************/
/*************************************************************************************/

//milans 221223 - This is for board 1v1

#define CHAIN_SIZE 8 // chain bytes
#define STATE_SIZE 10 // board state bytes (chain bytes + MCU STATE byte + MISC byte)


#define SPI_2_MCU_DIR_OUT_in_BYTE   0
#define SPI_2_MCU_DIR_OUT_in_BIT    0

#define LMS8001_1_SSENn_BYTE        0
#define LMS8001_1_SSENn_BIT         1

#define LMS8001_2_SSENn_BYTE        0
#define LMS8001_2_SSENn_BIT         2

#define EXT_PLL_SSENn_BYTE          0
#define EXT_PLL_SSENn_BIT           3

#define LMS8001_1_RESETn_BYTE       0
#define LMS8001_1_RESETn_BIT        4

#define LMS8001_2_RESETn_BYTE       0
#define LMS8001_2_RESETn_BIT        5

#define SC1905_1_SSENn_BYTE         0
#define SC1905_1_SSENn_BIT          6

#define SC1905_2_SSENn_BYTE         0
#define SC1905_2_SSENn_BIT          7

//milans 221223 - This is not used on 1v1
//#define GPIO_SEL_A_LMS8001_BYTE     1
//#define GPIO_SEL_A_LMS8001_BIT      0

#define SC1905_1_RESETn_BYTE        1
#define SC1905_1_RESETn_BIT         1

#define SC1905_2_RESETn_BYTE        1
#define SC1905_2_RESETn_BIT         2


#define BYPASS_AMP1_BYTE            2
#define BYPASS_AMP1_BIT             0

#define DISABLE_AMP1_BYTE           2
#define DISABLE_AMP1_BIT            1

#define BYPASS_AMP2_BYTE            2
#define BYPASS_AMP2_BIT             2

#define DISABLE_AMP2_BYTE           2
#define DISABLE_AMP2_BIT            3

//milans 221223 - PA was renamed to DA
//#define PA1_A_EN_BYTE               3
//#define PA1_A_EN_BIT                0
#define DA1_A_EN_BYTE               3
#define DA1_A_EN_BIT                0

//#define PA1_B_EN_BYTE               3
//#define PA1_B_EN_BIT                1
#define DA1_B_EN_BYTE               3
#define DA1_B_EN_BIT                1

//#define PA2_A_EN_BYTE               3
//#define PA2_A_EN_BIT                2
#define DA2_A_EN_BYTE               3
#define DA2_A_EN_BIT                2

//#define PA2_B_EN_BYTE               3
//#define PA2_B_EN_BIT                3
#define DA2_B_EN_BYTE               3
#define DA2_B_EN_BIT                3

#define LNA1_EN_BYTE                3
#define LNA1_EN_BIT                 4

#define LNA2_EN_BYTE                3
#define LNA2_EN_BIT                 5

//milans 221223 - DA was renamed to PDA
//#define DA1_EN_BYTE                 3
//#define DA1_EN_BIT                  6
#define PDA1_EN_BYTE                 3
#define PDA1_EN_BIT                  6

//#define DA2_EN_BYTE                 3
//#define DA2_EN_BIT                  7
#define PDA2_EN_BYTE                 3
#define PDA2_EN_BIT                  7


//milans 221223 - PA was renamed to DA
//#define PA1_A_B_CTRL_BYTE           4
//#define PA1_A_B_CTRL_BIT            0
#define DA1_A_B_CTRL_BYTE           4
#define DA1_A_B_CTRL_BIT            0

//milans 221223
#define ORX1_ATT_D0_BYTE            4
#define ORX1_ATT_D0_BIT             1
#define ORX1_ATT_D1_BYTE            4
#define ORX1_ATT_D1_BIT             2
#define ORX1_ATT_D2_BYTE            4
#define ORX1_ATT_D2_BIT             3
#define ORX1_ATT_D3_BYTE            4
#define ORX1_ATT_D3_BIT             4
#define ORX1_ATT_D4_BYTE            4
#define ORX1_ATT_D4_BIT             5
#define ORX1_ATT_D5_BYTE            4
#define ORX1_ATT_D5_BIT             6
#define ORX1_ATT_D6_BYTE            4
#define ORX1_ATT_D6_BIT             7

//milans 221223 - PA was renamed to DA
//#define PA2_A_B_CTRL_BYTE           4
//#define PA2_A_B_CTRL_BIT            1
#define DA2_A_B_CTRL_BYTE           5
#define DA2_A_B_CTRL_BIT            0

#define ORX2_ATT_D0_BYTE            5
#define ORX2_ATT_D0_BIT             1
#define ORX2_ATT_D1_BYTE            5
#define ORX2_ATT_D1_BIT             2
#define ORX2_ATT_D2_BYTE            5
#define ORX2_ATT_D2_BIT             3
#define ORX2_ATT_D3_BYTE            5
#define ORX2_ATT_D3_BIT             4
#define ORX2_ATT_D4_BYTE            5
#define ORX2_ATT_D4_BIT             5
#define ORX2_ATT_D5_BYTE            5
#define ORX2_ATT_D5_BIT             6
#define ORX2_ATT_D6_BYTE            5
#define ORX2_ATT_D6_BIT             7


#define TX1_ATT_D0_BYTE             6
#define TX1_ATT_D0_BIT              1
#define TX1_ATT_D1_BYTE             6
#define TX1_ATT_D1_BIT              2
#define TX1_ATT_D2_BYTE             6
#define TX1_ATT_D2_BIT              3
#define TX1_ATT_D3_BYTE             6
#define TX1_ATT_D3_BIT              4
#define TX1_ATT_D4_BYTE             6
#define TX1_ATT_D4_BIT              5
#define TX1_ATT_D5_BYTE             6
#define TX1_ATT_D5_BIT              6
#define TX1_ATT_D6_BYTE             6
#define TX1_ATT_D6_BIT              7

#define TX2_ATT_D0_BYTE             7
#define TX2_ATT_D0_BIT              1
#define TX2_ATT_D1_BYTE             7
#define TX2_ATT_D1_BIT              2
#define TX2_ATT_D2_BYTE             7
#define TX2_ATT_D2_BIT              3
#define TX2_ATT_D3_BYTE             7
#define TX2_ATT_D3_BIT              4
#define TX2_ATT_D4_BYTE             7
#define TX2_ATT_D4_BIT              5
#define TX2_ATT_D5_BYTE             7
#define TX2_ATT_D5_BIT              6
#define TX2_ATT_D6_BYTE             7
#define TX2_ATT_D6_BIT              7

//milans 221223
/*
#define PA2_A_B_CTRL_BYTE           4
#define PA2_A_B_CTRL_BIT            1

#define PA1_CPL_D0_BYTE             4
#define PA1_CPL_D0_BIT              2

#define PA1_CPL_D1_BYTE             4
#define PA1_CPL_D1_BIT              3

#define PA1_CPL_D2_BYTE             4
#define PA1_CPL_D2_BIT              4

#define PA1_CPL_D3_BYTE             4
#define PA1_CPL_D3_BIT              5

#define PA1_CPL_D4_BYTE             4
#define PA1_CPL_D4_BIT              6

#define PA1_CPL_D5_BYTE             4
#define PA1_CPL_D5_BIT              7


#define PA1_CPL_D6_BYTE             5
#define PA1_CPL_D6_BIT              0

#define PA2_CPL_D0_BYTE             5
#define PA2_CPL_D0_BIT              1

#define PA2_CPL_D1_BYTE             5
#define PA2_CPL_D1_BIT              2

#define PA2_CPL_D2_BYTE             5
#define PA2_CPL_D2_BIT              3

#define PA2_CPL_D3_BYTE             5
#define PA2_CPL_D3_BIT              4

#define PA2_CPL_D4_BYTE             5
#define PA2_CPL_D4_BIT              5

#define PA2_CPL_D5_BYTE             5
#define PA2_CPL_D5_BIT              6

#define PA2_CPL_D6_BYTE             5
#define PA2_CPL_D6_BIT              7
*/

//milans 221223
//#define MCU_BYTE                    6
#define MCU_BYTE                    8
#define MCU_TXRX_1_BIT              0
#define MCU_TXRX_2_BIT              1

//milans 221223
//#define MISC_BYTE                   7
#define MISC_BYTE                   9
#define MISC_CHANNEL_BIT            0

//milans 221223 - This was for board 1v0
/*
#define CHAIN_SIZE 6 // chain bytes
// #define STATE_SIZE                   7  // board state bytes (chain bytes + MCU STATE byte)
#define STATE_SIZE 8 // board state bytes (chain bytes + MCU STATE byte + MISC byte)

#define SPI_2_MCU_DIR_OUT_in_BYTE 0
#define SPI_2_MCU_DIR_OUT_in_BIT 0

#define LMS8001_1_SSENn_BYTE 0
#define LMS8001_1_SSENn_BIT 1

#define LMS8001_2_SSENn_BYTE 0
#define LMS8001_2_SSENn_BIT 2

#define EXT_PLL_SSENn_BYTE 0
#define EXT_PLL_SSENn_BIT 3

#define LMS8001_1_RESETn_BYTE 0
#define LMS8001_1_RESETn_BIT 4

#define LMS8001_2_RESETn_BYTE 0
#define LMS8001_2_RESETn_BIT 5

#define SC1905_1_SSENn_BYTE 0
#define SC1905_1_SSENn_BIT 6

#define SC1905_2_SSENn_BYTE 0
#define SC1905_2_SSENn_BIT 7

#define GPIO_SEL_A_LMS8001_BYTE 1
#define GPIO_SEL_A_LMS8001_BIT 0

#define SC1905_1_RESETn_BYTE 1
#define SC1905_1_RESETn_BIT 1

#define SC1905_2_RESETn_BYTE 1
#define SC1905_2_RESETn_BIT 2

#define BYPASS_AMP1_BYTE 2
#define BYPASS_AMP1_BIT 0

#define DISABLE_AMP1_BYTE 2
#define DISABLE_AMP1_BIT 1

#define BYPASS_AMP2_BYTE 2
#define BYPASS_AMP2_BIT 2

#define DISABLE_AMP2_BYTE 2
#define DISABLE_AMP2_BIT 3

#define PA1_A_EN_BYTE 3
#define PA1_A_EN_BIT 0

#define PA1_B_EN_BYTE 3
#define PA1_B_EN_BIT 1

#define PA2_A_EN_BYTE 3
#define PA2_A_EN_BIT 2

#define PA2_B_EN_BYTE 3
#define PA2_B_EN_BIT 3

#define LNA1_EN_BYTE 3
#define LNA1_EN_BIT 4

#define LNA2_EN_BYTE 3
#define LNA2_EN_BIT 5

#define DA1_EN_BYTE 3
#define DA1_EN_BIT 6

#define DA2_EN_BYTE 3
#define DA2_EN_BIT 7

#define PA1_A_B_CTRL_BYTE 4
#define PA1_A_B_CTRL_BIT 0

#define PA2_A_B_CTRL_BYTE 4
#define PA2_A_B_CTRL_BIT 1

#define PA1_CPL_D0_BYTE 4
#define PA1_CPL_D0_BIT 2

#define PA1_CPL_D1_BYTE 4
#define PA1_CPL_D1_BIT 3

#define PA1_CPL_D2_BYTE 4
#define PA1_CPL_D2_BIT 4

#define PA1_CPL_D3_BYTE 4
#define PA1_CPL_D3_BIT 5

#define PA1_CPL_D4_BYTE 4
#define PA1_CPL_D4_BIT 6

#define PA1_CPL_D5_BYTE 4
#define PA1_CPL_D5_BIT 7

#define PA1_CPL_D6_BYTE 5
#define PA1_CPL_D6_BIT 0

#define PA2_CPL_D0_BYTE 5
#define PA2_CPL_D0_BIT 1

#define PA2_CPL_D1_BYTE 5
#define PA2_CPL_D1_BIT 2

#define PA2_CPL_D2_BYTE 5
#define PA2_CPL_D2_BIT 3

#define PA2_CPL_D3_BYTE 5
#define PA2_CPL_D3_BIT 4

#define PA2_CPL_D4_BYTE 5
#define PA2_CPL_D4_BIT 5

#define PA2_CPL_D5_BYTE 5
#define PA2_CPL_D5_BIT 6

#define PA2_CPL_D6_BYTE 5
#define PA2_CPL_D6_BIT 7

// MCU state byte

#define MCU_BYTE 6
#define MCU_TXRX_1_BIT 0
#define MCU_TXRX_2_BIT 1

// MISC byte

#define MISC_BYTE 7
#define MISC_CHANNEL_BIT 0
*/
/*************************************************************************************/
/*************************************************************************************/
/*************************************************************************************/

/// LimeLimeRFE_8001P board configuration parameters
typedef struct
{
	//	char channelIDRX;	///<RX channel ID (convenience constants defined in limeLimeRFE_8001P.h).For example constant LimeRFE_8001P_CID_HAM_0145 identifies 2m(144 - 146 MHz) HAM channel.
	//	char channelIDTX;	///<TX channel ID (convenience constants defined in limeLimeRFE_8001P.h).For example constant LimeRFE_8001P_CID_HAM_0145 identifies 2m(144 - 146 MHz) HAM channel.If - 1 then the same channel as for RX is used.
	//	char selPortRX;	///<RX port (convenience constants defined in limeLimeRFE_8001P.h).
	//	char selPortTX;	///<TX port (convenience constants defined in limeLimeRFE_8001P.h).
	//	char mode;	///<Operation mode (defined in limeLimeRFE_8001P.h). Not all modes all applicable to all congfigurations.HAM channels using same port for RX and TX are not allowed LimeRFE_8001P_MODE_TXRX mode. Cellular FDD bands 1, 2, 3, and 7 are always in LimeRFE_8001P_MODE_TXRX mode.Cellular TDD band 38 can not be in LimeRFE_8001P_MODE_TXRX.
	//	char notchOnOff;	///<Specifies whether the notch filter is applied or not (convenience constants defined in limeLimeRFE_8001P.h).
	//	char attValue;	///<Specifies the attenuation in the RX path. Attenuation [dB] = 2 * attenuation.
	//	char enableSWR;	///<Enable SWR subsystem. (convenience constants defined in limeLimeRFE_8001P.h).
	//	char sourceSWR;	///<SWR subsystem source. (convenience constants defined in limeLimeRFE_8001P.h).

	char SPI_2_MCU_DIR_OUT_in;
	char LMS8001_1_SSENn;
	char LMS8001_2_SSENn;
	char EXT_PLL_SSENn;
	char LMS8001_1_RESETn;
	char LMS8001_2_RESETn;
	char SC1905_1_SSENn;
	char SC1905_2_SSENn;
//milans 221223
//	char GPIO_SEL_A_LMS8001;
	char SC1905_1_RESETn;
	char SC1905_2_RESETn;
	char BP_AMP1;
	char SD_AMP1;
	char BP_AMP2;
	char SD_AMP2;
//milans 221223
//	char PA1_A_EN;
//	char PA1_B_EN;
//	char PA2_A_EN;
//	char PA2_B_EN;
	char DA1_A_EN;
	char DA1_B_EN;
	char DA2_A_EN;
	char DA2_B_EN;

	char LNA1_EN;
	char LNA2_EN;
//milans 221223
//	char DA1_EN;
//	char DA2_EN;
//	char PA1_A_B_CTRL;
//	char PA2_A_B_CTRL;
//	char PA1_CPL_ATT;
//	char PA2_CPL_ATT;
    char PDA1_EN;
	char PDA2_EN;
	char DA1_A_B_CTRL;
	char DA2_A_B_CTRL;
	char ORX1_ATT;
	char ORX2_ATT;

//milans 221223
	char TX1_ATT;
	char TX2_ATT;
	
	char TXRX_1;
	char TXRX_2;
	char ActiveChannel;
} limerfe_8001p_boardState;

#ifdef __cplusplus
extern "C"
{
#endif

#if defined _WIN32 || defined __CYGWIN__
#define CALL_CONV __cdecl
#ifdef __GNUC__
#define API_EXPORT __attribute__((dllexport))
#else
#define API_EXPORT __declspec(dllexport)
#endif
#elif defined _DOXYGEN_ONLY_
/** Marks an API routine to be made visible to the dynamic loader.
 *  This is OS and/or compiler-specific. */
#define API_EXPORT
/** Specifies calling convention, if necessary.
 *  This is OS and/or compiler-specific. */
#define CALL_CONV
#else
#define API_EXPORT __attribute__((visibility("default")))
#define CALL_CONV
#endif

	typedef void limerfe_8001p_dev_t;
	/****************************************************************************
	 *   LimeLimeRFE_8001P API Functions
	 *****************************************************************************/
	/**
	 * @defgroup LimeRFE_8001P_API    LimeLimeRFE_8001P API Functions
	 *
	 * @{
	 */
	/**
	 *This functions opens LimeLimeRFE_8001P device. Connection can be direct via USB or through SDR board.
	 *
	 * @param serialport  Serial port name, (e.g. COM3) for control via USB. NULL if LimeLimeRFE_8001P is controlled via SDR.
	 * @param dev         LimeSDR device obtained by invoking LMS_Open. May be NULL if direct USB connection is used.
	 *
	 * @return            Positive number on success, (-1) on failure
	 */
	API_EXPORT limerfe_8001p_dev_t *CALL_CONV LimeRFE_8001P_Open(const char *serialport, lms_device_t *dev);

	/**
	 *This function closes the device previously opened with LimeRFE_8001P_Open.
	 *
	 * @param LimeRFE_8001P         handle previously obtained from invoking LimeRFE_8001P_Open.
	 *
	 * @return            None
	 */
	API_EXPORT void CALL_CONV LimeRFE_8001P_Close(limerfe_8001p_dev_t *LimeRFE_8001P);

	/**
	 *This function gets the firmware and hardware version, as well as 2 status bytes (reserved for future use).
	 *
	 * @param LimeRFE_8001P         handle previously obtained from invoking LimeRFE_8001P_Open.
	 * @param cinfo       Board info: cinfo[0] - Firmware version; cinfo[1] - Hardware version; cinfo[2] - Status (reserved for future use); cinfo[3] - Status (reserved for future use)
	 *
	 * @return             0 on success, other on failure (see LimeLimeRFE_8001P error codes)
	 */
	API_EXPORT int CALL_CONV LimeRFE_8001P_GetInfo(limerfe_8001p_dev_t *LimeRFE_8001P, unsigned char *cinfo);

	/**
	 *This function loads LimeLimeRFE_8001P configuration from an .ini file, and configures the board accordingly.
	 *
	 * @param LimeRFE_8001P         handle previously obtained from invoking LimeRFE_8001P_Open.
	 * @param filename    Full path to .ini configuration file
	 *
	 * @return            0 on success, other on failure (see LimeLimeRFE_8001P error codes)
	 */
	API_EXPORT int CALL_CONV LimeRFE_8001P_LoadConfig(limerfe_8001p_dev_t *LimeRFE_8001P, const char *filename);
	
	// B.J.
	API_EXPORT int CALL_CONV LimeRFE_8001P_SaveConfig(limerfe_8001p_dev_t *LimeRFE_8001P, const char *filename); //, limerfe_8001p_boardState state);

	/**
	 *This function Resets the board.
	 *
	 * @param LimeRFE_8001P         handle previously obtained from invoking LimeRFE_8001P_Open.
	 *
	 * @return            0 on success, other on failure (see LimeLimeRFE_8001P error codes)
	 */
	API_EXPORT int CALL_CONV LimeRFE_8001P_Reset(limerfe_8001p_dev_t *LimeRFE_8001P);

//milans 221128
	API_EXPORT int CALL_CONV LimeRFE_8001P_LMS8_Enable(limerfe_8001p_dev_t* LimeRFE_8001P, int value);
//milans 221130
	API_EXPORT int CALL_CONV LimeRFE_8001P_Select_Channel(limerfe_8001p_dev_t* LimeRFE_8001P, int channel);
//milans 221201
	API_EXPORT int CALL_CONV LimeRFE_8001P_SetState(limerfe_8001p_dev_t* LimeRFE_8001P, limerfe_8001p_boardState state);
	API_EXPORT int CALL_CONV LimeRFE_8001P_GetState(limerfe_8001p_dev_t* LimeRFE_8001P, limerfe_8001p_boardState* state);

	/**
	 *This function configures the LimeLimeRFE_8001P board.
	 *
	 * @param LimeRFE_8001P         handle previously obtained from invoking LimeRFE_8001P_Open.
	 * @param channelIDRX   RX channel to be acitvated (convenience constants defined in limeLimeRFE_8001P.h). For example constant LimeRFE_8001P_CID_HAM_0145 identifies 2m (144 - 146 MHz) HAM channel.
	 * @param channelIDTX   TX channel to be acitvated (convenience constants defined in limeLimeRFE_8001P.h). For example constant LimeRFE_8001P_CID_HAM_0145 identifies 2m (144 - 146 MHz) HAM channel. If -1 then the same channel as for RX is used.
	 * @param portRX        RX port (convenience constants defined in limeLimeRFE_8001P.h).
	 * @param portTX        TX port (convenience constants defined in limeLimeRFE_8001P.h).
	 * @param mode          Operation mode (defined in limeLimeRFE_8001P.h). Not all modes all applicable to all congfigurations. HAM channels using same port for RX and TX are not allowed LimeRFE_8001P_MODE_TXRX mode. Cellular FDD bands 1, 2, 3, and 7 are always in LimeRFE_8001P_MODE_TXRX mode. Cellular TDD band 38 can not be in LimeRFE_8001P_MODE_TXRX.
	 * @param notch         Specifies whether the notch filter is applied or not (convenience constants defined in limeLimeRFE_8001P.h).
	 * @param attenuation   Specifies the attenuation in the RX path. Attenuation [dB] = 2 * attenuation.
	 * @param enableSWR     Enable SWR subsystem. (convenience constants defined in limeLimeRFE_8001P.h).
	 * @param sourceSWR     SWR subsystem source. (convenience constants defined in limeLimeRFE_8001P.h).
	 *
	 * @return              0 on success, other on failure (see LimeLimeRFE_8001P error codes)
	 */
	//API_EXPORT int CALL_CONV LimeRFE_8001P_Configure(limerfe_8001p_dev_t *LimeRFE_8001P, char channelIDRX, char channelIDTX, char portRX, char portTX, char mode, char notch, char attenuation, char enableSWR, char sourceSWR);

	/**
	 *This function configures the LimeLimeRFE_8001P board. It's functionality is identical to LimeRFE_8001P_Configure, with different arguments.
	 *
	 * @param LimeRFE_8001P           handle previously obtained from invoking LimeRFE_8001P_Open.
	 * @param state         Structure containing configuration parameters.
	 *
	 * @return              0 on success, other on failure (see LimeLimeRFE_8001P error codes)
	 */
	//API_EXPORT int LimeRFE_8001P_ConfigureState(limerfe_8001p_dev_t *LimeRFE_8001P, limerfe_8001p_boardState state);

	/**
	 *This function gets the state of the LimeLimeRFE_8001P board. It's functionality is identical to Cmd_GetConfig internal command
	 *
	 * @param LimeRFE_8001P           handle previously obtained from invoking LimeRFE_8001P_Open.
	 * @param state         Pointer to structure where configuration parameters are returned.
	 *
	 * @return              0 on success, other on failure (see LimeLimeRFE_8001P error codes)
	 */
	//API_EXPORT int LimeRFE_8001P_GetState(limerfe_8001p_dev_t *LimeRFE_8001P, limerfe_8001p_boardState *state);

	/**
	 *This function sets the LimeLimeRFE_8001P mode (receive, transmit, both, or none)
	 *
	 * @param LimeRFE_8001P           handle previously obtained from invoking LimeRFE_8001P_Open.
	 * @param mode          Operation mode (convenience constants defined in limeLimeRFE_8001P.h). Not all modes all applicable to all congfigurations. HAM channels using same port for RX and TX are not allowed LimeRFE_8001P_MODE_TXRX mode. Cellular FDD bands 1, 2, 3, and 7 are always in LimeRFE_8001P_MODE_TXRX mode. Cellular TDD band 38 can not be in LimeRFE_8001P_MODE_TXRX.
	 *
	 * @return              0 on success, other on failure (see LimeLimeRFE_8001P error codes)
	 */
	//API_EXPORT int CALL_CONV LimeRFE_8001P_Mode(limerfe_8001p_dev_t *LimeRFE_8001P, int mode);

	/**
	 *This function reads the value of the speficied ADC.
	 *
	 * @param LimeRFE_8001P         handle previously obtained from invoking LimeRFE_8001P_Open.
	 * @param adcID         Specifies which ADC is to be read (convenience constants defined in limeLimeRFE_8001P.h).
	 * @param value         ADC value.
	 *
	 * @return              0 on success, other on failure (see LimeLimeRFE_8001P error codes)
	 */
//	API_EXPORT int CALL_CONV LimeRFE_8001P_ReadADC(limerfe_8001p_dev_t *LimeRFE_8001P, int adcID, int *value);

	/**
	 *This function configures GPIO pin. Only pins 4 and 5 are configurable.
	 *
	 * @param LimeRFE_8001P         handle previously obtained from invoking LimeRFE_8001P_Open.
	 * @param gpioNum       GPIO pin number. Only pins 4 and 5 are configurable.
	 * @param direction     GPIO pin direction (convenience constants defined in limeLimeRFE_8001P.h). 0 - Output; 1 - Input.
	 *
	 * @return              0 on success, other on failure (see LimeLimeRFE_8001P error codes)
	 */
//	API_EXPORT int CALL_CONV LimeRFE_8001P_ConfGPIO(limerfe_8001p_dev_t *LimeRFE_8001P, int gpioNum, int direction);

	/**
	 *This function sets the GPIO pin value. GPIO pin should have been previously configured as output using LimeRFE_8001P_ConfGPIO function.
	 *
	 * @param LimeRFE_8001P           handle previously obtained from invoking LimeRFE_8001P_Open.
	 * @param gpioNum       GPIO pin number. Only pins 4 and 5 are configurable.
	 * @param val           GPIO pin value.
	 *
	 * @return              0 on success, other on failure (see LimeLimeRFE_8001P error codes)
	 */
//	API_EXPORT int CALL_CONV LimeRFE_8001P_SetGPIO(limerfe_8001p_dev_t *LimeRFE_8001P, int gpioNum, int val);

	/**
	 *This function reads the GPIO pin value. GPIO pin should have been previously configured as input using LimeRFE_8001P_ConfGPIO function.
	 *
	 * @param LimeRFE_8001P           handle previously obtained from invoking LimeRFE_8001P_Open.
	 * @param gpioNum       GPIO pin number. Only pins 4 and 5 are configurable.
	 * @param val           GPIO pin value.
	 *
	 * @return              0 on success, other on failure (see LimeLimeRFE_8001P error codes)
	 */
//	API_EXPORT int CALL_CONV LimeRFE_8001P_GetGPIO(limerfe_8001p_dev_t *LimeRFE_8001P, int gpioNum, int *val);

	/**
	 * Links LimeLimeRFE_8001P Rx and Tx to specific SDR boards channels for automatic band
	 * selection and RF switching purposes. By default channel 0 is used, so this
	 * function is only needed if different channel is going to be used.
	 *
	 * @param LimeRFE_8001P        handle previously obtained from invoking LimeRFE_8001P_Open.
	 * @param rxChan     Rx channel index
	 * @param txChan     Tx channels index
	 *
	 * @return            0 on success, other on failure (see LimeLimeRFE_8001P error codes)
	 */
//	API_EXPORT int CALL_CONV LimeRFE_8001P_AssignSDRChannels(limerfe_8001p_dev_t *LimeRFE_8001P, int rxChan, int txChan);

	/**
	 *This function enables/disables the Lime_LimeRFE_8001P fan.
	 *
	 * @param LimeRFE_8001P           handle previously obtained from invoking LimeRFE_8001P_Open.
	 * @param enable        fan state: 0 - disable; 1 - enable.
	 *
	 * @return              0 on success, other on failure (see LimeLimeRFE_8001P error codes)
	 */
//	API_EXPORT int CALL_CONV LimeRFE_8001P_Fan(limerfe_8001p_dev_t *LimeRFE_8001P, int enable);

	/**
	 *This function is TEST !!!.
	 *
	 * @param LimeRFE_8001P           handle previously obtained from invoking LimeRFE_8001P_Open.
	 * @param state         diode state: 0 - OFF; 1 - ON.
	 *
	 * @return              0 on success, other on failure (see LimeLimeRFE_8001P error codes)
	 */
//	API_EXPORT int LimeRFE_8001P_Diode(limerfe_8001p_dev_t *LimeRFE_8001P, int state);

	/**
	 *This function is TEST !!!. Control diode on through SPI.
	 *
	 * @param LimeRFE_8001P           handle previously obtained from invoking LimeRFE_8001P_Open.
	 * @param state         diode state: 0 - OFF; 1 - ON.
	 *
	 * @return              0 on success, other on failure (see LimeLimeRFE_8001P error codes)
	 */
//	API_EXPORT int LimeRFE_8001P_DiodeSPI(limerfe_8001p_dev_t *LimeRFE_8001P, int state);

	/**
	 *This function is TEST !!! Read or write the register in SC1905 using SPI
	 *
	 */
	API_EXPORT int LimeRFE_8001P_SC1905_SPI_Message_Memory(limerfe_8001p_dev_t *LimeRFE_8001P, uint16_t address, uint8_t *val, bool isRead, int bytesNo, bool isEEPROM = false);

	/**
	 *This function is TEST !!! Send special command to CS1905
	 *
	 */
	API_EXPORT int LimeRFE_8001P_SC1905_SPI_Special_Command(limerfe_8001p_dev_t *LimeRFE_8001P, int command);

	/**
	 *This function is TEST !!! Read or write the register in SC1905 using SPI
	 *
	 */
	API_EXPORT int LimeRFE_8001P_SC1905_Reset(limerfe_8001p_dev_t *LimeRFE_8001P);

	/**
	 *This function is TEST !!! Set the frequencies of SC1905
	 *
	 */
	API_EXPORT int LimeRFE_8001P_SC1905_Apply_Frequency(limerfe_8001p_dev_t *LimeRFE_8001P, int freqRange, int minFreq, int maxFreq);

	/**
	 *This function is TEST !!! Send full configuration data to LimeRFE_8001P
	 *
	 */

	API_EXPORT int LimeRFE_8001P_SC1905_Enable(limerfe_8001p_dev_t *LimeRFE_8001P, uint8_t channel, uint8_t enable);
	API_EXPORT int LimeRFE_8001P_SC1905_Set_Duty_Cycle_Feedback(limerfe_8001p_dev_t *LimeRFE_8001P, uint8_t Enabled);
	API_EXPORT int LimeRFE_8001P_SC1905_Set_Adaptation_State(limerfe_8001p_dev_t *LimeRFE_8001P, uint8_t Running);
	API_EXPORT int LimeRFE_8001P_SC1905_Set_Correction_Enable(limerfe_8001p_dev_t *LimeRFE_8001P, uint8_t Enabled);
    API_EXPORT int LimeRFE_8001P_SC1905_Read_RFIN_AGC(limerfe_8001p_dev_t *LimeRFE_8001P, int * rfinAgc);
	API_EXPORT int LimeRFE_8001P_SC1905_Read_RFFB_AGC(limerfe_8001p_dev_t *LimeRFE_8001P, int * rffbAgc);
	API_EXPORT int LimeRFE_8001P_SC1905_Read_Center_Frequency(limerfe_8001p_dev_t *LimeRFE_8001P, float * centerFreq);
	API_EXPORT int LimeRFE_8001P_SC1905_Read_Signal_Bandwidth(limerfe_8001p_dev_t *LimeRFE_8001P, float * bandwidth);
	API_EXPORT int LimeRFE_8001P_SC1905_Read_Error_Code(limerfe_8001p_dev_t *LimeRFE_8001P, char * stringValue);
	API_EXPORT int LimeRFE_8001P_SC1905_Read_Warning_Code(limerfe_8001p_dev_t *LimeRFE_8001P, char * stringValue);
	API_EXPORT int LimeRFE_8001P_SC1905_GetStatus(limerfe_8001p_dev_t *LimeRFE_8001P, char * statusString);
	API_EXPORT int LimeRFE_8001P_Set_TX_Att(limerfe_8001p_dev_t *LimeRFE_8001P, uint8_t channel, float attenuation);
	API_EXPORT int LimeRFE_8001P_Set_ORX_Att(limerfe_8001p_dev_t *LimeRFE_8001P, uint8_t channel, float attenuation);
	API_EXPORT int LimeRFE_8001P_Get_TX_Att(limerfe_8001p_dev_t *LimeRFE_8001P, uint8_t channel, float *attenuation);
	API_EXPORT int LimeRFE_8001P_Get_ORX_Att(limerfe_8001p_dev_t *LimeRFE_8001P, uint8_t channel, float *attenuation);
	


 
	API_EXPORT int LimeRFE_8001P_Set_Config_Full(limerfe_8001p_dev_t *LimeRFE_8001P, uint8_t *state, int size);

	/**
	 *This function is TEST !!! Read full configuration data from LimeRFE_8001P
	 *
	 */
	API_EXPORT int LimeRFE_8001P_Get_Config_Full(limerfe_8001p_dev_t *LimeRFE_8001P, uint8_t *state, int size);

	/**
	 *This function is TEST !!! Get the LMS8001 device, to be used with LMS8 API functions
	 *
	 */
	extern "C" API_EXPORT int LimeRFE_8001P_LMS8_Open(limerfe_8001p_dev_t * LimeRFE_8001P, lms_device_t * *device);

	/** @} (End LimeRFE_8001P_API) */

		// B.J. temprary
	API_EXPORT int LimeRFE_8001P_SPI_write(limerfe_8001p_dev_t *LimeRFE_8001P, uint16_t maddress, uint16_t address, uint16_t data);
	API_EXPORT int LimeRFE_8001P_SPI_read(limerfe_8001p_dev_t *LimeRFE_8001P, uint16_t maddress, uint16_t address, uint16_t * pData);
	API_EXPORT int LimeRFE_8001P_SPI_write_buffer(lms_device_t *lms, unsigned char *c, int size);
	API_EXPORT int LimeRFE_8001P_SPI_read_buffer(lms_device_t *lms, unsigned char *c, int size);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // __limeLimeRFE_8001P__
