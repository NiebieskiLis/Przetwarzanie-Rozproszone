
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
     if ((int*)a > (int*)b) return 1;
     else if ((int*)a==(int*)b) return 0;
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

ListH_t* createList(int (* funkcja)(void*,void*))
{
    //Tworzy uchwyt do funkcji oraz funkcję dla 
	ListH_t *ListHandler = (ListH_t *)malloc(sizeof(ListH_t));
	ListHandler-> lista = NULL;
	ListHandler-> funkcja = funkcja;
	return ListHandler;
}

void insert (ListH_t* ListH , void * dane){
	//Tworzymy nowy element listy
	ListE_t *list = (ListE_t *)malloc(sizeof(ListE_t));
	//Gdy Lista nie jest pusta
	//*(arguments *)
	int data = *(int*)(dane);
	if (ListH->lista) {
		// dane które chcemy dodać do listy są większe od tego co jest na jej początku  
		if(ListH->funkcja(dane, ListH->lista->dane) )
		{
			ListH->lista->prev = list;
			list->next = ListH->lista;
			list->prev =  NULL;
			ListH->lista = list;
		}
		else if (ListH->funkcja(dane, ListH->lista->dane) == -1 ) 
		{
    		//dodajemy element który będzie przeszukiwał listę
    		
    		ListE_t *find ;
    		find =  ListH->lista;
    		//Przeszukujemy listę
    		while ( ListH->funkcja(find-> dane , dane ))
    		    find = find->next;
    		    
    		    
    		//dołączamy element
    		
    		list->prev = find->prev; 
    	    find->prev->next = list;
    	    find->prev = list;
    	    list->next = find;
    	    list->dane = dane;
    		
    		//usuwamy dodatkowy element
    		free(find);
    	}
	
	}
	//Dodajemy pierwszy element listy
	else {
        	ListH-> lista = list;
        	list->next = NULL;
        	list->prev = NULL;
        	list->dane = dane;
	
	}
		printf("%i \n",*(int*)list->dane);


}
//funkcja oczyszczająca całą listę
void freeList(ListH_t * listH)
{
    ListE_t *pom;
    while(listH->lista)
    {
        pom = listH->lista;
        free(listH->lista);
        listH->lista = pom->next;
    }
    free(listH);
    
}
void readList(ListH_t * listH){
    ListE_t *find ;
    		find =  listH->lista;
    		//Przeszukujemy listę
    		while ( find){

                 printf("%c \n",*(int*)find->dane);
    		    find = find->next;
               
            }
}
int main ()
{
      ListH_t * lista = createList(compare_strings);
    
    //jak do danych dodać wartość np. 5??
    void * dane =  (int *)malloc(sizeof(int));
	*((int*)dane) = 5; 

    insert(lista,dane);
    void * dane1 =  (int *)malloc(sizeof(int));
	*((int*)dane1) = 7; 
   // insert(lista,dane1);

    readList(lista);
    freeList(lista);
    
    return 0;
}


