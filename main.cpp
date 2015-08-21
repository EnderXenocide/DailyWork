/*********************************************************************
 * Name:      	main.cpp
 * Purpose:   	Implements simple wxWidgets application with GUI
 * 				created using wxFormBuilder.
 * Author:    
 * Created:   
 * Copyright: 
 * License:   	wxWidgets license (www.wxwidgets.org)
 * 
 * Notes:		Note that all GUI creation code is implemented in
 * 				gui.cpp source file which is generated by wxFormBuilder.
 *********************************************************************/

#include "main.h"
#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP

// initialize the application
IMPLEMENT_APP(MainApp);

////////////////////////////////////////////////////////////////////////////////
// application class implementation 
////////////////////////////////////////////////////////////////////////////////

bool MainApp::OnInit()
{
    START_EASYLOGGINGPP(wxGetApp().argc, wxGetApp().argv);
	SetTopWindow( new MainFrame( NULL ) );
	GetTopWindow()->Show();
	
	// true = enter the main loop
	return true;
}

////////////////////////////////////////////////////////////////////////////////
// main application frame implementation 
////////////////////////////////////////////////////////////////////////////////

MainFrame::MainFrame(wxWindow *parent) : MainFrameBase( parent )
{
 //   dwparser.ConnectCallback([&this](int i) { this.callbackFunction(i); })
    dwparser.ConnectCallback([this](std::string msg) { this->OnStatusBarMessage(msg); });
    if ( ! dwparser.Parse()) 
        LoadDatesTree(); 
}

MainFrame::~MainFrame()
{
}

// BEGIN EVENTS

void MainFrame::OnCloseFrame(wxCloseEvent& event)
{
	Destroy();
}

void MainFrame::OnExitClick(wxCommandEvent& event)
{
	Destroy();
}

void MainFrame::OnCalendarDblClick(wxCalendarEvent& event) 
{ 
    wxTreeItemId ItemID=m_treeDates->GetSelection();
    wxString msg = m_treeDates->GetItemText(ItemID);
    OnStatusBarMessage(msg.ToStdString());
//    if (ItemID != NULL)
 //       m_treeDates->Delete(ItemID);
 //wxWindowBase child;
   // m_treeDates->AddChild()
}  

void MainFrame::OnTreeSelChanged( wxTreeEvent& event )
{
    wxString texte = dwparser.GetWorkFromTree(m_treeDates);
    m_editor->Clear();
    m_editor->WriteText(texte);
}

void MainFrame::OnStatusBarMessage(std::string msg)
{
	//std::cout << msg << std::endl;
    LOG(INFO) << msg ;
    m_statusBar->SetStatusText(wxString::FromUTF8(msg.c_str()));
}

// END EVENTS

void MainFrame::LoadDatesTree()
{
    dwparser.LoadDatesTree(m_treeDates, FALSE);  // LoadDatesTreeHierarchy  unimplemented
}

