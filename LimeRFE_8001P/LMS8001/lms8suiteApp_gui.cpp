///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif //WX_PRECOMP

#include "lms8001_mainPanel.h"

#include "lms8suiteApp_gui.h"

///////////////////////////////////////////////////////////////////////////

lms8_AppFrame_view::lms8_AppFrame_view( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	mbar = new wxMenuBar( 0 );
	fileMenu = new wxMenu();
	wxMenuItem* menuFileQuit;
	menuFileQuit = new wxMenuItem( fileMenu, idMenuQuit, wxString( wxT("&Quit") ) + wxT('\t') + wxT("Alt+F4"), wxT("Quit the application"), wxITEM_NORMAL );
	fileMenu->Append( menuFileQuit );
	
	mbar->Append( fileMenu, wxT("&File") ); 
	
	mnuOption = new wxMenu();
	wxMenuItem* mnuConnectionSettings;
	mnuConnectionSettings = new wxMenuItem( mnuOption, wxID_ANY, wxString( wxT("Connection Settings") ) , wxEmptyString, wxITEM_NORMAL );
	mnuOption->Append( mnuConnectionSettings );
	
	mbar->Append( mnuOption, wxT("Options") ); 
	
	helpMenu = new wxMenu();
	wxMenuItem* menuHelpAbout;
	menuHelpAbout = new wxMenuItem( helpMenu, idMenuAbout, wxString( wxT("&About") ) + wxT('\t') + wxT("F1"), wxT("Show info about this application"), wxITEM_NORMAL );
	helpMenu->Append( menuHelpAbout );
	
	mbar->Append( helpMenu, wxT("&Help") ); 
	
	mnuModules = new wxMenu();
	wxMenuItem* mnuADF4002;
	mnuADF4002 = new wxMenuItem( mnuModules, wxID_ANY, wxString( wxT("ADF4002") ) , wxEmptyString, wxITEM_NORMAL );
	mnuModules->Append( mnuADF4002 );
	
	wxMenuItem* mnuSi5351C;
	mnuSi5351C = new wxMenuItem( mnuModules, wxID_ANY, wxString( wxT("Si5351C") ) , wxEmptyString, wxITEM_NORMAL );
	mnuModules->Append( mnuSi5351C );
	
	wxMenuItem* mnuDeviceInfo;
	mnuDeviceInfo = new wxMenuItem( mnuModules, wxID_ANY, wxString( wxT("Device Info") ) , wxEmptyString, wxITEM_NORMAL );
	mnuModules->Append( mnuDeviceInfo );
	
	wxMenuItem* mnuSPI;
	mnuSPI = new wxMenuItem( mnuModules, wxID_ANY, wxString( wxT("SPI") ) , wxEmptyString, wxITEM_NORMAL );
	mnuModules->Append( mnuSPI );
	
	wxMenuItem* mnuGPIO;
	mnuGPIO = new wxMenuItem( mnuModules, wxID_ANY, wxString( wxT("GPIO") ) , wxEmptyString, wxITEM_NORMAL );
	mnuModules->Append( mnuGPIO );
	
	mbar->Append( mnuModules, wxT("Modules") ); 
	
	this->SetMenuBar( mbar );
	
	statusBar = this->CreateStatusBar( 3, wxST_SIZEGRIP, wxID_ANY );
	contentSizer = new wxFlexGridSizer( 0, 1, 0, 0 );
	contentSizer->AddGrowableCol( 0 );
	contentSizer->AddGrowableRow( 0 );
	contentSizer->SetFlexibleDirection( wxBOTH );
	contentSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	mContent = new lms8001_mainPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	contentSizer->Add( mContent, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( contentSizer );
	this->Layout();
	contentSizer->Fit( this );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( lms8_AppFrame_view::OnClose ) );
	this->Connect( menuFileQuit->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( lms8_AppFrame_view::OnQuit ) );
	this->Connect( mnuConnectionSettings->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( lms8_AppFrame_view::OnShowConnectionSettings ) );
	this->Connect( menuHelpAbout->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( lms8_AppFrame_view::OnAbout ) );
	this->Connect( mnuADF4002->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( lms8_AppFrame_view::OnShowADF4002 ) );
	this->Connect( mnuSi5351C->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( lms8_AppFrame_view::OnShowSi5351C ) );
	this->Connect( mnuDeviceInfo->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( lms8_AppFrame_view::OnShowDeviceInfo ) );
	this->Connect( mnuSPI->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( lms8_AppFrame_view::OnShowSPI ) );
	this->Connect( mnuGPIO->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( lms8_AppFrame_view::OnShowGPIO ) );
}

lms8_AppFrame_view::~lms8_AppFrame_view()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( lms8_AppFrame_view::OnClose ) );
	this->Disconnect( idMenuQuit, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( lms8_AppFrame_view::OnQuit ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( lms8_AppFrame_view::OnShowConnectionSettings ) );
	this->Disconnect( idMenuAbout, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( lms8_AppFrame_view::OnAbout ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( lms8_AppFrame_view::OnShowADF4002 ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( lms8_AppFrame_view::OnShowSi5351C ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( lms8_AppFrame_view::OnShowDeviceInfo ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( lms8_AppFrame_view::OnShowSPI ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( lms8_AppFrame_view::OnShowGPIO ) );
	
}

lms8_dlgAbout_view::lms8_dlgAbout_view( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );
	
	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer2->SetFlexibleDirection( wxBOTH );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxFlexGridSizer* fgSizer3;
	fgSizer3 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer3->SetFlexibleDirection( wxBOTH );
	fgSizer3->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	imgLogo = new wxStaticBitmap( this, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxSize( 195,106 ), 0 );
	fgSizer3->Add( imgLogo, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxFlexGridSizer* fgSizer4;
	fgSizer4 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer4->AddGrowableCol( 0 );
	fgSizer4->AddGrowableRow( 0 );
	fgSizer4->SetFlexibleDirection( wxBOTH );
	fgSizer4->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	ID_STATICTEXT1 = new wxStaticText( this, wxID_ANY, wxT("LMS8001 Software "), wxDefaultPosition, wxDefaultSize, 0 );
	ID_STATICTEXT1->Wrap( -1 );
	ID_STATICTEXT1->SetFont( wxFont( 18, 70, 90, 90, false, wxEmptyString ) );
	
	fgSizer4->Add( ID_STATICTEXT1, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	txtVersion = new wxStaticText( this, wxID_ANY, wxT("v. 1.0.0.0\nBuild date: 2016-01-27"), wxDefaultPosition, wxDefaultSize, 0 );
	txtVersion->Wrap( -1 );
	fgSizer4->Add( txtVersion, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	fgSizer3->Add( fgSizer4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	fgSizer2->Add( fgSizer3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	txtDescription = new wxStaticText( this, wxID_ANY, wxT("Software Description"), wxDefaultPosition, wxDefaultSize, 0 );
	txtDescription->Wrap( -1 );
	fgSizer2->Add( txtDescription, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxFlexGridSizer* fgSizer5;
	fgSizer5 = new wxFlexGridSizer( 0, 3, 0, 50 );
	fgSizer5->SetFlexibleDirection( wxBOTH );
	fgSizer5->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	ID_STATICTEXT4 = new wxStaticText( this, wxID_ANY, wxT("Lime Microsystems\nSurrey Tech Centre\nOccam Road\nThe Surrey Research Park\nGuildford Surrey\nGU2 7YG\nUNITED KINGDOM"), wxDefaultPosition, wxDefaultSize, 0 );
	ID_STATICTEXT4->Wrap( -1 );
	fgSizer5->Add( ID_STATICTEXT4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxFlexGridSizer* fgSizer6;
	fgSizer6 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer6->SetFlexibleDirection( wxBOTH );
	fgSizer6->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	ID_STATICTEXT5 = new wxStaticText( this, wxID_ANY, wxT("Phone: +44 (0) 1483 685 063"), wxDefaultPosition, wxDefaultSize, 0 );
	ID_STATICTEXT5->Wrap( -1 );
	fgSizer6->Add( ID_STATICTEXT5, 1, wxALIGN_LEFT|wxALIGN_BOTTOM, 5 );
	
	ID_HYPERLINKCTRL1 = new wxHyperlinkCtrl( this, wxID_ANY, wxT("http://www.limemicro.com"), wxT("http://www.limemicro.com"), wxDefaultPosition, wxDefaultSize, wxHL_DEFAULT_STYLE );
	fgSizer6->Add( ID_HYPERLINKCTRL1, 1, wxALIGN_LEFT|wxALIGN_TOP, 5 );
	
	
	fgSizer5->Add( fgSizer6, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	fgSizer2->Add( fgSizer5, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	btnClose = new wxButton( this, wxID_ANY, wxT("Close"), wxDefaultPosition, wxDefaultSize, 0 );
	btnClose->SetDefault(); 
	fgSizer2->Add( btnClose, 1, wxBOTTOM|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	this->SetSizer( fgSizer2 );
	this->Layout();
	fgSizer2->Fit( this );
	
	// Connect Events
	this->Connect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( lms8_dlgAbout_view::OnInit ) );
	btnClose->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( lms8_dlgAbout_view::OnbtnClose ), NULL, this );
}

lms8_dlgAbout_view::~lms8_dlgAbout_view()
{
	// Disconnect Events
	this->Disconnect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( lms8_dlgAbout_view::OnInit ) );
	btnClose->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( lms8_dlgAbout_view::OnbtnClose ), NULL, this );
	
}
