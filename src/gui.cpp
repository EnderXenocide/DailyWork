///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "gui.h"

///////////////////////////////////////////////////////////////////////////

MainFrameBase::MainFrameBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	m_menuBar = new wxMenuBar( 0 );
	m_menuFile = new wxMenu();
	wxMenuItem* menuFileExit;
	menuFileExit = new wxMenuItem( m_menuFile, wxID_EXIT, wxString( _("E&xit") ) + wxT('\t') + wxT("Alt+X"), wxEmptyString, wxITEM_NORMAL );
	m_menuFile->Append( menuFileExit );
	
	m_menuBar->Append( m_menuFile, _("&File") ); 
	
	this->SetMenuBar( m_menuBar );
	
	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* datesSizer;
	datesSizer = new wxBoxSizer( wxVERTICAL );
	
	m_calendar = new wxCalendarCtrl( this, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxCAL_SHOW_HOLIDAYS );
	datesSizer->Add( m_calendar, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 2 );
	
	m_treeDates = new wxTreeCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE );
	datesSizer->Add( m_treeDates, 1, wxALL|wxEXPAND, 2 );
	
	
	mainSizer->Add( datesSizer, 0, wxEXPAND, 5 );
	
	wxBoxSizer* editorSizer;
	editorSizer = new wxBoxSizer( wxVERTICAL );
	
	m_buttonGoNextAvailable = new wxButton( this, wxID_ANY, _("Go to the next available date"), wxDefaultPosition, wxDefaultSize, 0 );
	editorSizer->Add( m_buttonGoNextAvailable, 0, wxALL|wxEXPAND, 2 );
	
	m_buttonGoTomorrow = new wxButton( this, wxID_ANY, _("Go Tomorrow"), wxDefaultPosition, wxDefaultSize, 0 );
	editorSizer->Add( m_buttonGoTomorrow, 0, wxALL|wxEXPAND, 2 );
	
	m_staticTextCurDate = new wxStaticText( this, wxID_ANY, _("Unknow"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE|wxST_NO_AUTORESIZE );
	m_staticTextCurDate->Wrap( -1 );
	m_staticTextCurDate->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	editorSizer->Add( m_staticTextCurDate, 0, wxALL|wxEXPAND, 5 );
	
	m_editor = new wxRichTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0|wxVSCROLL|wxHSCROLL|wxNO_BORDER|wxWANTS_CHARS );
	editorSizer->Add( m_editor, 1, wxEXPAND | wxALL, 2 );
	
	m_buttonYesterday = new wxButton( this, wxID_ANY, _("Go Yesterday"), wxDefaultPosition, wxDefaultSize, 0 );
	editorSizer->Add( m_buttonYesterday, 0, wxALL|wxEXPAND, 2 );
	
	m_buttonGoPrevAvailable = new wxButton( this, wxID_ANY, _("Go to the preivous available date"), wxDefaultPosition, wxDefaultSize, 0 );
	editorSizer->Add( m_buttonGoPrevAvailable, 0, wxALL|wxEXPAND, 2 );
	
	
	mainSizer->Add( editorSizer, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( mainSizer );
	this->Layout();
	m_statusBar = this->CreateStatusBar( 1, wxST_SIZEGRIP, wxID_ANY );
	m_mainToolBar = this->CreateToolBar( wxTB_HORIZONTAL, wxID_ANY ); 
	m_mainToolBar->Realize(); 
	
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( MainFrameBase::OnCloseFrame ) );
	this->Connect( menuFileExit->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnExitClick ) );
	m_calendar->Connect( wxEVT_CALENDAR_DOUBLECLICKED, wxCalendarEventHandler( MainFrameBase::OnCalendarDblClick ), NULL, this );
	m_calendar->Connect( wxEVT_KILL_FOCUS, wxFocusEventHandler( MainFrameBase::OnCalendarKillFocus ), NULL, this );
	m_calendar->Connect( wxEVT_SET_FOCUS, wxFocusEventHandler( MainFrameBase::OnCalendarSetFocus ), NULL, this );
	m_treeDates->Connect( wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler( MainFrameBase::OnTreeSelChanged ), NULL, this );
	m_buttonGoNextAvailable->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrameBase::OnButtonGoNextAvailableClick ), NULL, this );
}

MainFrameBase::~MainFrameBase()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( MainFrameBase::OnCloseFrame ) );
	this->Disconnect( wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnExitClick ) );
	m_calendar->Disconnect( wxEVT_CALENDAR_DOUBLECLICKED, wxCalendarEventHandler( MainFrameBase::OnCalendarDblClick ), NULL, this );
	m_calendar->Disconnect( wxEVT_KILL_FOCUS, wxFocusEventHandler( MainFrameBase::OnCalendarKillFocus ), NULL, this );
	m_calendar->Disconnect( wxEVT_SET_FOCUS, wxFocusEventHandler( MainFrameBase::OnCalendarSetFocus ), NULL, this );
	m_treeDates->Disconnect( wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler( MainFrameBase::OnTreeSelChanged ), NULL, this );
	m_buttonGoNextAvailable->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrameBase::OnButtonGoNextAvailableClick ), NULL, this );
	
}

DlgPreference::DlgPreference( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Excludes Days") ), wxVERTICAL );
	
	wxString m_checkListExcludeDaysChoices[] = { _("Monday"), _("Tuesday") };
	int m_checkListExcludeDaysNChoices = sizeof( m_checkListExcludeDaysChoices ) / sizeof( wxString );
	m_checkListExcludeDays = new wxCheckListBox( sbSizer1->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, m_checkListExcludeDaysNChoices, m_checkListExcludeDaysChoices, 0 );
	sbSizer1->Add( m_checkListExcludeDays, 1, wxALL|wxEXPAND, 5 );
	
	m_staticText2 = new wxStaticText( sbSizer1->GetStaticBox(), wxID_ANY, _("All days can't be checked"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	sbSizer1->Add( m_staticText2, 0, wxALIGN_CENTER|wxALL, 5 );
	
	
	bSizer4->Add( sbSizer1, 1, wxEXPAND, 5 );
	
	m_sdbSizer1 = new wxStdDialogButtonSizer();
	m_sdbSizer1OK = new wxButton( this, wxID_OK );
	m_sdbSizer1->AddButton( m_sdbSizer1OK );
	m_sdbSizer1Cancel = new wxButton( this, wxID_CANCEL );
	m_sdbSizer1->AddButton( m_sdbSizer1Cancel );
	m_sdbSizer1->Realize();
	
	bSizer4->Add( m_sdbSizer1, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer4 );
	this->Layout();
	
	this->Centre( wxBOTH );
}

DlgPreference::~DlgPreference()
{
}
