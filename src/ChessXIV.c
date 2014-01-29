#include "Control.h"

int main(void){
	ControlHandle * MainHandle = Control_Initialize();
	MainHandle = Control_MainLoop(MainHandle);
	MainHandle = Control_CleanUp(MainHandle);
	return 0;
}