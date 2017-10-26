#include <stdio.h>
#include <stdlib.h>

int main(){
	char s[2];
	int n=0;

	s[0] = '0';
	s[1] = '1';

	printf("%s\n", s);
	printf("%c\n", s[0]);
	n = s[1] - '0';
	printf("%d\n", n);

	return 0;
}