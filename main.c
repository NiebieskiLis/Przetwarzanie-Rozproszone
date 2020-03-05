#include  <lista.h>

int main ()
{
    ListH_t * lista = createList(compare_strings);
    
    //jak do danych dodać wartość np. 5??
    void * dane =  (int *)malloc(sizeof(int));
	*((int*)dane) = 5; 

    insert(lista,dane);
    
    freeList(lista);
    
    return 0;
}
