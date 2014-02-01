
#include "ObjectHandleList.h"

ObjectHandleList * ObjectHandleList_Initialize(void){
	ObjectHandleList * ReturnPt = malloc(sizeof(ObjectHandleList));
	ReturnPt->FirstNode = NULL;
	ReturnPt->LastNode = NULL;
	return ReturnPt;
}