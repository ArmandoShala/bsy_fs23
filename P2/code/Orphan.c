#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    if(fork() == 0){
        printf("Hello from child with id: %d\n", getpid());;
    }else{
        printf("Hello from parent with id: %d\nParent exiting now!\n",getpid());
        exit(0);
    }
    sleep(30);
    return 0;
}