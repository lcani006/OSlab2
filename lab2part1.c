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

//below statement controls synchonizations
#define PTHREAD_SYNC 1

    pthread_mutex_t mutex;
    pthread_barrier_t barrier;
    

    int SharedVar = 0;

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

    pthread_t threadid[threads];

    #ifdef PTHREAD_SYNC
	pthread_barrier_init(&barrier, NULL, threads);
	pthread_mutex_init(&mutex, NULL);
    #endif // PTHREAD_SYNC

    int counter = 0;
    int rc;

	for (counter = 0; counter < threads; counter++)
	{
		rc = pthread_create(&threadid[counter], NULL, SimpleThread, (void*)counter);
		if (rc) {
			printf("ERROR COULD NOT CREATE THREAD %d return code: %d\n", counter, rc);
			return -1;
		}
	}

	
	for (counter = 0; counter < threads; counter++)
	{
		rc = pthread_join(threadid[counter], NULL);
	}


	pthread_exit(NULL);
	return 0;

	
}//end main

void SimpleThread(void *args)
{
	int which = (int)args;
	int num, val;
	for (num = 0; num < 20; num++)
	{
		if (random() > RAND_MAX / 2)
		{
			usleep(10);
		}

#ifdef PTHREAD_SYNC
	pthread_mutex_lock(&mutex);
#endif // PTHREAD_SYNC


		val = SharedVar;
		printf("*** thread %d sees value %d\n", which, val);
		SharedVar = val + 1;

#ifdef PTHREAD_SYNC
	pthread_mutex_unlock(&mutex);
#endif // PTHREAD_SYNC

	}

#ifdef PTHREAD_SYNC
	pthread_barrier_wait(&barrier);
#endif
	val = SharedVar;
	printf("Thread %d sees final value %d\n", which, val);
	

}//end SimpleThread