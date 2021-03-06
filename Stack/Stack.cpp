#include "stdafx.h"
#include "utilities.h"
#include "interface.h"
#include "mData.h"
#include "mStack.h"

int main()
{
	STACK_Init(MDATA_Free, MDATA_Print, MDATA_savetoFunc,
		MDATA_readFromFile,MDATA_TableHeader,MDATA_TableBottom);

	int option;
	bool flag = true;
	while (flag) {
		menu();
		printf("Choose option: ");
		option = readIntFromTo(0,8);
		switch (option) {
			case PUSH: push();							break;
			case POP: pop();							break;
			case DISPLAY_STACK: displayStack();			break;
			case CLEAR: clear();						break;
			case FIND_LASTNAME: find_lastname();		break;
			case SAVE_TO_FILE: STACK_saveToFile();		break;
			case LOAD_FROM_FILE: STACK_readfromFile();	break;
			case EXIT:								
			{
				flag = false;
			}
		}	
	}
	STACK_Free();
    return 0;
}

