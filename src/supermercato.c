/*
    File: supermercato.c
    Specifica: file principale del progetto, implementa tutte le procedure di avvio e chiusura
    Autore: Arena Luigi
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


//  Funzione main del progetto
int main(int argc, char* argv[]) {
    FILE *config;
    char* config_name;

    // Controllo gli argomenti
    switch (argc) {
        case 1:{
            config_name = "../config.txt";
            break;
        }
        case 3:{
            if (strcmp(argv[1], "-c")==0 || strcmp(argv[1], "-C")==0) {
                config_name = argv[2];
                break;
            }
        }
        default: {
            fprintf(stderr, "Usage: %s [-c] [nomeFile]\n", argv[0]);
            exit(errno);
            break;
        }
    }

    // Provo ad aprile il file di configurazione
    if((config = fopen(config_name, "r")) == NULL) {
        perror("Opening configuration file");
        exit(errno);
    }
    

}
