#ifndef __MINHEAP_H
#define __MINHEAP_H
#include "Lista/Lista.h"
#include "Grafo/Grafo.h"

struct MinHeapNode{
    int v;//numero di vertici ricavato dal grafo
    int dist;//distanza
};
struct MinHeap{
    int size;//grandezza
    int capacity;//capacita
    int *pos;//posizione
    struct MinHeapNode **array;//puntatore di array
};
PrezzoTempo dijkstraEconomico( Grafo* , int ,int );
PrezzoTempo dijkstraTempo( Grafo* , int ,int );
PrezzoTempo trattaEconomicaSenzaMeta(int [],int , int [],int ,Grafo *,int []);
PrezzoTempo trattaBreveConMeta(int [],int , int [],int ,Grafo *,int ,int []);
PrezzoTempo TrattaEconomicaConMeta(int [],int , int [],int ,Grafo *,int ,int []);
struct MinHeapNode* newMinHeapNode(int , int );
struct MinHeap* createMinHeap(int );
void swapMinHeapNode(struct MinHeapNode** , struct MinHeapNode** );
void MinHeapify(struct MinHeap* , int );
int isEmpty(struct MinHeap* );
void decreaseKey(struct MinHeap* , int , int );
struct MinHeapNode* extractMin(struct MinHeap* );
int isInMinHeap(struct MinHeap* , int );
void stampaPercorsoTratta(int [], int ,Grafo*);
#endif // __MINHEAP_H
