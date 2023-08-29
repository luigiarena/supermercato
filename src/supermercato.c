/*
    File: supermercato.c
    Specifica: file principale del progetto, implementa tutte le procedure di avvio e chiusura
    Autore: Arena Luigi
*/

#include "supermercato.h"

//param* config = malloc(sizeof(param));

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
/*
int param_check(param* config) {
    if(config->K < 1 || config->K > 20) {
        perror("This supermarket will not open. In config file 'K' has bad value");
        CONFIG_VALUE();
        return 1;    }
    if(k > K || k < 1)
        k = 1;
    if(C < 2 || C > MAXC) {
        perror("This supermarket will not open. In config file 'C' has bad value");
        CONFIG_VALUE();
        return 1;
    }
    if(E >= C || E < 1) {
        perror("This supermarket will not open. In config file 'E' has bad value");
        CONFIG_VALUE();
        return 1;
    }
    if(T < MINT || T > MAXT) {
        perror("This supermarket will not open. In config file 'T' has bad value");
        CONFIG_VALUE();
        return 1;
    }
    if(P < 0 || P > MAXP) {
        perror("This supermarket will not open. In config file 'P' has bad value");
        CONFIG_VALUE();
        return 1;
    }
    if(S1 < MINS || S1 > K) {
        perror("This supermarket will not open. In config file 'S1' has bad value");
        CONFIG_VALUE();
        return 1;
    }
    if(S2 < MINS || S2 > C) {
        perror("This supermarket will not open. In config file 'S2' has bad value");
        CONFIG_VALUE();
        return 1;
    }
    if(Td < MINTD || Td > MAXTD) {
        perror("This supermarket will not open. In config file 'Td' has bad value");
        CONFIG_VALUE();
        return 1;
    }
    if(Tp < 1 || Tp > MAXTP) {
        perror("This supermarket will not open. In config file 'Tp' has bad value");
        CONFIG_VALUE();
        return 1;
    }
    return 0;
}*/

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
                fprintf(stderr, "Usage: %s [-h] [-v] [-c] [nomeFile]\n", argv[0]);
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

    // Leggo i valori dei parametri e li salvo nella struttura param
    param* config = malloc(sizeof(param));
    char buffer[BUF_SIZE];
    char* par; 
    int val, val_c;

    while (fgets(buffer, BUF_SIZE, config_file) != NULL) {
        remove_spaces(buffer);
        if (buffer[0] == '#' || buffer[0] == '\n') continue;
        printf("%s", buffer);
        
        par = strtok(buffer, ":");
        val = atoi(strtok(NULL, ":"));
        if      (strcmp(par, "K")  == 0 && (val_c=val_check(val, 1, 400))==0) {config->K = val;}
        else if (strcmp(par, "Ki") == 0 && (val_c=val_check(val, 1, 400))==0) {config->Ki = val;}
        else if (strcmp(par, "C")  == 0 && (val_c=val_check(val, 1, 400))==0) {config->C = val;}
        else if (strcmp(par, "E")  == 0 && (val_c=val_check(val, 1, 400))==0) {config->E = val;}
        else if (strcmp(par, "P")  == 0 && (val_c=val_check(val, 1, 400))==0) {config->P = val;}
        else if (strcmp(par, "T")  == 0 && (val_c=val_check(val, 1, 400))==0) {config->T = val;}
        else if (strcmp(par, "Tp") == 0 && (val_c=val_check(val, 1, 400))==0) {config->Tp = val;}
        else if (strcmp(par, "Td") == 0 && (val_c=val_check(val, 1, 400))==0) {config->Td = val;}
        else if (strcmp(par, "S")  == 0 && (val_c=val_check(val, 1, 400))==0) {config->S = val;}
        else if (strcmp(par, "S1") == 0 && (val_c=val_check(val, 1, 400))==0) {config->S1 = val;}
        else if (strcmp(par, "S2") == 0 && (val_c=val_check(val, 1, 400))==0) {config->S2 = val;}
        else {
            if (val_c == 1) fprintf(stderr, "Valore di %s: %d non valido.\n", par, val); 
            else fprintf(stderr, "Parametro di configurazione %s non riconosciuto.\n", par);
            exit(EXIT_FAILURE);
        }
    }

    //TEST
    printf("\n");
    printf("Test: param K ha val: %d\n", config->K);

    // Chiusura del file di configurazione
    if(fclose(config_file) == -1) {
        perror("Closing configuration file");
        exit(errno);
    }
}
