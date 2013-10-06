#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	char code[3];
	memset(code,'0',sizeof(code));
	code[1] = 'a';
	//code[0] = '0';
	code[2] = '1';
	//code[3] = '0';
	code[4] = '\0';
	printf("hola mundo: %s", code);
	return 0;
}
