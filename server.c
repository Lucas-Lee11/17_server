#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char const *argv[]) {


    while(1){
        mkfifo("wkp", 0666);
        int rcheck = open("./wkp", O_RDONLY);

        char pid[256];
        read(rcheck, pid, sizeof(pid));
        close(rcheck);
        remove("./wkp");

        printf("Server recieved pid on wkp\n");
        printf("Server sending ack on pid\n");

        int scheck = open(pid, O_WRONLY);
        char ack[256] = "ack";
        write(scheck, ack, sizeof(ack));


        while (access( "./temp", F_OK ));


        while(1){
            int random = open("/dev/random", O_RDONLY);
            int num [1];
            read(random, num, 4);

            int fd = open("./temp", O_RDONLY);

            if(fd == -1){
                printf("Lost client\n");
                break;
            }

            char buffer[1024], *c = buffer;
            read(fd, buffer, sizeof(buffer));

            printf("Got: %s", buffer);

            close(fd);

            while(*c){
                *c += *num % 10;
                c++;
            }
            *(c-1) = '\0';

            printf("Sending: %s\n", buffer);

            fd = open("./temp2", O_WRONLY);

            write(fd, buffer, sizeof(buffer));
            close(fd);
        }
    }




    return 0;
}
