#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h> 
#include <sys/types.h>
#include <sys/wait.h>
int main() {
    sem_t *S, *T;
    char *n1 = "/name1";
    char *n2 = "/name2";
    sem_unlink(n1);
    sem_unlink(n2);
    pid_t pid;
    S = sem_open(n1, O_CREAT | O_RDWR, 0644, 0);
    T = sem_open(n2, O_CREAT | O_RDWR, 0644, 1);
    pid = fork();
    if (pid == 0) {
        while (1) {
            sem_wait(S); 
            sleep(1);
            fprintf(stderr, "1");
            fprintf(stderr, "1");
            sem_post(T); 
        }
    }
    else {
        while (1) {
            sem_wait(T); 
            sleep(1);
            fprintf(stderr, "0");
            fprintf(stderr, "0");
            sem_post(S);
        }
        wait(NULL); 
    }
    sem_close(S);
    sem_close(T);
    sem_unlink(n1);
    sem_unlink(n2);
    return 0;
}


