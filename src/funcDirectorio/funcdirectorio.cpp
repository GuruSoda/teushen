#ifndef __FUNCDIRECTORIOLIB__
#define __FUNCDIRECTORIOLIB__

#include <GuruInterprete/GuruInterprete.hpp>
#include <GuruInterprete/GuruDirectorioFunciones.hpp>

#ifdef __cplusplus
        extern "C" {
#endif

#if (defined __WIN32__) || (defined WIN32)
#define LIBRARY_EXPORT __declspec(dllexport)
#else
#define LIBRARY_EXPORT
#endif

LIBRARY_EXPORT GuruInterprete::IGuruFuncion* ptr_funciones () { return new GuruDirectorioFunciones();};

#ifdef __cplusplus
        }
#endif

#endif
