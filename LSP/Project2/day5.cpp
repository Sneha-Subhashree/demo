#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(){

int fd[2];
pid_t pid;
char write_msg[]= "hello from parent process!";
char read_msg[100];

pipe (fd);

//create a child process using fork 

pid= fork ();

if (pid ==0){
//Child process;
close (fd[1]); //close the write end of the 
//read the message from pipe 
read (fd[0],read_msg, sizeof(read_msg));

printf("Child process received message: %s\n", read_msg);
close(fd[0]);
}
else{
//Parent process 
close (fd[0]);//close the read end of the pipe (parent only writes)

//Write a message to the pipe 

write (fd[1], write_msg, strlen(write_msg)+1);// +1 to include null terminator 

printf("Parent process send message : %s\n", write_msg);
close(fd [1]); // close the write end of the pipe 
//wait for the child process to finish 

}
return 0;
}

