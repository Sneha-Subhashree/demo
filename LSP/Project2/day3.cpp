#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
using namespace std;
int main(int argc, char * argv[]){
	if (argc < 3) {
        cerr << "Usage: " << argv[0] << " <keyword> <file1> [file2 ...]" << endl;
        return 1;
    }
	const char * keyword = argv[1];
	int num_files = argc-2;
	vector <int> child_pipes;
	vector <pid_t> child_pids;
	for (int i=0;i<num_files;i++){
		const char * filename = argv[i+2];
		pid_t pid=fork();
		int pipefd[2];
		if (pid==0){
			close(pipefd[0]);
			dup2(pipefd[1],STDOUT_FILENO);
			close(pipefd[1]);
			execlp("grep","grep",keyword,filename,(char *)nullptr);
		}
		
		else {
			close(pipefd[1]);
			child_pipes.push_back(pipefd[0]);
			child_pids.push_back(pid);
		}
	}
	char buffer[1024];
	if (argc < 3) {
        cerr << "Usage: " << argv[0] << " <keyword> <file1> [file2 ...]" << endl;
        return 1;
    }
	for (int i=0;i<num_files;i++){
		const char * filename = argv[i+2];
		cout<<"Results from "<<filename<<"\n";
		ssize_t bytes_read;
		while(bytes_read=read(child_pipes[i], buffer,sizeof(buffer - i)) > 0){
			buffer[bytes_read]='\0';
			cout<<buffer;
		}
		close(child_pipes[i]);
	}
	return 0;
}
