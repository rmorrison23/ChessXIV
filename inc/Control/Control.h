#ifndef CONTROL_H
#define CONTROL_H
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


#include "Model.h"
#include "View.h"

typedef struct {
	ChessBoard * MainChessBoard;
	ChessMoveList * MainMoveList;
} ControlHandle;


ControlHandle * Control_Initialize();
ControlHandle * Control_MainLoop(ControlHandle *);
ControlHandle * Control_CleanUp(ControlHandle *);

#endif