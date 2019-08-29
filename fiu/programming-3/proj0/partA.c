#include <stdio.h>
#include <stdlib.h>

void reverseLines(FILE *file)
{
	char *lines[100];
	int counter;

	for(int i = 0; i < 100; i++)
	{
		//allocating space for each line in memory
		lines[i] = calloc(81, sizeof(char));

		//reading lines from text file
		if(fgets(lines[i], 81, file) == NULL)
		{
			counter = i;
			i = 100;
		}

	}

	//outputing text lines in reverse order
	for(int i = counter - 1; i >= 0; i--)
		printf("%s", lines[i]);
}
