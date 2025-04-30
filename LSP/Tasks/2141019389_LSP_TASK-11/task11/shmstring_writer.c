#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
int main() {
    key_t key = ftok("key.txt", 65);  // Create unique key
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);  // Create shared memory
    char *str = (char *)shmat(shmid, NULL, 0);  // Attach shared memory
    printf("Enter a message to store in shared memory: ");
    fgets(str, 1024, stdin);  // Write string to shared memory
    printf("Message written to shared memory.\n");
    shmdt(str);  // Detach
    return 0;
}

