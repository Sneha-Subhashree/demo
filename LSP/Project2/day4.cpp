#include<iostream>
#include<unistd.h>
#include<sys/wait.h>
#include<vector>
using namespace std;
int main(int argc, char* argv[]){
	if(argc<3){
    	cerr  << "Usage: " << argv[0] << "<keyword> <file1> <file2> ...\n";
    	return 1;
  	}
  	const char* keyword=argv[1];
  	int num_files=argc-2;
  	cout<< "Searching for keyword: " << keyword << "\n";
  	cout << "Files to search : \n";
  	vector<int> child_pipes; //pipes to read child o/p
  	vector<pid_t> child_pids; //child pid for tracking later
  	for(int i=0; i <num_files; ++i){
    	const char* filename=argv[i+2];
    	int pipefd[2];
    	pid_t pid=fork();
    	pipe(pipefd);
    	if(pid==0){
      	close(pipefd[0]);
      	dup2(pipefd[1], STDOUT_FILENO);
      	close (pipefd[1]);
      	execlp("grep", "grep", keyword, filename, (char*)nullptr);
    	}
    	else{
      		wait(NULL);
      		close(pipefd[1]);
      		child_pipes.push_back(pipefd[0]);
      		child_pids.push_back(pid); //save child pid
    	}
  	}
  	char buffer[1024];
  	for(int i=0; i<num_files; ++i){
    	const char* filename=argv[i+2];
    	cout << "results from " << filename << "\n";
    	ssize_t bytes_read;
    	while((bytes_read=read(child_pipes[i], buffer, sizeof(buffer)-1)>0)){
      		buffer[bytes_read]='\0';
      		for(int i=0; i<num_files; ++i){
        		const char* filename=argv[i+2];
        		cout << "results from" << filename << buffer <<"\n";
      		}
    	}
    	close(child_pipes[i]);
  	}
 	for(pid_t pid : child_pids){
    	int status;
    	if(waitpid(pid, &status,0)==1){
    		perror("waitpid failed");
  		}
  		else
  		{
    		if(WIFEXITED(status)){
      			int exit_status = WEXITSTATUS(status);
      			if(exit_status != 0){
        			cerr << "Child process " << pid << "exited with error code " << exit_status << "\n";      
      			}
      			else if(WIFSIGNALED(status)){
        			cerr << "Child process " << pid << "was terminated by signal " << WTERMSIG(status) << "\n"; 
      			}
			}
		}
  	}
  	return 0;
}
//corrected code
//WIFEXITED(status) - Did the child finish normally ?
//WEXTSTATUS(status)- Get the exit code (0 = success || non-zero = error)
//WIFSIGNALED(status) - Did it crash or get killed ?

//DAY 4
// use wait() to track child completion

// ensure parent will wait for all child processes to finish
//handle process status and error

//WIFEXITED(status) - did the child finish normally?
//WEXITSTATUS(status) - get the exit code (0 = success || non-zero = error)
//WIFSIGNALED(status) - dit it crash or get killed 

/*#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<vector>
#include<fcntl.h>

using namespace std;

int main(int argc , char* argv[]){

        const char* keyword = argv[1];
        int num_files = argc - 2;
        
        vector<int> child_pipes; //pipes to read child output
        vector<pid_t> child_pids; //child processes IDS for tracking later
       
       for(int i = 0;i<num_files; ++i){
          const char* filename = argv[i+2];
          
          int pipefd[2];
          pid_t pid = fork();
          
          if(pid == 0){
               close(pipefd[0]);
               
               dup2(pipefd[1] , STDOUT_FILENO);
               close(pipefd[1]); //close original write end
               execlp("grep" , "grep" , keyword , filename , (char*)nullptr);
          }
          else{
                close(pipefd[1]); // close write end
                
                child_pipes.push_back(pipefd[0]);//save read end
                child_pids.push_back(pid); // save child pid
          }
       }
       //parent reads output from each child pipe
       char buff[1024]; 
       
       for(int i = 0; i< num_files; ++i){
             const char* filename = argv[i+2];
             std::cout << "results from" << filename << "\n";
             ssize_t bytes_read;
             
             //reading from childs pipe until its done sending.each time print what you got
             
             while((bytes_read = read(child_pipes[1] , buff , sizeof(buff) - 1)) > 0){
                  buff[bytes_read] = '\0';
                  cout << buff;
             }
             close(child_pipes[i]);
             
             }
             
             for(pid_t pid : child_pids){
                     int status;
                     
                     if(waitpid(pid , &status , 0)){
                     
                             if(WIFEXITED(status)){
                                    int exit_status = WEXITSTATUS(status) ;
                                    if(exit_status != 0){
                                             cerr << "child process " << pid << "exited with zero error code " << exit_status << "\n";
                                    }
                           }
                            else if (WIFSIGNALED(status)){
                                        cerr << "child process " << pid << "was terminated by signal " << WTERMSIG(status) << "\n";
                            }
                    }
             
             }
             return 0;
           }*/
