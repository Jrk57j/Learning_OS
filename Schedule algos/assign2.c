#include <stdio.h>
#include <stdlib.h>
#include "pslibrary.h"
void sys_er(char *msg){
    perror(msg);
    exit(-1);
}

int main(int argc, char *argv[]){
    char *s1 = malloc(50);
    char *s2 = malloc(50);
    printf("%d argv count\n", argc);
    if(argc!= 8){
        perror("You did not enter the correct paramaters\n");
    }else{
    int quantum = atoi(argv[1]);
    int x1 = atoi(argv[2]);
    int y1 = atoi(argv[3]);
    int z1 = atoi(argv[4]);
    int x2 = atoi(argv[5]);
    int y2 = atoi(argv[6]);
    int z2 = atoi(argv[7]);
    printf("Assignment 2 program was written by Julian Itwaru\nQuantum=%d\n\nProcess 1:\nFirst CPU Burst=%d,IO Burst=%d, Second CPU Burst=%d\n\nProcess 2:\nFirst CPU Burst=%d, IO Burst=%d, Second CPU Burst=%d\n\n",quantum,x1,y1,z1,x2,y2,z2);
    fcfs( s1,  s2, x1,  y1,  z1,  x2,  y2,  z2);
    sjf( s1, s2,  x1,  y1,  z1,  x2,  y2,  z2);
    psjf(s1, s2, x1, y1, z1,x2,  y2,  z2);
    rr( s1,  s2,  quantum,  x1,  y1,  z1,  x2,  y2,  z2);
    }
    free(s1);
    free(s2);
    return 0;
}