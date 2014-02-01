#include "ObjectHandle.h"


ObjectHandle * ObjectHandle_Initialize(ObjectType type, int x, int y, int width, int height){
	ObjectHandle * Handle = malloc(sizeof(ObjectHandle));
	Handle->Type = type;
	Handle->X = x;
	Handle->Y = y;
	Handle->Width = width;
	Handle->Height = height;
	
	Handle->ImageFileName = NULL;
	return Handle;
	
}

ObjectHandle_Render(ViewHandle * MainHandle, ObjectHandle * Handle){
	switch (Handle->Type){
		case Image:
			assert(Handle->ImageFileName);
			Handle->Texture =  loadTexture(Handle->ImageFileName, MainHandle->CurrentWindow->WindowRenderer);
			if (Handle->Width > 0 && Handle->Height > 0){
				renderTexture(Handle->Texture, MainHandle->CurrentWindow->WindowRenderer, Handle->X, Handle->Y, Handle->Width, Handle->Height);
			} else {
				
			}
			break;
	}
}

ObjectHandle * ObjectHandle_Free(ObjectHandle * handle){
	free(handle);
	return NULL;
}