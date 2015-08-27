MINGWPATH=/cygdrive/c/cygwin
CYGPATH=/cygdrive/c/cygwin

MATLABROOT=/cygdrive/c/Progra~1/MATLAB/R2011a
CC=x86_64-w64-mingw32-gcc
CFLAG= -m64 -I./include -shared -I$(MATLABROOT)/extern/include

#MEXFLAG=-m64 -shared -DMATLAB_MEX_FILE -I$(MATLABROOT)/extern/include -Wl,--export-all-symbols $(LIBS) $(MEXSRC) -o $(MEXTGT).mexw64

LIBS= -Llib -lgclibo -lgclib -L$(MATLABROOT)/bin/win64 -L$(MATLABROOT)/extern/lib/win64/microsoft -lmex -lmx -lmwlapack -lmwblas -leng
SRC= src/GOpen.c src/GCommand.c src/GClose.c
EXE= $(patsubst src/%.c, %.mexw64, $(SRC))

all: dir $(EXE)

dir:
	mkdir -p bin
	cp -n dll/*.dll bin
	cp src/*.m bin

%.mexw64: src/%.c
	$(CC) $(CFLAG) $< $(LIBS) -o bin/$@