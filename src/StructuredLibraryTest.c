#include <stdio.h>
#include <stdlib.h>
#include "Control/Control.h"

int main(void){
  /*ViewSpeak();
  ControlSpeak();
  ModelSpeak();*/
  
  GameInitialize();
  GameMainLoop();
  GameQuit();
	printf ("Hanchel is here.\n");
 return 0; 
}
