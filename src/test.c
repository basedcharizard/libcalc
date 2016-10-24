#include <stdio.h>
#include "calc.h"

int main(int argc, char *argv[]) 
{
	if (argc != 2) {
		fprintf(stderr, "usage: %s <expression>\n", argv[0]);
		return -1;
	}
	printf("calc() returned: %f\n",calc(argv[1]));
	return 0;
}
