#include  <lista.h>

int main ()
{
    char type = 's';
    ListH_t * lista = createList(compare_strings , type);
    //Dodajemy dane do listy
    void * dane =  (char *)malloc(20*sizeof(char));
	*((char*)dane) = 'kupa'; 
    insert(lista,dane);
    void * dane1 =  (char *)malloc(20*sizeof(char));
	*((char*)dane1) = 'dupa'; 
    insert(lista,dane1);
    // void * dane2 =  (int *)malloc(sizeof(int));
	// *((int*)dane2) = 10; 
    // insert(lista,dane2);
    // void * dane3 =  (int *)malloc(sizeof(int));
	// *((int*)dane3) = 6; 
    // insert(lista,dane3);
    // 
	readList(lista , lista->type);
    deleteNth(lista , 0);
    

    readList(lista , lista->type);
    freeList(lista);
    // free(dane3);
    // free(dane2);
    free(dane1);
    free(dane);
    return 0;
}