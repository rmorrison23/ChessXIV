
#include "ObjectHandleList.h"

ObjectHandleList * ObjectHandleList_Initialize(void){
	ObjectHandleList * ReturnPt = malloc(sizeof(ObjectHandleList));
	ReturnPt->FirstNode = NULL;
	ReturnPt->LastNode = NULL;
	return ReturnPt;
}

ObjectHandleList * ObjectHandleList_AppendObject(ObjectHandleList * List, ObjectHandle * Object){
	ObjectHandleNode * NewNode = malloc(sizeof(ObjectHandleNode));
	assert(NewNode);
	NewNode->Object = Object;
	NewNode->NextNode = NULL;
	/*NewNode->List = List;*/
	if (List->FirstNode){		
		List->LastNode->NextNode = NewNode;
		NewNode->PrevNode = List->LastNode;
		List->LastNode = NewNode;
	} else {
		/*empty list*/
		List->FirstNode = NewNode;
		List->LastNode = NewNode;
		NewNode->PrevNode = NULL;
		
	}
	return List;
#if 0
	ObjectHandleNode * NewNode = malloc(sizeof(ObjectHandleNode));
	assert(NewNode);
	NewNode->Object = Object;
	NewNode->NextNode = NULL;
	if (!List->FirstNode){
		List->FirstNode = NewNode;
		List->LastNode = NewNode;
		NewNode->PrevNode = NULL;		
	} else {
		List->LastNode->NextNode = NewNode;
		NewNode->PrevNode = List->LastNode;
		List->LastNode = NewNode;
	}
	return List;

#endif

}

void ObjectHandleList_ShallowFree(ObjectHandleList * List){
	ObjectHandleNode * CurrNode, * NextNode;
	CurrNode = List->FirstNode;
	while (CurrNode){
		NextNode = CurrNode->NextNode;
		free(CurrNode);
		CurrNode = NextNode;
	}

}

void ObjectHandleList_DeepFree(ObjectHandleList * List){
	ObjectHandleNode * CurrNode, * NextNode;
	CurrNode = List->FirstNode;
	while (CurrNode){
		NextNode = CurrNode->NextNode;
		switch(CurrNode->Object->Type){
			case Image:
				free(CurrNode->Object->ImageFileName);
				break;
			case Text:
			case Button:
				free(CurrNode->Object->String);
				free(CurrNode->Object->FontName);
				break;
		}
		free(CurrNode->Object);
		free(CurrNode);
		CurrNode = NextNode;
	}
	
	List->FirstNode = NULL;
	List->LastNode = NULL;

}
