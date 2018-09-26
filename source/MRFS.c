//#include<string.h>
//#include <ctype.h> //classify and convert single characters

#include "recursive_functions.h"

int main(int argc, char *argv[]) {
	
	#define MAX_LINE 512
	
	if (argc == 1) {
		fpruintf(stderr, "Error: Specify file with the input data\n");
		exit(1);
	}
	
	FILE *finput = fopen(argv[1], "r");
	if (fp == NULL) {
		fpruintf(stderr, "Error: Cannot open the file: %s\n", argv[1]);
		exit(1);
	}
	
	fclose(finput);
	
	return 0;
}