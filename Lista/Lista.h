#ifndef __LISTA_H
#define __LISTA_H
typedef struct voloPrenotato{
    char aeroportoDiPartenza[20];
    char aeroportoDiArrivo[20];
    int tempo;
    int costo;
}Volo;

typedef struct utente{
    char username[16];
    char password[11];
    Volo prenotazioni[10];
    int numPrenotazioni;
    int punti;
    struct utente *next;
}Utente;

typedef struct prezzoTempo{
    int prezzo;
    int tempo;
    int aeroportoArrivo;
}PrezzoTempo;

Utente *nuovoUtente();
void aggiungiUtenteAllaLista(Utente *, Utente *);
void visualizzaUtenti(Utente *);
int contaUtenti(Utente *);
Utente *selezionaUtente(int, Utente *);
#endif // __LISTA_H
