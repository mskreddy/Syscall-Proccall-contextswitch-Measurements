target:
	gcc -o om overheadmeasure.c
	gcc -o sm systemcallmeasure.c
	gcc -o pm proccallmeasure.c
	gcc -w -o tm taskcreatemeasure.c
	gcc -w -o csm contextswitchmeasure.c
