/*
    File: supermercato.c
    Specifica: file principale del progetto, implementa tutte le procedure di avvio e chiusura
    Autore: Arena Luigi
*/

#include "supermercato.h"

//  Funzione main del progetto
int main(int argc, char* argv[]) {
    int opt, cflag = 0, vflag = 0;
    FILE *config_file;
    char* config_name;

    // Controllo gli argomenti
    while ((opt = getopt(argc, argv, "c:vh")) != -1) {
        switch (opt) {
            case 'c':
                cflag = 1; config_name = optarg; break;
            case 'v':
                vflag = 1; break;
            case 'h':
                fprintf(stderr, "Usage: %s [-c] [nomeFile]\n", argv[0]);
                exit(errno); break;
            default:
                fprintf(stderr, "No valid argument\n");
                exit(EXIT_FAILURE);
        }
    }

    if(cflag == 0) config_name = "config.txt";

// TEST
if(vflag==1) printf("nome file: %s\ncflag: %d\nvflag: %d\n", config_name, cflag, vflag);

    // Provo ad aprile il file di configurazione
    if((config_file = fopen(config_name, "r")) == NULL) {
        perror("Opening configuration file");
        exit(errno);
    }


}
