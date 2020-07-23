#ifndef __GRAFO_H
#define __GRAFO_H
typedef struct edge{
    int key; /** Identifica a che nodo si collega questo arco **/
    int costo;
    int tempo;
    struct edge *next; /** Prossimo nodo nella lista degli adiacenti **/

}Edge; /** Arco **/


typedef struct Grafo{
    int numeroVertici; /** Numero vertici del grafo **/
    char nome[70][40]; /** Nome aeroporti **/
    int gettonata[40]; /** METE gettonate **/
    Edge **adj; /** Vettore con le liste delle adiacenze **/

} Grafo;


Grafo *grafoVuoto(int);
int isEmptyG(Grafo *);
void stampaGrafoAmministratore(Grafo *);
Grafo *inserisciNodo(Grafo *,char []);
void aggiungiTratta(Grafo *, int , int , int , int );
void rimuoviArco(Grafo *, int , int);
void gradoGrafo(Grafo *, int *, int *);
void ricercaProfonditaDFS1(Grafo *, int , int *);
void ricercaProfonditaDFS(Grafo *);
char *ritornoNomeAeroporto(Grafo *, int );
int IndiceAeroporto(Grafo *,char [50]);
Grafo* aggiuntaTratte(Grafo *);
int ritornoIndiceMetaGettonata(Grafo *, int );
void AumentoGettonata(Grafo *,int );
void  g_remove_edge(Grafo *, int, int);
void g_grado(Grafo *, int *, int *);
void g_remove_nodo(Grafo *, int);
int EsistenzaTrattaTraAeroporti(Grafo *,int ,int );
void stampaGrafoViaggiatore (Grafo *);
#endif // __GRAFO_H
