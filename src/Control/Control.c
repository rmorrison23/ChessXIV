#include "Control.h"

static ChessBoard * MainChessBoard_pt;

void ControlSpeak(void){
 printf("Control is speaking.\n"); 
}


void GameInitialize(void){
    unsigned char ColorChoice = 0;
  
    /*initialize view module*/
      
    /*ask user to choose human vs. human, human vs. computer and computer vs. computer*/
    unsigned char AIChoice = AskUserAIChoice();
    
    
    
     /*ask user to choose white or black*/
    if (AIChoice == 1) {
      ColorChoice = AskUserChooseColor();
    }

    /*initialize model module*/
    MainChessBoard_pt = InitializeChessBoard(AIChoice, ColorChoice);
    
    /*display initial board*/
    DisplayChessBoard(MainChessBoard_pt);
    
    
}

void GameMainLoop(void){
    
}

void GameQuit(void){
  
}
