#include <iostream>
#include <fstream>
#include <ostream>

#include <argtable/argtable2.h>

#include <GuruInterprete/GuruLenguaje.hpp>
#include <GuruInterprete/GuruPreprocesador.hpp>
#include <GuruInterprete/GuruCargaLibs.hpp>

int main(int argc, char* argv[])
{
	struct arg_lit* opt_help		= arg_lit0(NULL,"help", "Muestra la ayuda.");
	struct arg_lit* opt_verbose		= arg_lit0(NULL,"verbose", "Muestra informacion extra.");
	struct arg_str* opt_entrada		= arg_str1("i","entrada","archivo", "Nombre archivo entrada.");
	struct arg_str* opt_salida		= arg_str0("o","salida","archivo", "Nombre archivo salida.");
	struct arg_str* opt_librerias	= arg_str0("l","libreria","archivo", "Libreria a cargar.");

	struct arg_end* end				= arg_end(20);

	void* argtable[]				= {opt_help,opt_verbose,opt_entrada,opt_salida, opt_librerias,end};
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

	string archivo_salida;
	if (opt_salida->count == 0) archivo_salida = opt_salida->sval[0];

	ifstream ifs;

	ifs.open(opt_entrada->sval[0], ios_base::binary);

	if (!ifs.is_open()) {
		cout << "Error abriendo " << opt_entrada->sval[0] << endl;
		return 1;
	}

	string libs;

	libs = (opt_librerias->count > 0) ? opt_librerias->sval[0] : "..\\libs\\";

	ostream os(cout.rdbuf());
	ofstream ofs;

	if (!archivo_salida.empty()) {
		ofs.open(archivo_salida.c_str(),ios_base::binary|ios_base::trunc);

		if (!ofs.is_open()) {
			cout << "Error abriendo " << archivo_salida << endl;
			return 2;
		} else {
			os.rdbuf(ofs.rdbuf());
		}
	}

	GuruLenguaje		lang;
	GuruPreprocesador	prepro;
	teushen::GuruCargaLibs		librerias;

/*
	cout << "GuruLenguaje:" << sizeof(GuruLenguaje) << endl;
	cout << "GuruPreprocesador:" << sizeof(GuruPreprocesador) << endl;
	cout << "GuruCargaLibs:" << sizeof(GuruCargaLibs) << endl;
*/

	librerias.cargar(libs);

	for (teushen::GuruCargaLibs::iterator it=librerias.begin();it!=librerias.end();++it) {
		lang.agregar_funciones(it.funciones());
	}

	try {
		prepro.procesar(ifs, os, lang, "<?Guru","?>");
	}catch (string& e) {
		cout << "Error:" << e << endl;
	}

	return 0;
}
