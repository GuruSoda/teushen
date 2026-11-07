#include <GuruInterprete\GuruLenguaje.hpp>
#include <sstream>

#include <GuruInterprete\GuruStringFunciones.hpp>
#include <GuruInterprete\GuruSistemaFunciones.hpp>

int main(int argc, char* argv[])
{
	GuruLenguaje i;

	GuruStringFunciones a;
	GuruSistemaFunciones b;

	i.agregar_funciones(a);
	i.agregar_funciones(b);

	std::istringstream iss(string("var(\"nada\", \"151\") nada=\"0010\" println(\"Variable TMP: \", sis.var(\"TMP\"));"));

	try  {
		i.interpretar(iss, cout, static_cast<uint32_t>(iss.str().length()));
	} catch (InterpreteException& e) {
		cout << e.what() << endl;
	}

	return 0;
}
