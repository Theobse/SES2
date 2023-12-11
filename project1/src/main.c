#include <stdio.h>
#include <stdint.h>
//#include "platform.h"
//#include "project1.h"
//#include "memory.h"
//#include "conversion.h"
//#include "debug.h"


void project1(void);

int main()
{
    
    #ifdef PROJECT1
    project1();
    #else
    printf("\n\n-DPROJECT1 not provided\n\n");
    #endif   
    return 0;
}
