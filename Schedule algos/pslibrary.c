#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define READY  0
#define RUNNING  1
#define WAITING  2
#define DONE  3

static char stateChars[] = {'r','R','w', 0};
/*
    Wait_Time returns an integer value that is wait time of the process. 
    the time waiting is calculated by the amount of time spent in ready. 
    
*/
int wait_time(char *time_waiting){
    int i; 
    int wait = 0;
    for(i = 0; i < strlen(time_waiting); i++){
        if(time_waiting[i] == 'r'){
            wait++;
        }
    }
    return wait; 
}
/*
    avr_wait_time takes in two doubles of wait times.
    it then calculates the average wait time. 

*/
double avr_wait_time(double proc1, double proc2){
    return ((proc1+proc2)/2);
}
/*
    cpu_utilization takes in two procs, and calulcates the cpu utilization times
    based on the amount of time spent Running. 
    use two for loops to count the amount of times R status is hit for each process. 

    
*/
double cpu_utilization(char *s1, char *s2){
    int i,j;//counters for the for loops
    double cpu_uti, var;//cpu_uti is the final double time for the time spent utilizing the cpu
    double count = 0; //counter for the procs. 
    for(i = 0; i < strlen(s1); i++){
        if(s1[i] == 'R'){
            count++;
        }
    }
    for(j = 0; j < strlen(s2); j++){
        if(s2[j] == 'R'){
            count++;
        }
    }
    if(strlen(s1) >= strlen(s2)){
        var = strlen(s1);
    }else{
        var = strlen(s2);
    }
    cpu_uti = count/var;
    return cpu_uti;
}    
/* 1) handle state changes:
         running process completes CPU burst
         running process has quantum expire
         IO complete
   2) do context switch if necessary
         both ready
         one ready and CPU free
   3) append appropriate characters to character arrays
         avoid putting in multiple string terminators */

// assume s1 and s2 point to buffers with enough space to hold the result 
// assume that the int parameters are strictly greater than 0 


void rr(char *s1, char *s2, int quantum, int x1, int y1, int z1, int x2, int y2, int z2) {
	int i;                                   // next string position (time) 
	int state1 = READY;                            // start with both ready 
	int state2 = READY;
	int cpuLeft1 = x1;                       // P1 next CPU burst remaining 
	int cpuLeft2 = x2;                       // P2 next CPU burst remaining 
	int ioLeft1 = y1;        // P1 next IO burst remaining, 0 if no more IO 
	int ioLeft2 = y2;        // P2 next IO burst remaining, 0 if no more IO 
	int qleft;                                         // quantum remaining 

   for (i=0; (state1 != DONE) || (state2 != DONE); i++) {
                                // running process completes its CPU burst 
          /* running process completes its CPU burst */
        if ((state1 == RUNNING) && (cpuLeft1== 0)) {
            if (ioLeft1 == 0) {
                state1 = DONE;
                s1[i] = stateChars[state1];            /* terminate the string */
            }
            else{
                 state1 = WAITING;
            }
        }

        else if ((state2 == RUNNING) && (cpuLeft2 == 0) ) {
            if (ioLeft2 == 0){
                state2 = DONE;
                s2[i] = stateChars[state2];
            }else{
                state2 = WAITING;
            }
        }
        
        /* running process has quantum expire */
            
        if ((state1 == WAITING) && (ioLeft1 == 0)) {
            state1 = READY;
            cpuLeft1 = z1;
        }


        if ((state2 == WAITING) && (ioLeft2 == 0)) {
            state2 = READY;
            cpuLeft2 = z2;
        }

        //switch process if both are ready and there is no more quantum left.

            // handle one ready and CPU available 
            //so tl/dr if the proc on in state1 is ready and state2 is not running, 
            //it has until the quantum to run. once the quantum time is hit, the proc needs to 
            //switch status. In the round robin algo, it is based on the time it
            //take for the quanum to be reached. 
        if((state1 == RUNNING) && (qleft == 0)){
            if(state2 == READY){
                state2 = RUNNING;
                state1 = READY;
                qleft = quantum;
            }
        }

        //switch process if both are ready and ther eis no more quantum left.
        if((state2 == RUNNING) && (qleft == 0)){
            if(state1 == READY){
                state1 = RUNNING;
                state2 = READY;
                qleft = quantum;
            }
        }

        //if both are ready, start the one that hasn't gone yet.
        if ((state1 == READY) && (state2 == READY)) {
            state1 = RUNNING;
            qleft = quantum;
        }

        else if ((state1 == READY) && (state2 != RUNNING)) {
            state1 = RUNNING;
            qleft = quantum;
        }

        else if ((state2 == READY) && (state1 != RUNNING)) {
            state2 = RUNNING;
            qleft = quantum;
        }


        if (state1 != DONE)
            s1[i] = stateChars[state1];
        if (state2 != DONE)
            s2[i] = stateChars[state2];
                                                             
    
        //subtract from the quantum.
        qleft--;

        if (state1 == RUNNING)
            cpuLeft1--;
        if (state1 == WAITING)
            ioLeft1--;
        if (state2 == RUNNING)
            cpuLeft2--;
        if (state2 == WAITING)
            ioLeft2--;

    }
    int p1 = wait_time(s1);
    int p2 = wait_time(s2);
    //get average wait time
    double wait_time = avr_wait_time((double)p1, (double)p2);
    //get cpu utilization rate
    double cpu = cpu_utilization(s1, s2);         
    printf("Round Robin\nProcess 1: %s\nProcess 2: %s\n%d %d %0.1f %f\n", s1, s2, p1, p2, wait_time, cpu);
    // end of main for loop
}
void fcfs(char *s1, char *s2, int x1, int y1, int z1, int x2, int y2, int z2){

    int state1 = READY;  
    int state2 = READY;
    int i;                   /* next string position (time) */
    int cpuLeft1 = x1;       /* P1 next CPU burst remaining */
    int cpuLeft2 = x2;       /* P2 next CPU burst remaining */
    int ioLeft1 = y1;        /* P1 next IO burst remaining, 0 if no more IO */
    int ioLeft2 = y2;        /* P2 next IO burst remaining, 0 if no more IO */

    for (i=0; (state1 != DONE) || (state2 != DONE); i++) {
                                /* running process completes its CPU burst */

            if ((state1 == RUNNING) && (cpuLeft1== 0)) {
                if (ioLeft1 == 0) {
                    state1 = DONE;
                    s1[i] = stateChars[state1];  
                }else{
                    state1 = WAITING;
                }
            }else if ((state2 == RUNNING) && (cpuLeft2 == 0) ) {
                if(ioLeft2 == 0){
                    state2 = DONE;
                    s2[i] = stateChars[state2];
                }else{
                    state2 = WAITING;
                }
            }

                            /* handle IO complete */
            if ((state1 == WAITING) && (ioLeft1 == 0)) {
                state1 = READY;
                cpuLeft1 = z1;
            }

            if ((state2 == WAITING) && (ioLeft2 == 0)) {
                state2 = READY;
                cpuLeft2 = z2;
            }
                        /* if both ready, depends on algorithm */
                //first come first serve is just as it sounds. 
                //takes in the first proc runs it till its done move to the next. 
            if ( (state1 == READY) && (state2 == READY)) {
                state1 = RUNNING;;
            }
                        /* handle one ready and CPU available */
            else if ( (state1 == READY) && (state2 != RUNNING)) {
                state1 = RUNNING;
            }
            else if ( (state2 == READY) && (state1 != RUNNING)) {
                state2 = RUNNING;
            }
                /* insert chars in string, but avoid putting in extra string terminators */
            if (state1 != DONE)
                s1[i] = stateChars[state1];
            if (state2 != DONE)
                s2[i] = stateChars[state2];

                                            /* decrement counts */
                        /* OK to decrement even if nothing running */

            if (state1 == RUNNING)
                cpuLeft1--;
            if (state1 == WAITING)
                ioLeft1--;
            if (state2 == RUNNING)
                cpuLeft2--;
            if (state2 == WAITING)
                ioLeft2--;

        }
/*
    tl/dr
    FCFS is great when used with the sjf algo. Which is a whole new thing. 
    However, the algo is kind of crappy if you end up with a lot of long cpu burst. 
    anyways, there isnt a check in this guy, so the only comments will be left from the proto. 
*/


    int p1 = wait_time(s1);
    int p2 = wait_time(s2);
    //get average wait time
    double wait_time = avr_wait_time((double)p1, (double)p2);
    //get cpu utilization rate
    double cpu = cpu_utilization(s1, s2);

    printf("FCFS\nProcess 1: %s\nProcess 2: %s\n%d %d %0.1f %f\n", s1, s2, p1, p2, wait_time, cpu);                                     // end of main for loop 
}

void sjf(char *s1, char *s2 ,int x1, int y1, int z1, int x2, int y2, int z2) {
	int i;                                   // next string position (time) 
	int state1 = READY;                            // start with both ready 
	int state2 = READY;
	int cpuLeft1 = x1;                       // P1 next CPU burst remaining 
	int cpuLeft2 = x2;                       // P2 next CPU burst remaining 
	int ioLeft1 = y1;        // P1 next IO burst remaining, 0 if no more IO 
	int ioLeft2 = y2;        // P2 next IO burst remaining, 0 if no more IO 
	
   for (i=0; (state1 != DONE) || (state2 != DONE); i++) {
//		printf("state1 [ %c ] state2 [ %c ]\n", stateChars[state1], stateChars[state2]);
                                // running process completes its CPU burst 
      if ((state1 == RUNNING) && (cpuLeft1 == 0)) {
         if (ioLeft1 == 0) {
            state1 = DONE;
            s1[i] = stateChars[state1];            // terminate the string 
         }
         else
            state1 = WAITING;
      }  
      else if ((state2 == RUNNING) && (cpuLeft2 == 0) ) {
         if(ioLeft2==0){
             state2 = DONE;
             s2[i] = stateChars[state2];
         }else{
             state2 = WAITING;
         }
      }  
                                                     // handle IO complete 
      if ((state1 == WAITING) && (ioLeft1 == 0)) {
          state1 = READY;
          cpuLeft1 = z1;
      }  
      if ((state2 == WAITING) && (ioLeft2 == 0)) {
          state2 = READY;
          cpuLeft2 = z2;
      }  
                                    // if both ready, depends on algorithm 
        // TL/DR maybe...
        // Shortest job first, will check for the cpu burst to see who is the smallest to knock that proc first. 
        // the cpu utilization with this is dope, since it takes care of the smaller times first, and then goes in on the longer
        // running process first. HOWEVER, this is more than likely not actually used in this program persay, since its a Long Term Scheduler and 
        // not a Short term scheduler. Due to the nature of the algo, it needs to know what is in line next.
      if ( (state1 == READY) && (state2 == READY)) {
	  	if( cpuLeft1 < cpuLeft2) 
			state1 = RUNNING;
		else if ( cpuLeft1 > cpuLeft2)
			state2 = RUNNING;
		else
			state1 = RUNNING;

      }  
                                     // handle one ready and CPU available 
      else if ( (state1 == READY) && (state2 != RUNNING)) {
           state1 = RUNNING;
      }  
      else if ( (state2 == READY) && (state1 != RUNNING)) {
           state2 = RUNNING;
      }  

   // insert chars in string, but avoid putting in extra string terminators 
      if (state1 != DONE)
         s1[i] = stateChars[state1];
      if (state2 != DONE)
         s2[i] = stateChars[state2];
                                                        // decrement counts 
                      // OK to decrement even if nothing running 
      if (state1 == RUNNING)
         cpuLeft1--;
      if (state1 == WAITING)
         ioLeft1--;
      if (state2 == RUNNING)
         cpuLeft2--;
      if (state2 == WAITING)
         ioLeft2--;
   }   
    int p1 = wait_time(s1);
    int p2 = wait_time(s2);
    //get average wait time
    double wait_time = avr_wait_time((double)p1, (double)p2);
    //get cpu utilization rate
    double cpu = cpu_utilization(s1, s2);

    printf("SJF\nProcess 1: %s\nProcess 2: %s\n%d %d %0.1f %f\n", s1, s2, p1, p2, wait_time, cpu); 
   
                                                  // end of main for loop
   
}

//
//    Tl/Dr i still dont know what preemptive really means
 
void psjf(char *s1, char *s2, int x1, int y1, int z1,int x2, int y2, int z2) {
   int i;                                   // next string position (time) 
   int state1 = READY;                            // start with both ready 
   int state2 = READY;
   int cpuLeft1 = x1;                       // P1 next CPU burst remaining 
   int cpuLeft2 = x2;                       // P2 next CPU burst remaining 
   int ioLeft1 = y1;        // P1 next IO burst remaining, 0 if no more IO 
   int ioLeft2 = y2;        // P2 next IO burst remaining, 0 if no more IO 
    

   for (i=0; (state1 != DONE) || (state2 != DONE); i++) {
                                // running process completes its CPU burst 
      if ((state1 == RUNNING) && (cpuLeft1== 0)) {
         if (ioLeft1 == 0) {
            state1 = DONE;
            s1[i] = stateChars[state1];            // terminate the string 
         }
         else
            state1 = WAITING;
      }  
      else if ((state2 == RUNNING) && (cpuLeft2 == 0) ) {
         if(ioLeft2 == 0){
             state2 = DONE;
             s2[i] = stateChars[state2];
         }else{
             state2 = WAITING;
         }
      }                                           // handle IO complete 
      if ((state1 == WAITING) && (ioLeft1 == 0)) {
          state1 = READY;
          cpuLeft1 = z1;
      }  
      if ((state2 == WAITING) && (ioLeft2 == 0)) {
          state2 = READY;
          cpuLeft2 = z2;
      }  
                                    // if both ready, depends on algorithm 
      if ( (state1 == READY) && (state2 == READY)) {
	  	if( cpuLeft1 < cpuLeft2) 
			state1 = RUNNING;
		else if ( cpuLeft1 > cpuLeft2)
			state2 = RUNNING;
		else
			state1 = RUNNING;
      }//end if  
                                     // handle one ready and CPU available 
      else if ( (state1 == READY) && (state2 != RUNNING)) {
         state1 = RUNNING;
         
      }  
      else if ( (state2 == READY) && (state1 != RUNNING)) {
         state2 = RUNNING;
      }  
      else if( (state1 == READY) && (cpuLeft1 < cpuLeft2)){
          state1 = RUNNING;
          state2 = READY;
      }
      else if( (state2 == READY) && (cpuLeft2 < cpuLeft1)){
          state2 = RUNNING;
          state1 = READY;
      }
   // insert chars in string, but avoid putting in extra string terminators 
      if (state1 != DONE)
         s1[i] = stateChars[state1];
      if (state2 != DONE)
         s2[i] = stateChars[state2];
                                                        // decrement counts 
      
      if (state1 == RUNNING)
         cpuLeft1--;
      if (state1 == WAITING)
         ioLeft1--;
      if (state2 == RUNNING)
         cpuLeft2--;
      if (state2 == WAITING)
         ioLeft2--;
   }          
    int p1 = wait_time(s1);
    int p2 = wait_time(s2);
    //get average wait time
    double wait_time = avr_wait_time((double)p1, (double)p2);
    //get cpu utilization rate
    double cpu = cpu_utilization(s1, s2);

    printf("PSJF\nProcess 1: %s\nProcess 2: %s\n%d %d %0.1f %f\n", s1, s2, p1, p2, wait_time, cpu); 
}
                                     // end of main for loop 


