#include <stdio.h>
#include <stdlib.h>
#include "partA.h"
#include "partB.h"
#include "partC.h"
#include "partD.h"

int main(int argc, char *argv[])
{
	FILE *file;

	if(argc >= 2)
		if((file = fopen("./player.txt", "r")) == NULL)
			printf("File does not exist.\n");
	else
		printf("This program requires at least a <selection> parameter.\n");

	if(*argv[1] == 'A' || *argv[1] == 'a')
		partA(file, argv[2]);

	if(*argv[1] == 'B' || *argv[1] == 'b')
		partB(file, argv[2]);

	if(*argv[1] == 'C' || *argv[1] == 'c')
		partC(file);

	if(*argv[1] == 'D' || *argv[1] == 'd')
		partD(file);
}
