#include <stdlib.h>
#include <stdio.h>
#include <string.h> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
//word delimited. includes spaces and newlines. 
#define WDELIM " \n"
#define MAX_WORD_SIZE 100
//rather large buffer because 1024 isnt enough. 
/*
    Subroutine that does error checking using perror. 
    if something fails it will return -1 and exit. 
*/
void sys_err(char *msg){
  perror(msg);
  exit(-1);
}

/*
    Subroutine that is going to count the words based off spaces and new lines as a delimiter
    Paramaters: passed in is a file pointer from the argv array. 
*/
int wordcount(char *argv){
    //word count to be incremented as words are read. 
    int wcount;
    char *word, *last, *file_buffer;
    FILE *file_open = fopen(argv, "r");
    fseek(file_open, 0L, SEEK_END);
    long file_size = ftell(file_open);
    fseek(file_open, 0L, SEEK_SET);

    //read the file 
    file_buffer = (char *) calloc(file_size+1 ,sizeof(char));
    fread(file_buffer,sizeof(char), file_size, file_open);
    //resets the buffer. 
    file_buffer[file_size] = 0;
    //since strtok reads once, the count needs to be incremented one time. 
    strtok_r(file_buffer, WDELIM, &last);
    wcount++;//initial count for the files. 
    //while loop to count the words as there are words found. 
    while((word = strtok_r(NULL, WDELIM, &last)) != NULL){
        wcount++;
    }
    //close the file and return the word count
    fclose(file_open);
    free(file_buffer);
    return wcount;
}



/*
    Main Function is to run the wordcount subtrotuine..get it main function ....... kill -9 self
*/
int main(int argc, char *argv[]){
    /*
        int:
            i is for the for loop count
            wc is for the word count
            fc is file count which is argc -1, since c counts the program name in the argc
    */
    int i, wc, fc = argc-1;
    if(argc < 2){
        sys_err("You need to enter at least one file");
    }
    // children being created, and running the subroutine word count
    // to get the count of words from the file. 
    for(i = 1;i <= fc;i++){
        if(fork() == 0){
            wc = wordcount(argv[i]);
            fprintf(stderr,"Child process %d for File %s: number of words is %d\n", getpid(), argv[i], wc);
            exit(0);
        }
    }
    //waits for children of each proc. 
    for(i=1;i <= fc;i++){
        wait(0);
    }
    fprintf(stderr,"All %d files have been counted\n", fc);
    return(0);
}