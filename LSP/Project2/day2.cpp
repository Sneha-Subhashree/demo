#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
using namespace std;
int main(int argc, char * argv[]){
	if (argc < 3)
	{
		cerr << "Usage: " << argv[0] << "<keyword> <file1> <file2> ... \n";
		return 1;
	}
	const char * keyword = argv[1];
	int num_files = argc-2;
	cout << keyword << "\n";
	cout << "Files to search: \n";
	for (int i=2;i<argc;i++){
		cout << "- "<<argv[i]<<"\n";
	}
	for (int i=0;i<num_files;i++){
		const char * filename = argv[i+2];
		pid_t pid=fork();
		if (pid==0){
			execlp("grep","grep",keyword,filename,(char *)nullptr);
		}
		/*else if (pid > 0){
			//parent continues	
		} */
	}
	return 0;
}
