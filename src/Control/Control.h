#ifndef CONTROL_H
#define CONTROL_H
#include <stdio.h>
#include <stdlib.h>

#include "Model.h"
#include "View.h"

void ControlSpeak(void);

void GameInitialize(void);
void GameMainLoop(void);
void GameQuit(void);

ChessBoard * MainChessBoard_pt;

#endif