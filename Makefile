CC	:= gcc
CFLAGS	:= -Wall -g
LDFLAGS :=

MODULES   := Model Control View
SRC_DIR   := $(addprefix src/,$(MODULES))

MODEL_LIB := Model ChessCoordinate ChessPlayer ChessCoordinateList ChessMoveList ChessBoard ChessMove

CONTROL_LIB := Control

VIEW_LIB := View

ifeq ($(SESSION),ubuntu)
	CFLAGS +=-DLINUX_OS
endif

ifeq ($(GUI_ENABLE),y)
	GUI_FLAG=-DGUI_ENABLE $(shell pkg-config --cflags sdl2 SDL2_image SDL2_ttf)
	VIEW_LIB+= display render sdlUtilities ObjectHandleList
	LDFLAGS+= $(shell pkg-config --libs sdl2 SDL2_image SDL2_ttf)
else
        GUI_FLAG=
        CFLAGS +=-ansi
endif

MODEL_LIB_DEPEND := $(addprefix build/lib,$(MODEL_LIB))
MODEL_LIB_DEPEND := $(addsuffix .a,$(MODEL_LIB_DEPEND))
MODEL_LIB_COMPILE := $(addprefix -l,$(MODEL_LIB))

CONTROL_LIB_DEPEND := $(addprefix build/lib,$(CONTROL_LIB))
CONTROL_LIB_DEPEND := $(addsuffix .a,$(CONTROL_LIB_DEPEND))
CONTROL_LIB_COMPILE := $(addprefix -l,$(CONTROL_LIB))

VIEW_LIB_DEPEND := $(addprefix build/lib,$(VIEW_LIB))
VIEW_LIB_DEPEND := $(addsuffix .a,$(VIEW_LIB_DEPEND))
VIEW_LIB_COMPILE := $(addprefix -l,$(VIEW_LIB))

INCLUDES  := $(addprefix -Iinc/,$(MODULES))

VPATH = $(SRC_DIR) src

.PHONY: all clean test

all: ChessXIV

test: ModelUnitTest

clean:
	rm build/*
	rm bin/*

build/%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ $(GUI_FLAG)

build/lib%.a: build/%.o
	ar rc $@ $<
	ranlib $@

#StructuredLibraryTest: build/StructuredLibraryTest.o build/libModel.a build/libControl.a build/libView.a
#	$(CC) build/StructuredLibraryTest.o -Lbuild -lModel -lControl -lView -o build/$@ $(CFLAGS)

StructuredLibraryTest: build/StructuredLibraryTest.o $(MODEL_LIB_DEPEND) build/libControl.a build/libView.a
	$(CC) build/StructuredLibraryTest.o -Lbuild -lControl -lView $(MODEL_LIB_COMPILE) -o build/$@ $(CFLAGS)
	build/$@
	
CheckMate: build/TestCheckMate.o $(MODEL_LIB_DEPEND) $(CONTROL_LIB_DEPEND) $(VIEW_LIB_DEPEND)
	$(CC) build/TestCheckMate.o -Lbuild $(CONTROL_LIB_COMPILE) $(VIEW_LIB_COMPILE) $(MODEL_LIB_COMPILE) -o bin/$@ $(CFLAGS)
	
Transform:  build/TestSpecialMove_Transforming.o $(MODEL_LIB_DEPEND) $(CONTROL_LIB_DEPEND) $(VIEW_LIB_DEPEND)
	$(CC) build/TestSpecialMove_Transforming.o -Lbuild $(CONTROL_LIB_COMPILE) $(VIEW_LIB_COMPILE) $(MODEL_LIB_COMPILE) -o bin/$@ $(CFLAGS)

EnPassant:  build/TestSpecialMove_EnPassant.o $(MODEL_LIB_DEPEND) $(CONTROL_LIB_DEPEND) $(VIEW_LIB_DEPEND)
	$(CC) build/TestSpecialMove_EnPassant.o -Lbuild $(CONTROL_LIB_COMPILE) $(VIEW_LIB_COMPILE) $(MODEL_LIB_COMPILE) -o bin/$@ $(CFLAGS)

Castling:  build/TestSpecialMove_Castling.o $(MODEL_LIB_DEPEND) $(CONTROL_LIB_DEPEND) $(VIEW_LIB_DEPEND)
	$(CC) build/TestSpecialMove_Castling.o -Lbuild  $(CONTROL_LIB_COMPILE) $(VIEW_LIB_COMPILE) $(MODEL_LIB_COMPILE) -o bin/$@ $(CFLAGS)
	
ModelUnitTest: build/ModelUnitTest.o $(MODEL_LIB_DEPEND)
	$(CC) build/ModelUnitTest.o -Lbuild $(MODEL_LIB_COMPILE) -o bin/$@ $(CFLAGS)

TestDrawingFuncs: build/TestDrawingFuncs.o $(VIEW_LIB_DEPEND)
	$(CC) build/TestDrawingFuncs.o -Lbuild $(VIEW_LIB_COMPILE) $(LDFLAGS) -o bin/$@ $(CFLAGS)

TestGUI: build/TestGUI.o $(VIEW_LIB_DEPEND) $(MODEL_LIB_DEPEND)
	$(CC) build/TestGUI.o -Lbuild $(VIEW_LIB_COMPILE) $(MODEL_LIB_COMPILE) $(LDFLAGS) -o bin/$@ $(CFLAGS)
	
ViewUnitTest: build/ViewUnitTest.o build/libModel.a build/libView.a
	$(CC) build/ViewUnitTest.o -Lbuild -lModel -lView -o bin/$@ $(CFLAGS)

ControlUnitTest: build/ControlUnitTest.o build/libControl.a
	$(CC) build/ControlUnitTest.o -Lbuild -lControl -o bin/$@ $(CFLAGS)
	
ChessXIV: build/ChessXIV.o $(VIEW_LIB_DEPEND) $(CONTROL_LIB_DEPEND) $(MODEL_LIB_DEPEND)
	$(CC) build/ChessXIV.o -Lbuild $(CONTROL_LIB_COMPILE) $(VIEW_LIB_COMPILE) $(MODEL_LIB_COMPILE) -o bin/$@ $(CFLAGS)
	
#This line does nothing
