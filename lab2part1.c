//lab2part1.c
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
enum args   { MAIN, THREADNUM, CORRECT_ARGC };
#define INPUT_MIN 1		/*input minimum*/
//Main--------------------------------------------------------------------------
int main(int argc, char const *argv[]) {

	//verify argument input
	if (argc != CORRECT_ARGC)
    {
        //Value incorrect, print error message to console through stderr
	    fprintf(stderr,"usage: ./part1 [# of threads]\n"
	       "Value must be bewteen %d - %d.\n",INPUT_MIN, INT_MAX );
        return ERROR;
    }
    //initialize and assign threads for testing
    int threads = atoi(argv[THREADNUM]);
    if (threads < 0)
    {
        //Value incorrect, print error message to console through stderr
	    fprintf(stderr,"usage: ./part1 [# of threads]\n"
	       "Value must be bewteen %d - %d.\n",INPUT_MIN, INT_MAX );
        return ERROR;
    }

    int SharedVar = 0;
    pthread_mutex_t mutex;
    pthread_barrier_t barrier;


    

	
}//end main