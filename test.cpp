//hello.cpp
#include<iostream>
using namespace std;

class Kitty{
	public:
		char *str;
		void print(char *);
};

void Kitty::print(char *str){
	cout << str;
}

int main(){
	Kitty obj;
	obj.str = "Kitty on your lap";
	obj.print("hello,world!");

	return 0;
}