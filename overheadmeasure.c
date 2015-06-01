/*******************************************************************/
/*******************************************************************/
/*Filename 	:  overheadmeasure.c                               */
/*Description	:  This program determines the cost of the         */
/*                 overhead cycles taken by rdtsc().               */
/*Method Used   :  rdtsc()-Read time stamp counter    	           */
/*Input         :  None  		                           */
/*Output	:  Returns overhead in number of clock cycles      */
/*Refernces	: https://www.ccsl.carleton.ca/~jamuir/rdtscpm1.pdf*/
/*                http://www.mcs.anl.gov/~kazutomo/rdtsc.h         */ 
/*******************************************************************/
/*******************************************************************/
#include <stdio.h>
#include "rdtsc.h"
main()
{
/******Initialization of variables to store the start and end CPU cycles******/
unsigned long long start_cycle=0,end_cycle=0;
double total_cost=0, average_cost=0;
int i;
/*****Executed the process for 10000 iterations to get the****/
/*****accurate overhead using rdtsc() instruction with no*****/
/*****other operations                                                   *****/

for(i=0;i<10000;i++)
{
start_cycle = rdtsc();			//execute the rdtsc() for start cycle       		
end_cycle  = rdtsc();			//execute the rdtsc() for end cycle	
total_cost=total_cost+(end_cycle-start_cycle);  	// Calculate the elapsed time using start and end cycle.
}
//Calculate the average cost for 10000 iterations
average_cost=total_cost/10000;
printf("Average overhead in cycles:  %f\n", average_cost);
return 0;
}
