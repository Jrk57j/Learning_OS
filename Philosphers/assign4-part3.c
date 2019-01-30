#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h> 

#define EATING 0
#define THINKING 1
#define NUM 500
#define LEFTP (threadIndex + 2) % nthreads
#define RIGHTP (threadIndex - 2) % nthreads
/**
 * Int pointer PHILOSTATE is a global variable for the threads. Simplifies the use of having to 
 * recreate and keep track of local scoped variables
 * 
 * Int nthreads is a gloabl variable for the threads. Simplfies the use of having to recreate
 * and keep track of local scoped variables
**/
int *PHILOSTATE;
int nthreads;

/**
 *  phtread_mutex_t pointer lock. Lock is a global variable for thread locking. You need this to be
 * a global, since the whole program needs to keep track of the states. 
 * 
 * pthread_mutex_t condion will be implemented at a later time, since I couldnt figure out how to get this working. 
 * Also a global variable.
**/
pthread_mutex_t *lock; 
pthread_mutex_t condition;
// void pickUpChopsticks( int threadIndex); 
// void putDownChopsticks( int threadIndex); 
// void thinking(); 
// void eating(); 
// void createPhilosphers( int numOfThreads);
// void *philosophersThread( void *pVoid);
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
    nthreads = atoi( argv[1]);
    PHILOSTATE = (int *)calloc(nthreads, sizeof(int));
    lock = (pthread_mutex_t *)calloc(nthreads, sizeof(pthread_mutex_t));

    pthread_t tid[nthreads]; 
    printf("Julian Itwaru Assignment 4: number of threads = %d\n", nthreads); 
    createPhilosphers( nthreads); 

}
/**
 * for reasons unknown to me, the pthread_join in this case had to have its own for-loop. The 
 * join was not working properly at first use. So I created a new for-loop that would 
 * would handle the joins seperately.  
**/
void createPhilosphers( int numOfThreads){
    pthread_t tid[numOfThreads]; 
    int i, tcreate, threads[numOfThreads];

    for( i = 0; i < numOfThreads; i++){
        pthread_mutex_init(lock, NULL);
    }

    for( i = 0; i  < numOfThreads; i++){
        threads[i] = i;
        tcreate = pthread_create(&tid[i], NULL, philosophersThread,(void *)&threads[i]);
        PHILOSTATE[i] = THINKING;
        if(tcreate != 0){
            fprintf(stderr, "Thread died\n %d\n", tcreate);
        }
    }
    for(i = 0; i < numOfThreads; i++){
         pthread_join(tid[i], NULL);
    }
}
/**
 * Initial state is thinking, so we put all philisophers to thinking state, 
 * then we change the states to pickUpChopSticks, however, do to the modulo math
 * above in the initial declration with rightp and leftp no two philosphers can be
 * selected at the same time. Also no two philosphers should be put adjacent to each 
 * other. This works with thinking that two philisphers are sitting next to each other, 
 * and that they can reach over each other to grap the chopsticks in front of the other person. 
 * 
 * 
 * the order of which the philosphers are picked at still at random. Output order is the same. 
 * i.e 0 2 3 1 4 thinking and eating will be 0 2 3 1 4. 
**/
void *philosophersThread( void *pVoid){
    //printf("This is philosopher %d\n", *threadNum);
    int threadNum;
    threadNum = *((int *) pVoid);
    
    thinking();
    printf("philosopher %d is thinking\n", threadNum);
    pickUpChopsticks(threadNum);
    printf("Philosopher %d stopped thinking\n", threadNum);
    //sleep here is added to allow the philosphers to have time to do things for 
    //odering purposes. 
    sleep(1);
    eating();
    printf("Philosopher %d started eating\n", threadNum);
    putDownChopsticks(threadNum);
    printf("Philosoper %d stopped eating\n", threadNum);
}

void thinking(){
    usleep((rand() % 500) + 1);
}

void eating(){
    usleep((rand() % 500) + 1);
}
/**
 * rightp can be negative so we must change the value of it, by adding the thread index, 
 * back into it. This will keep it from having a nagative.
 * 
 * Simple statemachine check and locking with pthread_mutex_lock
 * then updating the PHILOSTATE[threadindex] to eating. 
**/
void pickUpChopsticks(int threadIndex){
    int rightP;
    //int k;
//     if(RIGHTP < 0){
//         rightP = RIGHTP + threadIndex;
//     }else{
//         rightP = RIGHTP + threadIndex;
//     }
//     if(rightP != EATING && LEFTP != EATING){
//       //  while(k != threadIndex){
//        //     pthread_cond_wait(&condition, lock);
        
//         pthread_mutex_lock(&lock[rightP]);
//         pthread_mutex_lock(&lock[LEFTP]);
        
//     }
//    // k++;
    //PHILOSTATE[threadIndex] = EATING;
    int k; 
    k = pthread_mutex_lock(&threadIndex);

}
/**
 * Same deal as above, just for putting the chopsticks down. 
**/
void putDownChopsticks(int threadIndex){
    // int rightP;
    //  if(RIGHTP < 0){
    //     rightP = RIGHTP + threadIndex;
    //  }else{
    //     rightP = RIGHTP + threadIndex;
    // }
    // if(rightP != THINKING && LEFTP != THINKING){
    //     pthread_mutex_unlock(&lock[rightP]);
    //     pthread_mutex_unlock(&lock[LEFTP]);
    //    // pthread_cond_broadcast(&condition);
    // }

    //PHILOSTATE[threadIndex] = THINKING;
    int k; 
    k = pthread_mutex_unlock(&threadIndex);
}