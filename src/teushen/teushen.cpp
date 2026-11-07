#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>

#include <argtable/argtable2.h>
#include <GuruInterprete/TeushenEx.hpp>
#include <GuruDirectorio.hpp>

std::vector< std::pair<std::string, std::string> >& parser_param_var(const std::string& linea, std::vector< std::pair<std::string, std::string> >& variables) {

	GuruTokenEx x(",");

	variables.clear();

	size_t total = x.extraer(linea);
	if (total > 0) {
		GuruTokenEx y("=");

		for (size_t i = 0; i < total; i++) {

			if (y.extraer(x[i]) > 0) {
				variables.push_back(make_pair(y[0], y[1]));
			}
		}
	}

	return variables;
}

int main(int argc, char* argv[])
{
	struct arg_lit* opt_help		= arg_lit0(NULL,"help", "Muestra la ayuda.");
	struct arg_lit* opt_verbose		= arg_lit0(NULL,"verbose", "Muestra informacion extra.");
	struct arg_str* opt_entrada		= arg_str1("i","entrada","archivo", "Nombre archivo entrada.");
	struct arg_str* opt_salida		= arg_str0("o","salida","archivo", "Nombre archivo de salida.");
	struct arg_str* opt_variables	= arg_strn("v","variable","Variable", 0, argc+2, "Definicion de variable.");
	struct arg_str* opt_librerias	= arg_str0("l","libreria","archivo", "Libreria a cargar.");
	struct arg_lit* opt_funciones	= arg_lit0("f","funciones","Lista las funciones cargadas.");

	struct arg_end* end				= arg_end(20);

	void* argtable[]				= {opt_help,opt_verbose,opt_entrada,opt_salida,opt_variables, opt_librerias,opt_funciones,end};
	int nerrors;

	nerrors = arg_parse(argc,argv,argtable);

	if (nerrors > 0) {
		arg_print_glossary(stdout,argtable,"  %-25s %s\n");
		return 1;
	}

	if (opt_help->count > 0) {
		arg_print_glossary(stdout,argtable,"  %-25s %s\n");
		return 0;
	}

	teushenEx lang;

	if (opt_librerias->count > 0) lang.cargar_desde_librerias(string(opt_librerias->sval[0]));

	if (opt_funciones->count > 0) {
		for (GuruInterprete::Interprete::iterator_funciones it=lang.begin_funciones();it!=lang.end_funciones();++it) cout << *it << endl;

		return 0;
	}

	ifstream ifs;

	ifs.open(opt_entrada->sval[0], ios_base::binary);

	if (!ifs.is_open()) {
		cout << "Error abriendo " << opt_entrada->sval[0] << endl;
		return 1;
	}

	ofstream ofs;

	if (opt_salida->count > 0) {
			ofs.open(opt_salida->sval[0], ios_base::binary | ios_base::trunc);

			if (!ofs.is_open()) {
				cout << "Error abriendo " << opt_salida->sval[0] << endl;
				return 1;
			}

			cout.rdbuf(ofs.rdbuf());
	} 

	std::vector< std::pair<std::string, std::string> > variables;

	if (opt_variables->count > 0) parser_param_var(opt_variables->sval[0], variables);

	try {
		for (std::vector< std::pair<std::string, std::string> >::iterator it = variables.begin(); it != variables.end(); ++it)
			lang.agregar_variable(it->first, it->second);

		lang.interpretar(ifs, cout);

		ifs.close();
		if (opt_salida->count > 0 && ofs.is_open()) ofs.close();
	}catch (GuruInterprete::Interprete::InterpreteException& e) {
		cerr << "Error:" << e.what() << endl;
	}

	return 0;
}
