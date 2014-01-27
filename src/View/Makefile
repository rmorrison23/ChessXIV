CX = gcc
SDL = -framework SDL2 -framework SDL2_ttf -framework SDL2_image
CFLAGS = -Wall -c 
LFLAGS = $(SDL)
EXE = Chess


all: $(EXE)

sdlUtilities.o: sdlUtilities.c sdlUtilities.h render.h display.h constants.h  
	$(CX) $(CFLAGS) sdlUtilities.c -o sdlUtilities.o

display.o: display.c display.h render.h constants.h
	$(CX) $(CFLAGS) display.c -o display.o

render.o: render.c render.h constants.h
	$(CX) $(CFLAGS) render.c -o render.o

TestDrawingFuncs.o: TestDrawingFuncs.c constants.h render.h display.h sdlUtilities.h
	$(CX) $(CFLAGS) TestDrawingFuncs.c -o TestDrawingFuncs.o

$(EXE): TestDrawingFuncs.o render.o display.o sdlUtilities.o
	$(CX) $(LFLAGS) TestDrawingFuncs.o render.o display.o sdlUtilities.o -o $(EXE)

clean:
	rm *.o && rm $(EXE)
