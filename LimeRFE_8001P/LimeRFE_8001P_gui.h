///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/radiobut.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/panel.h>
#include <wx/combobox.h>
#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/stattext.h>
#include <wx/notebook.h>
#include <wx/textctrl.h>
#include <wx/choice.h>
#include <wx/gauge.h>
#include <wx/grid.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class LimeRFE_8001P_view
///////////////////////////////////////////////////////////////////////////////
class LimeRFE_8001P_view : public wxFrame
{
	private:

	protected:
		wxMenuBar* mbar;
		wxMenu* mFile;
		wxMenu* mModules;
		wxNotebook* nbMain;
		wxPanel* pnlMain;
		wxPanel* m_panel15;
		wxRadioButton* rbI2C;
		wxRadioButton* rbUSB;
		wxPanel* m_panel161;
		wxComboBox* cmbbPorts;
		wxButton* btnRefreshPorts;
		wxButton* btnOpenPort;
		wxButton* btnClosePort;
		wxPanel* m_panel172;
		wxButton* btnOpen;
		wxButton* btnSave;
		wxButton* btnReset;
		wxButton* btnBoard2GUI;
		wxPanel* m_panel13;
		wxComboBox* cmbChannel;
		wxNotebook* m_notebook3;
		wxPanel* m_panel131;
		wxPanel* pnlChannel;
		wxCheckBox* cbBP_AMPX;
		wxCheckBox* cbSD_AMPX;
		wxCheckBox* cbSC1905_X_RESETn;
		wxCheckBox* cbLMS8001_X_RESETn;
		wxStaticText* m_staticText4311;
		wxComboBox* cmbTXX_ATT;
		wxCheckBox* cbPDAX_EN;
		wxCheckBox* cbLNAX_EN;
		wxStaticText* m_staticText431;
		wxComboBox* cmbORXX_ATT;
		wxCheckBox* cbDAX_X_EN;
		wxCheckBox* cbDAX_A_B_CTRL;
		wxCheckBox* cbTXRX_X;
		wxPanel* m_panel14;
		wxCheckBox* cbSPI_2_MCU_DIR_OUT_in;
		wxCheckBox* cbLMS8001_1_SSENn;
		wxCheckBox* cbLMS8001_2_SSENn;
		wxCheckBox* cbEXT_PLL_SSENn;
		wxCheckBox* cbLMS8001_1_RESETn;
		wxCheckBox* cbLMS8001_2_RESETn;
		wxCheckBox* cbSC1905_1_SSENn;
		wxCheckBox* cbSC1905_2_SSENn;
		wxCheckBox* cbSC1905_1_RESETn;
		wxCheckBox* cbSC1905_2_RESETn;
		wxCheckBox* cbBP_AMP1;
		wxCheckBox* cbSD_AMP1;
		wxCheckBox* cbBP_AMP2;
		wxCheckBox* cbSD_AMP2;
		wxCheckBox* cbDA1_A_EN;
		wxCheckBox* cbDA1_B_EN;
		wxCheckBox* cbDA2_A_EN;
		wxCheckBox* cbDA2_B_EN;
		wxCheckBox* cbLNA1_EN;
		wxCheckBox* cbLNA2_EN;
		wxCheckBox* cbPDA1_EN;
		wxCheckBox* cbPDA2_EN;
		wxCheckBox* cbDA1_A_B_CTRL;
		wxCheckBox* cbDA2_A_B_CTRL;
		wxStaticText* m_staticText43;
		wxComboBox* cmbORX1_ATT;
		wxStaticText* m_staticText44;
		wxComboBox* cmbORX2_ATT;
		wxStaticText* m_staticText432;
		wxComboBox* cmbTX1_ATT;
		wxStaticText* m_staticText441;
		wxComboBox* cmbTX2_ATT;
		wxCheckBox* cbTXRX_1;
		wxCheckBox* cbTXRX_2;
		wxButton* btnApplyData;
		wxButton* btnReadData;
		wxPanel* pnlRFPAL;
		wxPanel* m_panel8;
		wxButton* btnSC1905_Read_FW_Version;
		wxTextCtrl* txtCtrlSC1905_FW_Ver;
		wxButton* btnSC1905_Read_Product_ID;
		wxTextCtrl* txtCtrlSC1905_Product_ID;
		wxStaticText* m_staticText1;
		wxStaticText* m_staticText2;
		wxStaticText* m_staticText4;
		wxTextCtrl* txtCtrlSC1905_Product_Version;
		wxTextCtrl* txtCtrlSC1905_FW_Version;
		wxTextCtrl* txtCtrlSC1905_Frequency_Range;
		wxStaticText* m_staticText11;
		wxStaticText* m_staticText12;
		wxStaticText* m_staticText13;
		wxTextCtrl* txtCtrlSC1905_Operation_Mode;
		wxTextCtrl* txtCtrlSC1905_Min_Frequency;
		wxTextCtrl* txtCtrlSC1905_Max_Frequency;
		wxStaticText* m_staticText111;
		wxStaticText* m_staticText112;
		wxStaticText* m_staticText113;
		wxTextCtrl* txtCtrlSC1905_Duty_Cycle_Feedback;
		wxTextCtrl* txtCtrlSC1905_RFIN_AGC;
		wxTextCtrl* txtCtrlSC1905_RFFB_AGC;
		wxStaticText* m_staticText14;
		wxStaticText* m_staticText41;
		wxTextCtrl* txtCtrlSC1905_Overall_Status;
		wxChoice* chSC1905_Update_Rate;
		wxButton* btnSC1905_Force_Update;
		wxStaticText* m_staticText114;
		wxStaticText* m_staticText121;
		wxTextCtrl* txtCtrlSC1905_Center_Frequency;
		wxTextCtrl* txtCtrlSC1905_24dBc_BW;
		wxButton* btnSC1905_Reset_RFPAL;
		wxStaticText* m_staticText17;
		wxStaticText* m_staticText18;
		wxTextCtrl* txtCtrlSC1905_Error_Code;
		wxTextCtrl* txtCtrlSC1905_Error_Message;
		wxStaticText* m_staticText171;
		wxStaticText* m_staticText172;
		wxTextCtrl* txtCtrlSC1905_Warning_Code;
		wxTextCtrl* txtCtrlSC1905_Warning_Message;
		wxStaticText* m_staticText27;
		wxStaticText* m_staticText241;
		wxGauge* gaugeSC1905_RFIN_AGC;
		wxStaticText* m_staticText251;
		wxGauge* gaugeSC1905_RFFB_AGC;
		wxStaticText* m_staticText261;
		wxGauge* gaugeSC1905_Average_Coeff;
		wxStaticText* m_staticText28;
		wxStaticText* m_staticText29;
		wxStaticText* m_staticText30;
		wxStaticText* m_staticText31;
		wxStaticText* m_staticText32;
		wxTextCtrl* txtCtrlSC1905_RFIN_PMU;
		wxStaticText* m_staticText35;
		wxTextCtrl* txtCtrlSC1905_RFIN_Offset;
		wxStaticText* m_staticText36;
		wxTextCtrl* txtCtrlSC1905_RFIN_Power;
		wxTextCtrl* txtCtrlSC1905_RFFB_PMU;
		wxStaticText* m_staticText351;
		wxTextCtrl* txtCtrlSC1905_RFFB_Offset;
		wxStaticText* m_staticText361;
		wxTextCtrl* txtCtrlSC1905_RFFB_Power;
		wxTextCtrl* txtCtrlSC1905_Average_Coeff_PMU;
		wxNotebook* m_notebook2;
		wxPanel* pnlSC1905_Customer_Controls;
		wxStaticText* m_staticText24;
		wxStaticText* m_staticText25;
		wxStaticText* m_staticText26;
		wxChoice* chSC1905_Frequency_Range;
		wxTextCtrl* txtCtrlSC1905_Set_Min_Frequency;
		wxTextCtrl* txtCtrlSC1905_Set_Max_Frequency;
		wxButton* btnSC1905_Apply_Frequency;
		wxStaticText* m_staticText21;
		wxStaticText* m_staticText22;
		wxStaticText* m_staticText23;
		wxChoice* chSC1905_Set_Duty_Cycle_Feedback;
		wxChoice* chSC1905_Set_Adaptation_State;
		wxChoice* chSC1905_Set_Correction_Enable;
		wxButton* btnSC1905_Clear_Warnings;
		wxStaticText* m_staticText38;
		wxButton* btnSC1905_Set_Cal_Param_A;
		wxTextCtrl* txtCtrlSC1905_Set_Cal_Param_A_CalFreq;
		wxButton* btnSC1905_Set_Cal_Param_B;
		wxTextCtrl* txtCtrlSC1905_Set_Cal_Param_B_CalFreq;
		wxButton* btnSC1905_Clear_Cal_Param;
		wxStaticText* m_staticText37;
		wxButton* btnSC1905_Calibrate_RFIN_PMU;
		wxTextCtrl* txtCtrlSC1905_Calibrate_RFIN_PMU;
		wxButton* btnSC1905_Calibrate_RFFB_PMU;
		wxTextCtrl* txtCtrlSC1905_Calibrate_RFFB_PMU;
		wxStaticText* m_staticText39;
		wxChoice* chSC1905_Guard_Band;
		wxPanel* pnlSC1905_ACCP_Config;
		wxStaticText* m_staticText40;
		wxRadioButton* rbtnSC1905_EEPROM_Write;
		wxStaticText* m_staticText411;
		wxStaticText* m_staticText42;
		wxChoice* chSC1905_Variable_Type;
		wxRadioButton* rbtnSC1905_EEPROM_Read;
		wxTextCtrl* txtCtrlSC1905_EEPROM_Address;
		wxTextCtrl* txtCtrlSC1905_EEPROM_Value;
		wxButton* btnSC1905_EEPROM_Execute;
		wxGrid* gridSC1905_EEPROM_Parameters;
		wxPanel* m_panel173;
		wxTextCtrl* txtMessageField;
		wxPanel* m_panel18;
		wxButton* btnClearMessages;

		// Virtual event handlers, override them in your derived class
		virtual void OnClose_LimeRFE_8001P_view( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnQuit( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnmiLMS8001( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnrbI2CrbUSB( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnbtnRefreshPorts( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnbtnOpenPort( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnbtnClosePort( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnbtnOpen( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnbtnSave( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnbtnReset( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnbtnReadData( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDetailedChange( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEraseBackground_pnlChannel( wxEraseEvent& event ) { event.Skip(); }
		virtual void OnSimpleChanged( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnbtnApplyData( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnbtnSC1905_Read_FW_Version( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnbtnSC1905_Read_Product_ID( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnchSC1905_Update_Rate( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnbtnSC1905_Force_Update( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnbtnSC1905_Reset_RFPAL( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnKillFocustxtCtrlSC1905_RFIN_Offset( wxFocusEvent& event ) { event.Skip(); }
		virtual void OnKillFocustxtCtrlSC1905_RFFB_Offset( wxFocusEvent& event ) { event.Skip(); }
		virtual void OntxtCtrlSC1905_RFFB_Offset( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnchSC1905_Frequency_Range( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnbtnSC1905_Apply_Frequency( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnchSC1905_Set_Duty_Cycle_Feedback( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnchSC1905_Set_Adaptation_State( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnchSC1905_Set_Correction_Enable( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnbtnSC1905_Clear_Warnings( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnbtnSC1905_Set_Cal_Param_A( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnbtnSC1905_Set_Cal_Param( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnbtnSC1905_Clear_Cal_Param( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnbtnSC1905_Calibrate_RFIN_PMU( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnbtnSC1905_Calibrate_RFFB_PMU( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnchSC1905_Guard_Band( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnrbtnSC1905_EEPROM_Write( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnrbtnSC1905_EEPROM_Read( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnbtnSC1905_EEPROM_Execute( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnGridCellChangegridSC1905_EEPROM_Parameters( wxGridEvent& event ) { event.Skip(); }
		virtual void OnbtnClearMessages( wxCommandEvent& event ) { event.Skip(); }


	public:

		LimeRFE_8001P_view( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("LimeRFE_8001P Control"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxCAPTION|wxCLOSE_BOX|wxMINIMIZE_BOX|wxSYSTEM_MENU|wxTAB_TRAVERSAL );

		~LimeRFE_8001P_view();

};

