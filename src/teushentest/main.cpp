#include <GuruInterprete/Teushen.hpp>
#include <wx/wx.h>

// Modificar por el .h generado por wxFormbuilder
#include "teushentest.h"

// Modificar UI_MainFrame por el nombre de la clase generada por wxFormbuilder dentro de .h

class ui : public MainFrame {
protected:
	void OnSalirClick(wxCommandEvent& event) { }
	virtual void OnTecla(wxKeyEvent& event) {
		if (event.GetKeyCode() == WXK_F5) {
			ejecutarCodigo();
		}

		event.Skip();
	}
public:
	ui(wxWindow* parent):MainFrame(parent) {
//		m_editor->RegisterHotKey(1, 0, VK_F9); //WXK_F9
	}

	void ejecutarCodigo() {

		m_salida->Clear();

		teushen interprete;

		stringstream ifs;
		ostringstream ofs;

		ifs << m_editor->GetValue();

		try {
			interprete.interpretar(ifs, ofs);

			*m_salida << ofs.str();
		} catch (GuruInterprete::Interprete::InterpreteException& e) {
			*m_salida << "Error:" << e.what() << "\n";
		} catch (...) { // para que quede atrapado cualquier otra excepcion.
		}
	}
};

class wxWidgetsApp : public wxApp {
public:
	wxWidgetsApp() {};
	virtual ~wxWidgetsApp() {};

	virtual bool OnInit() {
		ui* dialog = new ui( (wxWindow*)NULL );
		dialog->Show();
		SetTopWindow( dialog );
		return true;
	}
};

DECLARE_APP(wxWidgetsApp)

IMPLEMENT_APP(wxWidgetsApp)
