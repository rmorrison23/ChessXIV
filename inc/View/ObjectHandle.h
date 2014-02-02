#ifndef OBJECT_HANDLE_H
#define OBJECT_HANDLE_H

#include "View.h"

ObjectHandle * ObjectHandle_Initialize(ObjectType type, int x, int y, int width, int height);
void ObjectHandle_Render(ViewHandle * MainHandle, ObjectHandle * Handle);
ObjectHandle * ObjectHandle_Free(ObjectHandle * Handle);
#endif
