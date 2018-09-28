//#include<string.h>
//#include <ctype.h> //classify and convert single characters

#include "basis.h"
#include "function.h"

int main(int argc, char *argv[]) {

	bool err = false;
	
	if (argc == 1) {
		fprintf(stderr, "Error: Specify file with the input data\n");
		err = true;
	}
	
	FILE *finput = fopen(argv[1], "r");
	if (finput == NULL) {
		fprintf(stderr, "Error: Cannot open the file: %s\n", argv[1]);
		err = true;
	}

	if (!err) {

	} else
		return 1;
	
	fclose(finput);
	
	return 0;
}