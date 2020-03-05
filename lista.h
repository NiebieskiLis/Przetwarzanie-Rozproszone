
#include "stdio.h"
#include "stdlib.h"
#include <string.h>

/*Konwencja
    pierwsza większe od drugiej = 1
    równe  = 0 
    druga większa = -1

*/
int compare_strings (void *a , void * b)
{
    return strcmp((char*)a, (char*)b);

}
/*czy mogę utworzyć taką uniwersalną funkcje*/
int compare_int (void *a , void * b)
{
     if (a > b) return 1;
     else if (a==b) return 0;
     else return -1;
}

typedef struct List{

	struct List * next;
	struct List * prev;
	void * dane;
	

}ListE_t;

typedef struct ListHandler{

	ListE_t * lista;
	int (* funkcja) (void *a , void * b);
	

}ListH_t;
ListH_t* createList(int (* funkcja)(void*,void*));

void freeList(ListH_t * listH);
void insert (ListH_t* ListH , void * dane);




