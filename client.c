#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>

#define FIFO_FILE       "master.cmd"

int main(int argc, char *argv[])
{
        FILE *fp;

        if ( argc != 2 ) {
                printf("USAGE: fifoclient [string]\n");
                exit(1);
        }
        if((fp = fopen(FIFO_FILE, "a")) == NULL) {
                perror("fopen");
                exit(1);
        }

        fputs(argv[1], fp);

        fclose(fp);
        return(0);
}

