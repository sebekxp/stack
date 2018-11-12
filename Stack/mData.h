#ifndef MDATA__H
#define MDATA__H
struct MDATA
{
	char *name;
	char *lastName;
	enum KIERUNEK foStudy; //field of study
	int year;
};
void *MDATA_Init(size_t sizename,char *name, size_t sizeLastname,char *lastName, int year, enum KIERUNEK kier);
void *MDATA_Push(size_t sizeName, char *name, size_t sieLastname,char *lastName, int year, enum KIERUNEK kier);
void MDATA_Print(void *ptr);
int MDATA_SerchLastName(void *pCurData, void *pSearchData);
void MDATA_Free(void *ptr);
void* MDATA_readFromFile(FILE* read, __int64 *arr, unsigned int rec, unsigned int noItems);
void MDATA_savetoFunc(void *ptr, FILE *save, __int64 *arr);
void MDATA_TableHeader();
void MDATA_TableBottom();

#endif