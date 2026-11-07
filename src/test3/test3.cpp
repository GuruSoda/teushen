#include <sstream>

#include <GuruInterprete/Teushen.hpp>

int main(int argc, char* argv[])
{
	teushen::interprete i;

	std::istringstream iss(string("sql.abrir(\"librerias.sqlite\") sql.ejecutar(\"select nombre from archivo where id_archivo=975\") println(\"Resultado: \", sql.columna(\"0\")) var(\"nada\", \"151\") nada=\"0010\" "));
//	std::istringstream iss(string("sql.abrir(\"librerias.sqlite\") sql.ejecutar(\"select id_archivo from archivo where nombre=\\\"http_client_winhttp.cpp\\\"\") var(\"nada\", \"151\") nada=\"0010\" println(\"Resultado: \", sql.columna(\"0\"))"));

	try  {
		i.interpretar(iss, cout, static_cast<uint32_t>(iss.str().length()));
	} catch (InterpreteException& e) {
		cout << e.what() << endl;
	}

	return 0;
}
