#include  <lista.h>



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
    		
    		ListE_t *find = (ListE_t *)malloc(sizeof(ListE_t));
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