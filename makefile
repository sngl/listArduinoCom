WORKDIR = pwd

CC = i586-mingw32msvc-gcc
CXX = i586-mingw32msvc-g++
LD = i586-mingw32msvc-g++

INC =
CFLAGS = -Wall
RESINC =
LIBDIR =
LIB = -lgdi32 -luser32 -lkernel32
LDFLAGS =


INC_RELEASE = $(INC)
CFLAGS_RELEASE = $(CFLAGS) -O2
RESINC_RELEASE = $(RESINC)
RCFLAGS_RELEASE = $(RCFLAGS)
LIBDIR_RELEASE = $(LIBDIR)
LIB_RELEASE = $(LIB) -lsetupapi
LDFLAGS_RELEASE = $(LDFLAGS) -s
OBJDIR_RELEASE = obj/
DEP_RELEASE =
OUT_RELEASE = bin/listArduinoCom.exe



OBJ_RELEASE = $(OBJDIR_RELEASE)/main.o

all: release

clean: clean_release

before_release:
	mkdir -p bin/
	mkdir -p $(OBJDIR_RELEASE)

after_release:

release: before_release out_release after_release

out_release: before_release $(OBJ_RELEASE) $(DEP_RELEASE)
	$(LD) $(LIBDIR_RELEASE) -o $(OUT_RELEASE) $(OBJ_RELEASE) $(LDFLAGS_RELEASE) $(LIB_RELEASE)

$(OBJDIR_RELEASE)/main.o: main.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c main.cpp -o $(OBJDIR_RELEASE)/main.o

clean_release:
	rm -r $(OBJ_RELEASE) $(OUT_RELEASE)
	rmdir bin/Release
	rmdir $(OBJDIR_RELEASE)

.PHONY: before_release after_release clean_release


