#include <stdio.h>

void reverseChars(FILE *file)
{
	char character[81];
	int counter;
	
	//repeats the algorithm every line until EOF
	while(!feof(file))
	{
		//reading the file character by character until an end of line is reached
		for(int i = 0; i < 81; i++)
		{
			character[i] = fgetc(file);
			
			if(character[i] == '\n' || character[i] == '\r')
			{
				counter = i;
				i = 100;
			}
		}

		//outputing what has been read from the file in reverse order
		for(int i = counter; i >= 0; i--)
			if(character[i] != EOF)
				printf("%c", character[i]);
	}

	printf("\n");
}
