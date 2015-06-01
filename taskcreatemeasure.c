/*******************************************************************/
/*******************************************************************/
/*Filename 	:  taskcreatemeasure.c                             */
/*Description	:  This program determines the overhead taken      */
/*                 to create a new process and new thread.         */
/*                 it has been repeated for 10000 times.These      */ 
/*                 statistics are used to calculate contex         */
/*                 switch time                                     */
/*Method Used   :  rdtsc()-Read time stamp counter                 */
/*                 to calculate the cost                           */
/*Build		:  gcc -o tm taskcreatemeasure.c   	           */
/*Execution	:  taskset -c 0 ./tm                               */
/*Input         :  None  		                           */
/*Output	:  Returns overhead in CPU cycles for fork()       */
/*                 and clone()                                     */
/*Refernces	: https://www.ccsl.carleton.ca/~jamuir/rdtscpm1.pdf*/
/*                http://www.mcs.anl.gov/~kazutomo/rdtsc.h         */ 
/*******************************************************************/
/*******************************************************************/

#define _GNU_SOURCE
#include <stdio.h>
#include <linux/sched.h>
#include <fcntl.h>
#include "rdtsc.h"
#include<stdlib.h>
#include <sched.h>

//Declaration of method
void test();
int main(int argc, char* argv[])
{  
//Initialize the variables to store the start and end cycle count
unsigned long long start_cycle=0,end_cycle=0;
double total_cost=0,avg_cost=0;  
int i,pid,kpid;
int result,result1;

void **check;
check = (void **) malloc(1024);

//execute the loop for 10000 times for accuracy
  
for(i=0;i<10000;i++)
  
{
start_cycle = rdtsc();		//start the cycle count		  
pid = fork();			//invokation for fork()	

//******set the CPU affinity to run on only one core
cpu_set_t  mask;
CPU_ZERO(&mask);
CPU_SET(0, &mask);
result = sched_setaffinity(pid, sizeof(mask), &mask);
//******end set affinity code

end_cycle = rdtsc();			//end of the cycle count
total_cost=total_cost+end_cycle-start_cycle;    	//calculate the elapsed time
//check if its a child process	  
if(pid==0)  
exit(0);
}

//calculate the average cost
avg_cost=total_cost/10000;  
printf("Time Taken for Fork is : %f \n", avg_cost);
//Calculate the overhead time for creation of new thread using clone()
//reinitialize the variables
total_cost=0;
avg_cost=0;
start_cycle=0;
end_cycle=0;

// calculation of overhead time at thread leve for context switch
for(i=0;i<10000;i++) 
{
start_cycle = rdtsc();				//start the cycle count	 
kpid = clone(&test, check, NULL, NULL);		//create a new thread by invoking clone()
//set CPU affinity to run the process on only one core.
cpu_set_t  mask1;
CPU_ZERO(&mask1);
CPU_SET(0, &mask1);
result1 = sched_setaffinity(kpid, sizeof(mask1), &mask1);
//end of set affinity code  

end_cycle = rdtsc();				//end the cycle count	   
total_cost=total_cost+end_cycle-start_cycle;	//overall cost for clone elapsed time
}
//calculate the average cost for clone invokation
avg_cost=total_cost/10000;
printf("Time taken for clone is : %f\n", avg_cost);
return 0;
}
void test()
{
}