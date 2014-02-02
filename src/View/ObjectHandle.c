#include "ObjectHandle.h"


ObjectHandle * ObjectHandle_Initialize(ObjectType type, ObjectTagEnum TagIn, int x, int y, int width, int height){
	ObjectHandle * Handle = malloc(sizeof(ObjectHandle));
	Handle->Type = type;
	Handle->Tag = TagIn;
	Handle->X = x;
	Handle->Y = y;
	Handle->Width = width;
	Handle->Height = height;
	
	strcpy(Handle->ImageFileName,"");
	/*text and color too set NULL*/
	
	return Handle;
	
}


#if 1


void ObjectHandle_Render(ViewHandle * MainHandle, ObjectHandle * Object){
	switch (Object->Type){
	case Image:
	  assert(Object->ImageFileName);
	  Object->Texture =  loadTexture(Object->ImageFileName, MainHandle->CurrentWindow->WindowRenderer);
	  if (Object->Width > 0 && Object->Height > 0){
	    renderTexture(Object->Texture, MainHandle->CurrentWindow->WindowRenderer, Object->X, Object->Y, Object->Width, Object->Height);
	   
	  } else {
	    
	  }
	  break;
	case Text:

	Object->Texture = renderText(Object->String, Object->FontName, Object->Color, Object->TextSize, MainHandle->CurrentWindow->WindowRenderer);
	renderTexture2(Object->Texture, MainHandle->CurrentWindow->WindowRenderer, Object->X, Object->Y);
	SDL_QueryTexture(Object->Texture , NULL, NULL, &(Object->Width), NULL);
	SDL_QueryTexture(Object->Texture , NULL, NULL, NULL, &(Object->Height));
	/*printf("text is %d wide and %d high\n", Object->Width, Object->Height);*/
	  break;
	case Color:
	  Object->Texture = renderFilledBox(Object->hexR, Object->hexG, Object->hexB, Object->hexA, Object->X, Object->Y, Object->Width, Object->Height, MainHandle->CurrentWindow->WindowRenderer);
	  renderTexture2(Object->Texture, MainHandle->CurrentWindow->WindowRenderer, 0, 0);
	  break;
	case Outline:
	  Object->Texture = renderEmptyBox(Object->hexR, Object->hexG, Object->hexB, Object->hexA, Object->X, Object->Y, Object->Width, Object->Height, MainHandle->CurrentWindow->WindowRenderer);
	  renderTexture2(Object->Texture, MainHandle->CurrentWindow->WindowRenderer, 0, 0);
	  break;
	}
}

ObjectHandle * ObjectHandle_Free(ObjectHandle * object){
	free(object);
	return NULL;
}


void windowRender(ViewHandle * MainHandle){

  	ObjectHandleNode * CurrNode = MainHandle->CurrentWindow->ObjectList->FirstNode;
	while(CurrNode){		
		ObjectHandle_Render(MainHandle, CurrNode->Object);
		CurrNode = CurrNode->NextNode;
	}
	SDL_RenderPresent(MainHandle->CurrentWindow->WindowRenderer);

}
#endif
Event GetSDLEvent(ViewHandle * MainHandle){
	SDL_Event event;
	Event ReturnEvent; ReturnEvent.Type = NoEvent;
	ObjectHandleList * ObjectSelectedList;
	ObjectHandleNode * Node;
	ObjectHandle * ObjectSelected;
	Boolean DoneFlag = False;
	while (!DoneFlag){
	while(SDL_PollEvent(&event)){

		switch(event.type){

			/*case SDL_QUIT:


				break;
	

			case SDL_MOUSEMOTION:
				
				break;*/

			case SDL_MOUSEBUTTONDOWN:
				/*find out where it is clicked then*/
				ObjectSelectedList = GetObjectByCoordinate(MainHandle, event.motion.x, event.motion.y);
				Node  = ObjectSelectedList->FirstNode;
				while (Node){
					ObjectSelected = Node->Object;
					switch (ObjectSelected->Tag){
						case Option_OnePlayer:
							ReturnEvent.Type = Option_OnePlayer_Clicked;
							DoneFlag = True;
							break;
						case Option_TwoPlayer:
							ReturnEvent.Type = Option_TwoPlayer_Clicked;
							DoneFlag = True;
							break;
						case Option_AIvsAI:
							ReturnEvent.Type = Option_AIvsAI_Clicked;
							DoneFlag = True;
							break;			
						case Option_White:
							ReturnEvent.Type = Option_White_Clicked;
							DoneFlag = True;
							break;
						case Option_Black:
							ReturnEvent.Type = Option_Black_Clicked;
							DoneFlag = True;
							break;
						case Option_EasyAI:
							ReturnEvent.Type = Option_EasyAI_Clicked;	
							DoneFlag = True;
							break;
						case Option_MediumAI:
							ReturnEvent.Type = Option_MediumAI_Clicked;
							DoneFlag = True;
							break;
						case Option_DifficultAI:
							ReturnEvent.Type = Option_DifficultAI_Clicked;
							DoneFlag = True;
							break;
							
					}
					Node = Node->NextNode;
				}
				
				ObjectHandleList_ShallowFree(ObjectSelectedList);
				if (DoneFlag) 
					return ReturnEvent;
				
				
				break;

		}      
	} 
	}
 }

ObjectHandleList * GetObjectByCoordinate(ViewHandle * MainHandle, int x, int y){
	ObjectHandleNode * CurrNode = MainHandle->CurrentWindow->ObjectList->FirstNode;
	ObjectHandleList * ReturnList = ObjectHandleList_Initialize();
	ObjectHandle * CurrentObject;
	while (CurrNode){
		CurrentObject = CurrNode->Object;
		if ((CurrentObject->X) < x && (CurrentObject->X + CurrentObject->Width > x) && (CurrentObject->Y < y) && (CurrentObject->Y + CurrentObject->Height > y))
			ObjectHandleList_AppendObject(ReturnList, CurrentObject);
		/*else {
			printf("%d %d %d %d doesn't cover %d %d\n", CurrentObject->X, CurrentObject->X + CurrentObject->Width, CurrentObject->Y, CurrentObject->Y + CurrentObject->Height, x, y);
		}*/
		CurrNode = CurrNode->NextNode;
	}
	
	return ReturnList;
}

ObjectHandle * GetObjectByTag(ViewHandle * MainHandle, ObjectTagEnum Tag){
	ObjectHandleNode * CurrNode = MainHandle->CurrentWindow->ObjectList->FirstNode;
	while (CurrNode){
		if (CurrNode->Object->Tag == Tag) return CurrNode->Object;		
		CurrNode = CurrNode->NextNode;
	}
	return NULL;
}


