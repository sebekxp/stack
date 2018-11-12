#include "stdafx.h"
#include <stdlib.h>
#include "messError.h"
#include <stdio.h>
#include <string.h>
#include "mDAta.h"
#include "interface.h"

void *MDATA_Init(size_t sizename, char *name, size_t sizeLastname,
	char *lastName, int year, enum KIERUNEK kier){
	
	MDATA *pDat = (MDATA*)malloc(sizeof(MDATA));
	if (!pDat) {
		MDATA_Free(pDat);
		messError(MEM_ALOC_ERROR);
	}
	else {
		pDat->name = (char*)malloc((sizename + 1) * sizeof(char));
		if (!pDat->name) {
			MDATA_Free(pDat->name);
			messError(MEM_ALOC_ERROR);
		}
		pDat->lastName = (char*)malloc((sizeLastname+1) * sizeof(char));
		if (!pDat->lastName) {
			MDATA_Free(pDat->lastName);
			messError(MEM_ALOC_ERROR);
		}
		strcpy(pDat->name, name);
		strcpy(pDat->lastName, lastName);
		pDat->year = year;
		pDat->foStudy = kier;
	}
	return (void*)(pDat);
}
void* MDATA_Push(size_t sizeName, char *name, size_t sizeLastname,
	char *lastName, int year, enum KIERUNEK kier) {

	return MDATA_Init(sizeName,name,sizeLastname,lastName,year, kier);
}
void MDATA_Print(void *ptr) {
	MDATA *temp = (MDATA*)ptr;
		if (temp) {
			printf("|%-15s      ", temp->name);
			printf("|%-15s    ", temp->lastName);
			printf("|%-11d    ", temp->year);
				switch (temp->foStudy)
				{
				case 0:
					printf("|%-13s   |\n", "Maths");
					break;
				case 1:
					printf("|%-13s   |\n", "Chemistry");
					break;
				case 2:
					printf("|%-13s   |\n", "Physics");
					break;
				};
		}
}
int MDATA_SerchLastName(void *pCurData, void *pSearchData) {
	MDATA *pCur = (MDATA *)pCurData;
	MDATA *pSearch = (MDATA *)pSearchData;

	if (strcmp(pCur->lastName, pSearch->lastName) == 0)
		return 1;

	return 0;

}
void MDATA_Free(void *ptr) {

	MDATA *pData = (MDATA *)ptr;

	if (!pData) return;

	if (pData->name)
		free(pData->name);
	pData->name = NULL;

	if (pData->lastName)
		free(pData->lastName);
	pData->lastName = NULL;

		free(pData);
}
void MDATA_savetoFunc(void *ptr, FILE *save, __int64 *arr) {

	MDATA *temp = (MDATA*)ptr;
	size_t len;
	if (temp) {
		len = strlen(temp->name);     
		if (fwrite(&len, sizeof(len), 1, save) != 1) {
			exitError(save, temp, arr, MDATA_Free);
		}

		if (fwrite(temp->name, sizeof(temp->name[0]), (len + 1), save) != len + 1) {
			exitError(save, temp, arr, MDATA_Free);
		}

		len = strlen(temp->lastName);
		if (fwrite(&len, sizeof(len), 1, save) != 1) {
			exitError(save, temp, arr, MDATA_Free);
		}
		if (fwrite(temp->lastName, sizeof(temp->lastName[0]), (len + 1), save) != len + 1) {
			exitError(save, temp, arr, MDATA_Free);
		}

		if (fwrite(&temp->year, sizeof(temp->year), 1, save) != 1) {
			exitError(save, temp, arr, MDATA_Free);

		}
		if (fwrite(&temp->foStudy, sizeof(temp->foStudy), 1, save) != 1) {
			exitError(save, temp, arr, MDATA_Free);
		}
	}
}

void* MDATA_readFromFile(FILE* read, __int64 *arr, unsigned int rec, unsigned int noItems) {
	
	MDATA *temp = NULL;

	temp = (MDATA*)malloc((noItems) * sizeof(MDATA));

	memset(temp, 0, noItems * sizeof(MDATA));

	int len = 0;
	if (fread(&len, sizeof(int), 1, read) != 1) {
		exitError(read, temp, arr, MDATA_Free);
	}
	temp[rec].name = (char*)malloc((len + 1) * sizeof(char));

	if (fread(temp[rec].name, sizeof(temp[rec].name[0]), len + 1, read) != len + 1) {
		exitError(read, temp, arr, MDATA_Free);
	}
	if (fread(&len, sizeof(int), 1, read) != 1) {
		exitError(read, temp, arr, MDATA_Free);
	}
	temp[rec].lastName = (char*)malloc((len + 1) * sizeof(char));

	if (fread(temp[rec].lastName, sizeof(temp[rec].lastName[0]), len + 1, read) != len + 1) {
		exitError(read, temp, arr, MDATA_Free);
	}

	if (fread(&temp[rec].year, sizeof(temp[rec].year), 1, read) != 1) {
		exitError(read, temp, arr, MDATA_Free);
	}

	if (fread(&temp[rec].foStudy, sizeof(temp[rec].foStudy), 1, read) != 1) {
		exitError(read, temp, arr, MDATA_Free);
	}
	void *pDat = MDATA_Push(strlen(temp[rec].name), temp[rec].name, strlen(temp[rec].lastName), temp[rec].lastName, temp[rec].year, temp[rec].foStudy);
	
	MDATA_Free(temp);

	return pDat;
}

void MDATA_TableHeader() {
	printf(" __________________________________________________________________________\n");
	printf("|%-15s|%-15s|%-11s|%-13s|\n", "\t  NAME ", "\t     LAST NAME    ", " YEAR OF BIRTH ", " FIELD OF STUDY ");
	printf("|_____________________|___________________|_______________|________________|\n");
}

void MDATA_TableBottom() {
	printf("|_____________________|___________________|_______________|________________|\n");

}




