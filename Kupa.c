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
     if (*(int*)a > *(int*)b) return 1;
     else if (*(int*)a==*(int*)b) return 0;
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
	char type;
}ListH_t;

ListH_t* createList(int (* funkcja)(void*,void*) , char type)
{
    //Tworzy uchwyt do funkcji oraz funkcję dla 
	ListH_t *ListHandler = (ListH_t *)malloc(sizeof(ListH_t));
	ListHandler-> lista = NULL;
	ListHandler-> funkcja = funkcja;
	ListHandler-> type = type;
	return ListHandler;
}

void insert (ListH_t* ListH , void * dane){
	//Tworzymy nowy element listy
	ListE_t *list = (ListE_t *)malloc(sizeof(ListE_t));
	//Gdy Lista nie jest pusta
	//*(arguments *)
	list->dane = dane;
	int data = *(int*)(dane);
	if (ListH->lista) {
		// dane które chcemy dodać do listy są większe od tego co jest na jej początku  
		if(ListH->funkcja(dane, ListH->lista->dane)>=0 )
		{
			ListH->lista->prev = list;
			list->next = ListH->lista;
			list->prev =  NULL;
			ListH->lista = list;
		}
		else if (ListH->funkcja(dane, ListH->lista->dane) == -1 ) 
		{
		    bool flaga = 1;
    		//dodajemy element który będzie przeszukiwał listę
    		ListE_t *find ;
    		find =  ListH->lista;
    		//Przeszukujemy listę ///// sprawdzić dołączanie na koniec listy
    		while ( (ListH->funkcja(find-> dane , dane )>0)&&(flaga==1))
    		    {
    		        if(find->next != NULL )find = find->next;
    		        else flaga = 0;
		         } 
    		//dołączamy element
			if (flaga){
    		list->prev = find->prev; 
    	    find->prev->next = list;
    	    find->prev = list;
    	    list->next = find;
			}
			//Dodawanie elementu na koniec listy
			 else{
				 find->next = list;
				 list->prev = find;
				 list->next = NULL;
			}
    	}
	}
	//Dodajemy pierwszy element listy
	else {
        	ListH-> lista = list;
        	list->next = NULL;
        	list->prev = NULL;
        }
}
//funkcja usuwająca nty element listy
// 0 to pierwszy element
ListE_t * deleteNth (ListH_t * listH, int n){
    ListE_t * element = listH->lista;
    //Wyszukujemy element do usunięcia
    while ((element->next != NULL)&&(n))
    {
        n--;
        element=element->next;
    }
    
    //Jeżeli jest 1 to 
    if (element->prev == NULL)
    {
        listH->lista = element->next;
        if(listH->lista != NULL)
        listH->lista->prev = NULL;
    }
    //Jeżeli jest ostatni
    else if (element->next == NULL)
    {
        element->prev->next = NULL;
        
    }else
    {
        ListE_t *pom = element;
        element->prev->next=pom->next ;
        element->next->prev=pom->prev; 
    }
    //Nie pozawala mi na to tu
    //free(element);


}
//funkcja oczyszczająca całą listę
void freeList(ListH_t * listH)
{
    ListE_t *pom;
    while(listH->lista!= NULL)
    {
        pom = listH->lista;
        free(listH->lista);
        listH->lista = pom->next;
    }
    free(listH);
    
}
int readListInt(ListH_t * listH){
    ListE_t *find ;
    find =  listH->lista;
    //Przeszukujemy listę
    	while ( find !=  NULL){
            printf("%i ",*(int*)find->dane);
            find = find->next;
            }
            printf("\n");

            return 0;
}
void readList(ListH_t * listH, char type){
   if (type == 'i') readListInt(listH);
   else if (type == 's') readListInt(listH);
   else printf("This is not a generic type - write your own readList function !");
}
int main ()
{
    char type = 'i';
    ListH_t * lista = createList(compare_int , type);
    
    void * dane =  (int *)malloc(sizeof(int));
	*((int*)dane) = 5; 
    insert(lista,dane);
    void * dane1 =  (int *)malloc(sizeof(int));
	*((int*)dane1) = 3; 
    insert(lista,dane1);
    void * dane2 =  (int *)malloc(sizeof(int));
	*((int*)dane2) = 10; 
    insert(lista,dane2);
    void * dane3 =  (int *)malloc(sizeof(int));
	*((int*)dane3) = 6; 
    insert(lista,dane3);
    readList(lista , lista->type);
    deleteNth(lista , 0);
        readList(lista , lista->type);

    deleteNth(lista , 0);
        readList(lista , lista->type);

    deleteNth(lista , 0);
        readList(lista , lista->type);

    deleteNth(lista , 0);

    readList(lista , lista->type);
    freeList(lista);
    free(dane3);
    free(dane2);
    free(dane1);
    free(dane);
    return 0;
}
