#include "Lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

Utente *nuovoUtente(){
    Utente *utente = NULL;
    utente = (Utente*) malloc(sizeof(Utente));
    utente->numPrenotazioni = -1;
    utente->punti = 0;
    utente->next = NULL;

    return utente;
}

void aggiungiUtenteAllaLista(Utente *testa, Utente *utenteNuovo){
    Utente *app = testa;

    while (app->next != NULL){
        app = app->next;
    }
    app->next = utenteNuovo;

}

void visualizzaUtenti(Utente *testa){
    Utente *app = testa;
    int i = 1;

    if(testa == NULL){
        printf("Non ci sono utenti registrati\n\n");
        return;
    }

    printf("ID\tUSERNAME\t\tPASSWORD\n");
    while (app->next != NULL){
        printf("%d\t%s\t\t\t%s\n", i, app->username, app->password);
        app = app->next;
        i++;
    }
    printf("%d\t%s\t\t\t%s\n", i, app->username, app->password);
}

Utente *selezionaUtente(int selezione, Utente *testa){
    Utente *app = testa;
    int i = 1;

    if(selezione <= contaUtenti(testa)){
        while (i < selezione){
            app = app->next;
            i++;
        }
        return app;
    } else{
        printf("ERRORE: Non esiste alcun utente con quell'ID.\n\n");
        return NULL;
    }
}

int contaUtenti(Utente *testa){
    Utente *app = testa;
    int conteggio = 0;

    if(testa == NULL){
        printf("Non ci sono utenti registrati\n\n");
        return 0;
    }

    while (app->next != NULL){
        app = app->next;
        conteggio++;
    }
    conteggio++;

    return conteggio;
}
