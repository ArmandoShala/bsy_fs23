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

    Purpose:  multi-process code for BSY-SCHED lab
              
    Remarks:  main routine 

    Author:   donn

    Date:     KW9 2021
    Version:  0.91 FS222

    $Id$

   ------------------------------------------------------------ */ 
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#include "workerUtils.h"
#include "setCPU.h"

#define ITERATIONS 20
#define WORK_HARD  2000000

//***************************************************************************
// Function: main(), parameter: none
//***************************************************************************

int main(void) {

    pid_t   pid;
    int     i;

    pid = fork();

    // check man pages
    selectCPU( 1 );

    switch ( pid ) {
      case -1:
        perror( "Could not fork" );
        break;
      case 0:
        for ( i = 0; i < ITERATIONS; ) {
            justWork( WORK_HARD );
            (void) printf( "%d \t\tChild\n", i );
            fflush( stdout );                 // force output
        }
        break;
      default:
        for ( i = 0; i < ITERATIONS; ) {;
            justWork( WORK_HARD );
            (void) printf( "%d \tMother\n", i );
            fflush( stdout );                 // force output
        }
    }
    printf( "Au revoir ...\n" );

    if ( pid > 0 )                            // wait for child to terminate
        waitpid( pid, NULL, 0 );
    
    return EXIT_SUCCESS;
}
//*************************************************************************** 