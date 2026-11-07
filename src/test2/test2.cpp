#include <GuruInterprete/Teushen.hpp>
#include <GuruInterprete/GuruCargaLibs.hpp>
#include <GuruSingleton.hpp>
#include <sstream>

void nada () {
	teushen::interprete inter;
	std::istringstream iss(string("println(\"Adios Mundo Cruel\") println(\"PROCESSOR_IDENTIFIER:\", sis.var(\"PROCESSOR_IDENTIFIER\"))"));

	try  {
		inter.interpretar(iss, cout);
	} catch (InterpreteException& e) {
		cout << e.what() << endl;
	}
};

int main(int argc, char* argv[])
{
	GuruSingleton<teushen::GuruCargaLibs>::instancia()->cargar("d:\\Desarrollo\\teushen\\libs\\");

	for (int i = 0;i<1000;i++) {
		nada ();
	}

	GuruSingleton<teushen::GuruCargaLibs>::instancia()->descargar();

	return 0;
}
