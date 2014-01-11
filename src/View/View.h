#ifndef VIEW_H
#define VIEW_H
#include <stdlib.h>
#include <stdio.h>

#include "ChessBoard.h"

unsigned char AskUserChooseColor();
unsigned char AskUserAIChoice();
void DisplayChessBoard(ChessBoard *);

#endif 
