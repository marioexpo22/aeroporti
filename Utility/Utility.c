#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "../Grafo/Grafo.h"
#include "../Lista/Lista.h"
#include "../MiniHeap.h"
#include "Utility.h"

void Suppercase(char *stringa)//trasformo le stringhe in maiuscole
{
    char *c;
    for (c = stringa; (*c = toupper(*c)); ++c);
}

Utente *creazioneUtente(Utente *listaUtenti)
{
    Utente* utenteNuovo;
    printf("\n*******************\n");
    printf("** REGISTRAZIONE **\n");
    printf("*******************\n");
    utenteNuovo = nuovoUtente();
    printf("Inserisci USERNAME:");
    scanf("%s",utenteNuovo->username);

    printf("Inserisci PASSWORD:");
    scanf("%s",utenteNuovo->password);
    printf("\n");
    if(listaUtenti == NULL)
    {
        listaUtenti = utenteNuovo;
    }
    else
    {
        aggiungiUtenteAllaLista(listaUtenti,utenteNuovo);
    }
    return listaUtenti;
}
void menuUtenteScelta1(Utente *listaUtenti,Grafo *G)
{

    char aeroportoPartenza[50];
    char aeroportoArrivo[50];
    int indicePartenza = 0;
    int indiceArrivo = 0;
    PrezzoTempo datiBigliettoEconomico;
    datiBigliettoEconomico.prezzo = 0;
    datiBigliettoEconomico.tempo = 0;
    PrezzoTempo datiBigliettoTempo;
    datiBigliettoTempo.prezzo = 0;
    datiBigliettoTempo.tempo = 0;
    int sceltaVolo = 0;
    int sceltaPagamento = 0;
    int calcoloSconto = 0;
    int sconto = 1;

    PrezzoTempo datiBigliettoEconomicoSenzaMeta;
    datiBigliettoEconomicoSenzaMeta.prezzo = 0;
    datiBigliettoEconomicoSenzaMeta.tempo = 0;
    PrezzoTempo datiBigliettoGettonata;
    datiBigliettoGettonata.prezzo = 0;
    datiBigliettoGettonata.tempo = 0;
    int menuUtente;
    int selezioneUtente;
    int sceltaMeta;
    /** VARIABILI ADMIN **/
    Utente* utenteScelto;
    /** VARIABILI VISUALIZZA PRENOTAZIONI **/
    int j = 0;
    /** STAMPA LISTA UTENTI **/

    printf("\n***********\n");
    printf("** LOGIN **\n");
    printf("***********\n");
    visualizzaUtenti(listaUtenti);

    if(listaUtenti != NULL)
    {
        printf("\nAccedi con uno dei seguenti utenti registrati inserendo il suo ID: ");
        scanf("%d", &selezioneUtente);
        utenteScelto = selezionaUtente(selezioneUtente, listaUtenti);
        if(utenteScelto != NULL)
        {
            system("cls");
            printf("\n**********************\n");
            printf("BENVENUTO %s!", utenteScelto->username);
            printf("\n**********************\n");

            /** MENU DELL'UTENTE SCELTO**/

            do
            {
                printf("*****************************\n");
                printf("* COSA VUOI FARE, %s ? *\n",utenteScelto->username);
                printf("*****************************\n");

                printf("[1] Prenota volo\n[2] Visualizza prenotazioni\n[3] Visualizza punti\n[4] Visualizza itinerario\n[0] Esci\n");
                do
                {
                    printf("Scelta:");
                    scanf("%d",&menuUtente);
                    if(menuUtente != 1 && menuUtente != 2 && menuUtente != 3 && menuUtente != 0 && menuUtente!=4)
                    {
                        printf("Seleziona una delle possibili scelte! [1] [2] [3] [4] [0]\n\n");
                    }
                }
                while(menuUtente != 1 && menuUtente != 2 && menuUtente != 3 && menuUtente != 0 && menuUtente !=4);

                if(menuUtente == 1)  /** PRENOTAZIONE DEL VOLO **/
                {
                    system("cls");

                    printf("\n**********************\n");
                    printf("* PRENOTAZIONE VOLO **\n");
                    printf("**********************\n");

                    /** SCELTA PARTENZA E ARRIVO **/
                    fflush(stdin);

                    do  /** INSERIMENTO AEROPORTO DI PARTENZA **/
                    {
                        printf("Inserisci aeroporto di partenza:");
                        scanf("%s",aeroportoPartenza);
                        Suppercase(aeroportoPartenza);
                        fflush(stdin);
                        indicePartenza = IndiceAeroporto(G,aeroportoPartenza);
                        if(indicePartenza == -1)
                        {
                            printf("Non esiste questo aeroporto!\n\n");
                        }
                    }
                    while (indicePartenza == -1);
                    fflush(stdin);

                    do  /** INSERIMENTO META **/
                    {
                        printf("Vuoi inserire una meta? [1] Si [2] No\n");
                        printf("Scelta:");
                        scanf("%d",&sceltaMeta);
                        if(sceltaMeta != 1 && sceltaMeta != 2)
                        {
                            printf("Seleziona una delle possibili scelte! [1] [2]\n\n");
                        }
                    }
                    while(sceltaMeta != 1 && sceltaMeta != 2);

                    if(sceltaMeta == 1)
                    {
                        //system("cls");
                        fflush(stdin);

                        do  /** INSERIMENTO AEROPORTO DI ARRIVO **/
                        {
                            fflush(stdin);
                            printf("Inserisci aeroporto di arrivo:");
                            scanf("%s",aeroportoArrivo);
                            Suppercase(aeroportoArrivo);
                            indiceArrivo = IndiceAeroporto(G,aeroportoArrivo);
                            if(indiceArrivo == -1)
                            {
                                printf("Non esiste questo aeroporto!\n\n");
                            }
                            else if(indiceArrivo==indicePartenza)
                            {
                                printf("l'aeroporto di partenza e arrivo coincidono\n");
                            }
                        }
                        while (indiceArrivo == -1 || indicePartenza==indiceArrivo);
                        fflush(stdin);

                    }
                    else if (sceltaMeta == 2)
                    {
                        indiceArrivo = -1;
                    }
                    /** FINE SCELTA PARTENZA E ARRIVO **/

                    /** ESECUZIONE DIJKSTRA **/
                    if(indicePartenza != -1 && indicePartenza != indiceArrivo && indiceArrivo != -1)
                    {
                        fflush(stdin);
                        system("cls");
                        datiBigliettoEconomico = dijkstraEconomico(G,indicePartenza,indiceArrivo);
                        datiBigliettoTempo = dijkstraTempo(G,indicePartenza,indiceArrivo);

                        printf("\n[1] Volo piu' economico: %s --> %s |PREZZO: %d euro |DURATA: %d ore\n",aeroportoPartenza,aeroportoArrivo,datiBigliettoEconomico.prezzo,datiBigliettoEconomico.tempo);
                        printf("[2] Volo piu' breve: %s --> %s |PREZZO: %d euro |DURATA: %d ore\n\n",aeroportoPartenza,aeroportoArrivo,datiBigliettoTempo.prezzo,datiBigliettoTempo.tempo);
                        printf("Scegli il biglietto:");
                        do
                        {
                            scanf("%d",&sceltaVolo);
                            fflush(stdin);

                            if(sceltaVolo != 1 && sceltaVolo != 2)
                            {
                                printf("Seleziona una delle possibili scelte! [1] [2]\n\n");
                                printf("Scegli il biglietto:");
                            }
                        }
                        while(sceltaVolo != 1 && sceltaVolo != 2);

                        if(utenteScelto->numPrenotazioni < 10)
                        {
                            printf("Prenotazione in corso...\n");
                            utenteScelto->numPrenotazioni++;
                            strcpy(utenteScelto->prenotazioni[utenteScelto->numPrenotazioni].aeroportoDiPartenza,aeroportoPartenza);
                            strcpy(utenteScelto->prenotazioni[utenteScelto->numPrenotazioni].aeroportoDiArrivo,aeroportoArrivo);

                            if(sceltaVolo == 1)  /** BIGLIETTO ECONOMICO **/
                            {
                                utenteScelto->prenotazioni[utenteScelto->numPrenotazioni].tempo = datiBigliettoEconomico.tempo;
                                utenteScelto->prenotazioni[utenteScelto->numPrenotazioni].costo = datiBigliettoEconomico.prezzo;
                                AumentoGettonata(G,datiBigliettoEconomico.aeroportoArrivo);
                                if(utenteScelto->punti > 0)
                                {
                                    printf("E' possibile usufruire di uno sconto di %d euro tramite punti fedelta'.\n", utenteScelto->punti);
                                    printf("Utilizzare ora lo sconto? [1] Si [2] No -->");
                                    do
                                    {
                                        scanf("%d",&sceltaPagamento);
                                        fflush(stdin);
                                        if(sceltaPagamento != 1 && sceltaPagamento != 2)
                                        {
                                            printf("Seleziona una delle possibili scelte! [1] [2]\n\n");
                                            printf("Utilizzare ora lo sconto? [1] Si [2] No -->");
                                        }
                                    }
                                    while(sceltaPagamento != 1 && sceltaPagamento != 2);

                                    calcoloSconto = 0;
                                    if(sceltaPagamento == 1)
                                    {
                                        sconto = 1;
                                        calcoloSconto = datiBigliettoEconomico.prezzo - utenteScelto->punti;
                                        if(calcoloSconto < 0)
                                        {
                                            utenteScelto->punti = calcoloSconto*(-1);
                                            calcoloSconto = 0;
                                        }
                                        else
                                        {
                                            utenteScelto->punti = utenteScelto->punti - (datiBigliettoEconomico.prezzo - calcoloSconto);
                                        }
                                        printf("Biglietto acquistato con sconto, hai pagato %d anziche' %d\n",calcoloSconto,datiBigliettoEconomico.prezzo);
                                        printf("Ti rimangono %d punti.\n",utenteScelto->punti);
                                    }
                                    else if (sceltaPagamento == 2)
                                    {
                                        printf("Biglietto acquistato senza sconto.\n");
                                        sconto = 0;
                                    }
                                    if(calcoloSconto > 0)
                                    {
                                        utenteScelto->punti = utenteScelto->punti + calcoloSconto;
                                        printf("Hai guadagnato %d punti, ora possiedi %d punti.\n\n",calcoloSconto,utenteScelto->punti);
                                    }
                                    else if(calcoloSconto == 0)
                                    {
                                        utenteScelto->punti = utenteScelto->punti + calcoloSconto;
                                        printf("Hai guadagnato %d punti, ora possiedi %d punti.\n\n",calcoloSconto,utenteScelto->punti);
                                    }
                                    else
                                    {
                                        utenteScelto->punti = utenteScelto->punti + datiBigliettoEconomico.prezzo;
                                        printf("Hai guadagnato %d punti, ora possiedi %d punti.\n\n",datiBigliettoEconomico.prezzo,utenteScelto->punti);
                                    }

                                }
                                else
                                {
                                    printf("Non possiedi punti, non e' possibile usufruire dello sconto.\n");
                                    utenteScelto->punti = utenteScelto->punti + datiBigliettoEconomico.prezzo;
                                    printf("Biglietto acquistato.\nHai guadagnato %d punti, ora possiedi %d punti.\n\n",datiBigliettoEconomico.prezzo,utenteScelto->punti);
                                }

                            }
                            else if (sceltaVolo == 2)    /** BIGLIETTO TEMPO BREVE **/
                            {

                                utenteScelto->prenotazioni[utenteScelto->numPrenotazioni].tempo = datiBigliettoTempo.tempo;
                                utenteScelto->prenotazioni[utenteScelto->numPrenotazioni].costo = datiBigliettoTempo.prezzo;
                                AumentoGettonata(G,datiBigliettoTempo.aeroportoArrivo);
                                if(utenteScelto->punti > 0)
                                {
                                    printf("E' possibile usufruire di uno sconto di %d euro tramite punti fedelta'.\n", utenteScelto->punti);
                                    printf("Utilizzare ora lo sconto? [1] Si [2] No -->");
                                    do
                                    {
                                        scanf("%d",&sceltaPagamento);
                                        if(sceltaPagamento != 1 && sceltaPagamento != 2)
                                        {
                                            printf("Seleziona una delle possibili scelte! [1] [2]\n\n");
                                            printf("Utilizzare ora lo sconto? [1] Si [2] No -->");
                                        }
                                    }
                                    while(sceltaPagamento != 1 && sceltaPagamento != 2);

                                    calcoloSconto = 0;
                                    if(sceltaPagamento == 1)
                                    {
                                        sconto = 1;
                                        calcoloSconto = datiBigliettoTempo.prezzo - utenteScelto->punti;
                                        if(calcoloSconto < 0)
                                        {
                                            utenteScelto->punti = calcoloSconto*(-1);
                                            calcoloSconto = 0;
                                        }
                                        else
                                        {
                                            utenteScelto->punti = utenteScelto->punti - (datiBigliettoTempo.prezzo - calcoloSconto);
                                        }
                                        printf("Biglietto acquistato con sconto, hai pagato %d anziche' %d\n",calcoloSconto,datiBigliettoTempo.prezzo);
                                        printf("Ti rimangono %d punti.\n",utenteScelto->punti);
                                    }
                                    else if (sceltaPagamento == 2)
                                    {
                                        printf("Biglietto acquistato senza sconto.\n");
                                        sconto = 0;
                                    }
                                    if(calcoloSconto > 0)
                                    {
                                        utenteScelto->punti = utenteScelto->punti + calcoloSconto;
                                        printf("Hai guadagnato %d punti, ora possiedi %d punti.\n\n",calcoloSconto,utenteScelto->punti);
                                    }
                                    else if(calcoloSconto == 0 && sconto == 1)
                                    {
                                        utenteScelto->punti = utenteScelto->punti + calcoloSconto;
                                        printf("Hai guadagnato %d punti, ora possiedi %d punti.\n\n",calcoloSconto,utenteScelto->punti);
                                    }
                                    else
                                    {
                                        utenteScelto->punti = utenteScelto->punti + datiBigliettoTempo.prezzo;
                                        printf("Hai guadagnato %d punti, ora possiedi %d punti.\n\n",datiBigliettoTempo.prezzo,utenteScelto->punti);
                                    }

                                }
                                else
                                {
                                    printf("Non possiedi punti, non e' possibile usufruire dello sconto.\n");
                                    utenteScelto->punti = utenteScelto->punti + datiBigliettoTempo.prezzo;
                                    printf("Biglietto acquistato.\nHai guadagnato %d punti, ora possiedi %d punti.\n\n",datiBigliettoTempo.prezzo,utenteScelto->punti);
                                }
                            }
                        }
                        else
                        {
                            printf("Hai raggiunto il limite massimo di prenotazioni per questo account.\n\n");
                        }
                        fflush(stdin);
                    }
                    else
                    {
                        if (indiceArrivo == -1)
                        {
                            fflush(stdin);
                            //system("cls");
                            printf("Non hai scelto la meta, te ne proponiamo 2.\n");
                            datiBigliettoEconomicoSenzaMeta = dijkstraEconomico(G,indicePartenza,indiceArrivo);
                            int indiceAeroportoArrivo = ritornoIndiceMetaGettonata(G,indicePartenza);
                            datiBigliettoGettonata = dijkstraTempo(G,indicePartenza, indiceAeroportoArrivo);
                            // datiBigliettoGettonata = dijkstraEconomico(G,indicePartenza,indiceAeroportoArrivo);

                            printf("\n[1] Volo piu' economico: %s --> %s |PREZZO: %d euro |DURATA: %d ore",aeroportoPartenza,ritornoNomeAeroporto(G,datiBigliettoEconomicoSenzaMeta.aeroportoArrivo),datiBigliettoEconomicoSenzaMeta.prezzo,datiBigliettoEconomicoSenzaMeta.tempo);
                            printf("\n[2] Volo piu' gettonato: %s --> %s |PREZZO: %d euro |DURATA: %d ore\n\n",aeroportoPartenza,ritornoNomeAeroporto(G,datiBigliettoGettonata.aeroportoArrivo),datiBigliettoGettonata.prezzo, datiBigliettoGettonata.tempo);

                            printf("Scegli il biglietto:");
                            do
                            {
                                scanf("%d",&sceltaVolo);
                                if(sceltaVolo != 1 && sceltaVolo != 2)
                                {
                                    printf("Seleziona una delle possibili scelte! [1] [2]\n\n");
                                    printf("Scegli il biglietto:");
                                }
                            }
                            while(sceltaVolo != 1 && sceltaVolo != 2);
                            fflush(stdin);

                            if(utenteScelto->numPrenotazioni < 10)
                            {
                                printf("Prenotazione in corso...\n");
                                utenteScelto->numPrenotazioni++;
                                strcpy(utenteScelto->prenotazioni[utenteScelto->numPrenotazioni].aeroportoDiPartenza,aeroportoPartenza);

                                if(sceltaVolo == 1)  /** BIGLIETTO ECONOMICO SENZA META **/
                                {
                                    strcpy(utenteScelto->prenotazioni[utenteScelto->numPrenotazioni].aeroportoDiArrivo,ritornoNomeAeroporto(G,datiBigliettoEconomicoSenzaMeta.aeroportoArrivo));
                                    utenteScelto->prenotazioni[utenteScelto->numPrenotazioni].tempo = datiBigliettoEconomicoSenzaMeta.tempo;
                                    utenteScelto->prenotazioni[utenteScelto->numPrenotazioni].costo = datiBigliettoEconomicoSenzaMeta.prezzo;
                                    AumentoGettonata(G,datiBigliettoEconomicoSenzaMeta.aeroportoArrivo);
                                    if(utenteScelto->punti > 0)
                                    {
                                        printf("E' possibile usufruire di uno sconto di %d euro tramite punti fedelta'.\n", utenteScelto->punti);
                                        printf("Utilizzare ora lo sconto? [1] Si [2] No -->");
                                        do
                                        {
                                            scanf("%d",&sceltaPagamento);
                                            fflush(stdin);
                                            if(sceltaPagamento != 1 && sceltaPagamento != 2)
                                            {
                                                printf("Seleziona una delle possibili scelte! [1] [2]\n\n");
                                                printf("Utilizzare ora lo sconto? [1] Si [2] No -->");
                                            }
                                        }
                                        while(sceltaPagamento != 1 && sceltaPagamento != 2);

                                        calcoloSconto = 0;
                                        if(sceltaPagamento == 1)
                                        {
                                            sconto = 1;
                                            calcoloSconto = datiBigliettoEconomicoSenzaMeta.prezzo - utenteScelto->punti;
                                            if(calcoloSconto < 0)
                                            {
                                                utenteScelto->punti = calcoloSconto*(-1);
                                                calcoloSconto = 0;
                                            }
                                            else
                                            {
                                                utenteScelto->punti = utenteScelto->punti - (datiBigliettoEconomicoSenzaMeta.prezzo - calcoloSconto);
                                            }
                                            printf("Biglietto acquistato con sconto, hai pagato %d anziche' %d\n",calcoloSconto,datiBigliettoEconomicoSenzaMeta.prezzo);
                                            printf("Ti rimangono %d punti.\n",utenteScelto->punti);
                                        }
                                        else if (sceltaPagamento == 2)
                                        {
                                            printf("Biglietto acquistato senza sconto.\n");
                                            sconto = 0;
                                        }
                                        if(calcoloSconto > 0)
                                        {
                                            utenteScelto->punti = utenteScelto->punti + calcoloSconto;
                                            printf("Hai guadagnato %d punti, ora possiedi %d punti.\n\n",calcoloSconto,utenteScelto->punti);
                                        }
                                        else if(calcoloSconto == 0 && sconto == 1)
                                        {
                                            utenteScelto->punti = utenteScelto->punti + calcoloSconto;
                                            printf("Hai guadagnato %d punti, ora possiedi %d punti.\n\n",calcoloSconto,utenteScelto->punti);
                                        }
                                        else
                                        {
                                            utenteScelto->punti = utenteScelto->punti + datiBigliettoEconomicoSenzaMeta.prezzo;
                                            printf("Hai guadagnato %d punti, ora possiedi %d punti.\n\n",datiBigliettoEconomicoSenzaMeta.prezzo,utenteScelto->punti);
                                        }

                                    }
                                    else
                                    {
                                        printf("Non possiedi punti, non e' possibile usufruire dello sconto.\n");
                                        utenteScelto->punti = utenteScelto->punti + datiBigliettoEconomicoSenzaMeta.prezzo;
                                        printf("Biglietto acquistato.\nHai guadagnato %d punti, ora possiedi %d punti.\n\n",datiBigliettoEconomicoSenzaMeta.prezzo,utenteScelto->punti);
                                    }

                                }
                                else if (sceltaVolo == 2)    /** BIGLIETTO ECONOMICO GETTONATA **/
                                {

                                    strcpy(utenteScelto->prenotazioni[utenteScelto->numPrenotazioni].aeroportoDiArrivo,ritornoNomeAeroporto(G,datiBigliettoGettonata.aeroportoArrivo));
                                    utenteScelto->prenotazioni[utenteScelto->numPrenotazioni].tempo = datiBigliettoGettonata.tempo;
                                    utenteScelto->prenotazioni[utenteScelto->numPrenotazioni].costo = datiBigliettoGettonata.prezzo;
                                    AumentoGettonata(G,datiBigliettoGettonata.aeroportoArrivo);
                                    if(utenteScelto->punti > 0)
                                    {
                                        printf("E' possibile usufruire di uno sconto di %d euro tramite punti fedelta'.\n", utenteScelto->punti);
                                        printf("Utilizzare ora lo sconto? [1] Si [2] No -->");
                                        do
                                        {
                                            scanf("%d",&sceltaPagamento);
                                            if(sceltaPagamento != 1 && sceltaPagamento != 2)
                                            {
                                                printf("Seleziona una delle possibili scelte! [1] [2]\n\n");
                                                printf("Utilizzare ora lo sconto? [1] Si [2] No -->");
                                            }
                                        }
                                        while(sceltaPagamento != 1 && sceltaPagamento != 2);

                                        calcoloSconto = 0;
                                        if(sceltaPagamento == 1)
                                        {
                                            sconto = 1;
                                            calcoloSconto = datiBigliettoGettonata.prezzo - utenteScelto->punti;
                                            if(calcoloSconto < 0)
                                            {
                                                utenteScelto->punti = calcoloSconto*(-1);
                                                calcoloSconto = 0;
                                            }
                                            else
                                            {
                                                utenteScelto->punti = utenteScelto->punti - (datiBigliettoGettonata.prezzo - calcoloSconto);
                                            }
                                            printf("Biglietto acquistato con sconto, hai pagato %d anziche' %d\n",calcoloSconto,datiBigliettoGettonata.prezzo);
                                            printf("Ti rimangono %d punti.\n",utenteScelto->punti);
                                        }
                                        else if (sceltaPagamento == 2)
                                        {
                                            printf("Biglietto acquistato senza sconto.\n");
                                            sconto = 0;
                                        }

                                        if(calcoloSconto > 0)
                                        {
                                            utenteScelto->punti = utenteScelto->punti + calcoloSconto;
                                            printf("Hai guadagnato %d punti, ora possiedi %d punti.\n\n",calcoloSconto,utenteScelto->punti);
                                        }
                                        else if(calcoloSconto == 0 && sconto == 1)
                                        {
                                            utenteScelto->punti = utenteScelto->punti + calcoloSconto;
                                            printf("Hai guadagnato %d punti, ora possiedi %d punti.\n\n",calcoloSconto,utenteScelto->punti);
                                        }
                                        else
                                        {
                                            utenteScelto->punti = utenteScelto->punti + datiBigliettoGettonata.prezzo;
                                            printf("Hai guadagnato %d punti, ora possiedi %d punti.\n\n",datiBigliettoGettonata.prezzo,utenteScelto->punti);
                                        }

                                    }
                                    else
                                    {
                                        printf("Non possiedi punti, non e' possibile usufruire dello sconto.\n");
                                        utenteScelto->punti = utenteScelto->punti + datiBigliettoGettonata.prezzo;
                                        printf("Biglietto acquistato.\nHai guadagnato %d punti, ora possiedi %d punti.\n\n",datiBigliettoGettonata.prezzo,utenteScelto->punti);
                                    }
                                }
                            }
                            else
                            {
                                printf("Hai raggiunto il limite massimo di prenotazioni per questo account.\n\n");
                            }
                        }
                        else
                        {
                            printf("L'aeroporto di partenza e di arrivo coincidono.\n");
                        }
                    }
                    /** FINE DIJKSTRA **/

                }
                else if(menuUtente == 2)    /** VISUALIZZA PRENOTAZIONI **/
                {
                    system("cls");
                    printf("\n***********************************\n");
                    printf("* Elenco delle prenotazioni di %s *\n", utenteScelto->username);
                    printf("***********************************\n");
                    j = 0;

                    while (j <= utenteScelto->numPrenotazioni)
                    {
                        printf("%d) %s --> %s |PREZZO: %d |DURATA: %d\n",j+1,utenteScelto->prenotazioni[j].aeroportoDiPartenza,utenteScelto->prenotazioni[j].aeroportoDiArrivo,utenteScelto->prenotazioni[j].costo,utenteScelto->prenotazioni[j].tempo);
                        j++;
                    }
                    printf("\n");

                }
                else if(menuUtente == 3)    /** VISUALIZZA PUNTI **/
                {
                    system("cls");
                    printf("\n***********************************\n");
                    printf("* Punti di %s *\n", utenteScelto->username);
                    printf("***********************************\n");
                    printf("L'utente ha %d punti.\n\n",utenteScelto->punti);

                }
                else if(menuUtente == 0)    /** LOGOUT **/
                {
                    system("cls");
                    printf("LOGOUT DA %s\n", utenteScelto->username);
                }
                else if(menuUtente == 4)
                {
                    system("cls");
                    stampaGrafoViaggiatore(G);
                }
                fflush(stdin);
            }
            while (menuUtente != 0);
            /** FINE MENU DELL'UTENTE SCELTO**/

        }
    }
}
void menuAmministratore(Utente *listaUtenti,Grafo *G)
{
    system("cls");
    int sceltaAdmin;
    char newAeroporto[50];
    char aeroportoPartenza[50];
    char aeroportoArrivo[50];
    int indicePartenza;
    int i;
    char tratta[50];
    int costo;
    int tempo;
    do
    {
        printf("***********************\n");
        printf("  MENU AMMINISTRATORE \n");
        printf("***********************\n");
        printf("[1] Aggiungi un nuovo aeroporto \n");
        printf("[2] Rimuovi una tratta \n");
        printf("[3] Aggiungi tratta \n");
        printf("[4] Visualizza itinerario \n");
        printf("[5] Visualizza Lista utenti \n");
        printf("[0] exit \n");
        printf("Scelta:");
        scanf("%d",&sceltaAdmin);
        if(sceltaAdmin==1)
        {
            system("cls");
            printf("INSERIMENTO DI UN NUOVO AEROPORTO \n");
            do  /** INSERIMENTO AEROPORTO DA AGGIUNGERE **/
            {
                printf("Inserisci aeroporto da aggiungere:");
                scanf("%s",newAeroporto);
                fflush(stdin);
                Suppercase(newAeroporto);
                indicePartenza = IndiceAeroporto(G,newAeroporto);
                if(indicePartenza == -1)
                {
                    /** SI PUO' AGGIUNGERE **/
                    printf("Non esiste questo aeroporto!\n\n Aeroporto creato\n");
                    G = inserisciNodo(G,newAeroporto);
                    int numeroAeroporti;
                    do
                    {
                        printf("L'aeroporto %s, da quanti aeroporti e' raggiunto?",newAeroporto);
                        scanf("%d",&numeroAeroporti);
                        fflush(stdin);

                    }
                    while(numeroAeroporti<=0 || numeroAeroporti>G->numeroVertici-1);
                    i=0;
                    do
                    {
                        printf("inserisci l'aeroporto \n");
                        scanf("%s",tratta);
                          fflush(stdin);
                        Suppercase(tratta);
                        if(IndiceAeroporto(G,tratta) != -1 && strcmp(tratta,newAeroporto) != 0)
                        {
                            do
                            {
                                printf("inserisci il costo del viaggio ");
                                scanf("%d",&costo);
                                  fflush(stdin);
                                if(costo==0)
                                {
                                    printf("errore \n");
                                }
                            }
                            while(costo<=0);
                            do
                            {
                                printf("inserisci il tempo del viaggio ");
                                scanf("%d",&tempo);
                                  fflush(stdin);
                                if(tempo==0)
                                {
                                    printf("errore \n");
                                }
                            }
                            while(tempo<=0);
                            aggiungiTratta(G,IndiceAeroporto(G,tratta),IndiceAeroporto(G,newAeroporto),costo,tempo);
                            i++;
                        }
                        else
                        {
                            printf("non esiste l'aroporto di arrivo");
                        }
                    }
                    while(i<numeroAeroporti);
                    do
                    {
                        printf("L'aeroporto %s quanti aeroporti raggiunge?",newAeroporto);
                        scanf("%d",&numeroAeroporti);
                          fflush(stdin);


                    }
                    while(numeroAeroporti<=0 || numeroAeroporti>G->numeroVertici-1);
                    i=0;
                    do
                    {
                        printf("inserisci l'aeroporto \n");
                        scanf("%s",tratta);
                          fflush(stdin);
                        Suppercase(tratta);
                        if(IndiceAeroporto(G,tratta) != -1 && strcmp(tratta,newAeroporto) != 0)
                        {
                            do
                            {
                                printf("inserisci il costo del viaggio ");
                                scanf("%d",&costo);
                                  fflush(stdin);
                                if(costo==0)
                                {
                                    printf("errore \n");
                                }
                            }
                            while(costo<=0);
                            do
                            {
                                printf("inserisci il tempo del viaggio ");
                                scanf("%d",&tempo);
                                  fflush(stdin);
                                if(tempo==0)
                                {
                                    printf("errore \n");
                                }
                            }
                            while(tempo<=0);
                            aggiungiTratta(G,IndiceAeroporto(G,newAeroporto),IndiceAeroporto(G,tratta),costo,tempo);
                            printf("Tratta Aggiunta\n");
                            i++;
                        }
                        else
                        {
                            printf("non esiste l'aroporto di arrivo");
                        }
                    }
                    while(i<numeroAeroporti);




                }
                else
                {
                    printf("L'aeroporto e' gia' presente!\n\n");
                }

            }
            while (indicePartenza !=- 1);

        }
        else
        {
            if(sceltaAdmin==2)
            {
                system("cls");
                printf("RIMOZIONE DI UNA TRATTA \n");
                int arrivo, partenza;
                do
                {
                    printf("inserisci nome dell'Aeroporto\n");
                    scanf("%s",aeroportoPartenza);
                    Suppercase(aeroportoPartenza);
                }
                while(IndiceAeroporto(G, aeroportoPartenza)==-1); //controllo esistenza
                partenza = IndiceAeroporto(G, aeroportoPartenza);
                fflush(stdin);
                do
                {
                    printf("inserisci nome dell'Aeroporto di arrivo\n");
                    scanf("%s", aeroportoArrivo);
                    Suppercase(aeroportoArrivo);
                    arrivo = IndiceAeroporto(G, aeroportoArrivo);
                    if(EsistenzaTrattaTraAeroporti(G,partenza,arrivo)==-1)
                    {
                        printf("Non esiste una tratta diretta tra l'aeroporto di %s e %s\n ",aeroportoPartenza,aeroportoArrivo);
                    }
                }
                while(EsistenzaTrattaTraAeroporti(G,partenza,arrivo)==-1);
                int g=G->numeroVertici;
                int ge[g], gu[g];
                g_remove_edge(G, partenza, arrivo);
                g_grado(G, ge, gu);
                system("cls");
                if(ge[partenza] == 0 || (ge[partenza] > 0 && gu[partenza] == 0))
                {
                    g_remove_nodo(G, partenza);
                    printf("l'aeroporto %s e' stato distrutto\n",aeroportoPartenza);
                }
                fflush(stdin);
                int sceltatratta;
                if(ge[arrivo] == 0 || (ge[arrivo] > 0 && gu[arrivo] == 0))
                {
                    do
                    {
                        printf("L'aeroporto %s non ha nessuna tratta in entrata\n Vuoi aggiungere una tratta ?[1]Si [2]No ",ritornoNomeAeroporto(G,arrivo));
                        scanf("%d",&sceltatratta);
                        fflush(stdin);
                    }
                    while(sceltatratta!=1 && sceltatratta!=2);
                    if(sceltatratta==1)
                    {
                        fflush(stdin);
                        int numeroAeroporti;
                        do
                        {
                            printf("L'aeroporto %s, da quanti aeroporti e' raggiunto?",ritornoNomeAeroporto(G,arrivo));
                            scanf("%d",&numeroAeroporti);

                        }
                        while(numeroAeroporti<=0 || numeroAeroporti>G->numeroVertici-1);
                        i=0;
                        char tratta[50];
                        int tempo;
                        int costo;
                        do
                        {
                            printf("inserisci l'aeroporto \n");
                            scanf("%s",tratta);
                            Suppercase(tratta);
                            if(IndiceAeroporto(G,tratta) != -1 && strcmp(tratta,ritornoNomeAeroporto(G,arrivo) )!= 0)
                            {
                                do
                                {
                                    printf("inserisci il costo del viaggio ");
                                    scanf("%d",&costo);
                                    if(costo==0)
                                    {
                                        printf("errore \n");
                                    }
                                }
                                while(costo<=0);
                                do
                                {
                                    printf("inserisci il tempo del viaggio ");
                                    scanf("%d",&tempo);
                                    if(tempo==0)
                                    {
                                        printf("errore \n");
                                    }
                                }
                                while(tempo<=0);
                                aggiungiTratta(G,IndiceAeroporto(G,tratta),arrivo,costo,tempo);
                                i++;
                            }
                            else
                            {
                                printf("non esiste l'aroporto di arrivo");
                            }
                        }
                        while(i<numeroAeroporti);

                    }
                    else
                    {
                        printf("L'aeroporto %s e' stato distrutto \n ",ritornoNomeAeroporto(G,arrivo));
                        g_remove_nodo(G, arrivo);
                    }
                }
                fflush(stdin);

            }
            else if(sceltaAdmin==3)
            {
                char newAeroporto[50];
                char arrivoAeroporto[50];
                int indiceArrivo,indicePartenza;
                int tempo;
                int costo;
                int flag=0;
                 system("cls");
                 printf("INSERIMENTO DI UNA NUOVA TRATTA\n");
                do
                {

                    printf("Inserisci aeroporto: ");
                    scanf("%s",newAeroporto);
                    fflush(stdin);
                    Suppercase(newAeroporto);
                    indicePartenza = IndiceAeroporto(G,newAeroporto);
                    if(indicePartenza==-1)
                    {
                        printf("inserire un'aeroporto esistente \n");
                    }
                }while(indicePartenza==-1);

                   do{
                        printf("Inserisci nome aeroporto da raggiungere:");
                        scanf("%s",arrivoAeroporto);
                        fflush(stdin);
                        Suppercase(arrivoAeroporto);
                        indiceArrivo = IndiceAeroporto(G,arrivoAeroporto);
                        if(strcmp(arrivoAeroporto,ritornoNomeAeroporto(G,indicePartenza) )!= 0)
                        {
                            if(EsistenzaTrattaTraAeroporti(G,indicePartenza,indiceArrivo)!=-1)
                            {
                                do
                                {
                                    printf("inserisci il costo del viaggio ");
                                    scanf("%d",&costo);
                                    if(costo==0)
                                    {
                                        printf("errore \n");
                                    }
                                }
                                while(costo<=0);
                                do
                                {
                                    printf("inserisci il tempo del viaggio ");
                                    scanf("%d",&tempo);
                                    if(tempo==0)
                                    {
                                        printf("errore \n");
                                    }
                                }
                                while(tempo<=0);
                                aggiungiTratta(G,IndiceAeroporto(G,newAeroporto),indiceArrivo,costo,tempo);
                                printf("Tratta aggiunta\n");
                                flag++;

                            }
                            else
                            {
                                if(indiceArrivo == -1)
                                    printf("inserire un'aeroporto esistente \n");
                                else
                                    printf("Esiste gia' una tratta diretta tra l'aeroporto di %s e %s\n ",newAeroporto,arrivoAeroporto);
                            }


                        }
                        else
                        {
                            printf("Aeroporto di partenza e arrivo coincidono\n ");
                        }
                   }while(flag==0);





            }
            else if(sceltaAdmin==4)
            {
                system("cls");
                stampaGrafoAmministratore(G);

            }
            else if(sceltaAdmin==5)
            {
                system("cls");
                visualizzaUtenti(listaUtenti);
            }
        }
        fflush(stdin);
    }
    while(sceltaAdmin!=0);
    system("cls");


}
