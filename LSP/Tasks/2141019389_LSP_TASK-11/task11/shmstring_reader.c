#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

int main() {
    key_t key = ftok("key.txt", 65);  // Same key as writer
    int shmid = shmget(key, 1024, 0666);  // Access shared memory

    char *str = (char *)shmat(shmid, NULL, 0);  // Attach

    printf("Message read from shared memory: %s", str);  // Display message

    shmdt(str);  // Detach
    shmctl(shmid, IPC_RMID, NULL);  // Remove shared memory
    return 0;
}

