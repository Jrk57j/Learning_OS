#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h> 
#include <semaphore.h> 
/**
 * You dont really need these states in this part of the assignment
 * but they are for the state machine later in the assignment. 
**/
#define EATING 0
#define HUNGRY 1
#define THINKING 2
#define LEFTP (phino + 2)% N
#define RIGHTP (phino -2 )% N
#define PHILOSTATE {0,1,2}

/**
 * As of this part of the assignment the states of the philospher do not matter, since 
 * this part of the assignment is to just verify that threads are created. However, due 
 * to how i decided to create a skeleton for the subsequent portions of the assignment
 * the states and their functions are going to be in each portion of the assignment. 
**/

/**
 * pickUpChopSticks will determine if the state of the philospher is about to eat or not
 * in order for this state to be a thing, the philospher would have to have started and stopped
 * thinking. this state will lead to eating. 
**/

void pickUpChopsticks( int threadIndex); 
/**
 * putDownChopSticks will determine if the state of the philospher is about to start thinking
 * in order for this state to be a thing, the philosper would have to have started eating and
 * finished eating. 
**/ 

void putDownChopsticks( int threadIndex); 

/**
 * thinking is a state that sets a sleep timer to give the philospher a set amount of time to think
 * before moving to the next states
**/
void thinking(); 

/**
 * eating is a state that sets up a sleep timer to gggive the philospher a set amount of time 
 * to eat before moving to the next states
**/
void eating(); 

/**
 * creation of the philospher thread, this will have more indepth comments later. 
 * as of now its just a function that is here. 
**/
void createPhilosphers( int numOfThreads);

/**
 * creation philosphers to be used in the createPhilosphers. This will have more indepth comments
 * later, as of now its just a function that is here. 
**/
void *philosophersThread( void *pVoid);

/**
 * Main program that executes all the things
**/

int main ( int argc, char *argv[]){
    
    if ( argc < 2){
        perror("Needs at least one argument for nthreads\n");
        exit(-1);
    }
    int nthreads = atoi( argv[1]); 
    pthread_t tid[nthreads]; 
    printf("Julian Itwaru Assignment 4: number of threads = %d\n", nthreads); 
    createPhilosphers( nthreads); 

}
/**
 * Simple creation of the philosphers. The numOfThreads is passed in from the user
 * via stdin. The function will then loop through the nThreads entered and create
 * the threads as needed. Join is left inside of the for loop to not create
 * a new for loop just to join. 
**/
void createPhilosphers( int numOfThreads){
     pthread_t tid[numOfThreads]; 
     int i, tcreate;
    //This is where we create the philiso's thread so that they can either wait, eat, ponder, or starve because
    //they should have brought more than 5 chopsticks 
    //philosophersThread( numOfThreads);
    for( i = 0; i  < numOfThreads; i++){
        tcreate = pthread_create(&tid[i], NULL, philosophersThread,(void *)&i);
        if(tcreate != 0){
            fprintf(stderr, "Thread died\n %d\n", tcreate);
        }
        pthread_join(tid[i], NULL);
    }
}
/**
 * Simple thread call that will print out the pthread count. 
**/
void *philosophersThread( void *pVoid){
    printf("This is philosopher: %d\n", *( (int*) pVoid));
}