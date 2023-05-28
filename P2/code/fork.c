#include <stdio.h>
#include <unistd.h>

int main(){
    if(fork() == 0){
        printf("Hello from child with id: %d\n", getpid());
    }else{
        printf("Hello from parent with id: %d\n",getpid());
    }
    sleep(30);
    return 0;
}