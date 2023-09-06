/*
    File: supermercato.c
    Specifica: file principale del progetto, implementa tutte le procedure di avvio e chiusura
    Autore: Arena Luigi
*/

#include "supermercato.h"
#include "direttore.h"

//param* config = malloc(sizeof(param));

//  Funzione main del progetto
int main(int argc, char* argv[]) {
    int opt, cflag = 0, vflag = 0;
    FILE *config_file;
    char* config_name;
    int pid_d;

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
    IFERROR((config_file = fopen(config_name, "r")),NULL,"Opening configuration file")

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

    // TEST
    printf("\n");
    printf("Test: param K ha val: %d\n", config->K);

    // Chiusura del file di configurazione
    IFERROR(fclose(config_file),-1,"Closing configuration file")

    // Faccio una fork del supermercato per creare il processo direttore
    pid_d = fork();
    switch (pid_d) {
        case 0: {
            // Direttore
            printf("Sono il direttore! PID: %d -PPID: %d\n", getpid(),getppid());
            
            // connessione server
            connessione_server();
            avvio_supermercato();
            chiudi_server();

            exit(EXIT_SUCCESS);
        }
        case -1: {
            perror("Creando il fork del direttore");
            exit(errno);
        }
        default: {
            // Supermercato
            printf("Sono il supermercato! PID: %d -PPID: %d\n", getpid(),getppid());
            break;
        }
    }
    
    // connessione client
    int fd_skt; char buf[N];
    struct sockaddr_un sa;

    strncpy(sa.sun_path, SOCKNAME, PATH_SIZE);
    sa.sun_family=AF_UNIX;

    fd_skt=socket(AF_UNIX,SOCK_STREAM,0);
    while(connect(fd_skt,(struct sockaddr*)&sa, sizeof(sa)) == -1) {
        if (errno == ENOENT) sleep(1);
        else exit(EXIT_FAILURE);
    }
    


    //connessione_client();

    // fai cose
    write(fd_skt, "Ciao Server!", 13);
    read(fd_skt,buf,N);
    printf("Supermercato(client) got: %s\n",buf);
printf("Sto preparando tutto...\n");

sleep(5);

printf("Ho quasi finito!\n");
write(fd_skt, "Eccomi sono pronto Server!", 27);

    close(fd_skt);


    exit(EXIT_SUCCESS);
}
