#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define BUFFER 1024

void sys_err(char *msg){ 
    perror(msg);
    exit(-1);
}

int main(int argc, char *argv[]){
    int fin, i, rbytes, n = 0;
    char buf;

    if(argc > 2){
        sys_err("Not enough args\n");
    }

    if( (fin = open(argv[1], O_RDONLY) < 0)){
        sys_err("Error opening file\n");
    }else{
        printf("File was opened\n");
    }
    while( (buf = fgetc(fin)) != EOF){
        n++;
    }
    printf("%d char counts\n",n);



}

