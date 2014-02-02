#include "ObjectHandle.h"


ObjectHandle * ObjectHandle_Initialize(ObjectType type, int x, int y, int width, int height){
	ObjectHandle * Handle = malloc(sizeof(ObjectHandle));
	Handle->Type = type;
	Handle->X = x;
	Handle->Y = y;
	Handle->Width = width;
	Handle->Height = height;
	
	strcpy(Handle->ImageFileName,"");
	/*text and color too set NULL*/
	printf("inside: %p\n", Handle);
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

  SDL_Renderer *renderer = MainHandle->CurrentWindow->WindowRenderer;


}
#endif
Event GetSDLEvent(ViewHandle * MainHandle){
	SDL_Event event;
	Event ReturnEvent; ReturnEvent.Type = NoEvent;
	Object * ObjectSelected;
	while(SDL_PollEvent(&event)){

		switch(event.type){

			case SDL_QUIT:


				break;
	

			case SDL_MOUSEMOTION:
				
				break;

			case SDL_MOUSEBUTTONDOWN:
				/*find out where it is clicked then*/
				ObjectHandleList * ObjectSelectedList = GetObjectByCoordinate(MainHandle, event.motion.x, event.motion.y);
				ObjectHandleNode * Node  = ObjectSelectedList->FirstNode;
				while (Node){
					switch (ObjectSelected->Tag){
						case WhiteColorButton:
							ReturnEvent.Type = Option_White;
							break;
						case BlackColorButton:
							ReturnEvent.Type = Option_Black;
							break;
						case EasyAIButton:
							ReturnEvent.Type = Option_EasyAI;	
							break;
						case MediumAIButton:
							ReturnEvent.Type = Option_MediumAI;
							break;
						case DifficultAIButton:
							ReturnEvent.Type = Option_DifficultAI;
							break;
							
					}
				}
				
				ObjectHandleList_ShallowFree(ObjectSelectedList);
				if (ReturnEvent.Type != NoEvent) return ReturnEvent;
				
				
				break;

		}      
	}    
 }

ObjectHandleList * GetObjectByCoordinate(ViewHandle * MainHandle, int x, int y){
	ObjectHandleNode * CurrNode = MainHandle->CurrentWindow->ObjectList;
	ObjectHandleList * ReturnList = ObjectHandleList_Initialize();
	while (CurrNode){
		ObjectHandle * CurrObject;
		if ((CurrentObject->X) < x && (CurrentObject->X + CurrentObject->Width > x) && (CurrentObject->Y < y) && (CurrentObject->Y + CurrentObject->Height > y))
			ObjectHandleList_AppendObject(ReturnList, CurrObject);
		CurrNode = CurrNode->NextNode;
	}
}

ObjectHandle * GetObjectByTag(ViewHandle * MainHandle, ObjectTagEnum Tag){
	ObjectHandleNode * CurrNode = MainHandle->CurrentWindow->ObjectList;
	while (CurrNode){
		if (CurrNode->Object->Tag == Tag) return CurrNode->Object;		
		CurrNode = CurrNode->NextNode;
	}
}
