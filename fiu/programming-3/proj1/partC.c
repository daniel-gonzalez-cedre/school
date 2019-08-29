#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Node;

typedef struct Node
{
	float x;
	float y;
	struct Node *next;
} node;

//structure modeling a point
typedef struct
{
	float x;
	float y;
} point;

//structure modeling a line
typedef struct
{
	point x;
	point y;
	float z;
} line;

//compares lines based on their lengths
int lineCompare(const void *a, const void *b)
{
	return (*((line *)(a))).z - ((*(line *)(b))).z;
}

void lengthSortedTour(FILE *file)
{
	int i;
	int flag = 1;
	int size = 0;
	float totalLength = 0;
	node *head = NULL;
	node *iterator;
	node *temp;
	point p;
	line t;

	//construct a linked list and read input
	while(fscanf(file, "%f %f", &(p.x), &(p.y)) != EOF)
	{
		temp = (node *) malloc(sizeof(node));
		temp -> x = p.x;
		temp -> y = p.y;
		temp -> next = NULL;

		if(flag)
		{
			flag = 0;
			head = temp;
			iterator = head;
		} else {
		
			iterator -> next = temp;
			iterator = iterator -> next;
		}

		size = size + 1;
	}

	//declare an array to hold the lines constructed from the points
	iterator = head;
	line lines[size - 1];

	//construct points, construct and store lines
	for(i = 0; i < size - 1; i++)
	{
		p.x = iterator -> x;
		p.y = iterator -> y;
		t.x = p;

		p.x = iterator -> next -> x;
		p.y = iterator -> next -> y;
		t.y = p;

		t.z = sqrt((iterator -> x - iterator -> next -> x)*(iterator -> x - iterator -> next -> x) + (iterator -> y - iterator -> next -> y)*(iterator -> y - iterator -> next -> y));

		lines[i] = t;
		iterator = iterator -> next;
	}

	//sort the lines based on lengths
	qsort(lines, size - 1, sizeof(line), lineCompare);

	//output
	printf("Total line segments = %d\n\n", size);

	for(i = 0; i < size - 1; i++)
	{
		totalLength = totalLength + lines[i].z;
		printf("Segment[%d]: (%0.2f, %0.2f) --> (%0.2f, %0.2f);\tlength = %0.2f\n", i + 1,  lines[i].x.x, lines[i].x.y, lines[i].y.x, lines[i].y.y, lines[i].z);
	}
}
