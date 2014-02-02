CX = gcc

SDL = $(shell pkg-config --cflags --libs sdl2 SDL2_image SDL2_ttf)#-framework SDL2 -framework SDL2_ttf -framework SDL2_image
CFLAGS =  -c -I../../inc/View -I../../inc/Model -I../../inc/Control -DGUI_ENABLE -g -DQUAN_VERSION -DLINUX_OS $(shell pkg-config --cflags --libs sdl2 SDL2_image SDL2_ttf)
LFLAGS = $(SDL) 

EXE = Chess


all: $(EXE)

testObjectHandle.o: testObjectHandle.c
	$(CX) $(CFLAGS) testObjectHandle.c -o testObjectHandle.o

testObjectHandle: testObjectHandle.o ObjectHandle.o
	$(CX)  testObjectHandle.o ObjectHandle.o -o $@

ObjectHandle.o: ObjectHandle.c
	$(CX) $(CFLAGS) ObjectHandle.c -o ObjectHandle.o

ObjectHandleList.o: ObjectHandleList.c
	$(CX) $(CFLAGS) ObjectHandleList.c -o ObjectHandleList.o

sdlUtilities.o: sdlUtilities.c # sdlUtilities.h render.h display.h constants.h  
	$(CX) $(CFLAGS) sdlUtilities.c -o sdlUtilities.o

display.o: display.c #display.h render.h constants.h
	$(CX) $(CFLAGS) display.c -o display.o

render.o: render.c #render.h constants.h
	$(CX) $(CFLAGS) render.c -o render.o

TestDrawingFuncs.o: TestDrawingFuncs.c #constants.h render.h display.h sdlUtilities.h
	$(CX) $(CFLAGS) TestDrawingFuncs.c -o TestDrawingFuncs.o

$(EXE): TestDrawingFuncs.o render.o display.o sdlUtilities.o ObjectHandleList.o ObjectHandle.o

	$(CX) TestDrawingFuncs.o render.o display.o sdlUtilities.o ObjectHandleList.o ObjectHandle.o  $(LFLAGS) -o $(EXE)

clean:
	rm *.o && rm $(EXE)
