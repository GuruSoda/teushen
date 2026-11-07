.SUFFIXES = .c .cpp

MIS_DEFINE= -DBOOST_ALL_NO_LIB -D__CON_LINEA_ERROR_
MIS_LINKS=

#CXXFLAGS=-march=pentium3m
CXXFLAGS=-march=native -fPIC -shared

BOOST=../../../boost
LIBRERIAS=../../../Librerias

# CXX=/usr/bin/arm-linux-gnueabi-g++-4.6

SALIDA_EJECUTABLE=../../libs

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
	${LIBRERIAS}/GuruCompat/ 

PARAM_INCLUDE:=$(addprefix "-I", ${INCLUDED})

VPATH=${INCLUDED}

DIR_OBJETOS = Objs/

PROGRAMA := funcEtiqueta.o
OBJETOS += $(addprefix ${DIR_OBJETOS}, ${PROGRAMA})

funcetiqueta.so: crear_directorios Makefile ${OBJETOS}
	@$(CXX) ${CXXFLAGS} $(LDFLAGS) -o $(SALIDA_EJECUTABLE)/$@ $(OBJETOS) ${MIS_LINKS}
	@echo "Todo terminado????"

${DIR_OBJETOS}%.o: %.cpp
	@echo "Compilando C++ $? -> $@"
	@${CXX} -O2 -x c++ -pipe ${CXXFLAGS} ${MIS_DEFINE} ${PARAM_INCLUDE} -c $? -o $@

${DIR_OBJETOS}%.o:%.c
	@echo "Compilando C $? -> $@"
	@${CC} -fPIC -O2 -s -pipe ${CFLAGS} ${PARAM_INCLUDE} ${MIS_DEFINE} -c $? -o $@

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

