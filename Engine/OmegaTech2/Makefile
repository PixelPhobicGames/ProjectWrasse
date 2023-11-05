CFLAGS = -O3 --std=c++20
LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
COMP = g++
BUILD_DIR = Build

# Create the Build directory if it doesn't exist
$(shell mkdir -p $(BUILD_DIR))

OBJS = $(BUILD_DIR)/raygui.o \
  $(BUILD_DIR)/Encoder.o \
  $(BUILD_DIR)/Language.o \
  $(BUILD_DIR)/OTCustom.so \
  $(BUILD_DIR)/Main.o

COREHEADERS = Source/Core.hpp \
  $(BUILD_DIR)/Encoder.o \
  $(BUILD_DIR)/Main.o

all: $(BUILD_DIR)/OTENGINE

$(BUILD_DIR)/OTENGINE: $(OBJS)
	$(COMP) $(OBJS) -o OTENGINE $(CFLAGS) $(LDFLAGS) -L. -l:Custom.so -Wl,-rpath=.

$(BUILD_DIR)/Main.o: Source/Main.cpp Source/*.hpp Source/Parasite/*.hpp Source/Language/*.hpp
	$(COMP) $(CFLAGS) -c Source/Main.cpp -o $@ $(LDFLAGS)

# Compiles .so for Custom Engine Behavior
$(BUILD_DIR)/OTCustom.so: Source/Custom/OTCustom.cpp
	$(COMP) $(CFLAGS) -c Source/Custom/OTCustom.cpp -o $@ $(LDFLAGS)

$(BUILD_DIR)/Language.o: Source/Language/Language.cpp
	$(COMP) $(CFLAGS) -c Source/Language/Language.cpp -o $@ $(LDFLAGS)

$(BUILD_DIR)/Encoder.o: Source/Encoder/Encoder.cpp
	$(COMP) $(CFLAGS) -c Source/Encoder/Encoder.cpp -o $@ $(LDFLAGS)

$(BUILD_DIR)/raygui.o: Source/raygui/raygui.c
	$(COMP) $(CFLAGS) -c Source/raygui/raygui.c -o $@ -shared -DRAYGUI_IMPLEMENTATION -DBUILD_LIBTYPE_SHARED -static-libgcc -lopengl32 -lgdi32 -lwinmm

.PHONY: clean
clean:
	rm -f $(BUILD_DIR)/*.o $(BUILD_DIR)/OTENGINE
