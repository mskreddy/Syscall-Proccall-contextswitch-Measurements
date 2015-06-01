/*******************************************************************/
/*******************************************************************/
/*Filename 	:  proccallmeasure.c                               */
/*Description	:  This program determines the cost taken          */
/*                 by the procedure call to execute.For accurarcy  */
/*                 it has been repeated for 10000 times with various*/
/*                 number of arguments and taken an avg. of it     */
/*Note		:  We have excluded the overhead of rdtsc() from   */      
/*                 from the total cost for each iteration.         */          
/*Method Used   :  rdtsc()-Read time stamp counter  to calculate   */
/*                 to calculate the cost                           */
/*Build		:  gcc -o pm proccallmeasure.c                     */
/*Execution	:  ./pm                                            */
/*Input         :  None  		                           */
/*Output	:  Returns cost taken for procedure call           */
/*Refernces	: https://www.ccsl.carleton.ca/~jamuir/rdtscpm1.pdf*/
/*                http://www.mcs.anl.gov/~kazutomo/rdtsc.h         */ 
/*******************************************************************/
/*******************************************************************/
#include <stdio.h>
#include "rdtsc.h"
#define overhead 28.50

//declarations the methods
void noargs();
void arg1(int a);
void arg2(int a,int b);
void arg3(int a,int b,int c);
void arg4(int a,int b,int c,int d);
void arg5(int a,int b,int c,int d,int e);
main()
{
/*****Initialization of variables to store the cycle count******/
unsigned long long start_cycle=0,end_cycle=0;	
double total_cost=0,avg_cost=0;
int i;

/******Executing the process for 10000 iterations to get an accurate result, with no arguments in the procedure call*******/	
for(i=0;i<10000;i++)
{
start_cycle = rdtsc();	             //start the cycle count	
noargs();		             //invoke the procedure call with no arguments
end_cycle = rdtsc();	             //end cycle count   	
total_cost=total_cost+end_cycle-start_cycle-overhead; //calculate the elapsed time	
}
avg_cost=total_cost/10000;
printf("Average cost for proc call with 0 args %f\n", avg_cost);
	

/******Executing the process for 10000 iterations to get an accurate result, with one argument in the procedure call*******/	
avg_cost=0;
total_cost=0;
	
for(i=0;i<10000;i++)	
{
start_cycle = rdtsc();					//start the cycle count
arg1(1);						//invoke procedure call using one argument
end_cycle = rdtsc();					//end the cycle count
total_cost=total_cost+end_cycle-start_cycle-overhead; 	//calculate the elapsed time
}
	

//calculate the average cost using total cost over 10000 iterations
avg_cost = total_cost/10000;
printf("Average cost for proc call with 1 args %f\n", avg_cost);
	

/******Executing the process for 10000 iterations to get an accurate result, with two arguments in the procedure call*******/	
avg_cost=0;
total_cost=0;
	
for(i=0;i<10000;i++)
{
start_cycle = rdtsc();					//start the cycle count			
arg2(1,2);						//invoke procedure call with two arguments
end_cycle = rdtsc();					//end the cycle count
total_cost=total_cost+end_cycle-start_cycle-overhead;  	//calculate the elapsed time
}
	

//calculate the average cost using total cost over 10000 iterations
avg_cost = total_cost/10000;
printf("Average cost for proc call with 2 args %f\n", avg_cost);
	

/******Executing the process for 10000 iterations to get an accurate result, with three arguments in the procedure call*******/	
avg_cost=0;
total_cost=0;
	
for(i=0;i<10000;i++)
{
start_cycle = rdtsc();				//start the cycle count	
arg3(1,2,3);					//invoke the procedure call with three arguments
end_cycle = rdtsc();				//end the cycle count
total_cost=total_cost+end_cycle-start_cycle-overhead;  	//calculate the elapsed time
}
	
//calculate the average cost using total cost over 10000 iterations
avg_cost = total_cost/10000;
printf("Average cost for proc call with 3 args %f\n", avg_cost);
	

/******Executing the process for 10000 iterations to get an accurate result, with four arguments in the procedure call*******/	
avg_cost=0;
total_cost=0;
	
for(i=0;i<10000;i++)
{
start_cycle = rdtsc();				//start the cycle count	
arg4(1,2,3,4);					//invoke the procedure call using four arguments
end_cycle = rdtsc();				//end the cycle count
total_cost=total_cost+end_cycle-start_cycle-overhead;  //calculate the elapsed time
}
	

//calculate the average cost using total cost over 10000 iterations
avg_cost = total_cost/10000;
printf("Average cost for proc call with 4 args %f\n", avg_cost);
	


/******Executing the process for 10000 iterations to get an accurate result, with five arguments in the procedure call*******/	
avg_cost=0;
total_cost=0;
	
for(i=0;i<10000;i++)
{
start_cycle = rdtsc();				//start the cycle count	
arg5(1,2,3,4,5);				//invoke the procedure call using five arguments
end_cycle = rdtsc();				//end the cycle count
total_cost=total_cost+end_cycle-start_cycle-overhead;  //calculate the elapsed time
}
	

//calculate the average cost using total cost over 10000 iterations
avg_cost = total_cost/10000;
printf("Average cost for proc call with 5 args %f\n", avg_cost);
	
return 0;

}

void noargs()
{
}

void arg1(int a)
{
}

void arg2(int a,int b)
{
}

void arg3(int a,int b,int c)
{
}

void arg4(int a,int b,int c,int d)
{
}

void arg5(int a,int b,int c,int d,int e)
{
}
