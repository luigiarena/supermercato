#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#define BUF_SIZE 128
#define PATH_SIZE 128
#define SOCKNAME "./unix_socket"
#define N 100

#define STDIN  0
#define STDOUT 1
#define STDERR 2

#define IFERROR(s,m) if((s)==-1) {perror(m); exit(errno);}
#define IFERROR3(s,m,c) if((s)==-1) {perror(m); c;}

#define WRITE(m) IFERROR(write(STDOUT,m,strlen(m)), m);
#define WRITELN(m) WRITE(m);WRITE("\n");

/*  Struttura che contiene i parametri di configurazione    */
typedef struct param {
    int K;  // Numero max di casse aperte
    int Ki; // Numero di casse aperte inizialmente
    int C;  // Numero max di clienti
    int E;  // C-E è la soglia per far entrare nuovi clienti
    int P;  // Numero max di prodotti acquistabili
    int T;  // Tempo di acquisto per cliente
    int Tp; // Tempo di controllo per ogni prodotto alla cassa
    int Td; // (ms) intervallo aggiornamento del direttore dai cassieri
    int S;  // (ms) intervallo controllo coda per cliente
    int S1; // Soglia per la chiusura delle casse
    int S2; // Soglia per l'apertura delle casse
} param;
