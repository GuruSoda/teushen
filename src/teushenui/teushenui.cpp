///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "teushenui.h"

///////////////////////////////////////////////////////////////////////////

MainFrame::MainFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	m_panel1 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	m_recientes = new wxListCtrl( m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_LIST );
	bSizer3->Add( m_recientes, 0, wxALL|wxEXPAND, 5 );
	
	m_editor = new wxTextCtrl( m_panel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_PROCESS_TAB );
	bSizer3->Add( m_editor, 1, wxALL|wxEXPAND, 5 );
	
	
	bSizer2->Add( bSizer3, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );
	
	m_salida = new wxTextCtrl( m_panel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY );
	bSizer4->Add( m_salida, 1, wxALL|wxEXPAND, 5 );
	
	
	bSizer2->Add( bSizer4, 1, wxEXPAND, 5 );
	
	
	m_panel1->SetSizer( bSizer2 );
	m_panel1->Layout();
	bSizer2->Fit( m_panel1 );
	bSizer1->Add( m_panel1, 1, wxEXPAND | wxALL, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	m_menubar1 = new wxMenuBar( 0 );
	m_menu = new wxMenu();
	wxMenuItem* m_menuCargar;
	m_menuCargar = new wxMenuItem( m_menu, wxID_ANY, wxString( wxT("Cargar") ) + wxT('\t') + wxT("F3"), wxEmptyString, wxITEM_NORMAL );
	m_menu->Append( m_menuCargar );
	
	wxMenuItem* m_menuGrabar;
	m_menuGrabar = new wxMenuItem( m_menu, wxID_ANY, wxString( wxT("Grabar") ) + wxT('\t') + wxT("F2"), wxEmptyString, wxITEM_NORMAL );
	m_menu->Append( m_menuGrabar );
	
	m_menu->AppendSeparator();
	
	wxMenuItem* m_menuSalir;
	m_menuSalir = new wxMenuItem( m_menu, wxID_ANY, wxString( wxT("Salir") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu->Append( m_menuSalir );
	
	m_menubar1->Append( m_menu, wxT("Archivo") ); 
	
	m_menuTeushen = new wxMenu();
	wxMenuItem* m_menuEjecutar;
	m_menuEjecutar = new wxMenuItem( m_menuTeushen, wxID_ANY, wxString( wxT("Ejecutar") ) + wxT('\t') + wxT("F9"), wxEmptyString, wxITEM_NORMAL );
	m_menuTeushen->Append( m_menuEjecutar );
	
	m_menubar1->Append( m_menuTeushen, wxT("Teushen") ); 
	
	this->SetMenuBar( m_menubar1 );
	
	m_statusBar1 = this->CreateStatusBar( 1, wxST_SIZEGRIP, wxID_ANY );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_editor->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler( MainFrame::OnTecla ), NULL, this );
	this->Connect( m_menuEjecutar->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnEjecutar ) );
}

MainFrame::~MainFrame()
{
	// Disconnect Events
	m_editor->Disconnect( wxEVT_KEY_DOWN, wxKeyEventHandler( MainFrame::OnTecla ), NULL, this );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnEjecutar ) );
	
}
