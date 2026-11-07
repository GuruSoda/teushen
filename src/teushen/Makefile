.SUFFIXES = .c .cpp

MIS_DEFINE= -DBOOST_ALL_NO_LIB -D__CON_LINEA_ERROR_ -DTEUSHEN_FULL -DSQLITE_THREADSAFE=0
MIS_LINKS=-ldl

#CXXFLAGS=-march=pentium3m
CXXFLAGS=-march=native -fPIC

BOOST=../../../boost
LIBRERIAS=../../../Librerias

# CXX=/usr/bin/arm-linux-gnueabi-g++-4.6

SALIDA_EJECUTABLE=../../bin

VERSION=1.6

# Para compilar en 64 sobre 32, instalar el paquete g++-multilib
ifeq ($(BITS),64)
    CXXFLAGS+=-m64
else ifeq ($(BITS),32)
        CXXFLAGS+=-m32
endif

ifeq (${DEBUG},1)
 CXXFLAGS+=-ggdb -g3
else
 CXXFLAGS+=-s -O2
endif

# mismos parametros para compilar C/C++
CFLAGS=$(CXXFLAGS)

RAIZ=.
INCLUDED=${BOOST}/ \
	${LIBRERIAS}/ \
	${LIBRERIAS}/argtable/ \
	${LIBRERIAS}/polarssl/include/ \
	${LIBRERIAS}/polarssl/library/ \
	${LIBRERIAS}/GuruCompat/ \
	${LIBRERIAS}/sqlite/ \
	${LIBRERIAS}/GuruCompat/ 

PARAM_INCLUDE:=$(addprefix "-I", ${INCLUDED})

VPATH=${INCLUDED}

DIR_OBJETOS = Objs/

ARGTABLE := argtable2.o arg_end.o arg_file.o arg_int.o arg_lit.o arg_rem.o arg_str.o getopt.o getopt1.o
OBJETOS += $(addprefix ${DIR_OBJETOS}, ${ARGTABLE})

MIS_LIBS := sqlite3.o xtoa.o md5.o sha1.o sha2.o sha4.o GuruConfigLeer.o GuruConfigV2.o 
OBJETOS += $(addprefix ${DIR_OBJETOS}, ${MIS_LIBS})

PROGRAMA := teushen.o
OBJETOS += $(addprefix ${DIR_OBJETOS}, ${PROGRAMA})

teushen: crear_directorios Makefile ${OBJETOS}
	@$(CXX) ${CXXFLAGS} $(LDFLAGS) -o $(SALIDA_EJECUTABLE)/$@ $(OBJETOS) ${MIS_LINKS}
	@echo "Todo terminado????"

${DIR_OBJETOS}%.o: %.cpp
	@echo "Compilando C++ $? -> $@"
	@${CXX} -O2 -x c++ -std=c++11 -pipe ${CXXFLAGS} ${MIS_DEFINE} ${PARAM_INCLUDE} -c $? -o $@

${DIR_OBJETOS}%.o:%.c
	@echo "Compilando C $? -> $@"
	@${CC} -O2 -s -pipe ${CFLAGS} ${PARAM_INCLUDE} ${MIS_DEFINE} -c $? -o $@

clean:
	@rm -f ${OBJETOS}

crear_directorios:
	@mkdir -p ${DIR_OBJETOS}

compilar:
	@echo ${VPATH} ${OBJETOS}

envdeb:
	@$(eval DST:=/usr/local)

envopt: 
	@$(eval DST:=/opt/atlas)

makedeb: teushen 
	@$(eval DIR_TEMP:=$(shell mktemp -du --suffix=teushen))
	@$(eval RELEASE:=$(shell date +%Y%m%d.%H%M))
	@mkdir -p ${DIR_TEMP}${DST}/bin
	@mkdir -p ${DIR_TEMP}${DST}/libs
	@mkdir -p ${DIR_TEMP}/DEBIAN
	@cp ../../bin/teushen ${DIR_TEMP}${DST}/bin
	@sed 's/^Version:\ [0-9]\..*/Version: ${VERSION}-${RELEASE}/' debian/control > ${DIR_TEMP}/DEBIAN/control 
	@dpkg -b ${DIR_TEMP} ../../teushen-${VERSION}-${RELEASE}_i386.deb
	@rm -rf ${DIR_TEMP}

deb: envdeb makedeb
	@echo "Todo Listo."

debopt: envopt makedeb
	@echo "Todo Listo."

