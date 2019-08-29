#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "partA.h"
#include "partB.h"
#include "partC.h"
#include "partD.h"


int main (int argc, char *argv[])
{
	FILE *file;

	if(argc == 3)
	{
		if((file = fopen(argv[1], "r")) == NULL)
		{
			printf("File path does not exist.\n");
			exit(0);
		}
	} else {
		printf("This program requires <file path> and <selection> paramaters.\n");
		exit(0);
	}

	if(!strcasecmp("A", argv[2]))
		naturalTour(file);

	if(!strcasecmp("B", argv[2]))
		sortedTour(file);

	if(!strcasecmp("C", argv[2]))
		lengthSortedTour(file);

	if(!strcasecmp("D", argv[2]))
		rectangleAreas(file);

	fclose(file);
}
