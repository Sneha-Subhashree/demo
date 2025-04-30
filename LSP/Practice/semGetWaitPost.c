#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<semaphore.h>
#include<fcntl.h>
int main(){
	char *n1="/mysemaphore1";
	sem_t * K;
	int val;
	K=sem_open(n1, O_CREAT | O_RDWR,0644,15);
	printf("%p\n",K); //address
	sem_getvalue(K,&val); //gets value assigned
	printf("%d\n",val);
	sem_post(K); //increments K by 1
	sem_getvalue(K,&val);
	printf("%d\n",val);
	sem_wait(K); //decrement K by 1
	sem_getvalue(K,&val);
	printf("%d\n",val);
	sem_close(K); 
	sem_unlink(n1);
	return 0;
}
	
	
