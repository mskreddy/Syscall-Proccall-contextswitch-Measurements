										ReadMe.txt
									=============================	
Project Name 
=======================
Operating System Project1 - Cost Measurements of System Call, Procedure Call and Context Switch

Team Members
=======================
Sai Kiran Reddy Malikireddy
Kiranmayi Karri

Overview
=======================
In this project, we implemented functionality for measuring the costs taken by system call, procedure call and context switch. This functionality has been tested on 4 systems with different architectures.
For any further details , please refer to "OS_Project1.pdf"

Note: rdtsc.h file should be included in the folder from which the below codes are going to be executed. rdtsc.h is available in zip file.
 
To compile the codes 
=======================
use makefile (we have used gcc compiler)
'make' command

To execute the codes 
=======================
overheadmeasure.c - to calculate the overhead of rdtsc()
-------------------------------------------------------------------
./om

Note: After the execution of this code systemcallmeasure.c should be updated with the latest overhead value (for eg.#define overhead 28.50)
systemcallmeasure.c - to calculate the cost involed in the execution of system call
------------------------------------------------------------------------------------------------
./sm

proccallmeasure.c - to calculate the cost involed in the execution of procedure call      	
-------------------------------------------------------------------------------------------------
./pm

taskcreatemeasure.c - to calculate the cost involed in the creation of process and thread (fork and clone) Note : here taskset is used to run the program on one processor.     	
---------------------------------------------------------------------------------------------------------------------------
taskset -c 0 ./tm

Note: After the execution of this code contextswitchmeasure.c should be updated with the latest overhead value (for eg.#define f_overhead 28913.66,
#define c_overhead 4071.32)

contextswitchmeasure.c - to calculate the cost involed in the context switch at process and thread levels  Note : here taskset is used to run the program on one processor.     	
--------------------------------------------------------------------------------------------------------------------------
taskset -c 0 ./csm

