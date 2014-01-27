CC	:= gcc
CFLAGS	:= -ansi -Wall -g

ifeq ($(GUI_ENABLE),y)
	GUI_FLAG=-DGUI_ENABLE
else
        GUI_FLAG=
endif


MODULES   := Model Control View
SRC_DIR   := $(addprefix src/,$(MODULES))

MODEL_LIB := Model ChessBoard ChessCoordinate ChessPlayer ChessCoordinateList
MODEL_LIB_DEPEND := $(addprefix build/lib,$(MODEL_LIB))
MODEL_LIB_DEPEND := $(addsuffix .a,$(MODEL_LIB_DEPEND))
MODEL_LIB_COMPILE := $(addprefix -l,$(MODEL_LIB))

INCLUDES  := $(addprefix -I,$(SRC_DIR))

VPATH = $(SRC_DIR) src

.PHONY: all clean

all: StructuredLibraryTest

clean:
	rm build/*

test:
	@echo "MODEL_LIB_DEPEND = " $(MODEL_LIB_DEPEND)

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

ViewUnitTest: build/ViewUnitTest.o build/libModel.a build/libView.a
	$(CC) build/ViewUnitTest.o -Lbuild -lModel -lView -o build/$@ $(CFLAGS)

ControlUnitTest: build/ControlUnitTest.o build/libControl.a
	$(CC) build/ControlUnitTest.o -Lbuild -lControl -o build/$@ $(CFLAGS)
	
ChessXIV: build/ChessXIV.o build/libControl.a build/libView.a $(MODEL_LIB_DEPEND)
	$(CC) build/ChessXIV.o -Lbuild  -lControl -lView $(MODEL_LIB_COMPILE) -o build/$@ $(CFLAGS)
	ln -s build/ChessXIV ChessXIV
	
#This line does nothing
