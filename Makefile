CC	:= gcc
CFLAGS	:= -ansi -Wall -g

ifeq ($(GUI_ENABLE),y)
	GUI_FLAG=-DGUI_ENABLE
else
        GUI_FLAG=
endif

mkdir bin

MODULES   := Model Control View
SRC_DIR   := $(addprefix src/,$(MODULES))

MODEL_LIB := Model ChessCoordinate ChessPlayer ChessCoordinateList ChessBoard 
MODEL_LIB_DEPEND := $(addprefix build/lib,$(MODEL_LIB))
MODEL_LIB_DEPEND := $(addsuffix .a,$(MODEL_LIB_DEPEND))
MODEL_LIB_COMPILE := $(addprefix -l,$(MODEL_LIB))

CONTROL_LIB := Control
CONTROL_LIB_DEPEND := $(addprefix build/lib,$(CONTROL_LIB))
CONTROL_LIB_DEPEND := $(addsuffix .a,$(CONTROL_LIB_DEPEND))
CONTROL_LIB_COMPILE := $(addprefix -l,$(CONTROL_LIB))

VIEW_LIB := View
VIEW_LIB_DEPEND := $(addprefix build/lib,$(VIEW_LIB))
VIEW_LIB_DEPEND := $(addsuffix .a,$(VIEW_LIB_DEPEND))
VIEW_LIB_COMPILE := $(addprefix -l,$(VIEW_LIB))

INCLUDES  := $(addprefix -I,$(SRC_DIR))

VPATH = $(SRC_DIR) src

.PHONY: all clean

all: StructuredLibraryTest

clean:
	rm build/*
	rm ChessXIV

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

ModelUnitTest: build/ModelUnitTest.o $(MODEL_LIB_DEPEND)
	$(CC) build/ModelUnitTest.o -Lbuild $(MODEL_LIB_COMPILE) -o bin/$@ $(CFLAGS)
	
ViewUnitTest: build/ViewUnitTest.o build/libModel.a build/libView.a
	$(CC) build/ViewUnitTest.o -Lbuild -lModel -lView -o bin/$@ $(CFLAGS)

ControlUnitTest: build/ControlUnitTest.o build/libControl.a
	$(CC) build/ControlUnitTest.o -Lbuild -lControl -o bin/$@ $(CFLAGS)
	
ChessXIV: build/ChessXIV.o $(VIEW_LIB_DEPEND) $(CONTROL_LIB_DEPEND) $(MODEL_LIB_DEPEND)
	$(CC) build/ChessXIV.o -Lbuild $(CONTROL_LIB_COMPILE) $(VIEW_LIB_COMPILE) $(MODEL_LIB_COMPILE) -o bin/$@ $(CFLAGS)
	
#This line does nothing
