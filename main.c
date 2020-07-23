#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include "MiniHeap.h"
#include "Grafo/Grafo.h"
#include "Lista/Lista.h"
#include "Utility/Utility.h"
int main()
{
    int scelta = -1;
    int sceltaUtente = 0;
    Utente *listaUtenti = NULL;
    srand(time(NULL));

    /** CREAZIONE GRAFO **/
    Grafo *G = grafoVuoto(20);
    /**FINE CREAZIONE GRAFO **/

    /** AGGIUNTA DELLE TRATTE **/
    G=aggiuntaTratte(G);
    /** FINE AGGIUNTA DELLE TRATTE **/

    /** UTENTE O AMMINISTRATORE?**/
    do
    {

        printf("**********************************************\n");
        printf("Vuoi interagire da utente o da amministratore?\n");
        printf("**********************************************\n");
        printf("[1] Utente\n[2] Amministratore\n[0] Esci\n\n");

        do
        {
            printf("Scelta:");
            scanf("%d",&scelta);
            if(scelta != 1 && scelta != 2 && scelta != 0)
            {
                printf("Seleziona una delle possibili scelte! [1] [2] [0]\n\n");
            }
        }
        while(scelta != 1 && scelta != 2 && scelta != 0 );
        system("cls");

        if(scelta == 1)  /****** GESTIONE UTENTE (VIAGGIATORE) ******/
        {
            do
            {
                printf("*****************\n");
                printf("   MENU UTENTE   \n");
                printf("*****************\n");

                printf("[1] Login\n[2] Registrati\n[0] Exit\n");
                do
                {
                    printf("Scelta:");
                    scanf("%d",&sceltaUtente);
                    if(sceltaUtente != 1 && sceltaUtente != 2 && sceltaUtente != 0)
                    {
                        printf("Seleziona una delle possibili scelte! [1] [2] [0]\n\n");
                    }
                }
                while(sceltaUtente != 1 && sceltaUtente != 2 && sceltaUtente != 0 );

                if (sceltaUtente == 1)
                {
                    menuUtenteScelta1(listaUtenti,G);
                }
                else if (sceltaUtente == 2)    /****** REGISTRAZIONE UTENTE ******/
                {
                    system("cls");
                    listaUtenti=creazioneUtente(listaUtenti);
                }
                else if (sceltaUtente == 0)
                {
                    system("cls");
                    printf("Ritorno al menu principale..\n\n");

                }
                // system("cls");
            }
            while(sceltaUtente!=0);
        }
        else if(scelta == 2)     /****** GESTIONE AMMINISTRATORE ******/
        {
            menuAmministratore(listaUtenti,G);
        }
        else if (scelta == 0)    /****** CHIUSURA APPLICAZIONE ******/
        {
            printf("Chiusura dell'applicazione..\n\n");
        }
    }
    while(scelta != 0);
    /** FINE UTENTE O AMMINISTRATORE **/

    system("PAUSE");
    return 0;
}
