#include "super_include.h"

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

void remove_spaces(char buffer[]) {
    int i=0, j=1;
    while (buffer[i] != '\0' && i < BUF_SIZE-1 && j < BUF_SIZE-1) {
        //printf("-iter i: %d\n", i);
        if (buffer[i] == ' ') {
            while (buffer[j] == ' ' && buffer[j] != '\0' && j < BUF_SIZE) j++; 
            buffer[i] = buffer[j];
            buffer[j] = ' ';         
        }
        if (buffer[i] == '\0') return;
        i++; j++;
    }
}

int val_check(int val, int min, int max) {
    if (val >= min && val <= max) return 0;
    else return 1; 
}

void cleanup() {
	unlink(SOCKNAME);
}
/*
void connessione_client() {
    strncpy(sa.sun_path, SOCKNAME, PATH_SIZE);
    sa.sun_family=AF_UNIX;

    fd_skt=socket(AF_UNIX,SOCK_STREAM,0);
    while(connect(fd_skt,(struct sockaddr*)&sa, sizeof(sa)) == -1) {
        if (errno == ENOENT) sleep(1);
        else exit(EXIT_FAILURE);
    }
}
*/