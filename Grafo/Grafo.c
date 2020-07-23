#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Grafo.h"
#include "../Utility/Utility.h"
#include "../Lista/Lista.h"
Grafo *grafoVuoto(int n){ /** Crea grafo **/
    Grafo *G;
    int i;
   char aeroporti[21][40] = {"Roma", "Milano", "Parigi", "Barcellona", "Madrid", "Lisbona", "Londra", "Dublino", "Glasgow", "Amsterdam", "Francoforte", "Amburgo", "Berlino", "Praga", "Varsavia", "Budapest", "Bucarest", "Kiev", "Istanbul", "Atene"};
    G = (Grafo*) malloc(sizeof(Grafo));
    if (G == NULL){
        printf("ERRORE: impossibile allocare memoria per il grafo\n");
    } else {
        G->adj = (Edge**)malloc(n*sizeof(Edge*)); /** Allocata la lista dei vertici **/
        if(G->adj == NULL){
            printf("ERRORE: impossibile allocare memoria per la lista del grafo\n");
            free(G);
            G = NULL;
        } else {
            G->numeroVertici = n;
            for (i=0; i<n; i++){

                G->gettonata[i] = rand()%5;
                Suppercase(aeroporti[i]);
                strcpy(G->nome[i], aeroporti[i]);
                G->adj[i] = NULL;
            }
        }
    }
    return G;
}

/** CONTROLLA SE IL GRAFO ESISTE O MENO **/
int isEmptyG(Grafo *G){
    return G == NULL;
}

/** SCRITTURA DEL GRAFO. NEL NOSTRO CASO, SCRIVE TUTTE LE TRATTE **/
void stampaGrafoAmministratore (Grafo *G){
    int i;
    int numeroArchi = 0;

    Edge *arco;
    if(!isEmptyG(G)){
        printf("\nNel database ci sono %d aeroporti:\n\n", G->numeroVertici);

        for(i=0; i< G->numeroVertici; i++){
            printf("Aeroporti raggiungibili da (%d)%s:\n", i, G->nome[i]);
            printf("*******************************************\n");
            arco = G->adj[i];

            while (arco != NULL){
                printf("(%d)%s \t\t(Costo: %d Euro, Durata: %d Gettonata: %d)\n", arco->key, G->nome[arco->key], arco->costo, arco->tempo, G->gettonata[arco->key]);
                numeroArchi = numeroArchi + 1;
                arco = arco->next;
            }
            printf("\n\n");
        }
        printf("Sono presenti %d tratte DIRETTE, e' possibile comunque scegliere tratte NON DIRETTE.\n", numeroArchi);
        printf("NOTA BENE: Le tratte non dirette prevederanno scali.\n");
    }
}
void stampaGrafoViaggiatore (Grafo *G){
    int i;
    int numeroArchi = 0;

    Edge *arco;
    if(!isEmptyG(G)){
        printf("\nNel database ci sono %d aeroporti:\n\n", G->numeroVertici);

        for(i=0; i< G->numeroVertici; i++){
            printf("Aeroporti raggiungibili da %s:\n", G->nome[i]);
            printf("*******************************************\n");
            arco = G->adj[i];

            while (arco != NULL){
                printf("%s \t\t(Costo: %d Euro, Durata: %d Gettonata: %d)\n", G->nome[arco->key], arco->costo, arco->tempo, G->gettonata[arco->key]);
                numeroArchi = numeroArchi + 1;
                arco = arco->next;
            }
            printf("\n\n");
        }
        printf("Sono presenti %d tratte DIRETTE, e' possibile comunque scegliere tratte NON DIRETTE.\n", numeroArchi);
        printf("NOTA BENE: Le tratte non dirette prevederanno scali.\n");
    }
}


/** FUNZIONE DI INSERIMENTO DI UN NUOVO NODO (NUOVO AEROPORTO) NELLA LISTA DI ADIACENZA**/
Grafo *inserisciNodo(Grafo *G, char nomeaeroporto[50]){
    Edge **adjNew;
    if(G == NULL){
        return grafoVuoto(1);
    }

    adjNew = realloc(G->adj, ((G->numeroVertici)+1) * sizeof(Edge)); /** sizeof con Edge* **/

    if(adjNew == NULL){
        printf("ERRORE: Impossibile reallocare la memoria\n");
    } else {
        G->adj = adjNew;
        strcpy(G->nome[G->numeroVertici],nomeaeroporto);
        G->gettonata[G->numeroVertici] = rand()%5;
        G->adj[G->numeroVertici] = NULL; /** Imposta il nuovo vertice a NULL, con la possibilità di assegnargli contenuto **/
        G->numeroVertici = G->numeroVertici+1;
    }

    return G;
}

/** FUNZIONE PER L'AGGIUNTA DI NUOVI ARCHI, NEL NOSTRO CASO AGGIUNGE UNA TRATTA **/
void aggiungiTratta(Grafo *G, int partenza, int destinazione, int euro, int tempo){
    Edge *arcoNew, *arco;
    if(G != NULL){
        if(partenza >= 0 && partenza <= G->numeroVertici-1){
            if(destinazione>= 0 && destinazione <= G->numeroVertici-1){
                arcoNew = (Edge*) malloc(sizeof(Edge));
                if(arcoNew == NULL){
                    printf("ERRORE: impossibile allocare memoria \n");
                } else {
                    arcoNew->key = destinazione;
                    arcoNew->costo = euro;
                    arcoNew->tempo = tempo;
                    arcoNew->next = NULL;

                    if(G->adj[partenza] == NULL) { /** Il nodo non ha archi **/
                        G->adj[partenza] = arcoNew;
                    } else {
                        arco = G->adj[partenza];
                        while (arco->next != NULL){
                            if(arco->key == destinazione || arco->next->key == destinazione){
                                printf("Il nodo e' gia' presente nella lista\n");
                                return;
                            }
                            arco = arco->next;
                        }
                        arco->next = arcoNew;
                    }
                }
            }
        }
    }
}

/** FUNZIONE PER RIMUOVERE UN ARCO DAL GRAFO (NEL NOSTRO CASO, RIMUOVE UNA TRATTA) **/
void rimuoviArco(Grafo *G, int partenza, int destinazione){

    Edge *prev; /** Arco precedente a quello da togliere nella lista degli archi **/
    Edge *arco; /** Arco da togliere dalla lista **/

    arco = G->adj[partenza];

    if(arco->key == destinazione){
        G->adj[partenza] = arco->next;
    } else {
        prev = arco;
        while (prev->next->key != destinazione){ /** NOTA: Si rischia di accedere ad un area di memoria non allocata **/
            prev = prev->next;
        }

        arco = prev->next;
        prev->next = arco->next;

    }
    free(arco);
}

/** FUNZIONE CHE CONTROLLA QUANTI ARCHI PARTONO DA UN NODO E QUANTI NE ARRIVANO VERSO DI LUI **/
/** NEL NOSTRO CASO, QUANTI VOLI PARTONO DA UN AEROPORTO E QUANTI VOLI, INVECE, LO RAGGIUNGONO **/
void gradoGrafo(Grafo *G, int *gradoEntrante, int *gradoUscente){

    int i;
    Edge *arco;

    if(!isEmptyG(G)){
        for(i=0; i<G->numeroVertici; i++){
            gradoEntrante[i] = 0;
            gradoUscente[i] = 0;
        }

        for(i=0; i<G->numeroVertici; i++){
            arco = G->adj[i];
            while(arco != NULL){
                gradoUscente[i]++;
                gradoEntrante[arco->key]++;
                arco = arco->next;
            }
        }
        for(i=0; i <G->numeroVertici; i++){
           printf("Aeroporto: %d, Voli entranti: %d, Voli uscenti: %d\n", i, gradoEntrante[i], gradoUscente[i]);
        }
    }
}

/** RICERCA IN PROFONDITA' (DFS - DEPTH FIRST SEARCH) **/
void ricercaProfonditaDFS(Grafo *G){
    int i;
    int *nodiVisitati = calloc(G->numeroVertici, sizeof(int)); /** Array dinamico per memorizzare i nodi già visitati **/
    Edge *arco = NULL;

    if(!nodiVisitati){
        printf("ERRORE: Array dinamico per memorizzare i nodi gia' visitati non inizializzato correttamente");
    } else {
        for(i=0; i<G->numeroVertici; i++){

            if(!nodiVisitati[i]){
                arco = G->adj[i];
                if(arco != NULL){
                    printf("\n%d %s: ",i, G->nome[i]);
                    ricercaProfonditaDFS1(G, i, nodiVisitati);
                }
            }

        }
        free(nodiVisitati);
    }
}

/** PROSEGUE LA VISITA DEL GRAFO, DOPO ESSER PASSATO ricercaProfonditaDFS **/
void ricercaProfonditaDFS1(Grafo *G, int i, int *nodiVisitati){
    Edge *arco = NULL;
    nodiVisitati[i] = 1; /** Stiamo visitando il primo nodo, quindi possiamo impostare questo valore ad 1 per dire che effettivamente lo abbiamo già guardato **/

    for(arco = G->adj[i]; arco; arco = arco->next){
        if(!nodiVisitati[arco->key]){
            printf("(%d)%s (%d Euro)\t", arco->key, G->nome[arco->key], arco->costo);
            ricercaProfonditaDFS1(G, arco->key, nodiVisitati);
        }
    }
}

/** RITORNA IL NOME DI UN AEROPORTO **/
char *ritornoNomeAeroporto(Grafo *G, int indice)
{
    if(G !=NULL)
    {

        if(indice!=-1){
            return G->nome[indice];
        } else
        {
            printf("errore aeroporto inesistente");

        }
    }
    return NULL;
}



/** RITORNA L'INDICE DELL'AEROPORTO **/
int IndiceAeroporto(Grafo *g,char NomeAeroporto[50])//ritorna l indice per la ricerca
{
    if(g!=NULL)
    {
        // edge* e;

        for(int i=0; i<=g->numeroVertici-1; i++)
        {
            if(strcmp(g->nome[i],NomeAeroporto)==0)
            {
                return i;
            }
        }
        return -1;
    }
    return -1;
}

int ritornoIndiceMetaGettonata(Grafo *g,int src)
{
    int d=-1;
    if(g!=NULL)
    {
        if(src!=IndiceAeroporto(g,g->nome[0]))
        {
            int gettonata=0;

            for(int i=0; i<g->numeroVertici-1; i++)
            {
                if(i!=IndiceAeroporto(g,g->nome[src]))
                {
                    if(gettonata<g->gettonata[i])
                    {

                        gettonata=g->gettonata[i];
                        d=i;

                    }
                }
            }
            return d;
        }
        else
        {
            int gettonata=0;
            for(int i=0; i<g->numeroVertici-1; i++)
            {
                if(i!=IndiceAeroporto(g,g->nome[src]))
                {
                    if(gettonata<g->gettonata[i])
                    {

                        gettonata=g->gettonata[i];
                        d=i;

                    }
                }
            }
            return d;

        }

    }
    return d;
}

/** AGGIUNGE TUTTE LE TRATTE (ARCHI)**/
Grafo * aggiuntaTratte(Grafo *G){

    aggiungiTratta(G,0,1,15,2);
    aggiungiTratta(G,1,2,20,3);
    aggiungiTratta(G,2,3,50,2);
    aggiungiTratta(G,3,4,45,1);
    aggiungiTratta(G,4,3,45,1);
    aggiungiTratta(G,4,5,30,2);
    aggiungiTratta(G,5,3,55,4);
    aggiungiTratta(G,5,2,70,6);
    aggiungiTratta(G,2,4,15,3);
    aggiungiTratta(G,2,7,60,10);
    aggiungiTratta(G,7,6,15,7);
    aggiungiTratta(G,6,8,18,4);
    aggiungiTratta(G,8,9,28,2);
    aggiungiTratta(G,9,10,10,1);
    aggiungiTratta(G,10,11,62,3);
    aggiungiTratta(G,10,12,47,2);
    aggiungiTratta(G,12,17,88,11);
    aggiungiTratta(G,10,14,50,8);
    aggiungiTratta(G,14,13,22,4);
    aggiungiTratta(G,10,13,10,1);
    aggiungiTratta(G,13,17,82,9);
    aggiungiTratta(G,10,17,65,8);
    aggiungiTratta(G,17,0,200,13);
    aggiungiTratta(G,0,17,200,13);
    aggiungiTratta(G,2,0,20,4);
    aggiungiTratta(G,0,6,78,8);
    aggiungiTratta(G,6,0,78,8);
    aggiungiTratta(G,1,10,150,15);
    aggiungiTratta(G,10,19,122,3);
    aggiungiTratta(G,19,0,30,2);
    aggiungiTratta(G,0,19,60,2);
    aggiungiTratta(G,19,16,132,3);
    aggiungiTratta(G,16,18,320,9);
    aggiungiTratta(G,18,15,50,4);
    aggiungiTratta(G,15,10,88,2);
    aggiungiTratta(G,16,15,57,5);
    aggiungiTratta(G,0,10,112,3);
    aggiungiTratta(G,11,10,62,2);
    aggiungiTratta(G,15,14,22,4);
    aggiungiTratta(G,13,14,22,4);
    aggiungiTratta(G,3,2,50,2);
    aggiungiTratta(G,7,2,60,10);
    aggiungiTratta(G,8,6,18,4);
    aggiungiTratta(G,11,9,11,2);
    aggiungiTratta(G,14,12,55,5);
    aggiungiTratta(G,17,12,88,11);
    aggiungiTratta(G,18,16,320,9);
    aggiungiTratta(G,2,10,26,3);

return G;
}


void AumentoGettonata(Grafo *g,int indice){
    if(g!=NULL){
        g->gettonata[indice]++;
    }

}

void  g_remove_edge(Grafo *G, int u, int v){
	Edge *prev; /* l'arco precedente a quello da togliere nella lista */
  	Edge *e; /* l'arco da togliere dalla lista */
	e = G->adj[u];
  	if(e->key == v)
        G->adj[u] = e->next;
  	else{
        prev = e;
        while(prev->next->key != v) prev=prev->next;
        e = prev->next;
        prev->next=e->next;
    }
  	free(e);
}

void g_grado(Grafo *G, int *ge, int *gu){
    int i;
    Edge *e;

    if(G != NULL){
        for(i = 0; i < G->numeroVertici; i++){
            ge[i] = 0;
            gu[i] = 0;
        }

        for(i = 0; i < G->numeroVertici; i++){
            e = G->adj[i];
            while(e != NULL){
                gu[i]++;
                ge[e->key] = ge[e->key] + 1;
                e = e->next;
            }
        }
    }
}

void g_remove_nodo(Grafo *G, int v){
    int i, j;
    Edge *e;
    if(G != NULL){

        for(j = 0; j < G->numeroVertici - 1; j++){
            e = G->adj[j];

            while(e != NULL){
                if(e->key == v)
                    g_remove_edge(G, j, e->key);

                e = e->next;
            }
        }

        for(i = v; i < G->numeroVertici; i++){
            G->adj[i] = G->adj[i + 1];
            strcpy(G->nome[i], G->nome[i+1]);
            G->gettonata[i] = G->gettonata[i + 1];

            for(j = 0; j < i; j++){
                e = G->adj[j];
                while(e != NULL){
                    if(e->key == i + 1 || e->key == j){
                        e->key = e->key - 1;
                    }
                    e = e->next;
                }
            }
        }

        free(G->nome[i]);
        free(G->adj[i]);
        G->adj[i] = NULL;

        G->numeroVertici = G->numeroVertici - 1;
    }
}
int EsistenzaTrattaTraAeroporti(Grafo *g,int partenza,int arrivo){
    if(g!=NULL){
        if(arrivo != -1){
            Edge *e=g->adj[partenza];
            while(e!=NULL){
                if(e->key==arrivo){
                    return -1;
                }
                e=e->next;
            }
            return 1;
        }else
            return -1;
    }
    return -1;
}

void contaArchiEntrantiEUscenti(Grafo *g)//conta gli archi entranti e uscentri tra i vari nodi
{
    if(g!=NULL)
    {
        Edge *e;
        int i,nodoEntrante,nodoUscente;
        for(i=0; i<g->numeroVertici; i++)
        {
            nodoEntrante=nodoUscente=0;
            e=g->adj[i];
            while(e!=NULL)
            {
                nodoUscente++;
                e=e->next;
            }
            for(int j=0; j<g->numeroVertici; j++)
            {
                e=g->adj[j];
                while(e!=NULL)
                {
                    if(e->key==i)

                        nodoEntrante+=1;
                    e=e->next;
                }
            }
            printf("nodo %d:\t archi uscenti: %d\t archi entrati: %d \n",i,nodoUscente,nodoEntrante);

        }
    }
}
