#include <GuruHttp/GuruhttpInterface.hpp>
#include <GuruDirectorio.hpp>
#include <GuruInterprete/TeushenEx.hpp>
#include <GuruHttp/GuruhttpFunciones.hpp>

#include <GuruInterprete/GuruPreprocesador.hpp>

#include <string>

static GuruPool_threadsafe<teushenEx> pool;

class teushenWeb: public IGuruhttpSitio {
	public:
		teushenWeb() {}
		virtual ~teushenWeb() {}

		void procesarGet() {
			std::string script(request()->recurso().ruta_absoluta() + ".teushen");

			if (!GuruDirectorio::existe(script)) throw GuruhttpExcepcion(404);

			if (!GuruDirectorio::esArchivo(script)) throw GuruhttpExcepcion(404);

			ostringstream oss;

			ejecutar_teushen(script, oss);

			// La ruta absoluta solo es modificada cuando el escript pide bajar un archivo 
			// y no enviar la salida del procesamiento del script.
			if (GuruStringAlgo::stringequals(request()->recurso().ruta_absoluta() + ".teushen", script)) {
				
				if (response()->content_type().empty()) response()->content_type("text/plain");
				
				response()->enviar_pagina(oss);

			} else
				response()->enviar_archivo();
		}

		ostream& ejecutar_teushen(const string& script, ostream& salida) {
			teushenEx* interprete = pool.obtener();

			interprete->limpiar();

			GuruhttpFunciones	funchttp(request());

			if (!request()->parametro().empty()) {
				map<string, string>::iterator itend = request()->parametro().end();
				for (map<string, string>::iterator it = request()->parametro().begin(); it != itend; ++it)
					interprete->agregar_variable(it->first, it->second);
			}

			interprete->agregar_funciones(&funchttp);

			ifstream ifs(script.c_str(), ios_base::binary);

			if (!ifs.is_open()) throw GuruhttpExcepcion(403);

			ControlFin_instruccion control_interprete("<?Guru", "?>");

			interprete->agregar_control(GuruInterprete::fin_analisis, &control_interprete);

			bool ok = true;

			try {
				interprete->interpretar(ifs, salida);
			} catch (GuruInterprete::Interprete::InterpreteException& e) {
				salida << "Error Interprete:" << e.what() << endl;
//				ok = false;
			} catch (std::exception& e) {
				salida << "Error gral:" << e.what() << endl;
			} catch (...) { // para que quede atrapado cualquier otra excepcion.
			}

			interprete->borrar_funciones(&funchttp);
			pool.liberar(interprete);

			ifs.close();

			if (!ok) throw GuruhttpExcepcion(500);

			return salida;
		}
};

#ifdef __cplusplus
extern "C" {
#endif

#if (defined __WIN32__) || (defined WIN32)
	#define LIBRARY_EXPORT __declspec(dllexport)
#else
	#define LIBRARY_EXPORT
#endif

LIBRARY_EXPORT 
GuruhttpInterface* libteushen (const std::map<std::string, std::string>& env) {
	try {
		std::map<std::string, std::string>::const_iterator it = env.find(string("base"));

		if (it != env.end()) {};

	} catch (std::exception&) {}

	return new GuruhttpSitio<teushenWeb>();
};

#ifdef __cplusplus
}
#endif
