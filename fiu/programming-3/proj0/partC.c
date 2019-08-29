#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverseWords(FILE *file)
{
	char *lines[100];
	char *words[81];
	int counter;

	for(int i = 0; i < 100; i++)
	{
		lines[i] = calloc(81, sizeof(char));
		
		if(fgets(lines[i], 81, file) != NULL)
		{
			counter = 81;
			words[0] = calloc(81, sizeof(char));
			words[0] = strtok(lines[i], " ");

			for(int j = 1; j < 81; j++)
			{
				words[j] = calloc(81, sizeof(char));
				words[j] = strtok(NULL, " \n");

				if(words[j] == NULL)
				{
					counter = j;
					j = 81;
				}
			}

			for(int j = counter - 1; j >=0; j--)
				printf("%s ", words[j]);
				//free(words[j]);
			
			printf("\n");
		} else {
			i = 100;
		}
	}
}
