///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "LimeRFE_8001P_gui.h"

///////////////////////////////////////////////////////////////////////////

LimeRFE_8001P_view::LimeRFE_8001P_view( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );
	this->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );

	mbar = new wxMenuBar( 0 );
	mFile = new wxMenu();
	wxMenuItem* miQuit;
	miQuit = new wxMenuItem( mFile, wxID_ANY, wxString( wxT("&Quit") ) + wxT('\t') + wxT("Alt+F4"), wxEmptyString, wxITEM_NORMAL );
	mFile->Append( miQuit );

	mbar->Append( mFile, wxT("&File") );

	mModules = new wxMenu();
	wxMenuItem* miLMS8001;
	miLMS8001 = new wxMenuItem( mModules, wxID_ANY, wxString( wxT("LMS8001") ) , wxEmptyString, wxITEM_NORMAL );
	mModules->Append( miLMS8001 );

	mbar->Append( mModules, wxT("Modules") );

	this->SetMenuBar( mbar );

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );

	wxFlexGridSizer* fgSizer5;
	fgSizer5 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer5->SetFlexibleDirection( wxBOTH );
	fgSizer5->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	nbMain = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	pnlMain = new wxPanel( nbMain, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	pnlMain->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOWTEXT ) );
	pnlMain->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );

	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer2->SetFlexibleDirection( wxBOTH );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_ALL );

	m_panel15 = new wxPanel( pnlMain, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer15;
	bSizer15 = new wxBoxSizer( wxHORIZONTAL );

	wxStaticBoxSizer* sbSizer31;
	sbSizer31 = new wxStaticBoxSizer( new wxStaticBox( m_panel15, wxID_ANY, wxT("Communication") ), wxHORIZONTAL );

	wxBoxSizer* bSizer21;
	bSizer21 = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizer19;
	bSizer19 = new wxBoxSizer( wxVERTICAL );

	rbI2C = new wxRadioButton( sbSizer31->GetStaticBox(), wxID_ANY, wxT("SDR"), wxDefaultPosition, wxSize( -1,-1 ), wxRB_GROUP );
	rbI2C->SetValue( true );
	bSizer19->Add( rbI2C, 0, wxALL, 1 );


	bSizer21->Add( bSizer19, 1, wxEXPAND, 0 );

	wxBoxSizer* bSizer20;
	bSizer20 = new wxBoxSizer( wxVERTICAL );

	rbUSB = new wxRadioButton( sbSizer31->GetStaticBox(), wxID_ANY, wxT("Direct (USB)"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	bSizer20->Add( rbUSB, 0, wxALL, 1 );


	bSizer21->Add( bSizer20, 1, wxEXPAND, 0 );


	sbSizer31->Add( bSizer21, 1, wxEXPAND, 0 );


	bSizer15->Add( sbSizer31, 1, wxEXPAND, 1 );


	m_panel15->SetSizer( bSizer15 );
	m_panel15->Layout();
	bSizer15->Fit( m_panel15 );
	fgSizer2->Add( m_panel15, 1, wxEXPAND | wxALL, 2 );

	m_panel161 = new wxPanel( pnlMain, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxHORIZONTAL );

	wxStaticBoxSizer* sbSizer3;
	sbSizer3 = new wxStaticBoxSizer( new wxStaticBox( m_panel161, wxID_ANY, wxT("USB") ), wxHORIZONTAL );

	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxVERTICAL );

	cmbbPorts = new wxComboBox( sbSizer3->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0, NULL, 0 );
	cmbbPorts->SetMaxSize( wxSize( 160,-1 ) );

	bSizer13->Add( cmbbPorts, 0, wxALL|wxEXPAND, 1 );


	bSizer12->Add( bSizer13, 1, wxEXPAND, 0 );

	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxVERTICAL );

	btnRefreshPorts = new wxButton( sbSizer3->GetStaticBox(), wxID_ANY, wxT("Refresh"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	bSizer14->Add( btnRefreshPorts, 0, wxALL, 1 );


	bSizer12->Add( bSizer14, 1, wxEXPAND, 0 );


	sbSizer3->Add( bSizer12, 1, wxEXPAND, 0 );


	bSizer9->Add( sbSizer3, 1, wxEXPAND, 0 );

	wxStaticBoxSizer* sbSizer18;
	sbSizer18 = new wxStaticBoxSizer( new wxStaticBox( m_panel161, wxID_ANY, wxT("Port") ), wxHORIZONTAL );

	wxBoxSizer* bSizer211;
	bSizer211 = new wxBoxSizer( wxVERTICAL );

	btnOpenPort = new wxButton( sbSizer18->GetStaticBox(), wxID_ANY, wxT("Open"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	bSizer211->Add( btnOpenPort, 0, wxALL, 1 );


	sbSizer18->Add( bSizer211, 1, wxEXPAND, 0 );

	wxBoxSizer* bSizer22;
	bSizer22 = new wxBoxSizer( wxVERTICAL );

	btnClosePort = new wxButton( sbSizer18->GetStaticBox(), wxID_ANY, wxT("Close"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	bSizer22->Add( btnClosePort, 0, wxALL, 1 );


	sbSizer18->Add( bSizer22, 1, wxEXPAND, 0 );


	bSizer9->Add( sbSizer18, 1, wxEXPAND, 0 );


	m_panel161->SetSizer( bSizer9 );
	m_panel161->Layout();
	bSizer9->Fit( m_panel161 );
	fgSizer2->Add( m_panel161, 1, wxEXPAND | wxALL, 2 );

	m_panel172 = new wxPanel( pnlMain, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxHORIZONTAL );

	wxStaticBoxSizer* sbSizer21;
	sbSizer21 = new wxStaticBoxSizer( new wxStaticBox( m_panel172, wxID_ANY, wxT("Configuration") ), wxHORIZONTAL );

	wxBoxSizer* bSizer23;
	bSizer23 = new wxBoxSizer( wxVERTICAL );

	btnOpen = new wxButton( sbSizer21->GetStaticBox(), wxID_ANY, wxT("Open"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	bSizer23->Add( btnOpen, 0, wxALL, 1 );


	sbSizer21->Add( bSizer23, 1, wxEXPAND, 0 );

	wxBoxSizer* bSizer25;
	bSizer25 = new wxBoxSizer( wxVERTICAL );

	btnSave = new wxButton( sbSizer21->GetStaticBox(), wxID_ANY, wxT("Save"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	bSizer25->Add( btnSave, 0, wxALL, 1 );


	sbSizer21->Add( bSizer25, 1, wxEXPAND, 0 );


	bSizer7->Add( sbSizer21, 1, wxEXPAND, 0 );

	wxStaticBoxSizer* sbSizer2;
	sbSizer2 = new wxStaticBoxSizer( new wxStaticBox( m_panel172, wxID_ANY, wxT("Synchronize") ), wxHORIZONTAL );

	wxBoxSizer* bSizer26;
	bSizer26 = new wxBoxSizer( wxVERTICAL );

	btnReset = new wxButton( sbSizer2->GetStaticBox(), wxID_ANY, wxT("Reset"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	bSizer26->Add( btnReset, 0, wxALL, 1 );


	sbSizer2->Add( bSizer26, 1, wxEXPAND, 0 );

	wxBoxSizer* bSizer27;
	bSizer27 = new wxBoxSizer( wxVERTICAL );

	btnBoard2GUI = new wxButton( sbSizer2->GetStaticBox(), wxID_ANY, wxT("Board->GUI"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	bSizer27->Add( btnBoard2GUI, 0, wxALL, 1 );


	sbSizer2->Add( bSizer27, 1, wxEXPAND, 0 );


	bSizer7->Add( sbSizer2, 1, wxEXPAND, 0 );


	m_panel172->SetSizer( bSizer7 );
	m_panel172->Layout();
	bSizer7->Fit( m_panel172 );
	fgSizer2->Add( m_panel172, 1, wxALL|wxEXPAND, 2 );

	m_panel13 = new wxPanel( pnlMain, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_RAISED|wxTAB_TRAVERSAL );
	wxFlexGridSizer* fgSizer18;
	fgSizer18 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer18->SetFlexibleDirection( wxBOTH );
	fgSizer18->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	wxStaticBoxSizer* sbSizer20;
	sbSizer20 = new wxStaticBoxSizer( new wxStaticBox( m_panel13, wxID_ANY, wxT("Which channel is controlled in GUI") ), wxVERTICAL );

	wxBoxSizer* bSizer241;
	bSizer241 = new wxBoxSizer( wxVERTICAL );

	wxGridSizer* gSizer13;
	gSizer13 = new wxGridSizer( 0, 2, 0, 0 );

	cmbChannel = new wxComboBox( sbSizer20->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	cmbChannel->Append( wxT("Channel 1") );
	cmbChannel->Append( wxT("Channel 2") );
	cmbChannel->SetSelection( 0 );
	gSizer13->Add( cmbChannel, 0, wxALL, 5 );


	bSizer241->Add( gSizer13, 1, wxEXPAND, 5 );


	sbSizer20->Add( bSizer241, 1, wxEXPAND, 5 );


	fgSizer18->Add( sbSizer20, 1, wxEXPAND, 5 );

	m_notebook3 = new wxNotebook( m_panel13, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_panel131 = new wxPanel( m_notebook3, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxStaticBoxSizer* sbSizer191;
	sbSizer191 = new wxStaticBoxSizer( new wxStaticBox( m_panel131, wxID_ANY, wxT("Data") ), wxVERTICAL );

	wxFlexGridSizer* fgSizer19;
	fgSizer19 = new wxFlexGridSizer( 2, 0, 0, 0 );
	fgSizer19->SetFlexibleDirection( wxBOTH );
	fgSizer19->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	wxBoxSizer* bSizer32;
	bSizer32 = new wxBoxSizer( wxVERTICAL );

	pnlChannel = new wxPanel( sbSizer191->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	pnlChannel->SetMinSize( wxSize( 700,221 ) );

	bSizer32->Add( pnlChannel, 1, wxEXPAND | wxALL, 5 );


	fgSizer19->Add( bSizer32, 1, wxEXPAND, 5 );

	wxGridSizer* gSizer1211;
	gSizer1211 = new wxGridSizer( 0, 4, 0, 0 );

	wxBoxSizer* bSizer2011;
	bSizer2011 = new wxBoxSizer( wxVERTICAL );

	cbBP_AMPX = new wxCheckBox( sbSizer191->GetStaticBox(), wxID_ANY, wxT("Bypass AMP"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2011->Add( cbBP_AMPX, 0, wxALL, 2 );

	cbSD_AMPX = new wxCheckBox( sbSizer191->GetStaticBox(), wxID_ANY, wxT("Disable AMP"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2011->Add( cbSD_AMPX, 0, wxALL, 2 );


	gSizer1211->Add( bSizer2011, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer2121;
	bSizer2121 = new wxBoxSizer( wxVERTICAL );

	cbSC1905_X_RESETn = new wxCheckBox( sbSizer191->GetStaticBox(), wxID_ANY, wxT("SC1905 Enable"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2121->Add( cbSC1905_X_RESETn, 0, wxALL, 2 );

	cbLMS8001_X_RESETn = new wxCheckBox( sbSizer191->GetStaticBox(), wxID_ANY, wxT("LMS8001 Enable"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2121->Add( cbLMS8001_X_RESETn, 0, wxALL, 2 );

	m_staticText4311 = new wxStaticText( sbSizer191->GetStaticBox(), wxID_ANY, wxT("TX Attenuation [dB]"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4311->Wrap( -1 );
	bSizer2121->Add( m_staticText4311, 0, wxALL, 2 );

	cmbTXX_ATT = new wxComboBox( sbSizer191->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY );
	bSizer2121->Add( cmbTXX_ATT, 0, wxALL, 2 );


	gSizer1211->Add( bSizer2121, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer2211;
	bSizer2211 = new wxBoxSizer( wxVERTICAL );

	cbPDAX_EN = new wxCheckBox( sbSizer191->GetStaticBox(), wxID_ANY, wxT("PDA Enable"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2211->Add( cbPDAX_EN, 0, wxALL, 2 );

	cbLNAX_EN = new wxCheckBox( sbSizer191->GetStaticBox(), wxID_ANY, wxT("LNA Enable"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2211->Add( cbLNAX_EN, 0, wxALL, 2 );

	m_staticText431 = new wxStaticText( sbSizer191->GetStaticBox(), wxID_ANY, wxT("ORX Attenuation [dB]"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText431->Wrap( -1 );
	bSizer2211->Add( m_staticText431, 0, wxALL, 2 );

	cmbORXX_ATT = new wxComboBox( sbSizer191->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY );
	bSizer2211->Add( cmbORXX_ATT, 0, wxALL, 2 );


	gSizer1211->Add( bSizer2211, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer28;
	bSizer28 = new wxBoxSizer( wxVERTICAL );

	cbDAX_X_EN = new wxCheckBox( sbSizer191->GetStaticBox(), wxID_ANY, wxT("DA Enable"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer28->Add( cbDAX_X_EN, 0, wxALL, 2 );

	cbDAX_A_B_CTRL = new wxCheckBox( sbSizer191->GetStaticBox(), wxID_ANY, wxT("A/B (0 - B; 1 - A)"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer28->Add( cbDAX_A_B_CTRL, 0, wxALL, 2 );

	cbTXRX_X = new wxCheckBox( sbSizer191->GetStaticBox(), wxID_ANY, wxT("TX/RX (0 - RX; 1 - TX)"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer28->Add( cbTXRX_X, 0, wxALL, 2 );


	gSizer1211->Add( bSizer28, 1, wxEXPAND, 5 );


	fgSizer19->Add( gSizer1211, 1, wxEXPAND, 5 );


	sbSizer191->Add( fgSizer19, 1, wxEXPAND, 5 );


	m_panel131->SetSizer( sbSizer191 );
	m_panel131->Layout();
	sbSizer191->Fit( m_panel131 );
	m_notebook3->AddPage( m_panel131, wxT("Simple"), true );
	m_panel14 = new wxPanel( m_notebook3, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxStaticBoxSizer* sbSizer19;
	sbSizer19 = new wxStaticBoxSizer( new wxStaticBox( m_panel14, wxID_ANY, wxT("Data") ), wxVERTICAL );

	wxGridSizer* gSizer121;
	gSizer121 = new wxGridSizer( 0, 4, 0, 0 );

	wxBoxSizer* bSizer191;
	bSizer191 = new wxBoxSizer( wxVERTICAL );

	cbSPI_2_MCU_DIR_OUT_in = new wxCheckBox( sbSizer19->GetStaticBox(), wxID_ANY, wxT("SPI_2_MCU_DIR_OUT_in"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer191->Add( cbSPI_2_MCU_DIR_OUT_in, 0, wxALL, 2 );

	cbLMS8001_1_SSENn = new wxCheckBox( sbSizer19->GetStaticBox(), wxID_ANY, wxT("LMS8001_#1_SSENn"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer191->Add( cbLMS8001_1_SSENn, 0, wxALL, 2 );

	cbLMS8001_2_SSENn = new wxCheckBox( sbSizer19->GetStaticBox(), wxID_ANY, wxT("LMS8001_#2_SSENn"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer191->Add( cbLMS8001_2_SSENn, 0, wxALL, 2 );

	cbEXT_PLL_SSENn = new wxCheckBox( sbSizer19->GetStaticBox(), wxID_ANY, wxT("EXT_PLL_SSENn"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer191->Add( cbEXT_PLL_SSENn, 0, wxALL, 2 );

	cbLMS8001_1_RESETn = new wxCheckBox( sbSizer19->GetStaticBox(), wxID_ANY, wxT("LMS8001_#1_RESETn"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer191->Add( cbLMS8001_1_RESETn, 0, wxALL, 2 );

	cbLMS8001_2_RESETn = new wxCheckBox( sbSizer19->GetStaticBox(), wxID_ANY, wxT("LMS8001_#2_RESETn"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer191->Add( cbLMS8001_2_RESETn, 0, wxALL, 2 );

	cbSC1905_1_SSENn = new wxCheckBox( sbSizer19->GetStaticBox(), wxID_ANY, wxT("SC1905_#1_SSENn"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer191->Add( cbSC1905_1_SSENn, 0, wxALL, 2 );

	cbSC1905_2_SSENn = new wxCheckBox( sbSizer19->GetStaticBox(), wxID_ANY, wxT("SC1905_#2_SSENn"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer191->Add( cbSC1905_2_SSENn, 0, wxALL, 2 );

	cbSC1905_1_RESETn = new wxCheckBox( sbSizer19->GetStaticBox(), wxID_ANY, wxT("SC1905_#1_RESETn"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer191->Add( cbSC1905_1_RESETn, 0, wxALL, 2 );

	cbSC1905_2_RESETn = new wxCheckBox( sbSizer19->GetStaticBox(), wxID_ANY, wxT("SC1905_#2_RESETn"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer191->Add( cbSC1905_2_RESETn, 0, wxALL, 2 );


	gSizer121->Add( bSizer191, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer201;
	bSizer201 = new wxBoxSizer( wxVERTICAL );

	cbBP_AMP1 = new wxCheckBox( sbSizer19->GetStaticBox(), wxID_ANY, wxT("BP_AMP1"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer201->Add( cbBP_AMP1, 0, wxALL, 2 );

	cbSD_AMP1 = new wxCheckBox( sbSizer19->GetStaticBox(), wxID_ANY, wxT("SD_AMP1"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer201->Add( cbSD_AMP1, 0, wxALL, 2 );

	cbBP_AMP2 = new wxCheckBox( sbSizer19->GetStaticBox(), wxID_ANY, wxT("BP_AMP2"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer201->Add( cbBP_AMP2, 0, wxALL, 2 );

	cbSD_AMP2 = new wxCheckBox( sbSizer19->GetStaticBox(), wxID_ANY, wxT("SD_AMP2"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer201->Add( cbSD_AMP2, 0, wxALL, 2 );

	cbDA1_A_EN = new wxCheckBox( sbSizer19->GetStaticBox(), wxID_ANY, wxT("DA1_A_EN"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer201->Add( cbDA1_A_EN, 0, wxALL, 2 );

	cbDA1_B_EN = new wxCheckBox( sbSizer19->GetStaticBox(), wxID_ANY, wxT("DA1_B_EN"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer201->Add( cbDA1_B_EN, 0, wxALL, 2 );

	cbDA2_A_EN = new wxCheckBox( sbSizer19->GetStaticBox(), wxID_ANY, wxT("DA2_A_EN"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer201->Add( cbDA2_A_EN, 0, wxALL, 2 );

	cbDA2_B_EN = new wxCheckBox( sbSizer19->GetStaticBox(), wxID_ANY, wxT("DA2_B_EN"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer201->Add( cbDA2_B_EN, 0, wxALL, 2 );

	cbLNA1_EN = new wxCheckBox( sbSizer19->GetStaticBox(), wxID_ANY, wxT("LNA1_EN"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer201->Add( cbLNA1_EN, 0, wxALL, 2 );

	cbLNA2_EN = new wxCheckBox( sbSizer19->GetStaticBox(), wxID_ANY, wxT("LNA2_EN"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer201->Add( cbLNA2_EN, 0, wxALL, 2 );


	gSizer121->Add( bSizer201, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer212;
	bSizer212 = new wxBoxSizer( wxVERTICAL );

	cbPDA1_EN = new wxCheckBox( sbSizer19->GetStaticBox(), wxID_ANY, wxT("PDA1_EN"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer212->Add( cbPDA1_EN, 0, wxALL, 2 );

	cbPDA2_EN = new wxCheckBox( sbSizer19->GetStaticBox(), wxID_ANY, wxT("PDA2_EN"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer212->Add( cbPDA2_EN, 0, wxALL, 2 );

	cbDA1_A_B_CTRL = new wxCheckBox( sbSizer19->GetStaticBox(), wxID_ANY, wxT("DA1_A_B_CTRL"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer212->Add( cbDA1_A_B_CTRL, 0, wxALL, 2 );

	cbDA2_A_B_CTRL = new wxCheckBox( sbSizer19->GetStaticBox(), wxID_ANY, wxT("DA2_A_B_CTRL"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer212->Add( cbDA2_A_B_CTRL, 0, wxALL, 2 );

	m_staticText43 = new wxStaticText( sbSizer19->GetStaticBox(), wxID_ANY, wxT("ORX1 Att. [dB]"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText43->Wrap( -1 );
	bSizer212->Add( m_staticText43, 0, wxALL, 2 );

	cmbORX1_ATT = new wxComboBox( sbSizer19->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY );
	bSizer212->Add( cmbORX1_ATT, 0, wxALL, 2 );

	m_staticText44 = new wxStaticText( sbSizer19->GetStaticBox(), wxID_ANY, wxT("ORX2 Att. [dB]"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText44->Wrap( -1 );
	bSizer212->Add( m_staticText44, 0, wxALL, 2 );

	cmbORX2_ATT = new wxComboBox( sbSizer19->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY );
	bSizer212->Add( cmbORX2_ATT, 0, wxALL, 2 );

	m_staticText432 = new wxStaticText( sbSizer19->GetStaticBox(), wxID_ANY, wxT("TX1 Att. [dB]"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText432->Wrap( -1 );
	bSizer212->Add( m_staticText432, 0, wxALL, 2 );

	cmbTX1_ATT = new wxComboBox( sbSizer19->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY );
	bSizer212->Add( cmbTX1_ATT, 0, wxALL, 2 );

	m_staticText441 = new wxStaticText( sbSizer19->GetStaticBox(), wxID_ANY, wxT("TX2 Att. [dB]"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText441->Wrap( -1 );
	bSizer212->Add( m_staticText441, 0, wxALL, 2 );

	cmbTX2_ATT = new wxComboBox( sbSizer19->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY );
	bSizer212->Add( cmbTX2_ATT, 0, wxALL, 2 );


	gSizer121->Add( bSizer212, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer221;
	bSizer221 = new wxBoxSizer( wxVERTICAL );

	cbTXRX_1 = new wxCheckBox( sbSizer19->GetStaticBox(), wxID_ANY, wxT("TXRX_1"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer221->Add( cbTXRX_1, 0, wxALL, 2 );

	cbTXRX_2 = new wxCheckBox( sbSizer19->GetStaticBox(), wxID_ANY, wxT("TXRX_2"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer221->Add( cbTXRX_2, 0, wxALL, 2 );


	gSizer121->Add( bSizer221, 1, wxEXPAND, 5 );


	sbSizer19->Add( gSizer121, 1, wxEXPAND, 5 );


	m_panel14->SetSizer( sbSizer19 );
	m_panel14->Layout();
	sbSizer19->Fit( m_panel14 );
	m_notebook3->AddPage( m_panel14, wxT("Detailed"), false );

	fgSizer18->Add( m_notebook3, 1, wxEXPAND | wxALL, 5 );

	wxGridSizer* gSizer14;
	gSizer14 = new wxGridSizer( 0, 2, 0, 0 );

	btnApplyData = new wxButton( m_panel13, wxID_ANY, wxT("Apply"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer14->Add( btnApplyData, 0, wxALL|wxEXPAND, 1 );

	btnReadData = new wxButton( m_panel13, wxID_ANY, wxT("Read"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer14->Add( btnReadData, 0, wxALL|wxEXPAND, 1 );


	fgSizer18->Add( gSizer14, 1, wxEXPAND, 0 );


	m_panel13->SetSizer( fgSizer18 );
	m_panel13->Layout();
	fgSizer18->Fit( m_panel13 );
	fgSizer2->Add( m_panel13, 1, wxEXPAND | wxALL, 2 );


	pnlMain->SetSizer( fgSizer2 );
	pnlMain->Layout();
	fgSizer2->Fit( pnlMain );
	nbMain->AddPage( pnlMain, wxT("Main"), true );
	pnlRFPAL = new wxPanel( nbMain, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxFlexGridSizer* fgSizer6;
	fgSizer6 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer6->SetFlexibleDirection( wxBOTH );
	fgSizer6->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_panel8 = new wxPanel( pnlRFPAL, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_RAISED|wxTAB_TRAVERSAL );
	m_panel8->Hide();

	wxStaticBoxSizer* sbSizer7;
	sbSizer7 = new wxStaticBoxSizer( new wxStaticBox( m_panel8, wxID_ANY, wxT("SC1905 Test") ), wxVERTICAL );

	wxFlexGridSizer* fgSizer4;
	fgSizer4 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer4->SetFlexibleDirection( wxBOTH );
	fgSizer4->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	btnSC1905_Read_FW_Version = new wxButton( sbSizer7->GetStaticBox(), wxID_ANY, wxT("Read FW Ver"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer4->Add( btnSC1905_Read_FW_Version, 0, wxALL|wxEXPAND, 5 );

	txtCtrlSC1905_FW_Ver = new wxTextCtrl( sbSizer7->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer4->Add( txtCtrlSC1905_FW_Ver, 0, wxALL, 5 );

	btnSC1905_Read_Product_ID = new wxButton( sbSizer7->GetStaticBox(), wxID_ANY, wxT("Read Product ID"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer4->Add( btnSC1905_Read_Product_ID, 0, wxALL, 5 );

	txtCtrlSC1905_Product_ID = new wxTextCtrl( sbSizer7->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer4->Add( txtCtrlSC1905_Product_ID, 0, wxALL, 5 );


	sbSizer7->Add( fgSizer4, 1, wxEXPAND, 5 );


	m_panel8->SetSizer( sbSizer7 );
	m_panel8->Layout();
	sbSizer7->Fit( m_panel8 );
	fgSizer6->Add( m_panel8, 1, wxEXPAND, 1 );

	wxFlexGridSizer* fgSizer7;
	fgSizer7 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer7->SetFlexibleDirection( wxHORIZONTAL );
	fgSizer7->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	wxFlexGridSizer* fgSizer9;
	fgSizer9 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer9->SetFlexibleDirection( wxBOTH );
	fgSizer9->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	wxStaticBoxSizer* sbSizer8;
	sbSizer8 = new wxStaticBoxSizer( new wxStaticBox( pnlRFPAL, wxID_ANY, wxT("IC Configuration") ), wxVERTICAL );

	wxGridSizer* gSizer1;
	gSizer1 = new wxGridSizer( 0, 3, 0, 0 );

	m_staticText1 = new wxStaticText( sbSizer8->GetStaticBox(), wxID_ANY, wxT("Product Version"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL );
	m_staticText1->Wrap( -1 );
	gSizer1->Add( m_staticText1, 0, wxALIGN_CENTER|wxALL, 0 );

	m_staticText2 = new wxStaticText( sbSizer8->GetStaticBox(), wxID_ANY, wxT("FW Version"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL );
	m_staticText2->Wrap( -1 );
	gSizer1->Add( m_staticText2, 0, wxALIGN_CENTER|wxALL, 0 );

	m_staticText4 = new wxStaticText( sbSizer8->GetStaticBox(), wxID_ANY, wxT("Frequency Range"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL );
	m_staticText4->Wrap( -1 );
	gSizer1->Add( m_staticText4, 0, wxALIGN_CENTER|wxALL, 0 );

	txtCtrlSC1905_Product_Version = new wxTextCtrl( sbSizer8->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	txtCtrlSC1905_Product_Version->Enable( false );

	gSizer1->Add( txtCtrlSC1905_Product_Version, 0, wxALL|wxEXPAND, 0 );

	txtCtrlSC1905_FW_Version = new wxTextCtrl( sbSizer8->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	txtCtrlSC1905_FW_Version->Enable( false );

	gSizer1->Add( txtCtrlSC1905_FW_Version, 0, wxALL|wxEXPAND, 0 );

	txtCtrlSC1905_Frequency_Range = new wxTextCtrl( sbSizer8->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	txtCtrlSC1905_Frequency_Range->Enable( false );

	gSizer1->Add( txtCtrlSC1905_Frequency_Range, 0, wxALL|wxEXPAND, 0 );

	m_staticText11 = new wxStaticText( sbSizer8->GetStaticBox(), wxID_ANY, wxT("Operation Mode"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL );
	m_staticText11->Wrap( -1 );
	gSizer1->Add( m_staticText11, 0, wxALIGN_CENTER|wxALL, 0 );

	m_staticText12 = new wxStaticText( sbSizer8->GetStaticBox(), wxID_ANY, wxT("Min Frequency"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL );
	m_staticText12->Wrap( -1 );
	gSizer1->Add( m_staticText12, 0, wxALIGN_CENTER|wxALL, 0 );

	m_staticText13 = new wxStaticText( sbSizer8->GetStaticBox(), wxID_ANY, wxT("Max Frequency"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL );
	m_staticText13->Wrap( -1 );
	gSizer1->Add( m_staticText13, 0, wxALIGN_CENTER|wxALL, 0 );

	txtCtrlSC1905_Operation_Mode = new wxTextCtrl( sbSizer8->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	txtCtrlSC1905_Operation_Mode->Enable( false );

	gSizer1->Add( txtCtrlSC1905_Operation_Mode, 0, wxALL|wxEXPAND, 0 );

	txtCtrlSC1905_Min_Frequency = new wxTextCtrl( sbSizer8->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	txtCtrlSC1905_Min_Frequency->Enable( false );

	gSizer1->Add( txtCtrlSC1905_Min_Frequency, 0, wxALL|wxEXPAND, 0 );

	txtCtrlSC1905_Max_Frequency = new wxTextCtrl( sbSizer8->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	txtCtrlSC1905_Max_Frequency->Enable( false );

	gSizer1->Add( txtCtrlSC1905_Max_Frequency, 0, wxALL|wxEXPAND, 0 );

	m_staticText111 = new wxStaticText( sbSizer8->GetStaticBox(), wxID_ANY, wxT("Duty Cycled Feedback"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL );
	m_staticText111->Wrap( -1 );
	gSizer1->Add( m_staticText111, 0, wxALIGN_CENTER|wxALL, 0 );

	m_staticText112 = new wxStaticText( sbSizer8->GetStaticBox(), wxID_ANY, wxT("RFIN AGC(PDET)"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL );
	m_staticText112->Wrap( -1 );
	gSizer1->Add( m_staticText112, 0, wxALIGN_CENTER|wxALL, 0 );

	m_staticText113 = new wxStaticText( sbSizer8->GetStaticBox(), wxID_ANY, wxT("RFFB_AGC"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL );
	m_staticText113->Wrap( -1 );
	gSizer1->Add( m_staticText113, 0, wxALIGN_CENTER|wxALL, 0 );

	txtCtrlSC1905_Duty_Cycle_Feedback = new wxTextCtrl( sbSizer8->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	txtCtrlSC1905_Duty_Cycle_Feedback->Enable( false );

	gSizer1->Add( txtCtrlSC1905_Duty_Cycle_Feedback, 0, wxALL|wxEXPAND, 0 );

	txtCtrlSC1905_RFIN_AGC = new wxTextCtrl( sbSizer8->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	txtCtrlSC1905_RFIN_AGC->Enable( false );

	gSizer1->Add( txtCtrlSC1905_RFIN_AGC, 0, wxALL|wxEXPAND, 0 );

	txtCtrlSC1905_RFFB_AGC = new wxTextCtrl( sbSizer8->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	txtCtrlSC1905_RFFB_AGC->Enable( false );

	gSizer1->Add( txtCtrlSC1905_RFFB_AGC, 0, wxALL|wxEXPAND, 0 );


	sbSizer8->Add( gSizer1, 1, wxEXPAND, 1 );


	fgSizer9->Add( sbSizer8, 1, wxEXPAND, 1 );

	wxStaticBoxSizer* sbSizer81;
	sbSizer81 = new wxStaticBoxSizer( new wxStaticBox( pnlRFPAL, wxID_ANY, wxT("Status") ), wxVERTICAL );

	wxGridSizer* gSizer11;
	gSizer11 = new wxGridSizer( 0, 3, 0, 0 );

	m_staticText14 = new wxStaticText( sbSizer81->GetStaticBox(), wxID_ANY, wxT("Overall Status"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL );
	m_staticText14->Wrap( -1 );
	gSizer11->Add( m_staticText14, 0, wxALIGN_CENTER|wxALL, 0 );

	m_staticText41 = new wxStaticText( sbSizer81->GetStaticBox(), wxID_ANY, wxT("Update Rate"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL );
	m_staticText41->Wrap( -1 );
	gSizer11->Add( m_staticText41, 0, wxALIGN_CENTER|wxALL, 0 );


	gSizer11->Add( 0, 0, 1, wxEXPAND, 0 );

	txtCtrlSC1905_Overall_Status = new wxTextCtrl( sbSizer81->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	txtCtrlSC1905_Overall_Status->Enable( false );

	gSizer11->Add( txtCtrlSC1905_Overall_Status, 0, wxALL|wxEXPAND, 0 );

	wxString chSC1905_Update_RateChoices[] = { wxT("No refresh"), wxT("0.5 seconds"), wxT("1 second") };
	int chSC1905_Update_RateNChoices = sizeof( chSC1905_Update_RateChoices ) / sizeof( wxString );
	chSC1905_Update_Rate = new wxChoice( sbSizer81->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, chSC1905_Update_RateNChoices, chSC1905_Update_RateChoices, 0 );
	chSC1905_Update_Rate->SetSelection( 0 );
	gSizer11->Add( chSC1905_Update_Rate, 0, wxALL|wxEXPAND, 0 );

	btnSC1905_Force_Update = new wxButton( sbSizer81->GetStaticBox(), wxID_ANY, wxT("Force Update"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer11->Add( btnSC1905_Force_Update, 0, wxALL|wxEXPAND, 0 );

	m_staticText114 = new wxStaticText( sbSizer81->GetStaticBox(), wxID_ANY, wxT("Center Frequency [MHz]"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL );
	m_staticText114->Wrap( -1 );
	gSizer11->Add( m_staticText114, 0, wxALIGN_CENTER|wxALL, 0 );

	m_staticText121 = new wxStaticText( sbSizer81->GetStaticBox(), wxID_ANY, wxT("24dBc BW [MHz]"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL );
	m_staticText121->Wrap( -1 );
	gSizer11->Add( m_staticText121, 0, wxALIGN_CENTER|wxALL, 0 );


	gSizer11->Add( 0, 0, 1, wxEXPAND, 0 );

	txtCtrlSC1905_Center_Frequency = new wxTextCtrl( sbSizer81->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	txtCtrlSC1905_Center_Frequency->Enable( false );

	gSizer11->Add( txtCtrlSC1905_Center_Frequency, 0, wxALL|wxEXPAND, 0 );

	txtCtrlSC1905_24dBc_BW = new wxTextCtrl( sbSizer81->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	txtCtrlSC1905_24dBc_BW->Enable( false );

	gSizer11->Add( txtCtrlSC1905_24dBc_BW, 0, wxALL|wxEXPAND, 0 );

	btnSC1905_Reset_RFPAL = new wxButton( sbSizer81->GetStaticBox(), wxID_ANY, wxT("Reset RFPAL"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer11->Add( btnSC1905_Reset_RFPAL, 0, wxALL|wxEXPAND, 0 );


	sbSizer81->Add( gSizer11, 1, wxEXPAND, 1 );

	wxFlexGridSizer* fgSizer8;
	fgSizer8 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer8->AddGrowableCol( 1 );
	fgSizer8->SetFlexibleDirection( wxBOTH );
	fgSizer8->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticText17 = new wxStaticText( sbSizer81->GetStaticBox(), wxID_ANY, wxT("Error Code"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText17->Wrap( -1 );
	fgSizer8->Add( m_staticText17, 0, wxALIGN_CENTER|wxALL, 0 );

	m_staticText18 = new wxStaticText( sbSizer81->GetStaticBox(), wxID_ANY, wxT("Error Message"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText18->Wrap( -1 );
	fgSizer8->Add( m_staticText18, 0, wxALIGN_CENTER|wxALL, 0 );

	txtCtrlSC1905_Error_Code = new wxTextCtrl( sbSizer81->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 126,-1 ), 0 );
	txtCtrlSC1905_Error_Code->Enable( false );

	fgSizer8->Add( txtCtrlSC1905_Error_Code, 0, wxALL, 0 );

	txtCtrlSC1905_Error_Message = new wxTextCtrl( sbSizer81->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	txtCtrlSC1905_Error_Message->Enable( false );

	fgSizer8->Add( txtCtrlSC1905_Error_Message, 0, wxALL|wxEXPAND, 0 );

	m_staticText171 = new wxStaticText( sbSizer81->GetStaticBox(), wxID_ANY, wxT("Warning Code"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText171->Wrap( -1 );
	fgSizer8->Add( m_staticText171, 0, wxALIGN_CENTER|wxALL, 0 );

	m_staticText172 = new wxStaticText( sbSizer81->GetStaticBox(), wxID_ANY, wxT("Warning Message"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText172->Wrap( -1 );
	fgSizer8->Add( m_staticText172, 0, wxALIGN_CENTER|wxALL, 0 );

	txtCtrlSC1905_Warning_Code = new wxTextCtrl( sbSizer81->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 126,-1 ), 0 );
	txtCtrlSC1905_Warning_Code->Enable( false );

	fgSizer8->Add( txtCtrlSC1905_Warning_Code, 0, wxALL|wxEXPAND, 0 );

	txtCtrlSC1905_Warning_Message = new wxTextCtrl( sbSizer81->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	txtCtrlSC1905_Warning_Message->Enable( false );

	fgSizer8->Add( txtCtrlSC1905_Warning_Message, 0, wxALL|wxEXPAND, 0 );


	sbSizer81->Add( fgSizer8, 1, wxEXPAND, 1 );


	fgSizer9->Add( sbSizer81, 1, wxEXPAND, 1 );

	wxStaticBoxSizer* sbSizer13;
	sbSizer13 = new wxStaticBoxSizer( new wxStaticBox( pnlRFPAL, wxID_ANY, wxT("RF") ), wxVERTICAL );

	wxFlexGridSizer* fgSizer12;
	fgSizer12 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer12->SetFlexibleDirection( wxBOTH );
	fgSizer12->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	wxFlexGridSizer* fgSizer13;
	fgSizer13 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer13->SetFlexibleDirection( wxBOTH );
	fgSizer13->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );


	fgSizer13->Add( 0, 0, 1, wxEXPAND, 1 );

	m_staticText27 = new wxStaticText( sbSizer13->GetStaticBox(), wxID_ANY, wxT("AGC"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText27->Wrap( -1 );
	fgSizer13->Add( m_staticText27, 0, wxALL, 2 );

	m_staticText241 = new wxStaticText( sbSizer13->GetStaticBox(), wxID_ANY, wxT("RFIN Power [dBm]"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText241->Wrap( -1 );
	fgSizer13->Add( m_staticText241, 0, wxALIGN_CENTER_VERTICAL|wxALL, 2 );

	gaugeSC1905_RFIN_AGC = new wxGauge( sbSizer13->GetStaticBox(), wxID_ANY, 100, wxDefaultPosition, wxSize( 80,-1 ), wxGA_HORIZONTAL );
	gaugeSC1905_RFIN_AGC->SetValue( 0 );
	fgSizer13->Add( gaugeSC1905_RFIN_AGC, 0, wxALL, 6 );

	m_staticText251 = new wxStaticText( sbSizer13->GetStaticBox(), wxID_ANY, wxT("RFFB Power [dBm]"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText251->Wrap( -1 );
	fgSizer13->Add( m_staticText251, 0, wxALIGN_CENTER_VERTICAL|wxALL, 2 );

	gaugeSC1905_RFFB_AGC = new wxGauge( sbSizer13->GetStaticBox(), wxID_ANY, 100, wxDefaultPosition, wxSize( 80,-1 ), wxGA_HORIZONTAL );
	gaugeSC1905_RFFB_AGC->SetValue( 0 );
	fgSizer13->Add( gaugeSC1905_RFFB_AGC, 0, wxALIGN_CENTER_VERTICAL|wxALL, 6 );

	m_staticText261 = new wxStaticText( sbSizer13->GetStaticBox(), wxID_ANY, wxT("Average Coeff"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText261->Wrap( -1 );
	fgSizer13->Add( m_staticText261, 0, wxALIGN_CENTER_VERTICAL|wxALL, 2 );

	gaugeSC1905_Average_Coeff = new wxGauge( sbSizer13->GetStaticBox(), wxID_ANY, 100, wxDefaultPosition, wxSize( 80,-1 ), wxGA_HORIZONTAL );
	gaugeSC1905_Average_Coeff->SetValue( 0 );
	fgSizer13->Add( gaugeSC1905_Average_Coeff, 0, wxALIGN_CENTER_VERTICAL|wxALL, 6 );


	fgSizer12->Add( fgSizer13, 1, wxEXPAND, 5 );

	wxFlexGridSizer* fgSizer11;
	fgSizer11 = new wxFlexGridSizer( 0, 5, 0, 0 );
	fgSizer11->SetFlexibleDirection( wxBOTH );
	fgSizer11->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticText28 = new wxStaticText( sbSizer13->GetStaticBox(), wxID_ANY, wxT("PMU"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText28->Wrap( -1 );
	fgSizer11->Add( m_staticText28, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 2 );

	m_staticText29 = new wxStaticText( sbSizer13->GetStaticBox(), wxID_ANY, wxT("+"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText29->Wrap( -1 );
	fgSizer11->Add( m_staticText29, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 2 );

	m_staticText30 = new wxStaticText( sbSizer13->GetStaticBox(), wxID_ANY, wxT("Offset"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText30->Wrap( -1 );
	fgSizer11->Add( m_staticText30, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 2 );

	m_staticText31 = new wxStaticText( sbSizer13->GetStaticBox(), wxID_ANY, wxT("="), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText31->Wrap( -1 );
	fgSizer11->Add( m_staticText31, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 2 );

	m_staticText32 = new wxStaticText( sbSizer13->GetStaticBox(), wxID_ANY, wxT("Power"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText32->Wrap( -1 );
	fgSizer11->Add( m_staticText32, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 2 );

	txtCtrlSC1905_RFIN_PMU = new wxTextCtrl( sbSizer13->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 60,-1 ), 0 );
	txtCtrlSC1905_RFIN_PMU->Enable( false );

	fgSizer11->Add( txtCtrlSC1905_RFIN_PMU, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 2 );

	m_staticText35 = new wxStaticText( sbSizer13->GetStaticBox(), wxID_ANY, wxT("+"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText35->Wrap( -1 );
	fgSizer11->Add( m_staticText35, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 2 );

	txtCtrlSC1905_RFIN_Offset = new wxTextCtrl( sbSizer13->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 60,-1 ), wxTE_PROCESS_ENTER );
	fgSizer11->Add( txtCtrlSC1905_RFIN_Offset, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 2 );

	m_staticText36 = new wxStaticText( sbSizer13->GetStaticBox(), wxID_ANY, wxT("="), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText36->Wrap( -1 );
	fgSizer11->Add( m_staticText36, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 2 );

	txtCtrlSC1905_RFIN_Power = new wxTextCtrl( sbSizer13->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 60,-1 ), 0 );
	txtCtrlSC1905_RFIN_Power->Enable( false );

	fgSizer11->Add( txtCtrlSC1905_RFIN_Power, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 2 );

	txtCtrlSC1905_RFFB_PMU = new wxTextCtrl( sbSizer13->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 60,-1 ), 0 );
	txtCtrlSC1905_RFFB_PMU->Enable( false );

	fgSizer11->Add( txtCtrlSC1905_RFFB_PMU, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 2 );

	m_staticText351 = new wxStaticText( sbSizer13->GetStaticBox(), wxID_ANY, wxT("+"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText351->Wrap( -1 );
	fgSizer11->Add( m_staticText351, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 2 );

	txtCtrlSC1905_RFFB_Offset = new wxTextCtrl( sbSizer13->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 60,-1 ), 0 );
	fgSizer11->Add( txtCtrlSC1905_RFFB_Offset, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 2 );

	m_staticText361 = new wxStaticText( sbSizer13->GetStaticBox(), wxID_ANY, wxT("="), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText361->Wrap( -1 );
	fgSizer11->Add( m_staticText361, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 2 );

	txtCtrlSC1905_RFFB_Power = new wxTextCtrl( sbSizer13->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 60,-1 ), 0 );
	txtCtrlSC1905_RFFB_Power->Enable( false );

	fgSizer11->Add( txtCtrlSC1905_RFFB_Power, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 2 );

	txtCtrlSC1905_Average_Coeff_PMU = new wxTextCtrl( sbSizer13->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 60,-1 ), 0 );
	txtCtrlSC1905_Average_Coeff_PMU->Enable( false );

	fgSizer11->Add( txtCtrlSC1905_Average_Coeff_PMU, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 2 );


	fgSizer12->Add( fgSizer11, 1, wxEXPAND, 5 );


	sbSizer13->Add( fgSizer12, 1, wxEXPAND, 5 );


	fgSizer9->Add( sbSizer13, 1, wxEXPAND, 1 );


	fgSizer7->Add( fgSizer9, 1, wxEXPAND, 1 );

	wxFlexGridSizer* fgSizer10;
	fgSizer10 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer10->SetFlexibleDirection( wxBOTH );
	fgSizer10->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_notebook2 = new wxNotebook( pnlRFPAL, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	pnlSC1905_Customer_Controls = new wxPanel( m_notebook2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxFlexGridSizer* fgSizer16;
	fgSizer16 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer16->SetFlexibleDirection( wxBOTH );
	fgSizer16->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	wxStaticBoxSizer* sbSizer10;
	sbSizer10 = new wxStaticBoxSizer( new wxStaticBox( pnlSC1905_Customer_Controls, wxID_ANY, wxT("Configure Application") ), wxVERTICAL );

	wxGridSizer* gSizer3;
	gSizer3 = new wxGridSizer( 0, 4, 0, 0 );

	m_staticText24 = new wxStaticText( sbSizer10->GetStaticBox(), wxID_ANY, wxT("Frequency Range"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText24->Wrap( -1 );
	gSizer3->Add( m_staticText24, 0, wxALIGN_CENTER|wxALL, 1 );

	m_staticText25 = new wxStaticText( sbSizer10->GetStaticBox(), wxID_ANY, wxT("Min Frequency"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText25->Wrap( -1 );
	gSizer3->Add( m_staticText25, 0, wxALIGN_CENTER|wxALL, 1 );

	m_staticText26 = new wxStaticText( sbSizer10->GetStaticBox(), wxID_ANY, wxT("Max Frequency"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText26->Wrap( -1 );
	gSizer3->Add( m_staticText26, 0, wxALIGN_CENTER|wxALL, 1 );


	gSizer3->Add( 0, 0, 1, wxEXPAND, 1 );

	wxArrayString chSC1905_Frequency_RangeChoices;
	chSC1905_Frequency_Range = new wxChoice( sbSizer10->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, chSC1905_Frequency_RangeChoices, 0 );
	chSC1905_Frequency_Range->SetSelection( 0 );
	gSizer3->Add( chSC1905_Frequency_Range, 0, wxALL|wxEXPAND, 2 );

	txtCtrlSC1905_Set_Min_Frequency = new wxTextCtrl( sbSizer10->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gSizer3->Add( txtCtrlSC1905_Set_Min_Frequency, 0, wxALL|wxEXPAND, 2 );

	txtCtrlSC1905_Set_Max_Frequency = new wxTextCtrl( sbSizer10->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gSizer3->Add( txtCtrlSC1905_Set_Max_Frequency, 0, wxALL|wxEXPAND, 2 );

	btnSC1905_Apply_Frequency = new wxButton( sbSizer10->GetStaticBox(), wxID_ANY, wxT("Apply Frequency"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer3->Add( btnSC1905_Apply_Frequency, 0, wxALL|wxEXPAND, 2 );


	sbSizer10->Add( gSizer3, 1, wxEXPAND, 5 );


	fgSizer16->Add( sbSizer10, 1, wxEXPAND, 5 );

	wxStaticBoxSizer* sbSizer11;
	sbSizer11 = new wxStaticBoxSizer( new wxStaticBox( pnlSC1905_Customer_Controls, wxID_ANY, wxT("Firmware Control") ), wxHORIZONTAL );

	wxGridSizer* gSizer4;
	gSizer4 = new wxGridSizer( 0, 3, 0, 0 );

	m_staticText21 = new wxStaticText( sbSizer11->GetStaticBox(), wxID_ANY, wxT("Duty Cycle Feedback"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText21->Wrap( -1 );
	gSizer4->Add( m_staticText21, 0, wxALIGN_CENTER|wxALL, 1 );

	m_staticText22 = new wxStaticText( sbSizer11->GetStaticBox(), wxID_ANY, wxT("Adaptation State"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText22->Wrap( -1 );
	gSizer4->Add( m_staticText22, 0, wxALIGN_CENTER|wxALL, 1 );

	m_staticText23 = new wxStaticText( sbSizer11->GetStaticBox(), wxID_ANY, wxT("Correction Enable"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText23->Wrap( -1 );
	gSizer4->Add( m_staticText23, 0, wxALIGN_CENTER|wxALL, 5 );

	wxString chSC1905_Set_Duty_Cycle_FeedbackChoices[] = { wxT("Off"), wxT("On") };
	int chSC1905_Set_Duty_Cycle_FeedbackNChoices = sizeof( chSC1905_Set_Duty_Cycle_FeedbackChoices ) / sizeof( wxString );
	chSC1905_Set_Duty_Cycle_Feedback = new wxChoice( sbSizer11->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, chSC1905_Set_Duty_Cycle_FeedbackNChoices, chSC1905_Set_Duty_Cycle_FeedbackChoices, 0 );
	chSC1905_Set_Duty_Cycle_Feedback->SetSelection( 1 );
	gSizer4->Add( chSC1905_Set_Duty_Cycle_Feedback, 0, wxALL|wxEXPAND, 2 );

	wxString chSC1905_Set_Adaptation_StateChoices[] = { wxT("Frozen"), wxT("Running") };
	int chSC1905_Set_Adaptation_StateNChoices = sizeof( chSC1905_Set_Adaptation_StateChoices ) / sizeof( wxString );
	chSC1905_Set_Adaptation_State = new wxChoice( sbSizer11->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, chSC1905_Set_Adaptation_StateNChoices, chSC1905_Set_Adaptation_StateChoices, 0 );
	chSC1905_Set_Adaptation_State->SetSelection( 1 );
	gSizer4->Add( chSC1905_Set_Adaptation_State, 0, wxALL|wxEXPAND, 2 );

	wxString chSC1905_Set_Correction_EnableChoices[] = { wxT("Disabled"), wxT("FW Control") };
	int chSC1905_Set_Correction_EnableNChoices = sizeof( chSC1905_Set_Correction_EnableChoices ) / sizeof( wxString );
	chSC1905_Set_Correction_Enable = new wxChoice( sbSizer11->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, chSC1905_Set_Correction_EnableNChoices, chSC1905_Set_Correction_EnableChoices, 0 );
	chSC1905_Set_Correction_Enable->SetSelection( 1 );
	gSizer4->Add( chSC1905_Set_Correction_Enable, 0, wxALL|wxEXPAND, 2 );


	sbSizer11->Add( gSizer4, 1, wxEXPAND, 5 );


	fgSizer16->Add( sbSizer11, 1, wxEXPAND, 5 );

	wxStaticBoxSizer* sbSizer12;
	sbSizer12 = new wxStaticBoxSizer( new wxStaticBox( pnlSC1905_Customer_Controls, wxID_ANY, wxT("Misc") ), wxVERTICAL );

	wxGridSizer* gSizer5;
	gSizer5 = new wxGridSizer( 0, 3, 0, 0 );

	btnSC1905_Clear_Warnings = new wxButton( sbSizer12->GetStaticBox(), wxID_ANY, wxT("Clear Warnings"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer5->Add( btnSC1905_Clear_Warnings, 0, wxALL|wxEXPAND, 2 );


	gSizer5->Add( 0, 0, 1, wxEXPAND, 5 );


	gSizer5->Add( 0, 0, 1, wxEXPAND, 5 );


	sbSizer12->Add( gSizer5, 1, wxEXPAND, 5 );


	fgSizer16->Add( sbSizer12, 1, wxEXPAND, 5 );

	wxFlexGridSizer* fgSizer14;
	fgSizer14 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer14->SetFlexibleDirection( wxBOTH );
	fgSizer14->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	wxGridSizer* gSizer7;
	gSizer7 = new wxGridSizer( 0, 2, 0, 0 );

	wxGridSizer* gSizer9;
	gSizer9 = new wxGridSizer( 0, 1, 0, 0 );

	wxStaticBoxSizer* sbSizer15;
	sbSizer15 = new wxStaticBoxSizer( new wxStaticBox( pnlSC1905_Customer_Controls, wxID_ANY, wxT("Operating Mode Functions") ), wxVERTICAL );

	wxGridSizer* gSizer8;
	gSizer8 = new wxGridSizer( 0, 2, 0, 0 );


	gSizer8->Add( 0, 0, 1, 0, 0 );

	m_staticText38 = new wxStaticText( sbSizer15->GetStaticBox(), wxID_ANY, wxT("Cal Freq"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText38->Wrap( -1 );
	gSizer8->Add( m_staticText38, 0, wxALIGN_CENTER|wxALL, 1 );

	btnSC1905_Set_Cal_Param_A = new wxButton( sbSizer15->GetStaticBox(), wxID_ANY, wxT("Set Cal Param A"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer8->Add( btnSC1905_Set_Cal_Param_A, 0, wxALL|wxEXPAND, 2 );

	txtCtrlSC1905_Set_Cal_Param_A_CalFreq = new wxTextCtrl( sbSizer15->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	txtCtrlSC1905_Set_Cal_Param_A_CalFreq->Enable( false );

	gSizer8->Add( txtCtrlSC1905_Set_Cal_Param_A_CalFreq, 0, wxALL|wxEXPAND, 2 );

	btnSC1905_Set_Cal_Param_B = new wxButton( sbSizer15->GetStaticBox(), wxID_ANY, wxT("Set Cal Param B"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer8->Add( btnSC1905_Set_Cal_Param_B, 0, wxALL|wxEXPAND, 2 );

	txtCtrlSC1905_Set_Cal_Param_B_CalFreq = new wxTextCtrl( sbSizer15->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	txtCtrlSC1905_Set_Cal_Param_B_CalFreq->Enable( false );

	gSizer8->Add( txtCtrlSC1905_Set_Cal_Param_B_CalFreq, 0, wxALL|wxEXPAND, 2 );

	btnSC1905_Clear_Cal_Param = new wxButton( sbSizer15->GetStaticBox(), wxID_ANY, wxT("Clear Cal Param"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer8->Add( btnSC1905_Clear_Cal_Param, 0, wxALL|wxEXPAND, 2 );


	gSizer8->Add( 0, 0, 1, 0, 0 );


	sbSizer15->Add( gSizer8, 1, wxEXPAND, 5 );


	gSizer9->Add( sbSizer15, 1, wxEXPAND, 5 );


	gSizer7->Add( gSizer9, 1, wxEXPAND, 5 );

	wxFlexGridSizer* fgSizer15;
	fgSizer15 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer15->SetFlexibleDirection( wxBOTH );
	fgSizer15->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	wxStaticBoxSizer* sbSizer14;
	sbSizer14 = new wxStaticBoxSizer( new wxStaticBox( pnlSC1905_Customer_Controls, wxID_ANY, wxT("PMU Functions") ), wxVERTICAL );

	wxGridSizer* gSizer6;
	gSizer6 = new wxGridSizer( 0, 2, 0, 0 );


	gSizer6->Add( 0, 0, 1, 0, 0 );

	m_staticText37 = new wxStaticText( sbSizer14->GetStaticBox(), wxID_ANY, wxT("Expected Power"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText37->Wrap( -1 );
	gSizer6->Add( m_staticText37, 0, wxALIGN_CENTER, 1 );

	btnSC1905_Calibrate_RFIN_PMU = new wxButton( sbSizer14->GetStaticBox(), wxID_ANY, wxT("Calibrate RFIN PMU"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer6->Add( btnSC1905_Calibrate_RFIN_PMU, 0, wxALL|wxEXPAND, 2 );

	txtCtrlSC1905_Calibrate_RFIN_PMU = new wxTextCtrl( sbSizer14->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gSizer6->Add( txtCtrlSC1905_Calibrate_RFIN_PMU, 0, wxALL|wxEXPAND, 2 );

	btnSC1905_Calibrate_RFFB_PMU = new wxButton( sbSizer14->GetStaticBox(), wxID_ANY, wxT("Calibrate RFFB PMU"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer6->Add( btnSC1905_Calibrate_RFFB_PMU, 0, wxALL|wxEXPAND, 2 );

	txtCtrlSC1905_Calibrate_RFFB_PMU = new wxTextCtrl( sbSizer14->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gSizer6->Add( txtCtrlSC1905_Calibrate_RFFB_PMU, 0, wxALL|wxEXPAND, 2 );


	sbSizer14->Add( gSizer6, 1, wxEXPAND, 5 );


	fgSizer15->Add( sbSizer14, 1, wxEXPAND, 5 );

	wxStaticBoxSizer* sbSizer16;
	sbSizer16 = new wxStaticBoxSizer( new wxStaticBox( pnlSC1905_Customer_Controls, wxID_ANY, wxT("Wideband Optimization") ), wxVERTICAL );

	wxGridSizer* gSizer111;
	gSizer111 = new wxGridSizer( 0, 2, 0, 0 );

	m_staticText39 = new wxStaticText( sbSizer16->GetStaticBox(), wxID_ANY, wxT("Guard Band"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText39->Wrap( -1 );
	gSizer111->Add( m_staticText39, 0, wxALIGN_CENTER_VERTICAL|wxALL, 2 );

	wxString chSC1905_Guard_BandChoices[] = { wxT("20% of SBW"), wxT("0.5 MHz"), wxT("1 MHz"), wxT("1.5 MHz"), wxT("2 MHz"), wxT("2.5 MHz") };
	int chSC1905_Guard_BandNChoices = sizeof( chSC1905_Guard_BandChoices ) / sizeof( wxString );
	chSC1905_Guard_Band = new wxChoice( sbSizer16->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, chSC1905_Guard_BandNChoices, chSC1905_Guard_BandChoices, 0 );
	chSC1905_Guard_Band->SetSelection( 0 );
	gSizer111->Add( chSC1905_Guard_Band, 0, wxALL|wxEXPAND, 2 );


	sbSizer16->Add( gSizer111, 1, wxEXPAND, 5 );


	fgSizer15->Add( sbSizer16, 1, wxEXPAND, 5 );


	gSizer7->Add( fgSizer15, 1, wxEXPAND, 5 );


	fgSizer14->Add( gSizer7, 1, wxEXPAND, 5 );


	fgSizer16->Add( fgSizer14, 1, wxEXPAND, 5 );


	pnlSC1905_Customer_Controls->SetSizer( fgSizer16 );
	pnlSC1905_Customer_Controls->Layout();
	fgSizer16->Fit( pnlSC1905_Customer_Controls );
	m_notebook2->AddPage( pnlSC1905_Customer_Controls, wxT("Customer Controls"), true );
	pnlSC1905_ACCP_Config = new wxPanel( m_notebook2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxFlexGridSizer* fgSizer171;
	fgSizer171 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer171->AddGrowableRow( 1 );
	fgSizer171->SetFlexibleDirection( wxBOTH );
	fgSizer171->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	wxStaticBoxSizer* sbSizer17;
	sbSizer17 = new wxStaticBoxSizer( new wxStaticBox( pnlSC1905_ACCP_Config, wxID_ANY, wxT("EEPROM Access") ), wxVERTICAL );

	wxGridSizer* gSizer12;
	gSizer12 = new wxGridSizer( 0, 5, 0, 0 );

	m_staticText40 = new wxStaticText( sbSizer17->GetStaticBox(), wxID_ANY, wxT("Variable Type:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText40->Wrap( -1 );
	gSizer12->Add( m_staticText40, 0, wxALIGN_CENTER_VERTICAL|wxALL, 2 );

	rbtnSC1905_EEPROM_Write = new wxRadioButton( sbSizer17->GetStaticBox(), wxID_ANY, wxT("Write"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP );
	gSizer12->Add( rbtnSC1905_EEPROM_Write, 0, wxALIGN_CENTER_VERTICAL|wxALL, 2 );

	m_staticText411 = new wxStaticText( sbSizer17->GetStaticBox(), wxID_ANY, wxT("Address (hex):"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText411->Wrap( -1 );
	gSizer12->Add( m_staticText411, 0, wxALIGN_CENTER_VERTICAL|wxALL, 2 );

	m_staticText42 = new wxStaticText( sbSizer17->GetStaticBox(), wxID_ANY, wxT("Value:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText42->Wrap( -1 );
	gSizer12->Add( m_staticText42, 0, wxALIGN_CENTER_VERTICAL|wxALL, 2 );


	gSizer12->Add( 0, 0, 1, wxEXPAND, 5 );

	wxString chSC1905_Variable_TypeChoices[] = { wxT("UINT8"), wxT("INT8"), wxT("UINT16"), wxT("INT16"), wxEmptyString, wxEmptyString };
	int chSC1905_Variable_TypeNChoices = sizeof( chSC1905_Variable_TypeChoices ) / sizeof( wxString );
	chSC1905_Variable_Type = new wxChoice( sbSizer17->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, chSC1905_Variable_TypeNChoices, chSC1905_Variable_TypeChoices, 0 );
	chSC1905_Variable_Type->SetSelection( 0 );
	gSizer12->Add( chSC1905_Variable_Type, 0, wxALL|wxEXPAND, 2 );

	rbtnSC1905_EEPROM_Read = new wxRadioButton( sbSizer17->GetStaticBox(), wxID_ANY, wxT("Read"), wxDefaultPosition, wxDefaultSize, 0 );
	rbtnSC1905_EEPROM_Read->SetValue( true );
	gSizer12->Add( rbtnSC1905_EEPROM_Read, 0, wxALIGN_CENTER_VERTICAL|wxALL, 2 );

	txtCtrlSC1905_EEPROM_Address = new wxTextCtrl( sbSizer17->GetStaticBox(), wxID_ANY, wxT("FDAC"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer12->Add( txtCtrlSC1905_EEPROM_Address, 0, wxALL|wxEXPAND, 2 );

	txtCtrlSC1905_EEPROM_Value = new wxTextCtrl( sbSizer17->GetStaticBox(), wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, 0 );
	txtCtrlSC1905_EEPROM_Value->Enable( false );

	gSizer12->Add( txtCtrlSC1905_EEPROM_Value, 0, wxALL|wxEXPAND, 2 );

	btnSC1905_EEPROM_Execute = new wxButton( sbSizer17->GetStaticBox(), wxID_ANY, wxT("Execute"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer12->Add( btnSC1905_EEPROM_Execute, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 2 );


	sbSizer17->Add( gSizer12, 0, wxEXPAND, 5 );


	fgSizer171->Add( sbSizer17, 1, wxEXPAND, 5 );

	wxStaticBoxSizer* sbSizer181;
	sbSizer181 = new wxStaticBoxSizer( new wxStaticBox( pnlSC1905_ACCP_Config, wxID_ANY, wxT("Parameters") ), wxVERTICAL );

	gridSC1905_EEPROM_Parameters = new wxGrid( sbSizer181->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );

	// Grid
	gridSC1905_EEPROM_Parameters->CreateGrid( 3, 5 );
	gridSC1905_EEPROM_Parameters->EnableEditing( true );
	gridSC1905_EEPROM_Parameters->EnableGridLines( true );
	gridSC1905_EEPROM_Parameters->EnableDragGridSize( false );
	gridSC1905_EEPROM_Parameters->SetMargins( 0, 0 );

	// Columns
	gridSC1905_EEPROM_Parameters->SetColSize( 0, 80 );
	gridSC1905_EEPROM_Parameters->SetColSize( 1, 221 );
	gridSC1905_EEPROM_Parameters->SetColSize( 2, 80 );
	gridSC1905_EEPROM_Parameters->SetColSize( 3, 80 );
	gridSC1905_EEPROM_Parameters->SetColSize( 4, 104 );
	gridSC1905_EEPROM_Parameters->EnableDragColMove( false );
	gridSC1905_EEPROM_Parameters->EnableDragColSize( true );
	gridSC1905_EEPROM_Parameters->SetColLabelValue( 0, wxT("Group") );
	gridSC1905_EEPROM_Parameters->SetColLabelValue( 1, wxT("Variable Name") );
	gridSC1905_EEPROM_Parameters->SetColLabelValue( 2, wxT("Address") );
	gridSC1905_EEPROM_Parameters->SetColLabelValue( 3, wxT("Value") );
	gridSC1905_EEPROM_Parameters->SetColLabelValue( 4, wxT("Commands") );
	gridSC1905_EEPROM_Parameters->SetColLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Rows
	gridSC1905_EEPROM_Parameters->EnableDragRowSize( true );
	gridSC1905_EEPROM_Parameters->SetRowLabelSize( 1 );
	gridSC1905_EEPROM_Parameters->SetRowLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Label Appearance

	// Cell Defaults
	gridSC1905_EEPROM_Parameters->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	sbSizer181->Add( gridSC1905_EEPROM_Parameters, 0, wxALIGN_CENTER_HORIZONTAL|wxALL|wxEXPAND, 2 );


	fgSizer171->Add( sbSizer181, 0, wxEXPAND, 5 );


	pnlSC1905_ACCP_Config->SetSizer( fgSizer171 );
	pnlSC1905_ACCP_Config->Layout();
	fgSizer171->Fit( pnlSC1905_ACCP_Config );
	m_notebook2->AddPage( pnlSC1905_ACCP_Config, wxT("ACCP Config"), false );

	fgSizer10->Add( m_notebook2, 1, wxEXPAND | wxALL, 1 );


	fgSizer7->Add( fgSizer10, 1, wxEXPAND, 1 );


	fgSizer6->Add( fgSizer7, 1, wxEXPAND, 1 );


	pnlRFPAL->SetSizer( fgSizer6 );
	pnlRFPAL->Layout();
	fgSizer6->Fit( pnlRFPAL );
	nbMain->AddPage( pnlRFPAL, wxT("SC1905"), false );

	fgSizer5->Add( nbMain, 1, wxEXPAND | wxALL, 5 );

	m_panel173 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL|wxBORDER_RAISED );
	wxFlexGridSizer* fgSizer17;
	fgSizer17 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer17->AddGrowableCol( 0 );
	fgSizer17->SetFlexibleDirection( wxBOTH );
	fgSizer17->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	txtMessageField = new wxTextCtrl( m_panel173, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY );
	txtMessageField->SetMinSize( wxSize( -1,100 ) );

	fgSizer17->Add( txtMessageField, 0, wxEXPAND, 5 );

	m_panel18 = new wxPanel( m_panel173, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer24;
	bSizer24 = new wxBoxSizer( wxVERTICAL );

	btnClearMessages = new wxButton( m_panel18, wxID_ANY, wxT("Clear"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer24->Add( btnClearMessages, 0, 0, 5 );


	m_panel18->SetSizer( bSizer24 );
	m_panel18->Layout();
	bSizer24->Fit( m_panel18 );
	fgSizer17->Add( m_panel18, 0, wxEXPAND, 5 );


	m_panel173->SetSizer( fgSizer17 );
	m_panel173->Layout();
	fgSizer17->Fit( m_panel173 );
	fgSizer5->Add( m_panel173, 1, wxEXPAND, 1 );


	bSizer2->Add( fgSizer5, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer2 );
	this->Layout();
	bSizer2->Fit( this );

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( LimeRFE_8001P_view::OnClose_LimeRFE_8001P_view ) );
	mFile->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( LimeRFE_8001P_view::OnQuit ), this, miQuit->GetId());
	mModules->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( LimeRFE_8001P_view::OnmiLMS8001 ), this, miLMS8001->GetId());
	rbI2C->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( LimeRFE_8001P_view::OnrbI2CrbUSB ), NULL, this );
	rbUSB->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( LimeRFE_8001P_view::OnrbI2CrbUSB ), NULL, this );
	btnRefreshPorts->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnbtnRefreshPorts ), NULL, this );
	btnOpenPort->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnbtnOpenPort ), NULL, this );
	btnClosePort->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnbtnClosePort ), NULL, this );
	btnOpen->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnbtnOpen ), NULL, this );
	btnSave->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnbtnSave ), NULL, this );
	btnReset->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnbtnReset ), NULL, this );
	btnBoard2GUI->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnbtnReadData ), NULL, this );
	cmbChannel->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( LimeRFE_8001P_view::OnDetailedChange ), NULL, this );
	pnlChannel->Connect( wxEVT_ERASE_BACKGROUND, wxEraseEventHandler( LimeRFE_8001P_view::OnEraseBackground_pnlChannel ), NULL, this );
	cbBP_AMPX->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnSimpleChanged ), NULL, this );
	cbSD_AMPX->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnSimpleChanged ), NULL, this );
	cbSC1905_X_RESETn->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnSimpleChanged ), NULL, this );
	cbLMS8001_X_RESETn->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnSimpleChanged ), NULL, this );
	cmbTXX_ATT->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( LimeRFE_8001P_view::OnSimpleChanged ), NULL, this );
	cbPDAX_EN->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnSimpleChanged ), NULL, this );
	cbLNAX_EN->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnSimpleChanged ), NULL, this );
	cmbORXX_ATT->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( LimeRFE_8001P_view::OnSimpleChanged ), NULL, this );
	cbDAX_X_EN->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnSimpleChanged ), NULL, this );
	cbDAX_A_B_CTRL->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnSimpleChanged ), NULL, this );
	cbTXRX_X->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnSimpleChanged ), NULL, this );
	cbSPI_2_MCU_DIR_OUT_in->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnDetailedChange ), NULL, this );
	cbLMS8001_1_SSENn->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnDetailedChange ), NULL, this );
	cbLMS8001_2_SSENn->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnDetailedChange ), NULL, this );
	cbEXT_PLL_SSENn->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnDetailedChange ), NULL, this );
	cbLMS8001_1_RESETn->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnDetailedChange ), NULL, this );
	cbLMS8001_2_RESETn->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnDetailedChange ), NULL, this );
	cbSC1905_1_SSENn->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnDetailedChange ), NULL, this );
	cbSC1905_2_SSENn->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnDetailedChange ), NULL, this );
	cbSC1905_1_RESETn->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnDetailedChange ), NULL, this );
	cbSC1905_2_RESETn->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnDetailedChange ), NULL, this );
	cbBP_AMP1->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnDetailedChange ), NULL, this );
	cbSD_AMP1->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnDetailedChange ), NULL, this );
	cbBP_AMP2->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnDetailedChange ), NULL, this );
	cbSD_AMP2->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnDetailedChange ), NULL, this );
	cbDA1_A_EN->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnDetailedChange ), NULL, this );
	cbDA1_B_EN->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnDetailedChange ), NULL, this );
	cbDA2_A_EN->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnDetailedChange ), NULL, this );
	cbDA2_B_EN->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnDetailedChange ), NULL, this );
	cbLNA1_EN->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnDetailedChange ), NULL, this );
	cbLNA2_EN->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnDetailedChange ), NULL, this );
	cbPDA1_EN->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnDetailedChange ), NULL, this );
	cbPDA2_EN->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnDetailedChange ), NULL, this );
	cbDA1_A_B_CTRL->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnDetailedChange ), NULL, this );
	cbDA2_A_B_CTRL->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnDetailedChange ), NULL, this );
	cmbORX1_ATT->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( LimeRFE_8001P_view::OnDetailedChange ), NULL, this );
	cmbORX2_ATT->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( LimeRFE_8001P_view::OnDetailedChange ), NULL, this );
	cmbTX1_ATT->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( LimeRFE_8001P_view::OnDetailedChange ), NULL, this );
	cmbTX2_ATT->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( LimeRFE_8001P_view::OnDetailedChange ), NULL, this );
	cbTXRX_1->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnDetailedChange ), NULL, this );
	cbTXRX_2->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnDetailedChange ), NULL, this );
	btnApplyData->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnbtnApplyData ), NULL, this );
	btnReadData->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnbtnReadData ), NULL, this );
	btnSC1905_Read_FW_Version->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnbtnSC1905_Read_FW_Version ), NULL, this );
	btnSC1905_Read_Product_ID->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnbtnSC1905_Read_Product_ID ), NULL, this );
	chSC1905_Update_Rate->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( LimeRFE_8001P_view::OnchSC1905_Update_Rate ), NULL, this );
	btnSC1905_Force_Update->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnbtnSC1905_Force_Update ), NULL, this );
	btnSC1905_Reset_RFPAL->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnbtnSC1905_Reset_RFPAL ), NULL, this );
	txtCtrlSC1905_RFIN_Offset->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( LimeRFE_8001P_view::OnKillFocustxtCtrlSC1905_RFIN_Offset ), NULL, this );
	txtCtrlSC1905_RFFB_Offset->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( LimeRFE_8001P_view::OnKillFocustxtCtrlSC1905_RFFB_Offset ), NULL, this );
	txtCtrlSC1905_RFFB_Offset->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( LimeRFE_8001P_view::OntxtCtrlSC1905_RFFB_Offset ), NULL, this );
	chSC1905_Frequency_Range->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( LimeRFE_8001P_view::OnchSC1905_Frequency_Range ), NULL, this );
	btnSC1905_Apply_Frequency->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnbtnSC1905_Apply_Frequency ), NULL, this );
	chSC1905_Set_Duty_Cycle_Feedback->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( LimeRFE_8001P_view::OnchSC1905_Set_Duty_Cycle_Feedback ), NULL, this );
	chSC1905_Set_Adaptation_State->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( LimeRFE_8001P_view::OnchSC1905_Set_Adaptation_State ), NULL, this );
	chSC1905_Set_Correction_Enable->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( LimeRFE_8001P_view::OnchSC1905_Set_Correction_Enable ), NULL, this );
	btnSC1905_Clear_Warnings->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnbtnSC1905_Clear_Warnings ), NULL, this );
	btnSC1905_Set_Cal_Param_A->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnbtnSC1905_Set_Cal_Param_A ), NULL, this );
	btnSC1905_Set_Cal_Param_B->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnbtnSC1905_Set_Cal_Param ), NULL, this );
	btnSC1905_Clear_Cal_Param->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnbtnSC1905_Clear_Cal_Param ), NULL, this );
	btnSC1905_Calibrate_RFIN_PMU->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnbtnSC1905_Calibrate_RFIN_PMU ), NULL, this );
	btnSC1905_Calibrate_RFFB_PMU->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnbtnSC1905_Calibrate_RFFB_PMU ), NULL, this );
	chSC1905_Guard_Band->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( LimeRFE_8001P_view::OnchSC1905_Guard_Band ), NULL, this );
	rbtnSC1905_EEPROM_Write->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( LimeRFE_8001P_view::OnrbtnSC1905_EEPROM_Write ), NULL, this );
	rbtnSC1905_EEPROM_Read->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( LimeRFE_8001P_view::OnrbtnSC1905_EEPROM_Read ), NULL, this );
	btnSC1905_EEPROM_Execute->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnbtnSC1905_EEPROM_Execute ), NULL, this );
	gridSC1905_EEPROM_Parameters->Connect( wxEVT_GRID_CELL_CHANGED, wxGridEventHandler( LimeRFE_8001P_view::OnGridCellChangegridSC1905_EEPROM_Parameters ), NULL, this );
	btnClearMessages->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnbtnClearMessages ), NULL, this );
}

LimeRFE_8001P_view::~LimeRFE_8001P_view()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( LimeRFE_8001P_view::OnClose_LimeRFE_8001P_view ) );
	rbI2C->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( LimeRFE_8001P_view::OnrbI2CrbUSB ), NULL, this );
	rbUSB->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( LimeRFE_8001P_view::OnrbI2CrbUSB ), NULL, this );
	btnRefreshPorts->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnbtnRefreshPorts ), NULL, this );
	btnOpenPort->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnbtnOpenPort ), NULL, this );
	btnClosePort->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnbtnClosePort ), NULL, this );
	btnOpen->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnbtnOpen ), NULL, this );
	btnSave->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnbtnSave ), NULL, this );
	btnReset->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnbtnReset ), NULL, this );
	btnBoard2GUI->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnbtnReadData ), NULL, this );
	cmbChannel->Disconnect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( LimeRFE_8001P_view::OnDetailedChange ), NULL, this );
	pnlChannel->Disconnect( wxEVT_ERASE_BACKGROUND, wxEraseEventHandler( LimeRFE_8001P_view::OnEraseBackground_pnlChannel ), NULL, this );
	cbBP_AMPX->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnSimpleChanged ), NULL, this );
	cbSD_AMPX->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnSimpleChanged ), NULL, this );
	cbSC1905_X_RESETn->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnSimpleChanged ), NULL, this );
	cbLMS8001_X_RESETn->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnSimpleChanged ), NULL, this );
	cmbTXX_ATT->Disconnect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( LimeRFE_8001P_view::OnSimpleChanged ), NULL, this );
	cbPDAX_EN->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnSimpleChanged ), NULL, this );
	cbLNAX_EN->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnSimpleChanged ), NULL, this );
	cmbORXX_ATT->Disconnect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( LimeRFE_8001P_view::OnSimpleChanged ), NULL, this );
	cbDAX_X_EN->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnSimpleChanged ), NULL, this );
	cbDAX_A_B_CTRL->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnSimpleChanged ), NULL, this );
	cbTXRX_X->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnSimpleChanged ), NULL, this );
	cbSPI_2_MCU_DIR_OUT_in->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnDetailedChange ), NULL, this );
	cbLMS8001_1_SSENn->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnDetailedChange ), NULL, this );
	cbLMS8001_2_SSENn->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnDetailedChange ), NULL, this );
	cbEXT_PLL_SSENn->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnDetailedChange ), NULL, this );
	cbLMS8001_1_RESETn->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnDetailedChange ), NULL, this );
	cbLMS8001_2_RESETn->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnDetailedChange ), NULL, this );
	cbSC1905_1_SSENn->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnDetailedChange ), NULL, this );
	cbSC1905_2_SSENn->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnDetailedChange ), NULL, this );
	cbSC1905_1_RESETn->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnDetailedChange ), NULL, this );
	cbSC1905_2_RESETn->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnDetailedChange ), NULL, this );
	cbBP_AMP1->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnDetailedChange ), NULL, this );
	cbSD_AMP1->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnDetailedChange ), NULL, this );
	cbBP_AMP2->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnDetailedChange ), NULL, this );
	cbSD_AMP2->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnDetailedChange ), NULL, this );
	cbDA1_A_EN->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnDetailedChange ), NULL, this );
	cbDA1_B_EN->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnDetailedChange ), NULL, this );
	cbDA2_A_EN->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnDetailedChange ), NULL, this );
	cbDA2_B_EN->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnDetailedChange ), NULL, this );
	cbLNA1_EN->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnDetailedChange ), NULL, this );
	cbLNA2_EN->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnDetailedChange ), NULL, this );
	cbPDA1_EN->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnDetailedChange ), NULL, this );
	cbPDA2_EN->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnDetailedChange ), NULL, this );
	cbDA1_A_B_CTRL->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnDetailedChange ), NULL, this );
	cbDA2_A_B_CTRL->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnDetailedChange ), NULL, this );
	cmbORX1_ATT->Disconnect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( LimeRFE_8001P_view::OnDetailedChange ), NULL, this );
	cmbORX2_ATT->Disconnect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( LimeRFE_8001P_view::OnDetailedChange ), NULL, this );
	cmbTX1_ATT->Disconnect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( LimeRFE_8001P_view::OnDetailedChange ), NULL, this );
	cmbTX2_ATT->Disconnect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( LimeRFE_8001P_view::OnDetailedChange ), NULL, this );
	cbTXRX_1->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnDetailedChange ), NULL, this );
	cbTXRX_2->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnDetailedChange ), NULL, this );
	btnApplyData->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnbtnApplyData ), NULL, this );
	btnReadData->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnbtnReadData ), NULL, this );
	btnSC1905_Read_FW_Version->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnbtnSC1905_Read_FW_Version ), NULL, this );
	btnSC1905_Read_Product_ID->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnbtnSC1905_Read_Product_ID ), NULL, this );
	chSC1905_Update_Rate->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( LimeRFE_8001P_view::OnchSC1905_Update_Rate ), NULL, this );
	btnSC1905_Force_Update->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnbtnSC1905_Force_Update ), NULL, this );
	btnSC1905_Reset_RFPAL->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnbtnSC1905_Reset_RFPAL ), NULL, this );
	txtCtrlSC1905_RFIN_Offset->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( LimeRFE_8001P_view::OnKillFocustxtCtrlSC1905_RFIN_Offset ), NULL, this );
	txtCtrlSC1905_RFFB_Offset->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( LimeRFE_8001P_view::OnKillFocustxtCtrlSC1905_RFFB_Offset ), NULL, this );
	txtCtrlSC1905_RFFB_Offset->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( LimeRFE_8001P_view::OntxtCtrlSC1905_RFFB_Offset ), NULL, this );
	chSC1905_Frequency_Range->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( LimeRFE_8001P_view::OnchSC1905_Frequency_Range ), NULL, this );
	btnSC1905_Apply_Frequency->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnbtnSC1905_Apply_Frequency ), NULL, this );
	chSC1905_Set_Duty_Cycle_Feedback->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( LimeRFE_8001P_view::OnchSC1905_Set_Duty_Cycle_Feedback ), NULL, this );
	chSC1905_Set_Adaptation_State->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( LimeRFE_8001P_view::OnchSC1905_Set_Adaptation_State ), NULL, this );
	chSC1905_Set_Correction_Enable->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( LimeRFE_8001P_view::OnchSC1905_Set_Correction_Enable ), NULL, this );
	btnSC1905_Clear_Warnings->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnbtnSC1905_Clear_Warnings ), NULL, this );
	btnSC1905_Set_Cal_Param_A->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnbtnSC1905_Set_Cal_Param_A ), NULL, this );
	btnSC1905_Set_Cal_Param_B->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnbtnSC1905_Set_Cal_Param ), NULL, this );
	btnSC1905_Clear_Cal_Param->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnbtnSC1905_Clear_Cal_Param ), NULL, this );
	btnSC1905_Calibrate_RFIN_PMU->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnbtnSC1905_Calibrate_RFIN_PMU ), NULL, this );
	btnSC1905_Calibrate_RFFB_PMU->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnbtnSC1905_Calibrate_RFFB_PMU ), NULL, this );
	chSC1905_Guard_Band->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( LimeRFE_8001P_view::OnchSC1905_Guard_Band ), NULL, this );
	rbtnSC1905_EEPROM_Write->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( LimeRFE_8001P_view::OnrbtnSC1905_EEPROM_Write ), NULL, this );
	rbtnSC1905_EEPROM_Read->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( LimeRFE_8001P_view::OnrbtnSC1905_EEPROM_Read ), NULL, this );
	btnSC1905_EEPROM_Execute->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnbtnSC1905_EEPROM_Execute ), NULL, this );
	gridSC1905_EEPROM_Parameters->Disconnect( wxEVT_GRID_CELL_CHANGED, wxGridEventHandler( LimeRFE_8001P_view::OnGridCellChangegridSC1905_EEPROM_Parameters ), NULL, this );
	btnClearMessages->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LimeRFE_8001P_view::OnbtnClearMessages ), NULL, this );

}
