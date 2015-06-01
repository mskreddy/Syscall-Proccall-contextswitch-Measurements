/*******************************************************************/
/*******************************************************************/
/*Filename 	:  systemcallmeasure.c                             */
/*Description	:  This program determines the cost taken          */
/*                 by the system call to execute.For accurarcy     */
/*                 it has been repeated for 10000 times and        */
/*                 taken an average of it.                         */
/*Note		:  We have excluded the overhead of rdtsc()        */      
/*                 from the total cost for each iteration.         */          
/*Method Used  	:  rdtsc()-Read time stamp counter                 */
/*                 to calculate the cost                           */
/*Build         : gcc -o sm systemcallmeasure.c                    */
/*Execution     : ./sm                                             */ 
/*Input         :  None  		                           */
/*Output	:  Returns number of clock cycles                  */
/*Refernces	: https://www.ccsl.carleton.ca/~jamuir/rdtscpm1.pdf*/
/*                http://www.mcs.anl.gov/~kazutomo/rdtsc.h         */ 
/*******************************************************************/
/*******************************************************************/
#include <stdio.h>
#include "rdtsc.h"
#define overhead 28.50

main()
{
/****Initialization of variables for storing start and end cycles****/
unsigned long long start_cycle=0,end_cycle=0; 
double total_cost=0, avg_cost=0;
int i;
/*****Executed the process for 10000 iterations to get the****/
/*****accurate cost of the system call execution*****/

for(i=0;i<10000;i++)  
{	  
start_cycle = rdtsc();		//start the cycle count
getpid();			//Invoke and execute the system call
end_cycle  = rdtsc();		//end the cycle count	 
total_cost=total_cost+end_cycle-start_cycle-overhead;     //calculating the elapsed time using start and end cycles
}
//calculate the average cost using total cost over number of iterations
avg_cost = total_cost/10000; 
printf("Average cost in CPU cycles for getpid :  %f\n", avg_cost);

//code to test for other system call-setuid
//reintialize the varibles total cost and average cost to zero
total_cost=0,avg_cost=0;
/*****Executed the process for 10000 iterations to get the****/
/*****accurate cost of the system call execution*****/

for(i=0;i<10000;i++)
{
start_cycle = rdtsc();    	//start the cycle count 
setuid();			//invoke and execute the system call
end_cycle = rdtsc();		//end the cycle count
total_cost=total_cost+end_cycle-start_cycle-overhead;       //calculating the elapsed time
}
//calculate the average cost using total cost over number of iterations

avg_cost = total_cost/10000;  
printf("Average cost in CPU cycles for setuid :  %f\n", avg_cost);
return 0;
}
