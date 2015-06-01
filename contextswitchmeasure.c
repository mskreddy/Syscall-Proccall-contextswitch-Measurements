/*******************************************************************/
/*******************************************************************/
/*Filename 	:  contextswitchmeasure.c                          */
/*Description	:  This program determines the cost taken          */
/*                 by the context switch to execute.For accurarcy  */
/*                 it has been repeated for 10000 times and also   */
/*                 tested at both process and thread levels        */
/*                 and then taken an avg. of it                    */
/*Note		:  We have excluded the overhead of fork(),clone() */      
/*                 from the total cost for each iteration.         */          
/*Method Used   :  rdtsc()-Read time stamp counter to calculate    */
/*                 to calculate the cycle count                    */
/*Build		:  gcc -o csm contextswitchmeasure.c               */
/*Execution	:  taskset -c 0 ./csm                              */
/*Refernces	: https://www.ccsl.carleton.ca/~jamuir/rdtscpm1.pdf*/
/*                http://www.mcs.anl.gov/~kazutomo/rdtsc.h         */ 
/*Input         :  None  		                           */
/*Output	:  Returns cost taken for context switch           */
/*******************************************************************/
/*******************************************************************/

#define _GNU_SOURCE
#include <stdio.h>
#include <linux/sched.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>
#include "rdtsc.h"
#include <stdlib.h>
#include <stddef.h>
#include <sched.h>
#define f_overhead 28913.66		//overhead of fork() invokation task	
#define c_overhead 4071.32		//overhead of clone invokation task

//declaration of test method
void test();

//initializtion of variables, pipes
int pi[2];
pipe(pi);
char kt[1];

int main(int argc, char* argv[])
{
//Initialization of variables to store start and end CPU cycles.
unsigned long long start_cycle=0,end_cycle=0;
double total_cost=0,avg_cost=0;
int i,pid,w,s;
int p[2];
pipe(p);
char t[1];
t[0] ='a';
int result,result1;

//for accuracy execute the loop for 10000 times
for(i=0;i<10000;i++)  
{
start_cycle = rdtsc();		//start the cycle count
pid = fork();			//invoke the fork() to create a child process

/*******set the CPU affinity , so that this process runs only on one core*****/
cpu_set_t  mask;
CPU_ZERO(&mask);
CPU_SET(0, &mask);		
result = sched_setaffinity(pid, sizeof(mask), &mask);	  
/********end of set affinity code*******/

/****check if its child or parent process and write into pipe****/
if(pid==0) 
{	  
write(p[1],(void*)t,1);
exit(0);  
}  
else			//if its a parent process then read the pipe	  
read(p[0],(void*)t,1);	  
end_cycle = rdtsc(); 	 //end cycle count
w = waitpid(pid,&s,0);	//invoke waitpid() to wait until the process is completed  

//calculate the elapsed time, note that we have used divided by 2 for the elapsed time , as this process involves 2 context switches, also overhead involved in fork() invokation is removed.

total_cost=total_cost+((end_cycle-start_cycle)/2 -f_overhead);
  
}

  
//calculate the average cost and print the output
avg_cost=total_cost/10000;
printf("Context Switch in Cycles for Process Level is =  %f\n", avg_cost);
  
  

//reintializaion of variables for calculation of context switch cost at thread level
total_cost=0;
avg_cost=0;
  
start_cycle=0;
end_cycle=0;
int kpid,kw,ks;
kt[0]='a';

void **check;
check = (void **) malloc(1024);
//execute the process for 10000 iterations for accuracy
for(i=0;i<10000;i++)
{
start_cycle = rdtsc();				//start the cycle count	  
kpid = clone(&test, check, NULL, NULL);	 	//invoke clone() to create a new thread

//****set the CPU affinity to run the process only on one core
cpu_set_t  mask1;
CPU_ZERO(&mask1);
CPU_SET(0, &mask1);
result1 = sched_setaffinity(kpid, sizeof(mask1), &mask1);	  
//****end of set affinity code
end_cycle = rdtsc();			//end cycle count
kw = waitpid(kpid,&s,__WCLONE);		//invoke waitpid() to complete the process

//calculate the elapsed time, note that we have used divided by 2 for the elapsed time , as this process involves 2 context switches, also overhead involved in fork() invokation is removed.
total_cost+=((end_cycle-start_cycle)/2 - c_overhead);
  
}
//calculate the average cost and print
avg_cost=total_cost/10000;	//calculate the average cost
printf("Context Switch in Cycles for Thread Level is =  %f\n", avg_cost);
return 0;
}
void test()
{
write(pi[1],(void*)kt,1);
}