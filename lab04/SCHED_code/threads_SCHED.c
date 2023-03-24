/* ------------------------------------------------------------
                    ____     ________
                   /  _/__  / __/ __/    
                  _/ // _ \/ _/_\ \        
                 /___/_//_/___/___/            

    Institute of Embedded Systems
    Zurich University of Applied Sciences
    8401 Winterthur, Switzerland


    Project:  BSY Labs
    File:     $RCSfile$

    Purpose:  skeleton code for the threads part of BSY-SCHED lab
              
    Remarks:  main routine 

    Author:   donn

    Date:     KW9 2021
    Version:  0.91 FS22

    $Id$

   ------------------------------------------------------------ */ 
#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include <pthread.h>
#include <unistd.h>
#include <sched.h>
#include <errno.h>

#include <sys/sysinfo.h>
#include <sys/syscall.h> 
#include <sys/types.h>
#include <sys/wait.h>

#include "workerUtils.h"
#include "setCPU.h"

#define ITERATIONS 20
#define WORK_HARD  2000000

// function prototypes
static int set_affinity( int, cpu_set_t *old_cpu_set );
//int get_affinity( int, cpu_set_t *old_cpu_set );
void print_affinity( const int );
void iterations( int * );

// unsure how portable this is but there you have it
char *schedulers_s[]  = {"SCHED_OTHER", "SCHED_FIFO", "SCHED_RR", "SCHED_BATCH", "SCHED_DEADLINE", "SCHED_IDLE"};

//***************************************************************************
// Function: main(), parameter: none
//***************************************************************************

int main(void) {

    int     id[5] = {1,2,3,4,5};
	pthread_t thread1, thread2, thread3, thread4, thread5;
	int policy, ret, pthr;

	// get the current scheduler
	policy = sched_getscheduler( 0 );

    // set the taskpriority and set the scheduler to Round Robin
    struct sched_param sp = { .sched_priority = 50 };
    ret = sched_setscheduler( 0, SCHED_RR, &sp );

    // check if the scheduler could be change - if not then apparently a VM problem, why??
    if ( -1 == ret ) {
        (void) printf( "set scheduler failed %d", errno );
    }
     
    (void) fprintf( stdout, "%d PID: %d CPU Conf: %d CPU avail: %d CPU: %d Policy: from %s -> %s \n",
            __LINE__ , getpid(), get_nprocs_conf(), get_nprocs(), sched_getcpu(), schedulers_s[policy], schedulers_s[sched_getscheduler(0)] );
                

    pthr = pthread_create( &thread1, NULL, (void *)iterations, (void *)&id[0] ); 
    if ( 0 != pthr ) { 
        perror( "Thread 1 creation failed\n" ); 
    } 

    pthr = pthread_create( &thread2, NULL, (void *)iterations, (void *)&id[1] );
    if ( 0 != pthr ) { 
        perror( "Thread 2 creation failed\n" ); 
    } 
       
    pthr = pthread_create( &thread3, NULL, (void *)iterations, (void *)&id[2] );
    if ( 0 != pthr ) { 
        perror( "Thread 3 creation failed\n" ); 
    } 

    pthr = pthread_create( &thread4, NULL, (void *)iterations, (void *)&id[3] );
    if ( 0 != pthr ) { 
        perror( "Thread  4 creation failed\n" ); 
    } 
    
    pthr = pthread_create( &thread5, NULL, (void *)iterations, (void *)&id[4] );
    if ( 0 != pthr ) { 
        perror( "Thread  5 creation failed\n" ); 
    } 
    
    pthread_join( thread1, NULL );
    pthread_join( thread2, NULL );
    pthread_join( thread3, NULL );
    pthread_join( thread4, NULL );
    pthread_join( thread5, NULL );

    return EXIT_SUCCESS;
}

void iterations(int *id) {
    int policy, pthr, tid;
    struct sched_param param;
    
    // thread five is the experimental one
    if ( 5 == *id ) {
    
        pthr = pthread_getschedparam(pthread_self(), &policy, &param);
        if ( 0 != pthr ) { 
            perror( "Thread 5 getschedpolicy failed" ); 
        }
        
        tid = syscall(SYS_gettid);
        (void)fprintf( stdout, "%d: TID %d CPU: %d Policy: %s Priority: %d\n", \
            __LINE__ , tid, sched_getcpu(), schedulers_s[sched_getscheduler(0)], param.sched_priority);
    }
    
   
    for (int i = 0; i < ITERATIONS; ) {;
        justWork(WORK_HARD);
//        printf("%d Thread\n", i);
        fflush( stdout );                 // force output
    }
    (void) printf("Au revoir ...\n");
}

void print_affinity(const int lineno) {
    cpu_set_t mask;
    long nproc, i;

    if ( sched_getaffinity(0, sizeof(cpu_set_t), &mask) == -1 ) {
        perror("sched_getaffinity");
        assert(false);
    }
    nproc = sysconf( _SC_NPROCESSORS_ONLN );
    (void) printf( "%d Task CPU affinity = ", lineno );
    for ( i = 0; i < nproc; i++ ) {
        (void) printf( "%d ", CPU_ISSET( i, &mask ) );
    }
    (void) printf( "\n" );
}

static int set_affinity(int cpu, cpu_set_t *old_cpu_set)
{
	cpu_set_t new_cpu_set;
	int rc;

	rc = sched_getaffinity(0, sizeof(*old_cpu_set), old_cpu_set);
	if (rc) {
		rc = errno;
		fprintf(stderr, "Can't get current process affinity mask: %d\n", rc);
		return rc;
	}

	CPU_ZERO(&new_cpu_set);
	CPU_SET(cpu, &new_cpu_set);
	rc = sched_setaffinity( 0, sizeof(new_cpu_set), &new_cpu_set );
	if ( rc ) {
		rc = errno;
        (void) fprintf( stderr,"Can't set process affinity to CPU %d: %d\n", cpu, rc );
		return rc;
	}

	return 0;
}

void print_info (char const *funct) {

    (void) fprintf(stdout, "%s PID: %d Sched: %s CPU: %d \n", funct, getpid(), schedulers_s[sched_getscheduler(0)],  sched_getcpu());
    
}


//***************************************************************************

// get a raw socket on layer 3
//sd = socket( AF_INET, SOCK_RAW, IPPROTO_RAW );

// get a raw socket on layer 2
// ETH_P_ALL means the socket accepts all packets
// this equates to a promiscuous setting in the MAC device
//sd = socket( AF_PACKET, SOC_RAW, htons(ETH_P_ALL) )