
    UOS=$(shell uname)
    
    ifeq ($(OS),Windows_NT)
        PLATFORM = windows
    else
		ifeq ($(UOS),Linux)
			PLATFORM = linux
		endif
	endif
  ifeq ($(PLATFORM),windows)
    CC = C:/raylib/mingw/bin/g++.exe
    exename ?= SilverLeach.exe
    CFLAGS  = -static -O2 -Wall -Iexternal -DPLATFORM_DESKTOP -lopengl32 -lraylib -lgdi32 -lwinmm -Wl,--subsystem,windows
  endif
  ifeq ($(PLATFORM),linux)
    CC = g++
    exename ?= Test
    CFLAGS  = -O3 -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -no-pie -DLinux -DUseAsm -lminizip
  endif

  all: $(TARGET)
	  $(CC) Main.cpp -o $(exename) $(CFLAGS)