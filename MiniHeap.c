#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "Grafo/Grafo.h"
#include "Lista/Lista.h"
#include "MiniHeap.h"

struct MinHeapNode* newMinHeapNode(int v, int dist)//creazione del miniheapNode
{
    struct MinHeapNode* minHeapNode = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    minHeapNode->v = v;
    minHeapNode->dist = dist;
    return minHeapNode;
}

struct MinHeap* createMinHeap(int capacity)//creazione del miniheap con la grandezza
{
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->pos = (int *)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNode**)malloc(sizeof(struct MinHeapNode*)*capacity);

    return minHeap;
}

void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b)//swap
{
    struct MinHeapNode* temp = *a;
    *a = *b;
    *b = temp;
}

void MinHeapify(struct MinHeap* minHeap, int i)//ordinamento del heap
{
    int left=2*i+1;
    int right=2*i+2;
    int smallest=i;

    if(left<minHeap->size && minHeap->array[left]->dist < minHeap->array[smallest]->dist){
        smallest=left;
    }
    if(right<minHeap->size && minHeap->array[right]->dist < minHeap->array[smallest]->dist)
        smallest=right;
    if(smallest!=i){
        struct MinHeapNode * smallestnode=minHeap->array[smallest];
        struct MinHeapNode * iNode=minHeap->array[i];
        minHeap->pos[smallestnode->v]=i;
        minHeap->pos[iNode->v]=smallest;
        swapMinHeapNode(&minHeap->array[smallest],&minHeap->array[i]);
        MinHeapify(minHeap,smallest);

    }
}
int isEmpty(struct MinHeap* heap)//è vuoto
{
    return heap->size == 0;
}
void decreaseKey(struct MinHeap* minHeap, int v, int dist)//decrementa il valore di una chiave di un min heap
{
    int i = minHeap->pos[v];

    minHeap->array[i]->dist = dist;

    while(i && minHeap->array[i]->dist < minHeap->array[(i-1)]->dist)
    {
        minHeap->pos[minHeap->array[i]->v] = (i-1);
        minHeap->pos[minHeap->array[(i-1)]->v] = i;
        swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i-1)]);

        i = (i-1);
    }
}

struct MinHeapNode* extractMin(struct MinHeap* minHeap)//ritorna il nodo del valore minimo di un minHeap dopo averlo rimosso dalla struttura
{
    if(isEmpty(minHeap))
        return NULL;

    struct MinHeapNode* root = minHeap->array[0];

    struct MinHeapNode* lastNode = minHeap->array[minHeap->size-1];
    minHeap->array[0] = lastNode;

    minHeap->pos[root->v] = minHeap->size-1;
    minHeap->pos[lastNode->v] = 0;

    --minHeap->size;
    MinHeapify(minHeap,0);

    return root;
}
int isInMinHeap(struct MinHeap* minHeap, int v)
{
    if(minHeap->pos[v] < minHeap->size)
        return 1;

    else
        return 0;
}
PrezzoTempo dijkstraEconomico( Grafo* graph, int partenza,int arrivo)//grafo in ingresso e la(nodo) sorgente di partenza TRATTA ECONOMICA
{
    int V=graph->numeroVertici;//ricavo il numero dei vertici;
    struct MinHeap* minHeap=createMinHeap(V);
    int arrayEuro[V];//array contenitore del costo delle varie tratte indicate tramite un indice
    int arrayTempo[V];//array contenitore del tempo tra le varie tratte
    minHeap->size=V;//assegno la grandezza del grafo al heap
    int percorso[V];//array contenitore degli indici del percorso
    percorso[partenza]=partenza;
    PrezzoTempo biglietto;
    //inizializzazione
    for(int i=0;i<V;i++){
        arrayEuro[i]=INT_MAX;
        minHeap->array[i]=newMinHeapNode(i,INT_MAX);
        minHeap->pos[i]=i;
        arrayTempo[i]=INT_MAX;
    }
    arrayEuro[partenza]=0;
    decreaseKey(minHeap,partenza,arrayEuro[partenza]);
    arrayTempo[partenza]=0;
    while(!isEmpty(minHeap)){
        struct MinHeapNode * minNode=extractMin(minHeap);//estrazione del minimo
        int u=minNode->v;
        for(struct edge * tmp= graph->adj[u];tmp;tmp=tmp->next){
            int key=tmp->key;
            if(isInMinHeap(minHeap,key)&& arrayEuro[u]!=INT_MAX && arrayEuro[u]+tmp->costo<arrayEuro[key]){
                arrayEuro[key]=tmp->costo+arrayEuro[u];
                arrayTempo[key]=tmp->tempo+arrayTempo[u];
                percorso[key]=u;
                decreaseKey(minHeap,key,arrayEuro[key]);
            }
        }

    }
    if(arrivo==-1){
       biglietto=trattaEconomicaSenzaMeta(arrayEuro,V,percorso,partenza,graph,arrayTempo);
    }else{
          biglietto=TrattaEconomicaConMeta(arrayEuro,V,percorso,partenza,graph,arrivo,arrayTempo);
    }
    return biglietto;
}

PrezzoTempo trattaEconomicaSenzaMeta(int arrayEuro[],int n, int percorso[],int partenza,Grafo *g,int tempo[])
{
    int economica,tempoFinale,vertice=0;
    PrezzoTempo biglietto;

    if(arrayEuro[0]==partenza)
    {
        economica=arrayEuro[1];
        vertice=arrayEuro[1];
        tempoFinale=tempo[1];

    }
    else
    {
        economica=arrayEuro[0];
        tempoFinale=tempo[0];
    }
    int i;
    for(i=0; i<n; i++)
    {
        if(i!=partenza)
        {
            if(economica > arrayEuro[i])
            {
                vertice=i;
                int tmp=arrayEuro[i];
                arrayEuro[i]=economica;
                economica=tmp;
                int tmp2=tempo[i];
                tempo[i]=tempoFinale;
                tempoFinale=tmp2;

            }

        }
    }
      printf("\nTratta da %s per %s :\n",ritornoNomeAeroporto(g,partenza),ritornoNomeAeroporto(g,vertice));
      for( i=vertice; i!=vertice-1 ; i--)
    {
        stampaPercorsoTratta(percorso,i,g);
        printf("%s\t",ritornoNomeAeroporto(g,i));
    }
    printf("\n");
    biglietto.prezzo = economica;
    biglietto.tempo = tempoFinale;
    biglietto.aeroportoArrivo = vertice;
    return biglietto;
}
PrezzoTempo TrattaEconomicaConMeta(int arrayEuro[],int n, int percorso[],int partenza,Grafo *g,int arrivo,int arrayTempo[])
{
    int economica,tempo,vertice=0;
    PrezzoTempo biglietto;

    if(arrayEuro[0]==partenza)
    {
        economica=arrayEuro[1];
        vertice=arrayEuro[1];
        tempo=arrayTempo[1];

    }
    else
    {
        economica=arrayEuro[0];
        tempo=arrayTempo[0];
    }
    int i;
    for(i=0; i<n; i++)
    {
        if(i!=partenza)
        {
            if(i==arrivo)
            {
                vertice=i;
                int tmp=arrayEuro[i];
                arrayEuro[i]=economica;
                economica=tmp;

                int tmp2=arrayTempo[i];
                arrayTempo[i]=tempo;
                tempo=tmp2;

            }

        }
    }
   printf("\nTratta da %s per %s :\n",ritornoNomeAeroporto(g,partenza),ritornoNomeAeroporto(g,vertice));
     for( i=vertice; i!=vertice-1 ; i--)
    {
        stampaPercorsoTratta(percorso,i,g);
        printf("%s\t",ritornoNomeAeroporto(g,i));
    }
    printf("\n");
    biglietto.prezzo = economica;
    biglietto.tempo = tempo;
    biglietto.aeroportoArrivo=vertice;
    return biglietto;
}

PrezzoTempo dijkstraTempo( Grafo* graph, int partenza,int arrivo)//Dijkstra del tempo
{
    int V=graph->numeroVertici;//ricavo il numero dei vertici;
    struct MinHeap* minHeap=createMinHeap(V);
    int arrayTempo[V];//array contenitore del tempo tra le varie tratte tramite indice
    int arrayEuro[V];//array contenitore del costo delle varie tratte indicate
    minHeap->size=V;//assegno la grandezza del grafo al heap
    int percorso[V];//array contenitore degli indici del percorso
    percorso[partenza]=partenza;
    PrezzoTempo Biglietto;
    for(int i=0;i<V;i++){
        arrayTempo[i]=INT_MAX;
        minHeap->array[i]=newMinHeapNode(i,INT_MAX);
        minHeap->pos[i]=i;
        arrayEuro[i]=INT_MAX;
    }
    arrayTempo[partenza]=0;
    decreaseKey(minHeap,partenza,arrayTempo[partenza]);
    arrayEuro[partenza]=0;

    int u;

    while(!isEmpty(minHeap)){
        struct MinHeapNode* minNode=extractMin(minHeap);//estrazione minimo
        u=minNode->v;
        for(struct edge * tmp=graph->adj[u];tmp;tmp=tmp->next){
            int key=tmp->key;
            if(isInMinHeap(minHeap,key)&& arrayTempo[u]!=INT_MAX && arrayTempo[u]+tmp->tempo <arrayTempo[key]){

                arrayTempo[key]=tmp->tempo+arrayTempo[u];

                arrayEuro[key]=tmp->costo+ arrayEuro[u];
                percorso[key]=u;
                decreaseKey(minHeap,key,arrayTempo[key]);

            }
        }


    }

    Biglietto=trattaBreveConMeta(arrayTempo,V,percorso,partenza,graph,arrivo,arrayEuro);

    return Biglietto;
}
PrezzoTempo trattaBreveConMeta(int arrayTempo[],int n, int percorso[],int partenza,Grafo *g,int arrivo,int arrayEuro[])//tratta breve conoscendo la meta
{
    int breve,prezzo,vertice=0;
    PrezzoTempo biglietto;

    if(arrayTempo[0]==partenza)
    {
        breve=arrayTempo[1];

        vertice=arrayTempo[1];
        prezzo=arrayEuro[1];
    }
    else
    {
        breve=arrayTempo[0];

        prezzo=arrayEuro[0];

    }
    int i;
    for(i=0; i<n; i++)
    {
        if(i!=partenza)
        {
            if(i==arrivo)
            {
                vertice=i;

                int tmp=arrayTempo[i];

                arrayTempo[i]=breve;
                breve=tmp;

                int tmp2=arrayEuro[i];
                arrayEuro[i]=prezzo;
                prezzo=tmp2;


            }

        }
    }
    biglietto.tempo = breve;



    biglietto.prezzo = prezzo;
    biglietto.aeroportoArrivo = vertice;
    printf("\nTratta da %s per %s :\n",ritornoNomeAeroporto(g,partenza),ritornoNomeAeroporto(g,vertice));
     for( i=vertice; i!=vertice-1 ; i--)
    {
        stampaPercorsoTratta(percorso,i,g);
        printf("%s\t",ritornoNomeAeroporto(g,i));
    }
    printf("\n");



    return biglietto;
}
void stampaPercorsoTratta(int parent[], int v,Grafo *g)
{
    if(parent[v]==v)
        return;
    stampaPercorsoTratta(parent,parent[v],g);
    printf("%s ->",ritornoNomeAeroporto(g,parent[v]));
}
