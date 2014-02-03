
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

void ObjectHandleList_KillAllPieces(ViewHandle * MainViewHandle){
	ObjectHandleList * List = MainViewHandle->CurrentWindow->ObjectList;
	
	ObjectHandleNode * Node1 = List->FirstNode, * Node2;
	while (Node1){
		Node2 = Node1->NextNode;
		if (Node1->Object->Type == Piece){
			/*free it*/
			free(Node1->Object->ImageFileName);
			free(Node1->Object);
			
			/*bind the nodes*/
			if (Node1->NextNode)
			Node1->NextNode->PrevNode = Node1->PrevNode;
			if (Node1->PrevNode)
			Node1->PrevNode->NextNode = Node1->NextNode;
			
			/*free the node*/
			free(Node1);
		}
		
		
		Node1 = Node2;
	}
}

ObjectHandleList * GetObjectListByTag(ObjectHandleList * List, ObjectTagEnum Tag){
	ObjectHandleNode * CurrNode = List->FirstNode;
	ObjectHandleList * ReturnList = ObjectHandleList_Initialize();
	while (CurrNode){
		if (CurrNode->Object->Tag ==Tag){
			ObjectHandleList_AppendObject(ReturnList, CurrNode->Object);
		}
	}
	return ReturnList;
}