#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif // WX_PRECOMP

#include "LimeRFE_8001P_wxgui.h"
#include "LimeRFE_8001P.h"
// #include "lms7suiteAppFrame.h"
#include "LimeRFE_8001P_Device.h"

#include <chrono>

#include "LimeRFE_8001P_channel_image.h"

// B.J.
const long LimeRFE_8001P_wxgui::ID_READING_FINISHED_EVENT = wxNewId();

wxBEGIN_EVENT_TABLE(LimeRFE_8001P_wxgui, wxWindow)
	EVT_TIMER(TIMER_ID2, LimeRFE_8001P_wxgui::OnTimer)
		wxEND_EVENT_TABLE()

			void LimeRFE_8001P_wxgui::OnTimer(wxTimerEvent &event)
{
	run();
}

void LimeRFE_8001P_wxgui::run()
{
	UpdateSC1905(false);
}

LimeRFE_8001P_wxgui::LimeRFE_8001P_wxgui(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos, const wxSize &size, long styles)
	: LimeRFE_8001P_view(parent, id, title, pos, size)
{
	lmsControl = nullptr;
	limerfe_8001p = nullptr;
	m_timer = new wxTimer(this, TIMER_ID2);

	// B.J. commented 24.11.2022
	for (int i = 0; i < 3; i++)
	{
		lastSelectionRX[i] = 0;
		lastSelectionTX[i] = 0;
	}
	for (int i = 0; i < 10; i++)
	{
		portRXvals[i] = 0;
		portTXvals[i] = 0;
	}
	// B.J. commented 24.11.2022
	userCancel = true;

	UpdateLimeRFE_8001PForm();

	freqRanges[0] = 4;
	freqRanges[1] = 5;
	freqRanges[2] = 6;
	freqRanges[3] = 7;
	freqRanges[4] = 8;
	freqRanges[5] = 9;

	freqRangesMin[0] = 698;
	freqRangesMin[1] = 1040;
	freqRangesMin[2] = 698;
	freqRangesMin[3] = 1800;
	freqRangesMin[4] = 2700;
	freqRangesMin[5] = 3300;

	freqRangesMax[0] = 1040;
	freqRangesMax[1] = 2080;
	freqRangesMax[2] = 2700;
	freqRangesMax[3] = 2700;
	freqRangesMax[4] = 3500;
	freqRangesMax[5] = 3800;

	//	StrFreqRanges[0] = "04 (698-1040 MHz)";
	//	StrFreqRanges[1] = "05 (1040-2080 MHz)";
	//	StrFreqRanges[2] = "06 (698-2700 MHz)";
	//	StrFreqRanges[3] = "07 (1800-2700 MHz)";
	//	StrFreqRanges[4] = "08 (2700-3500 MHz)";
	//	StrFreqRanges[5] = "09 (3300-3800 MHz)";

	wxString strTmp;
	for (int i = 0; i < 6; i++)
		StrFreqRanges[i] = strTmp.Format(wxT("%02d (%d-%d MHz)"), freqRanges[i], freqRangesMin[i], freqRangesMax[i]);

	chSC1905_Frequency_Range->Clear();
	chSC1905_Frequency_Range->Append(StrFreqRanges[0]);
	chSC1905_Frequency_Range->Append(StrFreqRanges[1]);
	chSC1905_Frequency_Range->Append(StrFreqRanges[2]);
	chSC1905_Frequency_Range->Append(StrFreqRanges[3]);
	chSC1905_Frequency_Range->Append(StrFreqRanges[4]);
	chSC1905_Frequency_Range->Append(StrFreqRanges[5]);

	chSC1905_Frequency_Range->SetSelection(3);

	txtCtrlSC1905_Set_Min_Frequency->SetValue("1950");
	txtCtrlSC1905_Set_Max_Frequency->SetValue("2050");

	//	chSC1905_Set_Correction_Enable->Disable();

	// Start the default timer thread to update Status
	wxCommandEvent tmp;
	OnchSC1905_Update_Rate(tmp);

	//	wxGridTableMessage msg(gridSC1905_EEPROM_Parameters->GetTable(), wxGRIDTABLE_NOTIFY_ROWS_APPENDED, SC1905_EEPROM_PARAMETERS_ROWS - 1);
	//	gridSC1905_EEPROM_Parameters->ProcessTableMessage(msg);

	SC1905_EEPROM_Parameters_Grid_Cells[0][0] = wxT("CONF");
	SC1905_EEPROM_Parameters_Grid_Cells[0][1] = wxT("MinFrequencyScan");
	SC1905_EEPROM_Parameters_Grid_Cells[0][2] = wxT("0xFC00");
	SC1905_EEPROM_Parameters_Grid_Cells[0][3] = wxT("");
	SC1905_EEPROM_Parameters_Grid_Cells[0][4] = wxT("");
	sc905_EEPROM_Parameters_Grid_Variable_Types[0] = SC1905_EEPROM_VARIABLE_TYPE_UINT16;

	SC1905_EEPROM_Parameters_Grid_Cells[1][0] = wxT("CONF");
	SC1905_EEPROM_Parameters_Grid_Cells[1][1] = wxT("MaxFrequencyScan");
	SC1905_EEPROM_Parameters_Grid_Cells[1][2] = wxT("0xFC02");
	SC1905_EEPROM_Parameters_Grid_Cells[1][3] = wxT("");
	SC1905_EEPROM_Parameters_Grid_Cells[1][4] = wxT("");
	sc905_EEPROM_Parameters_Grid_Variable_Types[1] = SC1905_EEPROM_VARIABLE_TYPE_UINT16;

	SC1905_EEPROM_Parameters_Grid_Cells[2][0] = wxT("MISC");
	SC1905_EEPROM_Parameters_Grid_Cells[2][1] = wxT("Enable special mode for GaN PA");
	SC1905_EEPROM_Parameters_Grid_Cells[2][2] = wxT("0xFDAC");
	SC1905_EEPROM_Parameters_Grid_Cells[2][3] = wxT("");
	SC1905_EEPROM_Parameters_Grid_Cells[2][4] = wxT("");
	sc905_EEPROM_Parameters_Grid_Variable_Types[2] = SC1905_EEPROM_VARIABLE_TYPE_UINT8;

	for (int i = 0; i < SC1905_EEPROM_PARAMETERS_ROWS; i++)
		for (int j = 0; j < 5; j++)
		{
			gridSC1905_EEPROM_Parameters->SetCellValue(i, j, SC1905_EEPROM_Parameters_Grid_Cells[i][j]);
			if (j != 3)
				gridSC1905_EEPROM_Parameters->SetReadOnly(i, j);
		}

	//	gridSC1905_EEPROM_Parameters->AutoSize();
	////	gridSC1905_EEPROM_Parameters->AutoSizeRows();
	//	gridSC1905_EEPROM_Parameters->ForceRefresh();
	////	gridSC1905_EEPROM_Parameters->EndBatch();

	//	grid->SetCellValue(0, 0, "wxGrid is good");
	//	// We can specify that some cells are read->only
	//	grid->SetCellValue(0, 3, "This is read->only");
	//	grid->SetReadOnly(0, 3);

	eeprom_variable_types_strings[SC1905_EEPROM_VARIABLE_TYPE_UINT8] = "UINT8";
	eeprom_variable_types_bytes[SC1905_EEPROM_VARIABLE_TYPE_UINT8] = 1;
	eeprom_variable_types_strings[SC1905_EEPROM_VARIABLE_TYPE_INT8] = "INT8";
	eeprom_variable_types_bytes[SC1905_EEPROM_VARIABLE_TYPE_INT8] = 1;
	eeprom_variable_types_strings[SC1905_EEPROM_VARIABLE_TYPE_UINT16] = "UINT16";
	eeprom_variable_types_bytes[SC1905_EEPROM_VARIABLE_TYPE_UINT16] = 2;
	eeprom_variable_types_strings[SC1905_EEPROM_VARIABLE_TYPE_INT16] = "INT16";
	eeprom_variable_types_bytes[SC1905_EEPROM_VARIABLE_TYPE_INT16] = 2;

	chSC1905_Variable_Type->Clear();
	for (int i = 0; i < SC1905_EEPROM_VARIABLE_TYPES_NUMBER; i++)
		chSC1905_Variable_Type->AppendString(eeprom_variable_types_strings[i]);
	chSC1905_Variable_Type->SetSelection(0);

	lms8001GUI = nullptr;

	char attString[100];

	// milans 221223
	//	cmbPA1_CPL->Clear();
	//	cmbPA2_CPL->Clear();
	//	cmbPAX_CPL->Clear();
	cmbORX1_ATT->Clear();
	cmbORX2_ATT->Clear();
	cmbORXX_ATT->Clear();
	// milans 221223
	cmbTX1_ATT->Clear();
	cmbTX2_ATT->Clear();
	cmbTXX_ATT->Clear();

	for (int i = 0; i < 128; i++)
	{
		sprintf(attString, "%.2f", i * 0.25);
		// milans 221223
		//		cmbPA1_CPL->AppendString(attString);
		//		cmbPA2_CPL->AppendString(attString);
		//		cmbPAX_CPL->AppendString(attString);
		cmbORX1_ATT->AppendString(attString);
		cmbORX2_ATT->AppendString(attString);
		cmbORXX_ATT->AppendString(attString);
		// milans 221223
		cmbTX1_ATT->AppendString(attString);
		cmbTX2_ATT->AppendString(attString);
		cmbTXX_ATT->AppendString(attString);
	}
	// milans 221223
	//	cmbPA1_CPL->SetSelection(0);
	//	cmbPA2_CPL->SetSelection(0);
	//	cmbPAX_CPL->SetSelection(0);
	cmbORX1_ATT->SetSelection(0);
	cmbORX2_ATT->SetSelection(0);
	cmbORXX_ATT->SetSelection(0);
	// milans 221223
	cmbTX1_ATT->SetSelection(0);
	cmbTX2_ATT->SetSelection(0);
	cmbTXX_ATT->SetSelection(0);

	bmpChannel = wxBITMAP_PNG_FROM_DATA(LimeRFE_8001P_channel);
}

void LimeRFE_8001P_wxgui::Initialize(lms_device_t *lms)
{
	lmsControl = lms;

	//	btnSC1905_Force_Update->Hide();

	//	timerSC1905Update = std::thread(&LimeRFE_8001P_wxgui::timerSC1905UpdateThreadFunction, this, 0);
}

void LimeRFE_8001P_wxgui::OnClose_LimeRFE_8001P_view(wxCloseEvent &event)
{
	// This is probably not working? Is it needed? How to do it?
	// Increase threadID, so that the current timing thread (which was detached) ends, and wait for 2 seconds to make sure it happens
	//	threadID++;
	//	std::this_thread::sleep_for(std::chrono::milliseconds(2000));

	// B.J. thread  commented this
	// stopTimerSC1905UpdateThread();
	m_timer->Stop();
	this->Destroy();
}

void LimeRFE_8001P_wxgui::OnbtnOpenPort(wxCommandEvent &event)
{

	//	HANDLE hCom;

	//	if (limerfe_8001p) {
	//		AddMssg("Port already opened.");
	//		return;
	//	}
	
	wxString PortName = cmbbPorts->GetValue();

	if (limerfe_8001p)
	{
		AddMssg("Port already opened.");
	}
	else
	{
		if (GetCommType() == LimeRFE_8001P_USB)
		{
			limerfe_8001p = LimeRFE_8001P_Open(PortName.mb_str(), lmsControl);
			/*
						char port[100] = "COM3";

						char port_name[20];

						sprintf(port_name, "\\\\.\\%s", port);

						hCom = CreateFileA(port_name, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);
						if (hCom == INVALID_HANDLE_VALUE)
						{
							return;
						}
						DCB dcbSerialParams = { 0 };

						dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

						if (!GetCommState(hCom, &dcbSerialParams))
						{
							printf("Unable to get the state of serial port");
							//error getting state
						}

						dcbSerialParams.BaudRate = 9600;
						dcbSerialParams.ByteSize = 8;
						dcbSerialParams.StopBits = ONESTOPBIT;
						dcbSerialParams.Parity = NOPARITY;

						dcbSerialParams.fDtrControl = DTR_CONTROL_ENABLE;

						if (!SetCommState(hCom, &dcbSerialParams))
						{
							printf("Unable to set serial port settings\n");
							//error setting serial port state
						}
						else {
							PurgeComm(hCom, PURGE_RXCLEAR | PURGE_TXCLEAR);
						}

						// DCB optional part ends here

						// COMTIMEOUTS Optional Part but very usefull especially against ReadHAngs

			//			COMMTIMEOUTS timeouts = { 1 };
			//			//previous values
			//			timeouts.ReadIntervalTimeout = 1;//=MAXDWORD;//=50;
			//			timeouts.ReadTotalTimeoutConstant = 1;//=50;
			//			timeouts.ReadTotalTimeoutMultiplier = 1;//=10;
			//			timeouts.WriteTotalTimeoutConstant = 10;//=50;
			//			timeouts.WriteTotalTimeoutMultiplier = 2;//=10;
			//
			//			if (!SetCommTimeouts(hCom, &timeouts))
			//			{
			//
			//				printf("Error setting Serial Port timeouts property\n");
			//				//error occureed. Inform user
			//			}

						LimeRFE_8001P_COM com;
						com.fd = -1;
			#ifndef __unix__
						com.hComm = hCom;
			#endif
						limerfe_8001p = new LimeRFE_8001P_Device(nullptr, com);
			*/
		}
		else		
			limerfe_8001p = LimeRFE_8001P_Open(nullptr, lmsControl);
		
		if (limerfe_8001p == nullptr)
		{
			AddMssg("Error initializing serial port");
			return;
		}
	}
	/*
		boardInfo info;
		int result = 0;
		auto* dev = static_cast<LimeRFE_8001P_Device*>(limerfe_8001p);

		unsigned char buf[LimeRFE_8001P_BUFFER_SIZE];
		int len;

		memset(buf, 0, LimeRFE_8001P_BUFFER_SIZE);

	//	strcpy(buf, "asdf");
		buf[0] = 'a';
		buf[1] = 's';
		buf[2] = 'd';
		buf[3] = 'f';
		buf[4] = '\0';
	//	int res = write_buffer(dev->sdrDevice, dev->com, buf, LimeRFE_8001P_BUFFER_SIZE);
		DWORD bytesSend, bytesRead;

		//Try to write the buffer on the Serial port
	//	bool res = WriteFile(dev->com.hComm, buf, LimeRFE_8001P_BUFFER_SIZE, &bytesSend, NULL);
	//	bool res = WriteFile(hCom, buf, LimeRFE_8001P_BUFFER_SIZE, &bytesSend, NULL);

		DWORD bytes_sent;
		COMSTAT status_;
		DWORD errors_;

	//	unsigned int data_sent_length = strlen(data_sent);

	//	bool res = WriteFile(hCom, buf, LimeRFE_8001P_BUFFER_SIZE, &bytesSend, NULL);
		bool res = WriteFile(dev->com.hComm, buf, LimeRFE_8001P_BUFFER_SIZE, &bytesSend, NULL);

		if (!res) {
	//		ClearCommError(hCom, &errors_, &status_);
			ClearCommError(dev->com.hComm, &errors_, &status_);
		}

	//	bool res = WriteFile(hComi, (void*)buffer, nbChar, &bytesSend, 0);

	//	res = ReadFile(hCom, buf, LimeRFE_8001P_BUFFER_SIZE, &bytesRead, NULL);

		Sleep(2000);

		res = ReadFile(dev->com.hComm, buf, LimeRFE_8001P_BUFFER_SIZE, &bytesRead, NULL);
		len = bytesRead;
	//	len = read_buffer(dev->sdrDevice, dev->com, buf, LimeRFE_8001P_BUFFER_SIZE);

		char msg[200];
		sprintf(msg, "Len: %d; Read: %s", len, buf);
		AddMssg(msg);
	*/

	unsigned char cinfo[4];

	int result = LimeRFE_8001P_GetInfo(limerfe_8001p, cinfo);
	if (result != LimeRFE_8001P_SUCCESS)
	{
		PrintError(result);
		return;
	}

	Limerfe_8001p_boardInfo info;

	info.fw_ver = cinfo[0];
	info.hw_ver = cinfo[1];
	info.status1 = cinfo[2];
	info.status2 = cinfo[3];

	if (((info.fw_ver == 255) && (info.hw_ver == 0xff)) ||
		((info.fw_ver == 0) && (info.hw_ver == 0x00)))
	{
		AddMssg("Error initializing serial port");
		AddMssg("Please check the connection between the SDR and LimeLimeRFE_8001P");
		LimeRFE_8001P_Close(limerfe_8001p);
		limerfe_8001p = nullptr;
		return;
	}

	AddMssg("Port opened");

	char msg[200];
	sprintf(msg, "Firmware version: %d", (int)info.fw_ver);
	AddMssg(msg);
	sprintf(msg, "Hardware version: %#x", (int)info.hw_ver);
	AddMssg(msg);

	OnbtnBoard2GUI(event);
}

void LimeRFE_8001P_wxgui::stopTimerSC1905UpdateThread()
{
	threadID++;
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}

void LimeRFE_8001P_wxgui::OnbtnClosePort(wxCommandEvent &event)
{
	// milans 220608

	// B.J. thread
	// stopTimerSC1905UpdateThread();
	m_timer->Stop();

	LimeRFE_8001P_Close(limerfe_8001p);
	limerfe_8001p = nullptr;
	AddMssg("Port closed");
	
	// B.J.
	configured = false;
	applied = false;
	
	UpdateLimeRFE_8001PForm();
}

void LimeRFE_8001P_wxgui::AddMssg(const char *mssg)
{
	wxString s(mssg, wxConvUTF8);
	AddMssg(s);
}

void LimeRFE_8001P_wxgui::AddMssg(const wxString &mssg)
{
	time_t rawtime;
	struct tm *timeinfo;
	char buffer[80];
	// add time stamp
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(buffer, 80, "%H:%M:%S", timeinfo);
	wxString line(wxString::Format("[%s] %s", buffer, mssg));

	txtMessageField->AppendText(line + _("\n"));
}

void LimeRFE_8001P_wxgui::ReadPorts()
{

	cmbbPorts->Clear();

#ifdef _MSC_VER
	TCHAR lpTargetPath[5000]; // buffer to store the path of the COMPORTS
	DWORD test;
	bool gotPort = 0; // in case the port is not found

	char portName[100];

	for (int i = 0; i < 255; i++) // checking ports from COM0 to COM255
	{
		sprintf(portName, "COM%d", i);

		test = QueryDosDeviceA((LPCSTR)portName, (LPSTR)lpTargetPath, 5000);

		// Test the return value and error if any
		if (test != 0) // QueryDosDevice returns zero if it didn't find an object
		{
			cmbbPorts->AppendString(portName);
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
	char portName[100];
	int fd;

	for (int i = 0; i < 256; ++i)
	{
		// sprintf(portName, "/dev/ttyUSB%d", i);
		//  B.J. raspberry pico serial port has different label
		sprintf(portName, "/dev/ttyACM%d", i); //
		//	    fd = open(portName, O_RDWR | O_NOCTTY | O_DELAY);
		fd = open(portName, O_RDWR | O_NOCTTY);
		if (fd != -1)
		{
			cmbbPorts->AppendString(portName);
		}
	}
#endif // LINUX

	cmbbPorts->SetSelection(0);
}

void LimeRFE_8001P_wxgui::OnbtnRefreshPorts(wxCommandEvent &event)
{
	ReadPorts();
}

void LimeRFE_8001P_wxgui::OnbtnReset(wxCommandEvent &event)
{

	int result = LimeRFE_8001P_Reset(limerfe_8001p);

	if (result != LimeRFE_8001P_SUCCESS)
	{
		PrintError(result);
		return;
	}

	OnbtnBoard2GUI(event);
}

void LimeRFE_8001P_wxgui::OnbtnOpen(wxCommandEvent &event)
{
	wxFileDialog dlg(this, _("Open config file"), "", "", "Project-File (*.ini)|*.ini", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (dlg.ShowModal() == wxID_CANCEL)
		return;

	int result = LimeRFE_8001P_LoadConfig(limerfe_8001p, dlg.GetPath().To8BitData());
	if (result != LimeRFE_8001P_SUCCESS)
	{
		PrintError(result);
		return;
	}

	OnbtnBoard2GUI(event);

	limerfe_8001p_boardState state;
	//	guiState stateGUI;
	//	ReadConfig(dlg.GetPath().To8BitData(), &state, &stateGUI);
	Limerfe_8001p_ReadConfig(dlg.GetPath().To8BitData(), &state);
	
	// B.J.
	applied = true;

	//	powerCellCalCorr = stateGUI.powerCellCorr;
	//	powerCalCorr = stateGUI.powerCorr;
	//	rlCalCorr = stateGUI.rlCorr;
}

void LimeRFE_8001P_wxgui::OnbtnSave(wxCommandEvent &event)
{
	// B.J.
	// if (!configured)
	if (!applied)
	{
		AddMssg("Error: The board has not been configured to the current settings. Please configure the board prior to saving the state.");
		return;
	}

	wxFileDialog dlg(this, _("Save config file"), "", "", "Project-File (*.ini)|*.ini", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
	if (dlg.ShowModal() == wxID_CANCEL)
		return;

	/*
		guiState stateGUI;
		configuredState.mode = activeMode;
		stateGUI.powerCellCorr = powerCellCalCorr;
		stateGUI.powerCorr = powerCalCorr;
		stateGUI.rlCorr = rlCalCorr;
	*/

	configuredState.SPI_2_MCU_DIR_OUT_in = cbSPI_2_MCU_DIR_OUT_in->GetValue();
	configuredState.LMS8001_1_SSENn = cbLMS8001_1_SSENn->GetValue();
	configuredState.LMS8001_2_SSENn = cbLMS8001_2_SSENn->GetValue();
	configuredState.EXT_PLL_SSENn = cbEXT_PLL_SSENn->GetValue();
	configuredState.LMS8001_1_RESETn = cbLMS8001_1_RESETn->GetValue();
	configuredState.LMS8001_2_RESETn = cbLMS8001_2_RESETn->GetValue();
	configuredState.SC1905_1_SSENn = cbSC1905_1_SSENn->GetValue();
	configuredState.SC1905_2_SSENn = cbSC1905_2_SSENn->GetValue();
	// milans 221223
	//	configuredState.GPIO_SEL_A_LMS8001 = cbGPIO_SEL_A_LMS8001->GetValue();
	configuredState.SC1905_1_RESETn = cbSC1905_1_RESETn->GetValue();
	configuredState.SC1905_2_RESETn = cbSC1905_2_RESETn->GetValue();
	configuredState.BP_AMP1 = cbBP_AMP1->GetValue();
	configuredState.SD_AMP1 = cbSD_AMP1->GetValue();
	configuredState.BP_AMP2 = cbBP_AMP2->GetValue();
	configuredState.SD_AMP2 = cbSD_AMP2->GetValue();
	// milans 221223
	//	configuredState.PA1_A_EN = cbPA1_A_EN->GetValue();
	//	configuredState.PA1_B_EN = cbPA1_B_EN->GetValue();
	//	configuredState.PA2_A_EN = cbPA2_A_EN->GetValue();
	//	configuredState.PA2_B_EN = cbPA2_B_EN->GetValue();
	configuredState.DA1_A_EN = cbDA1_A_EN->GetValue();
	configuredState.DA1_B_EN = cbDA1_B_EN->GetValue();
	configuredState.DA2_A_EN = cbDA2_A_EN->GetValue();
	configuredState.DA2_B_EN = cbDA2_B_EN->GetValue();

	configuredState.LNA1_EN = cbLNA1_EN->GetValue();
	configuredState.LNA2_EN = cbLNA2_EN->GetValue();
	// milans 221223
	//	configuredState.DA1_EN = cbDA1_EN->GetValue();
	//	configuredState.DA2_EN = cbDA2_EN->GetValue();
	//	configuredState.PA1_A_B_CTRL = cbPA1_A_B_CTRL->GetValue();
	//	configuredState.PA2_A_B_CTRL = cbPA2_A_B_CTRL->GetValue();
	//	configuredState.PA1_CPL_ATT = cmbPA1_CPL->GetSelection();
	//	configuredState.PA2_CPL_ATT = cmbPA2_CPL->GetSelection();
	configuredState.PDA1_EN = cbPDA1_EN->GetValue();
	configuredState.PDA2_EN = cbPDA2_EN->GetValue();
	configuredState.DA1_A_B_CTRL = cbDA1_A_B_CTRL->GetValue();
	configuredState.DA2_A_B_CTRL = cbDA2_A_B_CTRL->GetValue();
	configuredState.ORX1_ATT = cmbORX1_ATT->GetSelection();
	configuredState.ORX2_ATT = cmbORX2_ATT->GetSelection();
	configuredState.TX1_ATT = cmbTX1_ATT->GetSelection();
	configuredState.TX2_ATT = cmbTX2_ATT->GetSelection();

	configuredState.TXRX_1 = cbTXRX_1->GetValue();
	configuredState.TXRX_2 = cbTXRX_2->GetValue();

	// milans 220722
	//	int status = SaveConfig(dlg.GetPath().To8BitData(), configuredState, stateGUI);
	int status = Limerfe_8001p_WriteConfig(dlg.GetPath().To8BitData(), configuredState);
	//Limerfe_8001p_SaveConfig(dlg.GetPath().To8BitData(), configuredState);

	if (status != 0)
		wxMessageBox(_("Failed to save file"), _("Warning"));
}

void LimeRFE_8001P_wxgui::State2GUI(limerfe_8001p_boardState state)
{
}

void LimeRFE_8001P_wxgui::GUI2State(limerfe_8001p_boardState *state)
{
}

void LimeRFE_8001P_wxgui::OnbtnBoard2GUI(wxCommandEvent &event)
{
	//	State2GUI(state);
	OnbtnReadData(event);
}

void LimeRFE_8001P_wxgui::PrintError(int errorCode)
{
	switch (errorCode)
	{
	case LimeRFE_8001P_ERROR_COMM:
		AddMssg("ERROR: Communication error.");
		break;
	case LimeRFE_8001P_ERROR_TX_CONN:
		AddMssg("ERROR: Wrong TX connector.");
		break;
	case LimeRFE_8001P_ERROR_RX_CONN:
		AddMssg("Error: Wrong RX connector.");
		break;
	case LimeRFE_8001P_ERROR_RXTX_SAME_CONN:
		AddMssg("ERROR: Mode RX & TX not allowed when RX and TX are on the same port.");
		break;
	case LimeRFE_8001P_ERROR_CELL_WRONG_MODE:
		AddMssg("ERROR: Wrong mode for cellular channel.");
		break;
	case LimeRFE_8001P_ERROR_CELL_TX_NOT_EQUAL_RX:
		AddMssg("ERROR: For cellular channels RX and TX channels must be the same.");
		break;
	case LimeRFE_8001P_ERROR_WRONG_CHANNEL_CODE:
		AddMssg("ERROR: Wrong channel code.");
		break;
	case LimeRFE_8001P_ERROR_CONF_FILE:
		AddMssg("ERROR: Problem with .ini configuration file.");
		break;
	case LimeRFE_8001P_ERROR_GPIO_PIN:
		AddMssg("ERROR: Non-configurable GPIO pin specified. Only pins 4 and 5 are configurable.");
		break;
	case LimeRFE_8001P_ERROR_COMM_SYNC:
		AddMssg("ERROR: Communication synchronization error.");
		break;

	case LimeRFE_8001P_ERROR_SC1905_RSR:
		AddMssg("Error: SC1905 RSR Read Error.");
		break;

	case LimeRFE_8001P_ERROR_SC1905_CHK:
		AddMssg("Error: SC1905 CHK Read Error.");
		break;

	case LimeRFE_8001P_ERROR_SC1905_SPECIAL_MESSAGE_UNKNOWN:
		AddMssg("Error: Unknown or unimplemented SC1905 Special Message required.");
		break;

	case LimeRFE_8001P_ERROR_SC1905_SPECIAL_MESSAGE_WRONG_REPLY:
		AddMssg("Error: SC1905 provided wrong reply to Special Message sent.");
		break;

	case LimeRFE_8001P_ERROR_SC1905_EEPROM_BUSY:
		AddMssg("Error: SC1905 EEPROM Busy.");
		break;

	case LimeRFE_8001P_ERROR_SC1905_EEPROM_LOCKED:
		AddMssg("Error: SC1905 EEPROM Locked.");
		break;

	case LimeRFE_8001P_ERROR_SC1905_EEPROM_UNLOCKED:
		AddMssg("Error: SC1905 EEPROM Not Locked.");
		break;

	case LimeRFE_8001P_ERROR_SC1905_MAXPWRCLEARONGOING_TOO_LONG:
		AddMssg("Error: SC1905 Too many attempts to read the MaxPWRClearOnGOing flag until value 0x00 is returned.");
		break;

	default:
		AddMssg("Error: Unknown error.");
	}
}

void LimeRFE_8001P_wxgui::OnrbI2CrbUSB(wxCommandEvent &event)
{
	UpdateLimeRFE_8001PForm();
}

void LimeRFE_8001P_wxgui::UpdateLimeRFE_8001PForm()
{
	//	bool isI2C = (rbI2C->GetValue() == 1);
	//	cmbbPorts->Enable(!isI2C);
	//	btnRefreshPorts->Enable(!isI2C);
	//	//btnOpenPort->Enable(!isI2C);
	//	//btnClosePort->Enable(!isI2C);
	//
	//	GetSizer()->Layout();
	//	this->Fit();
}

int LimeRFE_8001P_wxgui::GetCommType()
{
	int commType;

	if (rbI2C->GetValue() == 1)
		commType = LimeRFE_8001P_I2C;
	else
		commType = LimeRFE_8001P_USB;

	return commType;
}

void LimeRFE_8001P_wxgui::OnQuit(wxCommandEvent &event)
{
	//	LMS7SuiteAppFrame* parentFrame;
	//	parentFrame = (LMS7SuiteAppFrame*)this->GetParent();
	// B.J 24.12.2022
	wxCloseEvent closeEvent;
	OnClose_LimeRFE_8001P_view(closeEvent);
}

void LimeRFE_8001P_wxgui::OnbtnClearMessages(wxCommandEvent &event)
{
	txtMessageField->Clear();
}
/*
void LimeRFE_8001P_wxgui::OntbtnDiode(wxCommandEvent& event)
{
	int state = tbtnDiode->GetValue();
	//	int state = 1;
	int result = LimeRFE_8001P_Diode(limerfe_8001p, state);
	if (result != LimeRFE_8001P_SUCCESS)
	{
		PrintError(result);
		return;
	}
}

void LimeRFE_8001P_wxgui::OntbtnDiodeSPI(wxCommandEvent &event)
{
	int state = tbtnDiodeSPI->GetValue();
	//	int state = 1;
	int result = LimeRFE_8001P_DiodeSPI(limerfe_8001p, state);
	if (result != LimeRFE_8001P_SUCCESS)
	{
		PrintError(result);
		return;
	}
}
*/
void LimeRFE_8001P_wxgui::OnbtnSC1905_Read_FW_Version(wxCommandEvent &event)
{
	uint16_t address = 0x003;
	uint8_t val = 0x00;
	// int LimeRFE_8001P_SC1905_SPI_Message_Memory(limerfe_8001p_dev_t * limerfe_8001p, uint16_t address, uint8_t * val, bool isRead, int bytesNo);
	int result = LimeRFE_8001P_SC1905_SPI_Message_Memory(limerfe_8001p, address, &val, true, 1);

	//	val = (0x69 + 0x59 + 0x00 + 0x00) % 256;
	//	val = ~val;

	char stringValue[100];
	sprintf(stringValue, "0x%02x", val);
	txtCtrlSC1905_FW_Ver->SetValue(stringValue);

	if (result != LimeRFE_8001P_SUCCESS)
	{
		PrintError(result);
		return;
	}
}

void LimeRFE_8001P_wxgui::OnbtnSC1905_Read_Product_ID(wxCommandEvent &event)
{
	uint16_t address = 0x959;
	uint8_t val[2];
	// int LimeRFE_8001P_SC1905_SPI_Message_Memory(limerfe_8001p_dev_t * limerfe_8001p, uint16_t address, uint8_t * val, bool isRead, int bytesNo);
	int result = LimeRFE_8001P_SC1905_SPI_Message_Memory(limerfe_8001p, address, val, true, 2);

	//	val = (0x69 + 0x59 + 0x00 + 0x00) % 256;
	//	val = ~val;

	char stringValue[100];
	uint16_t val16 = (val[0] << 8) | val[1];
	sprintf(stringValue, "0x%04x", val16);
	txtCtrlSC1905_Product_ID->SetValue(stringValue);

	if (result != LimeRFE_8001P_SUCCESS)
	{
		PrintError(result);
		return;
	}
}

void LimeRFE_8001P_wxgui::UpdateSC1905(bool full)
{
	uint16_t address;
	uint8_t val[2];
	int result;
	char stringValue[100];

	// Read Product Version
	address = 0x959;
	result = LimeRFE_8001P_SC1905_SPI_Message_Memory(limerfe_8001p, address, val, true, 2);

	uint16_t val16 = (val[0] << 8) | val[1];
	sprintf(stringValue, "SC%d", val16);
	txtCtrlSC1905_Product_Version->SetValue(stringValue);

	// Read FW Version
	address = 0x003;
	result = LimeRFE_8001P_SC1905_SPI_Message_Memory(limerfe_8001p, address, val, true, 1);
	uint8_t ms4b = (val[0] >> 4) & 0x0f;
	uint8_t ls4b = val[0] & 0x0f;
	address = 0x004;
	result = LimeRFE_8001P_SC1905_SPI_Message_Memory(limerfe_8001p, address, val, true, 1);
	int fwMSB = val[0];
	address = 0x00A;
	result = LimeRFE_8001P_SC1905_SPI_Message_Memory(limerfe_8001p, address, val, true, 1);
	int fwLSB = val[0];

	sprintf(stringValue, "%d.%d.%02d.%02d", ms4b, ls4b, fwMSB, fwLSB);
	txtCtrlSC1905_FW_Version->SetValue(stringValue);

	// Read Frequency Range
	address = 0x010;
	result = LimeRFE_8001P_SC1905_SPI_Message_Memory(limerfe_8001p, address, val, true, 1);
	int freqRange = val[0];

	int freqRangeIndex = -1;
	for (int i = 0; i < 6; i++)
	{
		if (freqRanges[i] == freqRange)
		{
			freqRangeIndex = i;
			break;
		}
	}

	if (freqRangeIndex != -1)
	{
		sprintf(stringValue, "%02d (%d-%d MHz)", freqRange, freqRangesMin[freqRangeIndex], freqRangesMax[freqRangeIndex]);
	}
	else
	{
		sprintf(stringValue, "%02d (Unknown)", freqRange);
	}
	txtCtrlSC1905_Frequency_Range->SetValue(stringValue);

	if ((full) && (freqRangeIndex != -1))
	{
		chSC1905_Frequency_Range->SetSelection(freqRangeIndex);
	}

	// Read Operation Mode
	// This requires reading of the EPROM address FC1B
	// EPROM manipulation requires control of the LOADENB pin
	// This pin in current version of the board cannot be controlled directly from the MCU
	// It could be controlled by using a wire to connect the LOADENB pin from the connector fot external control of the SC1905
	// to the connector with unused GPIO pins of the MCU.
	// It is not clear at this moment if the EPROM control will be needed for proper LimeRFE_8001P operation...
	address = 0xFC1B;
	//	address = 0xFC00;
	result = LimeRFE_8001P_SC1905_SPI_Message_Memory(limerfe_8001p, address, val, true, 2, true);

	uint16_t maxPWRCalParameter1A_unsigned = (val[0] << 8 | val[1]);
	int16_t maxPWRCalParameter1A = (int16_t)maxPWRCalParameter1A_unsigned;
	if (maxPWRCalParameter1A == 0)
		sprintf(stringValue, "Optimized Correction");
	else
		sprintf(stringValue, "Smooth Adaptation");
	//	sprintf(stringValue, "%d", maxPWRCalParameter1A);
	//	sprintf(stringValue, "%d", maxPWRCalParameter1A_unsigned);
	txtCtrlSC1905_Operation_Mode->SetValue(stringValue);

	// Read Min Frequency
	address = 0x011;
	result = LimeRFE_8001P_SC1905_SPI_Message_Memory(limerfe_8001p, address, val, true, 2);

	//	int minFreq = (val[0]<<8 + val[1])/2;
	uint16_t minFreq16 = (val[0] << 8 | val[1]);
	int minFreq = minFreq16 / 2;
	sprintf(stringValue, "%d", minFreq);
	txtCtrlSC1905_Min_Frequency->SetValue(stringValue);

	wxString strTmp;

	if (full)
	{
		txtCtrlSC1905_Set_Min_Frequency->SetValue(strTmp.Format("%d", minFreq));
	}

	// Read Max Frequency
	address = 0x013;
	result = LimeRFE_8001P_SC1905_SPI_Message_Memory(limerfe_8001p, address, val, true, 2);

	uint16_t maxFreq16 = (val[0] << 8 | val[1]);
	int maxFreq = maxFreq16 / 2;
	sprintf(stringValue, "%d", maxFreq);
	txtCtrlSC1905_Max_Frequency->SetValue(stringValue);

	if (full)
	{
		txtCtrlSC1905_Set_Max_Frequency->SetValue(strTmp.Format("%d", maxFreq));
	}

	// Read Duty Cycle Feedback (Adaptation Mode)
	address = 0x017;
	result = LimeRFE_8001P_SC1905_SPI_Message_Memory(limerfe_8001p, address, val, true, 1);

	int adaptationMode = val[0];

	if (adaptationMode == 0) // Adaptation Mode = 0
		sprintf(stringValue, "Off");
	else // Adaptation Mode = 1
		sprintf(stringValue, "On");

	if (adaptationMode > 1)
		adaptationMode = 1;
	else if (adaptationMode < 0)
		adaptationMode = 0;

	txtCtrlSC1905_Duty_Cycle_Feedback->SetValue(stringValue);

	if (full)
	{
		chSC1905_Set_Duty_Cycle_Feedback->SetSelection(adaptationMode);
	}

	// Read Adaptation State
	if (full)
	{
		address = 0x023;
		result = LimeRFE_8001P_SC1905_SPI_Message_Memory(limerfe_8001p, address, val, true, 1);

		int adaptState = val[0];

		// B.J. added, pokusaj da resim Segmentation fault
		// nije to u pitanju
		if (adaptState > 1)
			adaptState = 1;
		else if (adaptState < 0)
			adaptState = 0;

		chSC1905_Set_Adaptation_State->SetSelection(adaptState);
	}

	// Read Output Mode (Correction Enable)
	if (full)
	{
		address = 0x08;
		result = LimeRFE_8001P_SC1905_SPI_Message_Memory(limerfe_8001p, address, val, true, 1);

		int adaptState = val[0];
		if (adaptState > 1)
			adaptState = 1;
		else if (adaptState < 0)
			adaptState = 0;

		// chSC1905_Set_Adaptation_State->SetSelection(adaptState);
		// B.J. promenio sam ovo, mozda ovo treba, da nije greska?
		// treba da se probveri. Mislim da treba Correction enable mesto Adaptation State.F
		chSC1905_Set_Correction_Enable->SetSelection(adaptState);
	}

	// Read RFIN AGC
	address = 0x23C;
	result = LimeRFE_8001P_SC1905_SPI_Message_Memory(limerfe_8001p, address, val, true, 1);

	int rfinAgc = val[0];

	sprintf(stringValue, "%d", rfinAgc);
	txtCtrlSC1905_RFIN_AGC->SetValue(stringValue);

	// Read RFIN AGC
	address = 0x9C4;
	result = LimeRFE_8001P_SC1905_SPI_Message_Memory(limerfe_8001p, address, val, true, 1);

	int rffbAgc = val[0];

	sprintf(stringValue, "%d", rffbAgc);
	txtCtrlSC1905_RFFB_AGC->SetValue(stringValue);

	// milans 220725
	int rfinAgcMin = 0;
	int rfinAgcMax = 8;

	if (freqRange == 9)
	{ // Range 3400 - 3800 MHz
		rfinAgcMin = 7;
		rfinAgcMax = 14;
	}

	bool rfinWarningTooLow = false;
	bool rfinWarningTooHigh = false;

	//	If RFIN AGC(PDET) is higher, then RFIN is too highand needs to be lowered.
	//	If RFIN AGC(PDET) is lower, then RFIN is too lowand needs to be increased.
	float rfinAgcSliderValue = 100.0 * (((float)rfinAgc) - rfinAgcMin) / (rfinAgcMax - rfinAgcMin);
	if (rfinAgcSliderValue <= 0.0)
		rfinWarningTooLow = true;
	if (rfinAgcSliderValue > 100.0)
		rfinWarningTooHigh = true;

	rfinAgcSliderValue = (rfinAgcSliderValue > 0.0) ? rfinAgcSliderValue : 0.0;
	rfinAgcSliderValue = (rfinAgcSliderValue < 100.0) ? rfinAgcSliderValue : 100.0;

	gaugeSC1905_RFIN_AGC->SetValue(rfinAgcSliderValue);

	int rffbAgcMin = 4;
	int rffbAgcMax = 12;

	bool rffbWarningTooLow = false;
	bool rffbWarningTooHigh = false;

	//	If RFFB AGC is higher, then the RFFB is too low and needs to be increased.
	//	If RFFB AGC is lower, then the RFFB is too high and needs to be lowered.
	float rffbAgcSliderValue = 100.0 * (((float)rffbAgcMax) - rffbAgc) / (rffbAgcMax - rffbAgcMin);

	if (rffbAgcSliderValue < 0.0)
		rffbWarningTooLow = true;
	if (rffbAgcSliderValue > 100.0)
		rffbWarningTooHigh = true;

	rffbAgcSliderValue = (rffbAgcSliderValue > 0.0) ? rffbAgcSliderValue : 0.0;
	rffbAgcSliderValue = (rffbAgcSliderValue < 100.0) ? rffbAgcSliderValue : 100.0;

	gaugeSC1905_RFFB_AGC->SetValue(rffbAgcSliderValue);

	//******************
	// Status
	//******************

	// Read Overall Status
	UpdateSC1905Status();

	// Read Center Frequency
	address = 0x01A;
	result = LimeRFE_8001P_SC1905_SPI_Message_Memory(limerfe_8001p, address, val, true, 2);

	float centerFreq = (val[0] * 100 + val[1]) / 2;
	sprintf(stringValue, "%.1f", centerFreq);
	txtCtrlSC1905_Center_Frequency->SetValue(stringValue);

	// Read Signal Bandwidth (24dBc BW)
	address = 0x018;
	result = LimeRFE_8001P_SC1905_SPI_Message_Memory(limerfe_8001p, address, val, true, 2);

	float bandwidth = (val[0] * 100 + val[1]) / 2;
	sprintf(stringValue, "%.1f", bandwidth);
	txtCtrlSC1905_24dBc_BW->SetValue(stringValue);

	// Read Error Code & Generate Error Message
	address = 0x006;
	result = LimeRFE_8001P_SC1905_SPI_Message_Memory(limerfe_8001p, address, val, true, 2);

	int errorCode = val[0];
	sprintf(stringValue, "%d", errorCode);
	txtCtrlSC1905_Error_Code->SetValue(stringValue);

	switch (errorCode)
	{
	case 0:
		sprintf(stringValue, "No Error");
		break;
	case 3:
		sprintf(stringValue, "EEPROM Corrupted");
		break;
	case 5:
		sprintf(stringValue, "Center Frequency outside the Defined Frequencvy Range");
		break;
	case 13:
		sprintf(stringValue, "Wrong CLK Setting");
		break;
	default:
		sprintf(stringValue, "Internal Chip Error");
	}

	txtCtrlSC1905_Error_Message->SetValue(stringValue);

	// Read Warning Code & Generate Warning Message
	address = 0x007;
	result = LimeRFE_8001P_SC1905_SPI_Message_Memory(limerfe_8001p, address, val, true, 2);

	int warningCode = val[0];
	sprintf(stringValue, "%d", warningCode);
	txtCtrlSC1905_Warning_Code->SetValue(stringValue);

	switch (warningCode)
	{
	case 0:
		sprintf(stringValue, "No Warning");
		break;
	case 44:
	case 48:
		sprintf(stringValue, "Center Frequency Too Low");
		break;
	case 62:
		sprintf(stringValue, "IC Temperature Outside Allowed Range");
		break;
	default:
		sprintf(stringValue, "Internal Warning");
	}

	txtCtrlSC1905_Warning_Message->SetValue(stringValue);

	// Read RFIN & RFFB PMU
	address = 0x247;
	result = LimeRFE_8001P_SC1905_SPI_Message_Memory(limerfe_8001p, address, val, true, 2);

	uint16_t rfin_code_unsigned = (val[1] << 8) | val[0];
	int16_t rfin_code = (int16_t)rfin_code_unsigned;
	double frin_dBm = (rfin_code * 3.01) / 1024.0;

	sprintf(stringValue, "%.2f", frin_dBm);
	txtCtrlSC1905_RFIN_PMU->SetValue(stringValue);

	address = 0xFC19;
	result = LimeRFE_8001P_SC1905_SPI_Message_Memory(limerfe_8001p, address, val, true, 2, true);

	//	uint16_t rfin_offset_code_unsigned = (val[0] << 8 | val[1]);
	uint16_t rfin_offset_code_unsigned = (val[1] << 8 | val[0]);
	int16_t rfin_offset_code = (int16_t)rfin_offset_code_unsigned;
	float rfinOffset = (rfin_offset_code * 3.01) / 1024.0;
	sprintf(stringValue, "%.2f", rfinOffset);
	txtCtrlSC1905_RFIN_Offset->SetValue(stringValue);

	float rfin_power = frin_dBm + rfinOffset;
	sprintf(stringValue, "%.2f", rfin_power);
	txtCtrlSC1905_RFIN_Power->SetValue(stringValue);

	address = 0x245;
	result = LimeRFE_8001P_SC1905_SPI_Message_Memory(limerfe_8001p, address, val, true, 2);

	uint16_t rffb_code_unsigned = (val[1] << 8) | val[0];
	int16_t rffb_code = (int16_t)rffb_code_unsigned;
	double rffb_dBm = (rffb_code * 3.01) / 1024.0;

	sprintf(stringValue, "%.2f", rffb_dBm);
	txtCtrlSC1905_RFFB_PMU->SetValue(stringValue);

	address = 0xFC17;
	result = LimeRFE_8001P_SC1905_SPI_Message_Memory(limerfe_8001p, address, val, true, 2, true);

	//	uint16_t rffb_offset_code_unsigned = (val[0] << 8 | val[1]);
	uint16_t rffb_offset_code_unsigned = (val[1] << 8 | val[0]);
	int16_t rffb_offset_code = (int16_t)rffb_offset_code_unsigned;
	float rffbOffset = (rffb_offset_code * 3.01) / 1024.0;
	sprintf(stringValue, "%.2f", rffbOffset);
	txtCtrlSC1905_RFFB_Offset->SetValue(stringValue);

	float rffb_power = rffb_dBm + rffbOffset;
	sprintf(stringValue, "%.2f", rffb_power);
	txtCtrlSC1905_RFFB_Power->SetValue(stringValue);

	address = 0xfc62;
	result = LimeRFE_8001P_SC1905_SPI_Message_Memory(limerfe_8001p, address, val, true, 1, true);

	int selection = val[0];
	chSC1905_Guard_Band->SetSelection(selection);

	// Fill ther values in the SC1905 EEPROM Parameters grid
	for (int i = 0; i < SC1905_EEPROM_PARAMETERS_ROWS; i++)
	{
		uint16_t address;
		wxString addressString = SC1905_EEPROM_Parameters_Grid_Cells[i][2];
		long addressLong;
		if (!addressString.ToLong(&addressLong, 16))
		{
			AddMssg("Invalid EEPROM address value");
			return;
		}
		address = (uint16_t)addressLong;

		int bytesNo = 1;

		int selection = sc905_EEPROM_Parameters_Grid_Variable_Types[i];

		bytesNo = eeprom_variable_types_bytes[selection];
		result = LimeRFE_8001P_SC1905_SPI_Message_Memory(limerfe_8001p, address, val, true, bytesNo, true);

		wxString valueString;
		long valueRead = 0;

		bytes2str(val, selection, &valueRead);

		gridSC1905_EEPROM_Parameters->SetCellValue(i, 3, wxString::Format(wxT("%ld"), valueRead));
	}

	if (result != LimeRFE_8001P_SUCCESS)
	{
		PrintError(result);
		return;
	}
}

void LimeRFE_8001P_wxgui::OnbtnSC1905_Force_Update(wxCommandEvent &event)
{
	UpdateSC1905(true);
}

void LimeRFE_8001P_wxgui::OnbtnSC1905_Reset_RFPAL(wxCommandEvent &event)
{
	int result = LimeRFE_8001P_SC1905_Reset(limerfe_8001p);

	if (result != LimeRFE_8001P_SUCCESS)
	{
		PrintError(result);
		return;
	}
}

// not executing now, we created threads instead
void LimeRFE_8001P_wxgui::timerSC1905UpdateThreadFunction(float interval, int id, std::atomic<int> &currID)
{
	int millis = interval * 10000; // B.J. promenio
	char mssg[100];
	//	bool doLoop = true;
	//	while (doLoop) {
	//	while(timerSC1905UpdateActive){
	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(millis));

		sprintf(mssg, "Hello from Thread ID = %d", id);

		//. B.J.
		// aplikacija puca
		// desava se : pango_shape_full: assertion 'paragraph_text + paragraph_length >= item_text + item_length' failed
		// Segmentation fault
		// kao da je duzina teksta koji treba da se smesti u polje veca od predvidjene duzine

		// kontrole na dijalogu ne smeju da se updejtuju u threadu
		// u thread-u treba da se obavi citanje a tek onda, van thread-a, da se te informacije updejtuju u dijalog

		UpdateSC1905(false);
		//		AddMssg(mssg);
		//		if (!continue_flag) {
		if (id != currID)
		{
			sprintf(mssg, "Info: Exiting Thread ID = %d", id);
			// B.J.
			AddMssg(mssg);
			return;
		}
		//			break;
		//		int sel = this->chSC1905_Update_Rate->GetSelection();
		//		if (sel == 0)
		//			doLoop = false;
	}
}

void LimeRFE_8001P_wxgui::timerSC1905UpdateStatusThreadFunction(float interval, int id, std::atomic<int> &currID)
{
	int millis = interval * 1000;
	char mssg[100];
	//	bool doLoop = true;
	//	while (doLoop) {
	//	while(timerSC1905UpdateActive){
	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(millis));

		sprintf(mssg, "Hello from update Status thread ID = %d", id);
		UpdateSC1905Status();
		//		AddMssg(mssg);
		//		if (!continue_flag) {
		if (id != currID)
		{
			sprintf(mssg, "Info: Exiting Thread ID = %d", id);
			// B.J.
			AddMssg(mssg);
			return;
		}
		//			break;
		//		int sel = this->chSC1905_Update_Rate->GetSelection();
		//		if (sel == 0)
		//			doLoop = false;
	}
}

// ovdi!!!
void LimeRFE_8001P_wxgui::UpdateSC1905Status()
{
	uint16_t address;
	uint8_t val[2];
	int result;

	address = 0x005;
	result = LimeRFE_8001P_SC1905_SPI_Message_Memory(limerfe_8001p, address, val, true, 1);
	int status = val[0];

	char statusString[100];

	switch (status)
	{
	case 0:
		sprintf(statusString, "INIT");
		break;
	case 1:
		sprintf(statusString, "FSA");
		break;
	case 3:
		sprintf(statusString, "TRACK");
		break;
	case 6:
		sprintf(statusString, "CAL");
		break;
	case 9:
		sprintf(statusString, "PDET");
		break;
	default:
		sprintf(statusString, "Unknown");
	}

	// Bit #7 - Error
	// Bit #6 - Warning

	txtCtrlSC1905_Overall_Status->SetValue(statusString);
}

void LimeRFE_8001P_wxgui::OnchSC1905_Update_Rate(wxCommandEvent &event)
{
	//	if (timerSC1905Update != NULL)

	//	timerSC1905UpdateActive = false;

	//	std::this_thread::sleep_for(std::chrono::milliseconds(2000));

	//	try {
	//		timerSC1905Update.join();
	//	}
	//	catch (...) {}

	//	if (timerSC1905Update != NULL) {
	//		if (timerSC1905Update->joinable()) {
	//			timerSC1905Update->join();
	//			delete timerSC1905Update;
	//		}
	//	}

	int choice = chSC1905_Update_Rate->GetSelection();

	threadID++;

	float interval = 0.0;

	if (choice != 0)
	{

		btnSC1905_Force_Update->Hide();

		switch (choice)
		{
		case 1:
			interval = 0.5;
			break;
		case 2:
			interval = 1.0;
			break;
		}

		//		timerSC1905UpdateActive = true;

		// B.J. threads
		// timerSC1905Update = new std::thread(&LimeRFE_8001P_wxgui::timerSC1905UpdateThreadFunction, this, interval, (int)threadID, std::ref(threadID));
		// timerSC1905Update->detach();
		m_timer->Start((int)(10000.0 * interval));
		// std::thread tmp(&LimeRFE_8001P_wxgui::timerSC1905UpdateThreadFunction, interval);
	}
	else
	{
		// B.J. threads
		m_timer->Stop();

		// milans 220616
		//  Uncomment this, when the SC1905 is connected
		//  I commented it for the development, without the SC1905 connected
		//		interval = 1;
		//		timerSC1905Update = new std::thread(&LimeRFE_8001P_wxgui::timerSC1905UpdateStatusThreadFunction, this, interval, (int)threadID, std::ref(threadID));
		//		timerSC1905Update->detach();
		btnSC1905_Force_Update->Show();
	}
}

void LimeRFE_8001P_wxgui::OnbtnSC1905_Apply_Frequency(wxCommandEvent &event)
{

	int result = LimeRFE_8001P_SUCCESS;

	wxString StrMinFreq = txtCtrlSC1905_Set_Min_Frequency->GetValue();
	long minFreq = 0;
	if (!StrMinFreq.ToLong(&minFreq))
	{
		AddMssg("Error: Entered value for Min Frequency is not an integer number.");
		return;
	}
	wxString StrMaxFreq = txtCtrlSC1905_Set_Max_Frequency->GetValue();
	long maxFreq = 0;
	if (!StrMaxFreq.ToLong(&maxFreq))
	{
		AddMssg("Error: Entered value for Max Frequency is not an integer number.");
		return;
	}
	int freqRangeIndex = chSC1905_Frequency_Range->GetSelection();
	int freqRange = freqRanges[freqRangeIndex];
	result = LimeRFE_8001P_SC1905_Apply_Frequency(limerfe_8001p, freqRange, (int)minFreq, (int)maxFreq);

	if (result != LimeRFE_8001P_SUCCESS)
	{
		PrintError(result);
		return;
	}
}

void LimeRFE_8001P_wxgui::OnchSC1905_Frequency_Range(wxCommandEvent &event)
{
	int freqRangeIndex = chSC1905_Frequency_Range->GetSelection();
	wxString strTmp;
	txtCtrlSC1905_Set_Min_Frequency->SetValue(strTmp.Format("%d", freqRangesMin[freqRangeIndex]));
	txtCtrlSC1905_Set_Max_Frequency->SetValue(strTmp.Format("%d", freqRangesMax[freqRangeIndex]));
}

void LimeRFE_8001P_wxgui::OnchSC1905_Set_Duty_Cycle_Feedback(wxCommandEvent &event)
{
	int result = LimeRFE_8001P_SUCCESS;
	uint16_t address;
	uint8_t val[2] = {0x00, 0x00};
	val[0] = chSC1905_Set_Duty_Cycle_Feedback->GetSelection();
	address = 0x017;
	result = LimeRFE_8001P_SC1905_SPI_Message_Memory(limerfe_8001p, address, val, false, 1);
}

void LimeRFE_8001P_wxgui::OnchSC1905_Set_Adaptation_State(wxCommandEvent &event)
{
	int result = LimeRFE_8001P_SUCCESS;
	uint16_t address;
	uint8_t val[2] = {0x00, 0x00};
	val[0] = chSC1905_Set_Adaptation_State->GetSelection();
	address = 0x023;
	result = LimeRFE_8001P_SC1905_SPI_Message_Memory(limerfe_8001p, address, val, false, 1);
}

void LimeRFE_8001P_wxgui::OnchSC1905_Set_Correction_Enable(wxCommandEvent &event)
{
	int result = LimeRFE_8001P_SUCCESS;
	uint16_t address;
	uint8_t val[2] = {0x00, 0x00};
	val[0] = chSC1905_Set_Correction_Enable->GetSelection();
	address = 0x008;
	result = LimeRFE_8001P_SC1905_SPI_Message_Memory(limerfe_8001p, address, val, false, 1);

	// SC1905 SPI PRogramming Guide, page 17
	// "After changing Output Mode, send the "Activate Outputs" messages toi be effective. See Table 2."
	result = LimeRFE_8001P_SC1905_SPI_Special_Command(limerfe_8001p, LimeRFE_8001P_SC1905_COMMAND_ACTIVATE_OUTPUTS);
	if (result != LimeRFE_8001P_SUCCESS)
	{
		PrintError(result);
		return;
	}
}

void LimeRFE_8001P_wxgui::OnbtnSC1905_Clear_Warnings(wxCommandEvent &event)
{
	int result = LimeRFE_8001P_SUCCESS;
	result = LimeRFE_8001P_SC1905_SPI_Special_Command(limerfe_8001p, LimeRFE_8001P_SC1905_COMMAND_CLEAR_WARNING);
	if (result != LimeRFE_8001P_SUCCESS)
	{
		PrintError(result);
		return;
	}
}

void LimeRFE_8001P_wxgui::OnKillFocustxtCtrlSC1905_RFIN_Offset(wxFocusEvent &event)
{
	event.Skip();
	int dialog_return_value = wxID_NO; // initialize to a sane default value
	wxMessageDialog *dial = new wxMessageDialog(NULL, _("Do you want to apply changes made to RFIN offset?"), _("Quit"), wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);
	dialog_return_value = dial->ShowModal();
	if (dialog_return_value == wxID_YES)
	{
		uint16_t address;
		uint8_t val[2] = {0x00, 0x00};
		wxString rfinOffsetString = txtCtrlSC1905_RFIN_Offset->GetValue();
		double rfinOffsetFloat;
		if (!rfinOffsetString.ToDouble(&rfinOffsetFloat))
		{
			AddMssg("Invalid offset value");
			return;
		}
		int16_t rfinOffsetCode = (int16_t)((rfinOffsetFloat * 1024.0) / 3.01);
		val[1] = (rfinOffsetCode >> 8) & 0xff;
		val[0] = rfinOffsetCode & 0xff;
		address = 0xfc19;
		int result = LimeRFE_8001P_SC1905_SPI_Message_Memory(limerfe_8001p, address, val, false, 2, true);
		if (result != LimeRFE_8001P_SUCCESS)
		{
			PrintError(result);
			return;
		}
	}
}

void LimeRFE_8001P_wxgui::OnKillFocustxtCtrlSC1905_RFFB_Offset(wxFocusEvent &event)
{
	event.Skip();
	int dialog_return_value = wxID_NO; // initialize to a sane default value
	wxMessageDialog *dial = new wxMessageDialog(NULL, _("Do you want to apply changes made to RFFB offset?"), _("Quit"), wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);
	dialog_return_value = dial->ShowModal();
	if (dialog_return_value == wxID_YES)
	{
		uint16_t address;
		uint8_t val[2] = {0x00, 0x00};
		wxString rffbOffsetString = txtCtrlSC1905_RFFB_Offset->GetValue();
		double rffbOffsetFloat;
		if (!rffbOffsetString.ToDouble(&rffbOffsetFloat))
		{
			AddMssg("Invalid offset value");
			return;
		}
		int16_t rffbOffsetCode = (int16_t)((rffbOffsetFloat * 1024.0) / 3.01);
		val[1] = (rffbOffsetCode >> 8) & 0xff;
		val[0] = rffbOffsetCode & 0xff;
		address = 0xfc17;
		int result = LimeRFE_8001P_SC1905_SPI_Message_Memory(limerfe_8001p, address, val, false, 2, true);
		if (result != LimeRFE_8001P_SUCCESS)
		{
			PrintError(result);
			return;
		}
	}
}

void LimeRFE_8001P_wxgui::OnbtnSC1905_Calibrate_RFIN_PMU(wxCommandEvent &event)
{
	uint16_t address;
	uint8_t val[2] = {0x00, 0x00};
	wxString rfinCalibrateString = txtCtrlSC1905_Calibrate_RFIN_PMU->GetValue();
	double rfinCalibrateFloat;
	if (!rfinCalibrateString.ToDouble(&rfinCalibrateFloat))
	{
		AddMssg("Invalid calibrated value entered.");
		return;
	}
	wxString rfinPMUString = txtCtrlSC1905_RFIN_PMU->GetValue();
	double rfinPMUFloat;
	if (!rfinPMUString.ToDouble(&rfinPMUFloat))
	{
		AddMssg("Invalid RFIN PMU value");
		return;
	}
	double rfinOffsetFloat = rfinCalibrateFloat - rfinPMUFloat;
	int16_t rfinOffsetCode = (int16_t)((rfinOffsetFloat * 1024.0) / 3.01);
	val[1] = (rfinOffsetCode >> 8) & 0xff;
	val[0] = rfinOffsetCode & 0xff;
	address = 0xfc19;
	int result = LimeRFE_8001P_SC1905_SPI_Message_Memory(limerfe_8001p, address, val, false, 2, true);
	if (result != LimeRFE_8001P_SUCCESS)
	{
		PrintError(result);
		return;
	}
}

void LimeRFE_8001P_wxgui::OnbtnSC1905_Calibrate_RFFB_PMU(wxCommandEvent &event)
{
	uint16_t address;
	uint8_t val[2] = {0x00, 0x00};
	wxString rffbCalibrateString = txtCtrlSC1905_Calibrate_RFFB_PMU->GetValue();
	double rffbCalibrateFloat;
	if (!rffbCalibrateString.ToDouble(&rffbCalibrateFloat))
	{
		AddMssg("Invalid calibrated value entered.");
		return;
	}
	wxString rffbPMUString = txtCtrlSC1905_RFFB_PMU->GetValue();
	double rffbPMUFloat;
	if (!rffbPMUString.ToDouble(&rffbPMUFloat))
	{
		AddMssg("Invalid RFFB PMU value");
		return;
	}
	double rffbOffsetFloat = rffbCalibrateFloat - rffbPMUFloat;
	int16_t rffbOffsetCode = (int16_t)((rffbOffsetFloat * 1024.0) / 3.01);
	val[1] = (rffbOffsetCode >> 8) & 0xff;
	val[0] = rffbOffsetCode & 0xff;
	address = 0xfc17;
	int result = LimeRFE_8001P_SC1905_SPI_Message_Memory(limerfe_8001p, address, val, false, 2, true);
	if (result != LimeRFE_8001P_SUCCESS)
	{
		PrintError(result);
		return;
	}
}

void CancelDialog::SetMessage(wxString strMessage)
{
	sttxtMessage->SetLabel(strMessage);
	this->Fit();
}

void CancelDialog::OnbtnCancel(wxCommandEvent &event)
{
	event.Skip();
	this->EndModal(-1);
}

CancelDialog::CancelDialog(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize &size, long style) : wxDialog(parent, id, title, position, size, style)
{
	/*
		wxString dimensions = "", s;
		wxPoint p;
		wxSize  sz;

		sz.SetWidth(size.GetWidth() - 20);
		sz.SetHeight(size.GetHeight() - 70);

		p.x = 6; p.y = 2;
		s.Printf(_(" x = %d y = %d\n"), p.x, p.y);
		dimensions.append(s);
		s.Printf(_(" width = %d height = %d\n"), sz.GetWidth(), sz.GetHeight());
		dimensions.append(s);
	//	dimensions.append(AUTHOR);

		dialogText = new wxTextCtrl(this, -1, dimensions, p, sz, wxTE_MULTILINE);

		p.y += sz.GetHeight() + 10;
		wxButton* b = new wxButton(this, wxID_OK, _("OK"), p, wxDefaultSize);
		p.x += 110;
		wxButton* c = new wxButton(this, wxID_CANCEL, _("Cancel"), p, wxDefaultSize);
	*/
	/*
		wxPanel* panel = new wxPanel(this, -1);

		wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);
		wxBoxSizer* hbox = new wxBoxSizer(wxHORIZONTAL);

		wxStaticText* mssg = new wxStaticText(panel, -1, "Test Message");
	//	mssg->SetLabel("Test message");
	//	wxStaticBox* st = new wxStaticBox(panel, -1, wxT("Colors"), wxPoint(5, 5), wxSize(240, 150));

		wxButton* cancelButton = new wxButton(this, -1, wxT("Cancel"), wxDefaultPosition, wxSize(70, 30));

		hbox->Add(cancelButton, 1, wxRIGHT, 5);

		vbox->Add(panel, 1);
		vbox->Add(hbox, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);

		SetSizer(vbox);
	*/

	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	wxBoxSizer *bSizer5;
	bSizer5 = new wxBoxSizer(wxVERTICAL);

	m_panel2 = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	bSizer5->Add(m_panel2, 1, wxEXPAND | wxALL, 5);

	sttxtMessage = new wxStaticText(this, wxID_ANY, wxT("This is test message..."), wxDefaultPosition, wxDefaultSize, 0);
	sttxtMessage->Wrap(-1);
	bSizer5->Add(sttxtMessage, 0, wxALIGN_CENTER | wxALL, 5);

	btnCancel = new wxButton(this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer5->Add(btnCancel, 0, wxALIGN_CENTER | wxALL, 5);

	this->SetSizer(bSizer5);
	this->Layout();
	bSizer5->Fit(this);

	this->Centre(wxBOTH);

	// Connect Events
	btnCancel->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CancelDialog::OnbtnCancel), NULL, this);
}

CancelDialog::~CancelDialog()
{
	// Disconnect Events
	btnCancel->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CancelDialog::OnbtnCancel), NULL, this);
}

void LimeRFE_8001P_wxgui::SC1905_Set_Cal_Param(int freq)
{
	int command;

	//	uint16_t address;
	//	uint8_t val[2];

	if (freq == LimeRFE_8001P_SC1905_FREQUENCY_A)
	{
		command = LimeRFE_8001P_SC1905_COMMAND_WRITE_MAXPWRCALPARAM_A;
		//		address = 0xdc4;
	}
	if (freq == LimeRFE_8001P_SC1905_FREQUENCY_B)
	{
		command = LimeRFE_8001P_SC1905_COMMAND_WRITE_MAXPWRCALPARAM_B;
		//		address = 0xdc6;
	}

	int result = LimeRFE_8001P_SC1905_SPI_Special_Command(limerfe_8001p, command);
	if (result != LimeRFE_8001P_SUCCESS)
	{
		PrintError(result);
		return;
	}

	//	result = LimeRFE_8001P_SC1905_SPI_Message_Memory(limerfe_8001p, address, val, true, 1);

	CancelDialog cancelDialog(this, -1, _(""));
	cancelDialog.SetMessage("Setting Max Power. Please Wait...");

	userCancel = false;

	std::thread *maxPwrCalOngoingThread = new std::thread(&LimeRFE_8001P_wxgui::maxPwrCalOngoingThreadFunction, this, freq, std::ref(userCancel), &cancelDialog);

	int modalResult = cancelDialog.ShowModal();
	if (modalResult == -1)
		userCancel = true;
}

void LimeRFE_8001P_wxgui::OnbtnSC1905_Set_Cal_Param_A(wxCommandEvent &event)
{
	SC1905_Set_Cal_Param(LimeRFE_8001P_SC1905_FREQUENCY_A);
}

void LimeRFE_8001P_wxgui::OnbtnSC1905_Set_Cal_Param_B(wxCommandEvent &event)
{
	SC1905_Set_Cal_Param(LimeRFE_8001P_SC1905_FREQUENCY_B);
}

void LimeRFE_8001P_wxgui::maxPwrCalOngoingThreadFunction(int freq, std::atomic<bool> &userCancel, CancelDialog *cancelDialog)
{
	//	int i = 0;
	//	for (i = 0; i < 5; i++) {
	//		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	//		if (userCancel == true) {
	//			break;
	//		}
	//	}

	char mssg[100];
	bool done = false;

	uint16_t address;
	uint8_t val[2];

	// MaxPwrCalAOngoing
	//	address = 0xdc4;

	//	int command;

	if (freq == LimeRFE_8001P_SC1905_FREQUENCY_A)
	{
		//		command = LimeRFE_8001P_SC1905_COMMAND_WRITE_MAXPWRCALPARAM_A;
		address = 0xdc4;
	}
	if (freq == LimeRFE_8001P_SC1905_FREQUENCY_B)
	{
		//		command = LimeRFE_8001P_SC1905_COMMAND_WRITE_MAXPWRCALPARAM_B;
		address = 0xdc6;
	}

	int result;
	while (!done)
	{
		result = LimeRFE_8001P_SC1905_SPI_Message_Memory(limerfe_8001p, address, val, true, 1);
		if (result != LimeRFE_8001P_SUCCESS)
		{
			PrintError(result);
			return;
		}

		done = (val[0] == 0x00);

		sprintf(mssg, "Debug: maxPwrCalOngoing value = 0x%02x", val[0]);
		AddMssg(mssg);

		if (userCancel)
			break;

		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}

	if (!userCancel)
		cancelDialog->EndModal(0);
	//	sprintf(mssg, "Exiting maxPwrCalOngoingThread, i = %d", i);
	sprintf(mssg, "Debug: Exiting maxPwrCalOngoingThread");
	AddMssg(mssg);
}

void LimeRFE_8001P_wxgui::OnbtnSC1905_Clear_Cal_Param(wxCommandEvent &event)
{
	SC1905_Clear_Cal_Param(LimeRFE_8001P_SC1905_FREQUENCY_A);
	SC1905_Clear_Cal_Param(LimeRFE_8001P_SC1905_FREQUENCY_B);
}

void LimeRFE_8001P_wxgui::SC1905_Clear_Cal_Param(int freq)
{
	int command;

	char mssg[100];

	uint16_t address;
	uint8_t val[2];

	if (freq == LimeRFE_8001P_SC1905_FREQUENCY_A)
	{
		command = LimeRFE_8001P_SC1905_COMMAND_CLEAR_MAXPWRCALPARAM_A;
	}
	if (freq == LimeRFE_8001P_SC1905_FREQUENCY_B)
	{
		command = LimeRFE_8001P_SC1905_COMMAND_CLEAR_MAXPWRCALPARAM_B;
	}

	int result = LimeRFE_8001P_SC1905_SPI_Special_Command(limerfe_8001p, command);
	if (result != LimeRFE_8001P_SUCCESS)
	{
		PrintError(result);
		return;
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(100));

	bool done = false;
	address = 0xdc3;

	for (int i = 0; i < LimeRFE_8001P_SC1905_MAXPWRCLEARONGOING_ATTEMPTS; i++)
	{
		result = LimeRFE_8001P_SC1905_SPI_Message_Memory(limerfe_8001p, address, val, true, 1);
		if (result != LimeRFE_8001P_SUCCESS)
		{
			PrintError(result);
			return;
		}

		sprintf(mssg, "Debug: maxPwrClearOngoing value = 0x%02x", val[0]);
		AddMssg(mssg);

		done = (val[0] == 0x00);
		if (done)
			break;

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	if (!done)
	{
		PrintError(LimeRFE_8001P_ERROR_SC1905_MAXPWRCLEARONGOING_TOO_LONG);
	}
}

void LimeRFE_8001P_wxgui::OnchSC1905_Guard_Band(wxCommandEvent &event)
{
	int selection = chSC1905_Guard_Band->GetSelection();

	uint16_t address;
	uint8_t val[2] = {0x00, 0x00};

	val[0] = selection;
	address = 0xfc62;
	int result = LimeRFE_8001P_SC1905_SPI_Message_Memory(limerfe_8001p, address, val, false, 1, true);
	if (result != LimeRFE_8001P_SUCCESS)
	{
		PrintError(result);
		return;
	}
}

void LimeRFE_8001P_wxgui::OnrbtnSC1905_EEPROM_Write(wxCommandEvent &event)
{
	SC1905_EEPROM_Update_Form();
}

void LimeRFE_8001P_wxgui::OnrbtnSC1905_EEPROM_Read(wxCommandEvent &event)
{
	SC1905_EEPROM_Update_Form();
}

void LimeRFE_8001P_wxgui::OnbtnSC1905_EEPROM_Execute(wxCommandEvent &event)
{
	uint16_t address;
	wxString addressString = txtCtrlSC1905_EEPROM_Address->GetValue();
	long addressLong;
	if (!addressString.ToLong(&addressLong, 16))
	{
		AddMssg("Invalid EEPROM address value");
		return;
	}
	address = (uint16_t)addressLong;

	uint8_t val[2] = {0x00, 0x00};
	int bytesNo = 1;

	bool isRead = rbtnSC1905_EEPROM_Read->GetValue();

	//	uint8_t value_uint8 = 0x00;
	//	int8_t value_int8 = 0x00;
	//	uint16_t value_uint16 = 0x00;
	//	int16_t value_int16 = 0x00;

	int selection = chSC1905_Variable_Type->GetSelection();
	/*
		switch (selection) {
		case 0: //UINT8
			bytesNo = 1;
			break;
		case 1: //INT8
			bytesNo = 1;
			break;
		case 2: //UINT16
			bytesNo = 2;
			break;
		case 3: //INT16
			bytesNo = 2;
			break;
		}
	*/
	bytesNo = eeprom_variable_types_bytes[selection];

	if (!isRead)
	{ // Write
		wxString valueString = txtCtrlSC1905_EEPROM_Value->GetValue();
		str2bytes(valueString, selection, val);
		/*
				long valueLong;
				if (!valueString.ToLong(&valueLong))
				{
					AddMssg("Invalid EEPROM value");
					return;
				}

				switch (selection) {
				case 0: //UINT8
					val[0] = (uint8_t)valueLong;
					break;
				case 1: //INT8
					val[0] = (int8_t)valueLong;
					break;
				case 2: //UINT16
					value_uint16 = (uint16_t)valueLong;
					val[1] = (value_uint16 >> 8) & 0xff;
					val[0] = value_uint16 & 0xff;
					break;
				case 3: //INT16
					value_int16 = (int16_t)valueLong;
					val[1] = (value_int16 >> 8) & 0xff;
					val[0] = value_int16 & 0xff;
					break;
				}
		*/
	}

	int result = LimeRFE_8001P_SC1905_SPI_Message_Memory(limerfe_8001p, address, val, isRead, bytesNo, true);

	if (isRead)
	{

		wxString valueString;
		long valueRead = 0;

		bytes2str(val, selection, &valueRead);
		/*
				long valueRead = 0;

				switch (chSC1905_Variable_Type->GetSelection()) {
				case 0: //UINT8
					valueRead = (uint8_t)val[0];
					break;
				case 1: //INT8
					valueRead = (int8_t)val[0];
					break;
				case 2: //UINT16
					valueRead = (uint16_t)((val[1] << 8) | val[0]);
					break;
				case 3: //INT16
					valueRead = (int16_t)((val[1] << 8) | val[0]);
					break;
				}

				txtCtrlSC1905_EEPROM_Value->SetValue(wxString::Format(wxT("%ld"), valueRead));
		*/
		txtCtrlSC1905_EEPROM_Value->SetValue(wxString::Format(wxT("%ld"), valueRead));
	}

	if (result != LimeRFE_8001P_SUCCESS)
	{
		PrintError(result);
		return;
	}
}

void LimeRFE_8001P_wxgui::SC1905_EEPROM_Update_Form()
{
	txtCtrlSC1905_EEPROM_Value->Enable(rbtnSC1905_EEPROM_Write->GetValue());
}

void LimeRFE_8001P_wxgui::OnGridCellChangegridSC1905_EEPROM_Parameters(wxGridEvent &event)
{
	//	AddMssg("OnGridCellChange event!");

	int row = event.GetRow();

	uint16_t address;
	//	wxString addressString = txtCtrlSC1905_EEPROM_Address->GetValue();
	wxString addressString = gridSC1905_EEPROM_Parameters->GetCellValue(row, 2);
	long addressLong;
	if (!addressString.ToLong(&addressLong, 16))
	{
		AddMssg("Invalid EEPROM address value");
		return;
	}
	address = (uint16_t)addressLong;

	uint8_t val[2] = {0x00, 0x00};

	int selection = sc905_EEPROM_Parameters_Grid_Variable_Types[row];

	int bytesNo = eeprom_variable_types_bytes[selection];

	wxString valueString = gridSC1905_EEPROM_Parameters->GetCellValue(row, 3);
	str2bytes(valueString, selection, val);

	int result = LimeRFE_8001P_SC1905_SPI_Message_Memory(limerfe_8001p, address, val, false, bytesNo, true);

	if (result != LimeRFE_8001P_SUCCESS)
	{
		PrintError(result);
		return;
	}
}

void LimeRFE_8001P_wxgui::str2bytes(wxString valueString, int selection, uint8_t *val)
{
	uint8_t value_uint8 = 0x00;
	int8_t value_int8 = 0x00;
	uint16_t value_uint16 = 0x00;
	int16_t value_int16 = 0x00;

	long valueLong;
	if (!valueString.ToLong(&valueLong))
	{
		AddMssg("Invalid EEPROM value");
		return;
	}

	switch (selection)
	{
	case 0: // UINT8
		val[0] = (uint8_t)valueLong;
		break;
	case 1: // INT8
		val[0] = (int8_t)valueLong;
		break;
	case 2: // UINT16
		value_uint16 = (uint16_t)valueLong;
		val[1] = (value_uint16 >> 8) & 0xff;
		val[0] = value_uint16 & 0xff;
		break;
	case 3: // INT16
		value_int16 = (int16_t)valueLong;
		val[1] = (value_int16 >> 8) & 0xff;
		val[0] = value_int16 & 0xff;
		break;
	}
}

void LimeRFE_8001P_wxgui::bytes2str(uint8_t *val, int selection, long *valLong)
{
	switch (selection)
	{
	case 0: // UINT8
		*valLong = (uint8_t)val[0];
		break;
	case 1: // INT8
		*valLong = (int8_t)val[0];
		break;
	case 2: // UINT16
		*valLong = (uint16_t)((val[1] << 8) | val[0]);
		break;
	case 3: // INT16
		*valLong = (int16_t)((val[1] << 8) | val[0]);
		break;
	}
}
/*
void LMS8SuiteAppFrame::OnADF4002Close(wxCloseEvent& event)
{
	adfGUI->Destroy();
	adfGUI = nullptr;
}

void LMS8SuiteAppFrame::OnShowADF4002(wxCommandEvent& event)
{
	if (adfGUI) //it's already opened
		adfGUI->Show();
	else
	{
		adfGUI = new ADF4002_wxgui(this, wxNewId(), _("ADF4002"));
		adfGUI->Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(LMS8SuiteAppFrame::OnADF4002Close), NULL, this);
		adfGUI->Initialize(adfModule, lms8controlPort);
		adfGUI->Show();
	}
}
*/

// milans 220610

void LimeRFE_8001P_wxgui::OnLMS8001Close(wxCloseEvent &event)
{
	lms8001GUI->Destroy();
	lms8001GUI = nullptr;
}

void LimeRFE_8001P_wxgui::OnmiLMS8001(wxCommandEvent &event)
{
	auto *dev = static_cast<LimeRFE_8001P_Device *>(limerfe_8001p);
	
	if (limerfe_8001p == nullptr) return;

	if (lms8001GUI) // it's already opened
		lms8001GUI->Show();
	else
	{
		//		lms8001GUI = new LMS8SuiteAppFrame(this, wxNewId(), _("LMS8001"));
		lms8001GUI = new LMS8SuiteAppFrame(this);

		char mssg[200];
		sprintf(mssg, "dev->com.hComm =%d", (int)dev->com.hComm);
		AddMssg(mssg);
		cout << "(int)dev->com.hComm =" << (int)dev->com.hComm << std::endl; // B.J.
		wxCommandEvent event;
		// milans 221125 - added (int)
		if (((int)dev->com.hComm) > -1)
		{	// B.J. added check
			// sprintf(mssg, "(int)dev->com.hComm =%d", (int)dev->com.hComm);
			// AddMssg(mssg);
			lms8001GUI->Initialize(dev->com.hComm);
			lms8001GUI->InitializeSDR(nullptr);
			lms8001GUI->OnControlBoardConnect(event);
			// milans 220610
			// This is not multiplatform, since HANDLE is only for Windows... Make it work on Linux as well... !!!!!!!!!!!!!!!!!
		}

		else if (lmsControl != nullptr)
		{
			// lms8001GUI->Initialize(-1);
			lms8001GUI->InitializeSDR(lmsControl);
			lms8001GUI->OnControlBoardConnect(event);
		}

		lms8001GUI->Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(LimeRFE_8001P_wxgui::OnLMS8001Close), NULL, this);
		lms8001GUI->Show();
	}
}

void LimeRFE_8001P_wxgui::OnbtnApplyData(wxCommandEvent &event)
{
	uint8_t state[STATE_SIZE];

	memset(state, 0, STATE_SIZE);

	setStateBit(state, SPI_2_MCU_DIR_OUT_in_BYTE, SPI_2_MCU_DIR_OUT_in_BIT, cbSPI_2_MCU_DIR_OUT_in->GetValue());
	setStateBit(state, LMS8001_1_SSENn_BYTE, LMS8001_1_SSENn_BIT, cbLMS8001_1_SSENn->GetValue());
	setStateBit(state, LMS8001_2_SSENn_BYTE, LMS8001_2_SSENn_BIT, cbLMS8001_2_SSENn->GetValue());
	setStateBit(state, EXT_PLL_SSENn_BYTE, EXT_PLL_SSENn_BIT, cbEXT_PLL_SSENn->GetValue());
	setStateBit(state, LMS8001_1_RESETn_BYTE, LMS8001_1_RESETn_BIT, cbLMS8001_1_RESETn->GetValue());
	setStateBit(state, LMS8001_2_RESETn_BYTE, LMS8001_2_RESETn_BIT, cbLMS8001_2_RESETn->GetValue());
	setStateBit(state, SC1905_1_SSENn_BYTE, SC1905_1_SSENn_BIT, cbSC1905_1_SSENn->GetValue());
	setStateBit(state, SC1905_2_SSENn_BYTE, SC1905_2_SSENn_BIT, cbSC1905_2_SSENn->GetValue());
	// milans 221223
	//	setStateBit(state, GPIO_SEL_A_LMS8001_BYTE, GPIO_SEL_A_LMS8001_BIT, cbGPIO_SEL_A_LMS8001->GetValue());
	setStateBit(state, SC1905_1_RESETn_BYTE, SC1905_1_RESETn_BIT, cbSC1905_1_RESETn->GetValue());
	setStateBit(state, SC1905_2_RESETn_BYTE, SC1905_2_RESETn_BIT, cbSC1905_2_RESETn->GetValue());
	setStateBit(state, BYPASS_AMP1_BYTE, BYPASS_AMP1_BIT, cbBP_AMP1->GetValue());
	setStateBit(state, DISABLE_AMP1_BYTE, DISABLE_AMP1_BIT, cbSD_AMP1->GetValue());
	setStateBit(state, BYPASS_AMP2_BYTE, BYPASS_AMP2_BIT, cbBP_AMP2->GetValue());
	setStateBit(state, DISABLE_AMP2_BYTE, DISABLE_AMP2_BIT, cbSD_AMP2->GetValue());
	// milans 221223
	//	setStateBit(state, PA1_A_EN_BYTE, PA1_A_EN_BIT, cbPA1_A_EN->GetValue());
	//	setStateBit(state, PA1_B_EN_BYTE, PA1_B_EN_BIT, cbPA1_B_EN->GetValue());
	//	setStateBit(state, PA2_A_EN_BYTE, PA2_A_EN_BIT, cbPA2_A_EN->GetValue());
	//	setStateBit(state, PA2_B_EN_BYTE, PA2_B_EN_BIT, cbPA2_B_EN->GetValue());
	setStateBit(state, DA1_A_EN_BYTE, DA1_A_EN_BIT, cbDA1_A_EN->GetValue());
	setStateBit(state, DA1_B_EN_BYTE, DA1_B_EN_BIT, cbDA1_B_EN->GetValue());
	setStateBit(state, DA2_A_EN_BYTE, DA2_A_EN_BIT, cbDA2_A_EN->GetValue());
	setStateBit(state, DA2_B_EN_BYTE, DA2_B_EN_BIT, cbDA2_B_EN->GetValue());
    
	setStateBit(state, LNA1_EN_BYTE, LNA1_EN_BIT, cbLNA1_EN->GetValue());
	setStateBit(state, LNA2_EN_BYTE, LNA2_EN_BIT, cbLNA2_EN->GetValue());
	// milans 221223
	//	setStateBit(state, DA1_EN_BYTE, DA1_EN_BIT, cbDA1_EN->GetValue());
	//	setStateBit(state, DA2_EN_BYTE, DA2_EN_BIT, cbDA2_EN->GetValue());
	//	setStateBit(state, PA1_A_B_CTRL_BYTE, PA1_A_B_CTRL_BIT, cbPA1_A_B_CTRL->GetValue());
	//	setStateBit(state, PA2_A_B_CTRL_BYTE, PA2_A_B_CTRL_BIT, cbPA2_A_B_CTRL->GetValue());
	setStateBit(state, PDA1_EN_BYTE, PDA1_EN_BIT, cbPDA1_EN->GetValue());
	setStateBit(state, PDA2_EN_BYTE, PDA2_EN_BIT, cbPDA2_EN->GetValue());
	setStateBit(state, DA1_A_B_CTRL_BYTE, DA1_A_B_CTRL_BIT, cbDA1_A_B_CTRL->GetValue());
	setStateBit(state, DA2_A_B_CTRL_BYTE, DA2_A_B_CTRL_BIT, cbDA2_A_B_CTRL->GetValue());

	int selection = 0;
	int selectionBits[7];
	memset(selectionBits, 0, 7 * sizeof(selectionBits[0]));

	// milans 221223
	//	selection = cmbPA1_CPL->GetSelection();
	selection = cmbORX1_ATT->GetSelection();

	memset(selectionBits, 0, 7 * sizeof(selectionBits[0]));

	for (int i = 0; selection > 0; i++)
	{
		selectionBits[i] = selection % 2;
		selection = selection / 2;
	}

	// milans 22123
	//	setStateBit(state, PA1_CPL_D0_BYTE, PA1_CPL_D0_BIT, selectionBits[0]);
	//	setStateBit(state, PA1_CPL_D1_BYTE, PA1_CPL_D1_BIT, selectionBits[1]);
	///	setStateBit(state, PA1_CPL_D2_BYTE, PA1_CPL_D2_BIT, selectionBits[2]);
	//	setStateBit(state, PA1_CPL_D3_BYTE, PA1_CPL_D3_BIT, selectionBits[3]);
	//	setStateBit(state, PA1_CPL_D4_BYTE, PA1_CPL_D4_BIT, selectionBits[4]);
	//	setStateBit(state, PA1_CPL_D5_BYTE, PA1_CPL_D5_BIT, selectionBits[5]);
	//	setStateBit(state, PA1_CPL_D6_BYTE, PA1_CPL_D6_BIT, selectionBits[6]);
	setStateBit(state, ORX1_ATT_D0_BYTE, ORX1_ATT_D0_BIT, selectionBits[0]);
	setStateBit(state, ORX1_ATT_D1_BYTE, ORX1_ATT_D1_BIT, selectionBits[1]);
	setStateBit(state, ORX1_ATT_D2_BYTE, ORX1_ATT_D2_BIT, selectionBits[2]);
	setStateBit(state, ORX1_ATT_D3_BYTE, ORX1_ATT_D3_BIT, selectionBits[3]);
	setStateBit(state, ORX1_ATT_D4_BYTE, ORX1_ATT_D4_BIT, selectionBits[4]);
	setStateBit(state, ORX1_ATT_D5_BYTE, ORX1_ATT_D5_BIT, selectionBits[5]);
	setStateBit(state, ORX1_ATT_D6_BYTE, ORX1_ATT_D6_BIT, selectionBits[6]);

	// milans 221223
	//	selection = cmbPA2_CPL->GetSelection();
	selection = cmbORX2_ATT->GetSelection();

	memset(selectionBits, 0, 7 * sizeof(selectionBits[0]));

	for (int i = 0; selection > 0; i++)
	{
		selectionBits[i] = selection % 2;
		selection = selection / 2;
	}

	// milans 221223
	//	setStateBit(state, PA2_CPL_D0_BYTE, PA2_CPL_D0_BIT, selectionBits[0]);
	//	setStateBit(state, PA2_CPL_D1_BYTE, PA2_CPL_D1_BIT, selectionBits[1]);
	//	setStateBit(state, PA2_CPL_D2_BYTE, PA2_CPL_D2_BIT, selectionBits[2]);
	//	setStateBit(state, PA2_CPL_D3_BYTE, PA2_CPL_D3_BIT, selectionBits[3]);
	//	setStateBit(state, PA2_CPL_D4_BYTE, PA2_CPL_D4_BIT, selectionBits[4]);
	//	setStateBit(state, PA2_CPL_D5_BYTE, PA2_CPL_D5_BIT, selectionBits[5]);
	//	setStateBit(state, PA2_CPL_D6_BYTE, PA2_CPL_D6_BIT, selectionBits[6]);
	setStateBit(state, ORX2_ATT_D0_BYTE, ORX2_ATT_D0_BIT, selectionBits[0]);
	setStateBit(state, ORX2_ATT_D1_BYTE, ORX2_ATT_D1_BIT, selectionBits[1]);
	setStateBit(state, ORX2_ATT_D2_BYTE, ORX2_ATT_D2_BIT, selectionBits[2]);
	setStateBit(state, ORX2_ATT_D3_BYTE, ORX2_ATT_D3_BIT, selectionBits[3]);
	setStateBit(state, ORX2_ATT_D4_BYTE, ORX2_ATT_D4_BIT, selectionBits[4]);
	setStateBit(state, ORX2_ATT_D5_BYTE, ORX2_ATT_D5_BIT, selectionBits[5]);
	setStateBit(state, ORX2_ATT_D6_BYTE, ORX2_ATT_D6_BIT, selectionBits[6]);

	// milans 221223
	selection = cmbTX1_ATT->GetSelection();

	memset(selectionBits, 0, 7 * sizeof(selectionBits[0]));

	for (int i = 0; selection > 0; i++)
	{
		selectionBits[i] = selection % 2;
		selection = selection / 2;
	}

	setStateBit(state, TX1_ATT_D0_BYTE, TX1_ATT_D0_BIT, selectionBits[0]);
	setStateBit(state, TX1_ATT_D1_BYTE, TX1_ATT_D1_BIT, selectionBits[1]);
	setStateBit(state, TX1_ATT_D2_BYTE, TX1_ATT_D2_BIT, selectionBits[2]);
	setStateBit(state, TX1_ATT_D3_BYTE, TX1_ATT_D3_BIT, selectionBits[3]);
	setStateBit(state, TX1_ATT_D4_BYTE, TX1_ATT_D4_BIT, selectionBits[4]);
	setStateBit(state, TX1_ATT_D5_BYTE, TX1_ATT_D5_BIT, selectionBits[5]);
	setStateBit(state, TX1_ATT_D6_BYTE, TX1_ATT_D6_BIT, selectionBits[6]);

	selection = cmbTX2_ATT->GetSelection();

	memset(selectionBits, 0, 7 * sizeof(selectionBits[0]));

	for (int i = 0; selection > 0; i++)
	{
		selectionBits[i] = selection % 2;
		selection = selection / 2;
	}

	setStateBit(state, TX2_ATT_D0_BYTE, TX2_ATT_D0_BIT, selectionBits[0]);
	setStateBit(state, TX2_ATT_D1_BYTE, TX2_ATT_D1_BIT, selectionBits[1]);
	setStateBit(state, TX2_ATT_D2_BYTE, TX2_ATT_D2_BIT, selectionBits[2]);
	setStateBit(state, TX2_ATT_D3_BYTE, TX2_ATT_D3_BIT, selectionBits[3]);
	setStateBit(state, TX2_ATT_D4_BYTE, TX2_ATT_D4_BIT, selectionBits[4]);
	setStateBit(state, TX2_ATT_D5_BYTE, TX2_ATT_D5_BIT, selectionBits[5]);
	setStateBit(state, TX2_ATT_D6_BYTE, TX2_ATT_D6_BIT, selectionBits[6]);

	//	setStateBit(state, CHAIN_SIZE, MCU_BYTE_TXRX_1_BIT, cbTXRX_1->GetValue());
	//	setStateBit(state, CHAIN_SIZE, MCU_BYTE_TXRX_2_BIT, cbTXRX_2->GetValue());
	setStateBit(state, MCU_BYTE, MCU_TXRX_1_BIT, cbTXRX_1->GetValue());
	setStateBit(state, MCU_BYTE, MCU_TXRX_2_BIT, cbTXRX_2->GetValue());

	setStateBit(state, MISC_BYTE, MISC_CHANNEL_BIT, cmbChannel->GetSelection());

	int result = LimeRFE_8001P_Set_Config_Full(limerfe_8001p, state, STATE_SIZE);
	if (result != LimeRFE_8001P_SUCCESS)
	{
		PrintError(result);
		return;
	}

	applied = true;
	// B.J.
	// configured = true;
	btnApplyData->Enable(!applied);
}

void LimeRFE_8001P_wxgui::setStateBit(uint8_t *state, int byte, int bit, int value)
{
	if (value == 0)
		cbi(state[byte], bit);
	else
		sbi(state[byte], bit);
}

int LimeRFE_8001P_wxgui::getStateBit(uint8_t *state, int byte, int bit)
{
	int result;

	result = (state[byte] >> bit) & 0x01;

	return result;
}

void LimeRFE_8001P_wxgui::OnbtnReadData(wxCommandEvent &event)
{
	uint8_t state[STATE_SIZE];

	int result = LimeRFE_8001P_Get_Config_Full(limerfe_8001p, state, STATE_SIZE);
	if (result != LimeRFE_8001P_SUCCESS)
	{
		PrintError(result);
		return;
	}

	char mssg[200];
	sprintf(mssg, "State: 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x", state[0], state[1], state[2], state[3], state[4], state[5], state[6], state[7]);
	AddMssg(mssg);

	cbSPI_2_MCU_DIR_OUT_in->SetValue(getStateBit(state, SPI_2_MCU_DIR_OUT_in_BYTE, SPI_2_MCU_DIR_OUT_in_BIT));
	//	setStateBit(state, SPI_2_MCU_DIR_OUT_in_BYTE, SPI_2_MCU_DIR_OUT_in_BIT, cbSPI_2_MCU_DIR_OUT_in->GetValue());
	cbLMS8001_1_SSENn->SetValue(getStateBit(state, LMS8001_1_SSENn_BYTE, LMS8001_1_SSENn_BIT));
	//	setStateBit(state, LMS8001_1_SSENn_BYTE, LMS8001_1_SSENn_BIT, cbLMS8001_1_SSENn->GetValue());
	cbLMS8001_2_SSENn->SetValue(getStateBit(state, LMS8001_2_SSENn_BYTE, LMS8001_2_SSENn_BIT));
	//	setStateBit(state, LMS8001_2_SSENn_BYTE, LMS8001_2_SSENn_BIT, cbLMS8001_2_SSENn->GetValue());
	cbEXT_PLL_SSENn->SetValue(getStateBit(state, EXT_PLL_SSENn_BYTE, EXT_PLL_SSENn_BIT));
	//	setStateBit(state, EXT_PLL_SSENn_BYTE, EXT_PLL_SSENn_BIT, cbEXT_PLL_SSENn->GetValue());
	cbLMS8001_1_RESETn->SetValue(getStateBit(state, LMS8001_1_RESETn_BYTE, LMS8001_1_RESETn_BIT));
	//	setStateBit(state, LMS8001_1_RESETn_BYTE, LMS8001_1_RESETn_BIT, cbLMS8001_1_RESETn->GetValue());
	cbLMS8001_2_RESETn->SetValue(getStateBit(state, LMS8001_2_RESETn_BYTE, LMS8001_2_RESETn_BIT));
	//	setStateBit(state, LMS8001_2_RESETn_BYTE, LMS8001_2_RESETn_BIT, cbLMS8001_2_RESETn->GetValue());
	cbSC1905_1_SSENn->SetValue(getStateBit(state, SC1905_1_SSENn_BYTE, SC1905_1_SSENn_BIT));
	//	setStateBit(state, SC1905_1_SSENn_BYTE, SC1905_1_SSENn_BIT, cbSC1905_1_SSENn->GetValue());
	cbSC1905_2_SSENn->SetValue(getStateBit(state, SC1905_2_SSENn_BYTE, SC1905_2_SSENn_BIT));
	//	setStateBit(state, SC1905_2_SSENn_BYTE, SC1905_2_SSENn_BIT, cbSC1905_2_SSENn->GetValue());
	// milans 221223
	//	cbGPIO_SEL_A_LMS8001->SetValue(getStateBit(state, GPIO_SEL_A_LMS8001_BYTE, GPIO_SEL_A_LMS8001_BIT));
	//	setStateBit(state, GPIO_SEL_A_LMS8001_BYTE, GPIO_SEL_A_LMS8001_BIT, cbGPIO_SEL_A_LMS8001->GetValue());
	cbSC1905_1_RESETn->SetValue(getStateBit(state, SC1905_1_RESETn_BYTE, SC1905_1_RESETn_BIT));
	//	setStateBit(state, SC1905_1_RESETn_BYTE, SC1905_1_RESETn_BIT, cbSC1905_1_RESETn->GetValue());
	cbSC1905_2_RESETn->SetValue(getStateBit(state, SC1905_2_RESETn_BYTE, SC1905_2_RESETn_BIT));
	//	setStateBit(state, SC1905_2_RESETn_BYTE, SC1905_2_RESETn_BIT, cbSC1905_2_RESETn->GetValue());
	cbBP_AMP1->SetValue(getStateBit(state, BYPASS_AMP1_BYTE, BYPASS_AMP1_BIT));
	//	setStateBit(state, BYPASS_AMP1_BYTE, BYPASS_AMP1_BIT, cbBP_AMP1->GetValue());
	cbSD_AMP1->SetValue(getStateBit(state, DISABLE_AMP1_BYTE, DISABLE_AMP1_BIT));
	//	setStateBit(state, DISABLE_AMP1_BYTE, DISABLE_AMP1_BIT, cbSD_AMP1->GetValue());
	cbBP_AMP2->SetValue(getStateBit(state, BYPASS_AMP2_BYTE, BYPASS_AMP2_BIT));
	//	setStateBit(state, BYPASS_AMP2_BYTE, BYPASS_AMP2_BIT, cbBP_AMP2->GetValue());
	cbSD_AMP2->SetValue(getStateBit(state, DISABLE_AMP2_BYTE, DISABLE_AMP2_BIT));
	//	setStateBit(state, DISABLE_AMP2_BYTE, DISABLE_AMP2_BIT, cbSD_AMP2->GetValue());
	// milans 221223
	//	cbPA1_A_EN->SetValue(getStateBit(state, PA1_A_EN_BYTE, PA1_A_EN_BIT));
	//	setStateBit(state, PA1_A_EN_BYTE, PA1_A_EN_BIT, cbPA1_A_EN->GetValue());
	//	cbPA1_B_EN->SetValue(getStateBit(state, PA1_B_EN_BYTE, PA1_B_EN_BIT));
	//	setStateBit(state, PA1_B_EN_BYTE, PA1_B_EN_BIT, cbPA1_B_EN->GetValue());
	//	cbPA2_A_EN->SetValue(getStateBit(state, PA2_A_EN_BYTE, PA2_A_EN_BIT));
	//	setStateBit(state, PA2_A_EN_BYTE, PA2_A_EN_BIT, cbPA2_A_EN->GetValue());
	//	cbPA2_B_EN->SetValue(getStateBit(state, PA2_B_EN_BYTE, PA2_B_EN_BIT));
	//	setStateBit(state, PA2_B_EN_BYTE, PA2_B_EN_BIT, cbPA2_B_EN->GetValue());
	cbDA1_A_EN->SetValue(getStateBit(state, DA1_A_EN_BYTE, DA1_A_EN_BIT));
	cbDA1_B_EN->SetValue(getStateBit(state, DA1_B_EN_BYTE, DA1_B_EN_BIT));
	cbDA2_A_EN->SetValue(getStateBit(state, DA2_A_EN_BYTE, DA2_A_EN_BIT));
	cbDA2_B_EN->SetValue(getStateBit(state, DA2_B_EN_BYTE, DA2_B_EN_BIT));

	cbLNA1_EN->SetValue(getStateBit(state, LNA1_EN_BYTE, LNA1_EN_BIT));
	//	setStateBit(state, LNA1_EN_BYTE, LNA1_EN_BIT, cbLNA1_EN->GetValue());
	cbLNA2_EN->SetValue(getStateBit(state, LNA2_EN_BYTE, LNA2_EN_BIT));
	//	setStateBit(state, LNA2_EN_BYTE, LNA2_EN_BIT, cbLNA2_EN->GetValue());
	// milans 221223
	//	cbDA1_EN->SetValue(getStateBit(state, DA1_EN_BYTE, DA1_EN_BIT));
	//	setStateBit(state, DA1_EN_BYTE, DA1_EN_BIT, cbDA1_EN->GetValue());
	//	cbDA2_EN->SetValue(getStateBit(state, DA2_EN_BYTE, DA2_EN_BIT));
	//	setStateBit(state, DA2_EN_BYTE, DA2_EN_BIT, cbDA2_EN->GetValue());
	//	cbPA1_A_B_CTRL->SetValue(getStateBit(state, PA1_A_B_CTRL_BYTE, PA1_A_B_CTRL_BIT));
	//	setStateBit(state, PA1_A_B_CTRL_BYTE, PA1_A_B_CTRL_BIT, cbPA1_A_B_CTRL->GetValue());
	//	cbPA2_A_B_CTRL->SetValue(getStateBit(state, PA2_A_B_CTRL_BYTE, PA2_A_B_CTRL_BIT));
	//	setStateBit(state, PA2_A_B_CTRL_BYTE, PA2_A_B_CTRL_BIT, cbPA2_A_B_CTRL->GetValue());
	cbPDA1_EN->SetValue(getStateBit(state, PDA1_EN_BYTE, PDA1_EN_BIT));
	cbPDA2_EN->SetValue(getStateBit(state, PDA2_EN_BYTE, PDA2_EN_BIT));
	cbDA1_A_B_CTRL->SetValue(getStateBit(state, DA1_A_B_CTRL_BYTE, DA1_A_B_CTRL_BIT));
	cbDA2_A_B_CTRL->SetValue(getStateBit(state, DA2_A_B_CTRL_BYTE, DA2_A_B_CTRL_BIT));

	int selection = 0;
	//	int selectionBits[7];
	//	memset(selectionBits, 0, 7 * sizeof(selectionBits[0]));
	//
	//	selection = cmbPA1_CPL->GetSelection();
	//
	//	for (int i = 0; selection > 0; i++)
	//	{
	//		selectionBits[i] = selection % 2;
	//		selection = selection / 2;
	//	}

	// milans 221223
	//	selection += pow(2, 0) * getStateBit(state, PA1_CPL_D0_BYTE, PA1_CPL_D0_BIT);
	//	setStateBit(state, PA1_CPL_D0_BYTE, PA1_CPL_D0_BIT, selectionBits[0]);
	//	selection += pow(2, 1) * getStateBit(state, PA1_CPL_D1_BYTE, PA1_CPL_D1_BIT);
	//	setStateBit(state, PA1_CPL_D1_BYTE, PA1_CPL_D1_BIT, selectionBits[1]);
	//	selection += pow(2, 2) * getStateBit(state, PA1_CPL_D2_BYTE, PA1_CPL_D2_BIT);
	//	setStateBit(state, PA1_CPL_D2_BYTE, PA1_CPL_D2_BIT, selectionBits[2]);
	//	selection += pow(2, 3) * getStateBit(state, PA1_CPL_D3_BYTE, PA1_CPL_D3_BIT);
	//	setStateBit(state, PA1_CPL_D3_BYTE, PA1_CPL_D3_BIT, selectionBits[3]);
	//	selection += pow(2, 4) * getStateBit(state, PA1_CPL_D4_BYTE, PA1_CPL_D4_BIT);
	//	setStateBit(state, PA1_CPL_D4_BYTE, PA1_CPL_D4_BIT, selectionBits[4]);
	//	selection += pow(2, 5) * getStateBit(state, PA1_CPL_D5_BYTE, PA1_CPL_D5_BIT);
	//	setStateBit(state, PA1_CPL_D5_BYTE, PA1_CPL_D5_BIT, selectionBits[5]);
	//	selection += pow(2, 6) * getStateBit(state, PA1_CPL_D6_BYTE, PA1_CPL_D6_BIT);
	//	setStateBit(state, PA1_CPL_D6_BYTE, PA1_CPL_D6_BIT, selectionBits[6]);
	selection += pow(2, 0) * getStateBit(state, ORX1_ATT_D0_BYTE, ORX1_ATT_D0_BIT);
	selection += pow(2, 1) * getStateBit(state, ORX1_ATT_D1_BYTE, ORX1_ATT_D1_BIT);
	selection += pow(2, 2) * getStateBit(state, ORX1_ATT_D2_BYTE, ORX1_ATT_D2_BIT);
	selection += pow(2, 3) * getStateBit(state, ORX1_ATT_D3_BYTE, ORX1_ATT_D3_BIT);
	selection += pow(2, 4) * getStateBit(state, ORX1_ATT_D4_BYTE, ORX1_ATT_D4_BIT);
	selection += pow(2, 5) * getStateBit(state, ORX1_ATT_D5_BYTE, ORX1_ATT_D5_BIT);
	selection += pow(2, 6) * getStateBit(state, ORX1_ATT_D6_BYTE, ORX1_ATT_D6_BIT);

	// milans 221223
	//	cmbPA1_CPL->SetSelection(selection);
	cmbORX1_ATT->SetSelection(selection);

	selection = 0;

	// milans 221223
	//	selection += pow(2, 0) * getStateBit(state, PA2_CPL_D0_BYTE, PA2_CPL_D0_BIT);
	//	selection += pow(2, 1) * getStateBit(state, PA2_CPL_D1_BYTE, PA2_CPL_D1_BIT);
	//	selection += pow(2, 2) * getStateBit(state, PA2_CPL_D2_BYTE, PA2_CPL_D2_BIT);
	//	selection += pow(2, 3) * getStateBit(state, PA2_CPL_D3_BYTE, PA2_CPL_D3_BIT);
	//	selection += pow(2, 4) * getStateBit(state, PA2_CPL_D4_BYTE, PA2_CPL_D4_BIT);
	//	selection += pow(2, 5) * getStateBit(state, PA2_CPL_D5_BYTE, PA2_CPL_D5_BIT);
	//	selection += pow(2, 6) * getStateBit(state, PA2_CPL_D6_BYTE, PA2_CPL_D6_BIT);
	selection += pow(2, 0) * getStateBit(state, ORX2_ATT_D0_BYTE, ORX2_ATT_D0_BIT);
	selection += pow(2, 1) * getStateBit(state, ORX2_ATT_D1_BYTE, ORX2_ATT_D1_BIT);
	selection += pow(2, 2) * getStateBit(state, ORX2_ATT_D2_BYTE, ORX2_ATT_D2_BIT);
	selection += pow(2, 3) * getStateBit(state, ORX2_ATT_D3_BYTE, ORX2_ATT_D3_BIT);
	selection += pow(2, 4) * getStateBit(state, ORX2_ATT_D4_BYTE, ORX2_ATT_D4_BIT);
	selection += pow(2, 5) * getStateBit(state, ORX2_ATT_D5_BYTE, ORX2_ATT_D5_BIT);
	selection += pow(2, 6) * getStateBit(state, ORX2_ATT_D6_BYTE, ORX2_ATT_D6_BIT);

	// milans 221223
	//	cmbPA2_CPL->SetSelection(selection);
	cmbORX2_ATT->SetSelection(selection);

	selection = 0;

	// milans 221223
	selection += pow(2, 0) * getStateBit(state, TX1_ATT_D0_BYTE, TX1_ATT_D0_BIT);
	selection += pow(2, 1) * getStateBit(state, TX1_ATT_D1_BYTE, TX1_ATT_D1_BIT);
	selection += pow(2, 2) * getStateBit(state, TX1_ATT_D2_BYTE, TX1_ATT_D2_BIT);
	selection += pow(2, 3) * getStateBit(state, TX1_ATT_D3_BYTE, TX1_ATT_D3_BIT);
	selection += pow(2, 4) * getStateBit(state, TX1_ATT_D4_BYTE, TX1_ATT_D4_BIT);
	selection += pow(2, 5) * getStateBit(state, TX1_ATT_D5_BYTE, TX1_ATT_D5_BIT);
	selection += pow(2, 6) * getStateBit(state, TX1_ATT_D6_BYTE, TX1_ATT_D6_BIT);

	cmbTX1_ATT->SetSelection(selection);

	selection = 0;

	selection += pow(2, 0) * getStateBit(state, TX2_ATT_D0_BYTE, TX2_ATT_D0_BIT);
	selection += pow(2, 1) * getStateBit(state, TX2_ATT_D1_BYTE, TX2_ATT_D1_BIT);
	selection += pow(2, 2) * getStateBit(state, TX2_ATT_D2_BYTE, TX2_ATT_D2_BIT);
	selection += pow(2, 3) * getStateBit(state, TX2_ATT_D3_BYTE, TX2_ATT_D3_BIT);
	selection += pow(2, 4) * getStateBit(state, TX2_ATT_D4_BYTE, TX2_ATT_D4_BIT);
	selection += pow(2, 5) * getStateBit(state, TX2_ATT_D5_BYTE, TX2_ATT_D5_BIT);
	selection += pow(2, 6) * getStateBit(state, TX2_ATT_D6_BYTE, TX2_ATT_D6_BIT);

	cmbTX2_ATT->SetSelection(selection);

	cbTXRX_1->SetValue(getStateBit(state, MCU_BYTE, MCU_TXRX_1_BIT));
	//	setStateBit(state, CHAIN_SIZE, MCU_BYTE_TXRX_1_BIT, cbTXRX_1->GetValue());
	cbTXRX_2->SetValue(getStateBit(state, MCU_BYTE, MCU_TXRX_2_BIT));
	//	setStateBit(state, CHAIN_SIZE, MCU_BYTE_TXRX_2_BIT, cbTXRX_2->GetValue());

	cmbChannel->SetSelection(getStateBit(state, MISC_BYTE, MISC_CHANNEL_BIT));
	//	setStateBit(state, MISC_BYTE, MISC_CHANNEL_BIT, cmbChannel->GetSelection());

	Detailed2Simple();

	applied = true;
	// B.J.
	// configured = true;
	btnApplyData->Enable(!applied);
}

void LimeRFE_8001P_wxgui::OnEraseBackground_pnlChannel(wxEraseEvent &event)
{
	wxDC *dc = event.GetDC();
	wxCoord width, height;
	dc->GetSize(&width, &height);
	//	wxCoord x, y, w, h;

	dc->SetClippingRegion(0, 0, width, height);
	dc->Clear();
	dc->DrawBitmap(bmpChannel, 0, 0);
}

void LimeRFE_8001P_wxgui::OnSimpleChanged(wxCommandEvent &event)
{
	Simple2Detailed();
	applied = false;
	btnApplyData->Enable(!applied);
}
void LimeRFE_8001P_wxgui::Simple2Detailed()
{
	int channel = cmbChannel->GetSelection();

	switch (channel)
	{
	case 0:
		cbBP_AMP1->SetValue(cbBP_AMPX->GetValue());
		cbSD_AMP1->SetValue(cbSD_AMPX->GetValue());
		// milans 221223
		//		cbDA1_EN->SetValue(cbDAX_EN->GetValue());
		cbPDA1_EN->SetValue(cbPDAX_EN->GetValue());

		cbLNA1_EN->SetValue(cbLNAX_EN->GetValue());
		// milans 221223
		//		cmbPA1_CPL->SetSelection(cmbPAX_CPL->GetSelection());
		//		if (cbPAX_A_B_CTRL->GetValue() == 1)
		//		{ // Channel A
		//			cbPA1_A_EN->SetValue(cbLNAX_EN->GetValue());
		//			cbPA1_B_EN->SetValue(false);
		//		}
		//		else
		//		{
		//			cbPA1_A_EN->SetValue(false);
		//			cbPA1_B_EN->SetValue(cbLNAX_EN->GetValue());
		//		}
		//		cbPA1_A_B_CTRL->SetValue(cbPAX_A_B_CTRL->GetValue());
		cmbORX1_ATT->SetSelection(cmbORXX_ATT->GetSelection());

		// milans 221223
		cmbTX1_ATT->SetSelection(cmbTXX_ATT->GetSelection());

		if (cbDAX_A_B_CTRL->GetValue() == 1)
		{ // Channel A
			cbDA1_A_EN->SetValue(cbDAX_X_EN->GetValue());
			cbDA1_B_EN->SetValue(false);
		}
		else
		{
			cbDA1_A_EN->SetValue(false);
			cbDA1_B_EN->SetValue(cbDAX_X_EN->GetValue());
		}
		cbDA1_A_B_CTRL->SetValue(cbDAX_A_B_CTRL->GetValue());

		cbTXRX_1->SetValue(cbTXRX_X->GetValue());
		cbSC1905_1_RESETn->SetValue(cbSC1905_X_RESETn->GetValue());
		cbLMS8001_1_RESETn->SetValue(cbLMS8001_X_RESETn->GetValue());

		break;
	case 1:
		cbBP_AMP2->SetValue(cbBP_AMPX->GetValue());
		cbSD_AMP2->SetValue(cbSD_AMPX->GetValue());
		// milans 221223
		//		cbDA2_EN->SetValue(cbDAX_EN->GetValue());
		cbPDA2_EN->SetValue(cbPDAX_EN->GetValue());

		cbLNA2_EN->SetValue(cbLNAX_EN->GetValue());
		// milans 221223
		//		cmbPA2_CPL->SetSelection(cmbPAX_CPL->GetSelection());
		//		if (cbPAX_A_B_CTRL->GetValue() == 1)
		//		{ // Channel A
		//			cbPA2_A_EN->SetValue(cbLNAX_EN->GetValue());
		//			cbPA2_B_EN->SetValue(false);
		//		}
		//		else
		//		{
		//			cbPA2_A_EN->SetValue(false);
		//			cbPA2_B_EN->SetValue(cbLNAX_EN->GetValue());
		//		}
		//		cbPA2_A_B_CTRL->SetValue(cbPAX_A_B_CTRL->GetValue());

		cmbORX2_ATT->SetSelection(cmbORXX_ATT->GetSelection());

		// milans 221223
		cmbTX2_ATT->SetSelection(cmbTXX_ATT->GetSelection());

		if (cbDAX_A_B_CTRL->GetValue() == 1)
		{ // Channel A
			cbDA2_A_EN->SetValue(cbDAX_X_EN->GetValue());
			cbDA2_B_EN->SetValue(false);
		}
		else
		{
			cbDA2_A_EN->SetValue(false);
			cbDA2_B_EN->SetValue(cbDAX_X_EN->GetValue());
		}
		cbDA2_A_B_CTRL->SetValue(cbDAX_A_B_CTRL->GetValue());

		cbTXRX_2->SetValue(cbTXRX_X->GetValue());
		cbSC1905_2_RESETn->SetValue(cbSC1905_X_RESETn->GetValue());
		cbLMS8001_2_RESETn->SetValue(cbLMS8001_X_RESETn->GetValue());

		break;
	}
}

void LimeRFE_8001P_wxgui::OnDetailedChange(wxCommandEvent &event)
{
	Detailed2Simple();
	applied = false;
	btnApplyData->Enable(!applied);
}

void LimeRFE_8001P_wxgui::Detailed2Simple()
{
	int channel = cmbChannel->GetSelection();

	switch (channel)
	{
	case 0:
		cbBP_AMPX->SetValue(cbBP_AMP1->GetValue());
		cbSD_AMPX->SetValue(cbSD_AMP1->GetValue());
	// milans 221223
		//		cbDAX_EN->SetValue(cbDA1_EN->GetValue());
		cbPDAX_EN->SetValue(cbPDA1_EN->GetValue());
		cbLNAX_EN->SetValue(cbLNA1_EN->GetValue());
		// milans 221223
		//		cmbPAX_CPL->SetSelection(cmbPA1_CPL->GetSelection());
		//		cbPAX_A_B_CTRL->SetValue(cbPA1_A_B_CTRL->GetValue());
		cmbORXX_ATT->SetSelection(cmbORX1_ATT->GetSelection());
		cbDAX_A_B_CTRL->SetValue(cbDA1_A_B_CTRL->GetValue());

		// milans 221223
		cmbTXX_ATT->SetSelection(cmbTX1_ATT->GetSelection());

		cbTXRX_X->SetValue(cbTXRX_1->GetValue());
		// milans 221223
		//		if (cbPA1_A_B_CTRL->GetValue() == 1)
		if (cbDA1_A_B_CTRL->GetValue() == 1)
		{	// Channel A
			// milans 22123
			//			cbLNAX_EN->SetValue(cbPA1_A_EN->GetValue());
			cbDAX_X_EN->SetValue(cbDA1_A_EN->GetValue());
		}
		else
		{
			// milans 22123
			//			cbLNAX_EN->SetValue(cbPA1_B_EN->GetValue());
			cbDAX_X_EN->SetValue(cbDA1_B_EN->GetValue());
		}
		cbSC1905_X_RESETn->SetValue(cbSC1905_1_RESETn->GetValue());
		cbLMS8001_X_RESETn->SetValue(cbLMS8001_1_RESETn->GetValue());

		break;
	case 1:
		cbBP_AMPX->SetValue(cbBP_AMP2->GetValue());
		cbSD_AMPX->SetValue(cbSD_AMP2->GetValue());
		// milans 221223
		//		cbDAX_EN->SetValue(cbDA2_EN->GetValue());
		cbPDAX_EN->SetValue(cbPDA2_EN->GetValue());

		cbLNAX_EN->SetValue(cbLNA2_EN->GetValue());
		// milans 221223
		//		cmbPAX_CPL->SetSelection(cmbPA2_CPL->GetSelection());
		//		cbPAX_A_B_CTRL->SetValue(cbPA2_A_B_CTRL->GetValue());
		cmbORXX_ATT->SetSelection(cmbORX2_ATT->GetSelection());
		cbDAX_A_B_CTRL->SetValue(cbDA2_A_B_CTRL->GetValue());

		// milans
		cmbTXX_ATT->SetSelection(cmbTX2_ATT->GetSelection());

		cbTXRX_X->SetValue(cbTXRX_2->GetValue());
		// milans 221223
		//		if (cbPA2_A_B_CTRL->GetValue() == 1)
		if (cbDA2_A_B_CTRL->GetValue() == 1)
		{	// Channel A
			// milans 221223
			//			cbLNAX_EN->SetValue(cbPA2_A_EN->GetValue());
			cbDAX_X_EN->SetValue(cbDA2_A_EN->GetValue());
		}
		else
		{
			// milans 221223
			//			cbLNAX_EN->SetValue(cbPA2_B_EN->GetValue());
			cbDAX_X_EN->SetValue(cbDA2_B_EN->GetValue());
		}
		cbSC1905_X_RESETn->SetValue(cbSC1905_2_RESETn->GetValue());
		cbLMS8001_X_RESETn->SetValue(cbLMS8001_2_RESETn->GetValue());

		break;
	}
}

// B.J.
// milans 230127 - Commented out, since the wxFormBuilder file that was on the github did not contain this SPI part
/*
void LimeRFE_8001P_wxgui::OnbtnWRITESPI(wxCommandEvent &event)
{
	uint16_t regValue = 0x0000;

	wxString txt;
	txt = txtCtrlADDRSPI->GetValue();
	long addr = 0x0000;
	if (!txt.ToLong(&addr))
	{
		AddMssg("Invalid value");
		return;
	}
	txt = txtCtrlDATASPI->GetValue();
	long data = 0x0000;
	if (!txt.ToLong(&data))
	{
		AddMssg("Invalid value");
		return;
	}

	if (cbSingle->IsChecked())
		LimeRFE_8001P_SPI_write(limerfe_8001p, 170 * 32, addr, data);
	else
	{
		uint8_t c[64];
		for (int i = 0; i <= 63; i++)
			c[i] = 100 + i;
		LimeRFE_8001P_SPI_write_buffer(limerfe_8001p, c, 64);
	}
}
void LimeRFE_8001P_wxgui::OnbtnREADSPI(wxCommandEvent &event)
{
	char mssg[200];
	uint16_t regValue = 0x0000;

	wxString txt;
	txt = txtCtrlADDRSPI->GetValue();
	long addr = 0x0000;
	if (!txt.ToLong(&addr))
	{
		AddMssg("Invalid value");
		return;
	}

	if (cbSingle->IsChecked())
	{
		LimeRFE_8001P_SPI_read(limerfe_8001p, 170 * 32, addr, &regValue); // dummy read
		sprintf(mssg, "addr=0x%04x, retValue=0x%04x", addr, regValue);
		AddMssg(mssg);
	}
	else
	{
		uint8_t c[64];
		LimeRFE_8001P_SPI_read_buffer(limerfe_8001p, c, 64);
		for (int i = 0; i <= 63; i++)
		{
			sprintf(mssg, "c[%d]=0x%02x", i, c[i]);
			AddMssg(mssg);
		}
	}
}
*/
