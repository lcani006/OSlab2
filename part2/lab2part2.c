//lab2part2.c
//Author: Leonardo Canizares
//PID: 5159647
//Imported Libraries
#include <pthread.h>        /*thread testing*/
#include <stdio.h>			/*console print output, fgets*/
#include <stdlib.h>			/*standard defines*/
#include <limits.h>         /*int limits*/
#include <string.h>         /*string functions*/
#include <errno.h>          /*strtol overflow detection*/
//Enum & Variable Definitions---------------------------------------------------
//General
enum bool   { FALSE, TRUE };
enum error  { NO_ERROR, ERROR };
enum args   { MAIN, FIB_INPUT, CORRECT_ARGC };
#define INPUT_MIN 1		/*input minimum*/
#define MAX_FIB 90      /*upper limit for fib*/

void *runner(void *param);
long long fib[MAX_FIB];

//Main--------------------------------------------------------------------------
int main(int argc, char const *argv[]) {

	//verify argument input
	if (argc != CORRECT_ARGC)
    {
        //Value incorrect, print error message to console through stderr
	    fprintf(stderr,"usage: ./part2 [integer value]\n"
	       "Value must be bewteen %d - %d.\n",INPUT_MIN, MAX_FIB );
        return ERROR;
    }
    //initialize and assign threads for testing
    int fibNum = atoi(argv[FIB_INPUT]);
    if (fibNum < 0)
    {
        //Value incorrect, print error message to console through stderr
	    fprintf(stderr,"usage: ./part2 [integer value]\n"
	       "Value must be bewteen %d - %d.\n",INPUT_MIN, MAX_FIB );
        return ERROR;
    }

    pthread_t threadid; /* the thread identifier */
    pthread_attr_t attr; /* set of thread attributes */

    
    pthread_attr_init(&attr);   
    pthread_create(&threadid, &attr, runner, argv[1]);   
    pthread_join(threadid, NULL);

    for (int i = 0; i < fibNum; i++)
    {
      printf("fib #%-2d: %20lld\n", i + 1, fib[i]);
    }
   pthread_exit(0);
	
}//end main

void *runner(void *param)
{
   int i, fibNum = atoi(param);
   fib[0] = 0;
   fib[1] = 1;

   for (i = 2; i < fibNum; i++) {
      fib[i] = fib[i - 1] + fib[i - 2];      
   }

   pthread_exit(0);
}