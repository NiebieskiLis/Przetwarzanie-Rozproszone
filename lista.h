
#include "stdio.h"
#include "stdlib.h"
#include <string.h>


typedef struct List{

	struct List * next;
	struct List * prev;
	void * dane;
}ListE_t;

typedef struct ListHandler{
	ListE_t * lista;
	int (* funkcja) (void *a , void * b);
	char type;
}ListH_t;

int compare_int (void *a , void * b);
int compare_strings (void *a , void * b);
int readListInt(ListH_t * listH);
int readListStr(ListH_t * listH);
int readPointer(ListH_t * listH);
ListH_t* createList(int (* funkcja)(void*,void*) , char type);
ListE_t * deleteNth (ListH_t * listH, int n);
void readList(ListH_t * listH, char type);
void insert (ListH_t* ListH , void * dane);
void freeList(ListH_t * listH);

