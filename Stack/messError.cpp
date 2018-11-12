#include "stdafx.h"
#include <stdlib.h>
#include "mData.h"
#include "messError.h"
#include "mStack.h"

static char *messErrorTab[] = {
	(char*)"E Memory allocation error",	       //MEM_ALOC_ERROR
	(char*)"W Incorect line number",		  //INCORR_INDEX_WARN
	(char*)"W Memory allocation fault",      //MEM_ALLOC_NOT_FATAL
	(char*)"E Fatal Error",				    //FATAL_ERROR
	(char*)"E NO File"				       //NO_FILE
};

void messError(enum ERROR_MESSAGES mess) {
	puts(messErrorTab[mess] + 1);
	if (messErrorTab[mess][0] == 'E') {
		STACK_Free();
		system("pause");
		exit(1);
	}
}

void exitError(FILE *file, void *tmp, __int64 *arr, FreeData ptrFreeFunc) {
	if (file)
		fclose(file);
	if (arr)
		free(arr);
	ptrFreeFunc(tmp);  
	messError(FATAL_ERROR);
}

void exitErrorStack(FILE *file, __int64 *arr) {
	if (file)
		fclose(file);
	if (arr)
		free(arr);
	messError(FATAL_ERROR);
}
