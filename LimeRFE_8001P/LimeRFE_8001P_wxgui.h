#ifndef __LimeRFE_8001P_wxgui__
#define __LimeRFE_8001P_wxgui__

#include "wx/wxprec.h"

#include "LimeRFE_8001P_constants.h"
#include "LimeRFE_8001P_gui.h"

// #include "lms8001/lms8suiteAppFrame.h"
#include "lms8suiteAppFrame.h"

#include <iostream>
#include <fstream>

#include <stdio.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <vector>

#include <thread>
#include <wx/timer.h>
// B.J.
#include <atomic>
#include <memory>
#include <wx/wx.h>
enum
{
    TIMER_ID2 = 10
};
// end B.J.

#define sbi(p, n) ((p) |= (1UL << (n)))
#define cbi(p, n) ((p) &= ~(1 << (n)))

class CancelDialog : public wxDialog
{
protected:
	wxPanel *m_panel2;
	wxStaticText *sttxtMessage;
	wxButton *btnCancel;

	void OnbtnCancel(wxCommandEvent &event);

public:
	//	CancelDialog(wxWindow* parent, wxWindowID id, const wxString& title,
	//		const wxPoint& pos = wxDefaultPosition,
	//		const wxSize& size = wxDefaultSize,
	//		long style = wxDEFAULT_DIALOG_STYLE);

	CancelDialog(wxWindow *parent, wxWindowID id, const wxString &title,
				 const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize,
				 long style = wxDEFAULT_DIALOG_STYLE);

	void SetMessage(wxString strMessage);

	//	wxTextCtrl* dialogText;
	//	wxString GetText();

	~CancelDialog();

private:
	//	void OnOk(wxCommandEvent& event);

	//	DECLARE_EVENT_TABLE()
};

class LimeRFE_8001P_wxgui : public LimeRFE_8001P_view
{
protected:
	lms_device_t *lmsControl;

	void OnbtnREADSPI(wxCommandEvent &event); //B.J.
	void OnbtnWRITESPI(wxCommandEvent &event); //B.J.

	// Handlers for AppFrame events.
	void OnbtnOpenPort(wxCommandEvent &event);
	void OnbtnClosePort(wxCommandEvent &event);
	void AddMssg(const char *mssg);
	void AddMssg(const wxString &mssg);
	void ReadPorts();
	void OnbtnRefreshPorts(wxCommandEvent &event);
	void OnbtnReset(wxCommandEvent &event);
	void OnbtnOpen(wxCommandEvent &event);
	void OnbtnSave(wxCommandEvent &event);
	void State2GUI(limerfe_8001p_boardState state);
	void GUI2State(limerfe_8001p_boardState *state);
	void setTXRXBtns();
	void OnbtnBoard2GUI(wxCommandEvent &event);
	void OncTypeRX(wxCommandEvent &event);
	void OncTypeTX(wxCommandEvent &event);
	void SetChannelsChoices();
	void SetChannelsChoicesTXRX(int channelTXRX);
	void SetChannelsTypesTXRX(int channelTXRX);
	void OncChannelRX(wxCommandEvent &event);
	void OncChannelTX(wxCommandEvent &event);
	void SetConfigurationOptions();
	int GetChannelID(int channelTXRX);
	int GetChannelIndexes(int channelID, int *typeIndex, int *channelIndex);

	// B.J. commented 24.11.2022
	//int lastSelectionRX[3] = {0, 0, 0};
	//int lastSelectionTX[3] = {0, 0, 0};
	//int portRXvals[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	//int portTXvals[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int lastSelectionRX[3];
	int lastSelectionTX[3];
	int portRXvals[10];
	int portTXvals[10];

	bool SelectPort(int channelTXRX);

	int lastTypeSelectionRX = 0;
	int lastTypeSelectionTX = 0;

	int lastPortRXSelection = 0;
	int lastPortTXSelection = 0;

	void OncPortRX(wxCommandEvent &event);
	void OncPortTX(wxCommandEvent &event);

	void OntbtnTXRX(wxCommandEvent &event);
	void SetModeLabel();

	void OnbtnConfigure(wxCommandEvent &event);

	bool configured;

	limerfe_8001p_boardState configuredState;

	int activeMode;

	void UpdateLimeRFE_8001PForm();

	void OncbNotch(wxCommandEvent &event);
	void OncAttenuation(wxCommandEvent &event);

	void OncbTXasRX(wxCommandEvent &event);

	void OncbEnableSWR(wxCommandEvent &event);

	void OnbtnReadADC(wxCommandEvent &event);

	void OntbtnRXEN(wxCommandEvent &event);
	void OntbtnTXEN(wxCommandEvent &event);
	void OntbtnTXRXEN(wxCommandEvent &event);

	void OnrbI2CrbUSB(wxCommandEvent &event);

	void OnrbSWRext(wxCommandEvent &event);
	void OnrbSWRcell(wxCommandEvent &event);

	void OnbtnCalibrate(wxCommandEvent &event);

	void OnQuit(wxCommandEvent &event);

	void OnmiPowerMeter(wxCommandEvent &event);

	int CalculatePowerAndGamma(int adc1, int adc2, double *pin_dBm, double *gamma_dB);

	int GetCommType();

	limerfe_8001p_dev_t *limerfe_8001p; // Port handle

	double powerCellCalCorr;
	double powerCalCorr;
	double rlCalCorr;

	void PrintError(int errorCode);

	void FindChannelChoices(int type, wxArrayString *channelItems);

	void OnbtnClearMessages(wxCommandEvent &event);

	// milans 220429
	void OntbtnDiode(wxCommandEvent &event);
	// milans 220506
	void OntbtnDiodeSPI(wxCommandEvent &event);
	// milans 220519
	void OnbtnSC1905_Read_FW_Version(wxCommandEvent &event);
	// milans 220524
	void OnbtnSC1905_Read_Product_ID(wxCommandEvent &event);
	// milans 220524
	//		void UpdateSC1905();
	void UpdateSC1905(bool full = false);
	void UpdateSC1905Status();
	void OnbtnSC1905_Force_Update(wxCommandEvent &event);

	std::thread *timerSC1905Update = NULL;
	//		std::atomic_bool timerSC1905UpdateActive = false;
	//		std::atomic<bool> timerSC1905UpdateActive{ false };
	std::atomic<int> threadID{0};

	//		void timerSC1905UpdateThreadFunction(float interval);
	//		void timerSC1905UpdateThreadFunction(float interval, std::atomic<bool>& continue_flag);
	//		void timerSC1905UpdateThreadFunction(float interval, std::atomic<bool>& continue_flag, int id);
	void timerSC1905UpdateThreadFunction(float interval, int id, std::atomic<int> &currID);
	void timerSC1905UpdateStatusThreadFunction(float interval, int id, std::atomic<int> &currID);

	void OnbtnSC1905_Reset_RFPAL(wxCommandEvent &event);
	void OnchSC1905_Update_Rate(wxCommandEvent &event);
	void OnbtnSC1905_Apply_Frequency(wxCommandEvent &event);

	int freqRanges[6];
	int freqRangesMin[6];
	int freqRangesMax[6];
	wxString StrFreqRanges[6];

	void OnchSC1905_Frequency_Range(wxCommandEvent &event);
	void OnchSC1905_Set_Duty_Cycle_Feedback(wxCommandEvent &event);
	void OnchSC1905_Set_Adaptation_State(wxCommandEvent &event);
	void OnchSC1905_Set_Correction_Enable(wxCommandEvent &event);

	//void OnClose_LimeRFE_8001P_view(wxCommandEvent &event);
	// B.J. 24.12.2022
	void OnClose_LimeRFE_8001P_view(wxCloseEvent &event);

	void OnbtnSC1905_Clear_Warnings(wxCommandEvent &event);

	void OnKillFocustxtCtrlSC1905_RFIN_Offset(wxFocusEvent &event);
	void OnKillFocustxtCtrlSC1905_RFFB_Offset(wxFocusEvent &event);

	void OnbtnSC1905_Calibrate_RFIN_PMU(wxCommandEvent &event);
	void OnbtnSC1905_Calibrate_RFFB_PMU(wxCommandEvent &event);

	void OnbtnSC1905_Set_Cal_Param_A(wxCommandEvent &event);
	void OnbtnSC1905_Set_Cal_Param_B(wxCommandEvent &event);

	void SC1905_Set_Cal_Param(int freq);

	void OnbtnSC1905_Clear_Cal_Param(wxCommandEvent &event);

	void SC1905_Clear_Cal_Param(int freq);

	void OnchSC1905_Guard_Band(wxCommandEvent &event);

	void OnrbtnSC1905_EEPROM_Write(wxCommandEvent &event);
	void OnrbtnSC1905_EEPROM_Read(wxCommandEvent &event);
	void OnbtnSC1905_EEPROM_Execute(wxCommandEvent &event);
	void SC1905_EEPROM_Update_Form();

	// B.J. commented 24.11.2022
	// nece da se kompajlira sa true
	// std::atomic_bool userCancel; //  = true;
	std::atomic<bool> userCancel;

	void maxPwrCalOngoingThreadFunction(int freq, std::atomic<bool> &userCancel, CancelDialog *cancelDialog);

	void OnGridCellChangegridSC1905_EEPROM_Parameters(wxGridEvent &event);

	void str2bytes(wxString valueString, int selection, uint8_t *val);
	void bytes2str(uint8_t *val, int selection, long *valLong);

	void OnbtnApplyData(wxCommandEvent &event);
	void OnbtnReadData(wxCommandEvent &event);

	void setStateBit(uint8_t *state, int byte, int bit, int value);
	int getStateBit(uint8_t *state, int byte, int bit);

#define SC1905_EEPROM_PARAMETERS_ROWS 3
	wxString SC1905_EEPROM_Parameters_Grid_Cells[SC1905_EEPROM_PARAMETERS_ROWS][5];
	int sc905_EEPROM_Parameters_Grid_Variable_Types[SC1905_EEPROM_PARAMETERS_ROWS];

#define SC1905_EEPROM_VARIABLE_TYPE_UINT8 0
#define SC1905_EEPROM_VARIABLE_TYPE_INT8 1
#define SC1905_EEPROM_VARIABLE_TYPE_UINT16 2
#define SC1905_EEPROM_VARIABLE_TYPE_INT16 3

#define SC1905_EEPROM_VARIABLE_TYPES_NUMBER 4
	wxString eeprom_variable_types_strings[SC1905_EEPROM_VARIABLE_TYPES_NUMBER];
	int eeprom_variable_types_bytes[SC1905_EEPROM_VARIABLE_TYPES_NUMBER];

	void stopTimerSC1905UpdateThread();

	void OnEraseBackground_pnlChannel(wxEraseEvent &event);

	wxBitmap bmpChannel;

	// milans 220610
	LMS8SuiteAppFrame *lms8001GUI;

	void OnLMS8001Close(wxCloseEvent &event);
	void OnmiLMS8001(wxCommandEvent &event);

	void OnSimpleChanged(wxCommandEvent &event);
	void OnDetailedChange(wxCommandEvent &event);

	void Simple2Detailed();
	void Detailed2Simple();

	bool applied = false;

	// B.J.
	static const long ID_READING_FINISHED_EVENT;
	wxTimer * m_timer;
	void OnTimer(wxTimerEvent &event);
	void run();
	DECLARE_EVENT_TABLE();

public:
	/** Constructor */
	LimeRFE_8001P_wxgui(wxWindow *parent, wxWindowID id = wxID_ANY, const wxString &title = wxEmptyString, const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize, long styles = 0);
	void Initialize(lms_device_t *lms);
};

#endif // __LimeRFE_8001P_wxgui__
