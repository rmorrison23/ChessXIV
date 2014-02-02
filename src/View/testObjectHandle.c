

#include <stdio.h>
#include <stdlib.h>
#include "View.h"

int main(void){
ObjectHandle * NewObject = ObjectHandle_Initialize(Text, 1, 2, 3,4);
printf("Outside %p\n", NewObject);
printf("%d %d \n", NewObject->X, NewObject->Y);

return 0;
}
