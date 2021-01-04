#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>

static void sighandler(int signo){
    if(signo == SIGINT){
        remove("./temp");
        remove("./temp2");
        exit(0);
    }
}


int main(int argc, char const *argv[]) {
    signal(SIGINT, sighandler);

    while (access( "./wkp", F_OK ));

    int i = getpid();
    char pid[256];
    sprintf(pid, "%d", i);
    mkfifo(pid, 0666);

    printf("Client sending pid on wkp\n");

    int scheck = open("./wkp", O_WRONLY);
    write(scheck, pid, sizeof(pid));
    close(scheck);

    int rcheck = open(pid, O_RDONLY);
    char ack[256];
    read(rcheck, ack, sizeof(ack));

    printf("Client received %s\n", ack);
    close(rcheck);
    remove(pid);

    printf("Chooses a random number between -9 and 9, then adds that much to each character in the string by that amount\n");


    while(1){
        char buffer[1024];
        fgets(buffer, sizeof(buffer), stdin);

        char * file = "./temp";
        mkfifo(file, 0666);

        char * file2 = "./temp2";
        mkfifo(file2, 0666);


        int fd = open(file, O_WRONLY);
        write(fd, buffer, sizeof(buffer));

        close(fd);


        int fd2 = open(file2, O_RDONLY);
        char out[1024];
        read(fd2, out, sizeof(out));

        printf("Shuffled Output: %s\n", out);

        close(fd2);

        remove(file);
        remove(file2);

    }

    return 0;
}
