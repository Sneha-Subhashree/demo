#include <iostream>
using namespace std;
int main(){
	int num;
	cout<<"Enter number: ";
	cin>>num;
	if (num % 2 != 0){
		cout<<num<<" is odd"<<endl;
	}
	else if (num % 2 == 0) {
		cout<<num<<" is even"<<endl;
	}
	else{
		cout<<"Zero"<<endl;
	}
	return 0;
}
