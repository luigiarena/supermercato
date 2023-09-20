#include "direttore.h"

int  fd_skt, fd_c; char buf[N];
struct sockaddr_un sa;

int signal_HUP = 0;
int signal_QUIT = 0;

void connessione_server() {
    strncpy(sa.sun_path, SOCKNAME, PATH_SIZE);
    sa.sun_family=AF_UNIX;
    IFERROR((fd_skt=socket(AF_UNIX, SOCK_STREAM, 0)),-1, "errore socket")
    IFERROR((bind(fd_skt,(struct sockaddr *)&sa, sizeof(sa))),-1, "errore bind")
    IFERROR((listen(fd_skt, SOMAXCONN)),-1, "errore listen")
    IFERROR((fd_c=accept(fd_skt, NULL, 0)),-1, "errore accept")
}

void avvio_supermercato() {
    read(fd_c, buf, N);
    printf("Direttore(server) got: %s\n", buf);
    write(fd_c, "Ciao Client!", 13);
    read(fd_c, buf, N);
    printf("Direttore(server) got: %s\n", buf);
    printf("Ottimo, iniziamo: SUPERMERCATO APERTO.\n\n");
}

void chiudi_server() {
    close(fd_skt);
    close(fd_c);
    unlink(SOCKNAME);
}

void sighup_c()
 
{
    signal(SIGHUP, sighup_c); /* reset signal */
    signal_HUP = 1;
    printf("Il direttore ha catturato un segnale SIGHUP\n");
}
 
// sigquit() function definition
void sigquit_c()
 
{
    signal(SIGQUIT, sigquit_c); /* reset signal */
    signal_QUIT =1;
    printf("  Il direttore ha catturato un segnale SIGQUIT\n");
}
 
// sigint() function definition
void sigint_c()
{
    printf("My DADDY has Killed me!!!\n");
    exit(0);
}

void direttore_main(param *config) {
    
    while(!signal_QUIT) {
        printf("Sono nel ciclo main del direttore\n");
        sleep(1);
    }
    
    printf("Test 1 di config->k: %d\n", config->K);

}