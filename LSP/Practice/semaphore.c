#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<semaphore.h>
int main(){
	sem_t sem;
 	int rs ,val;
 	rs=sem_init(&sem,2,6);
 	if(rs==0){
 		printf( "Semaphore created sucessfully\n");
 	}
 	else{
 		perror("failed to create semaphore");
 		return 1;
 	}
 	sem_getvalue(&sem,&val);
 	printf("Semaphore value=%d\n", val);
 
 	sem_wait(&sem);
 	sem_getvalue(&sem ,&val);
 	printf("Updated Semaphore value after one call to sem wait()= %d\n",val);
 	sem_post(&sem);
 	sem_getvalue(&sem,&val);
  	printf("Updated Semaphore value after one call to sem wait()= %d\n",val);
 	return 0;
 }
