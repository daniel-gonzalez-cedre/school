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

//compares points based on their x co-ordinates
int pointCompare(const void *a, const void *b)
{
	return (*((point *)(a))).x - (*((point *)(b))).x;
}

void sortedTour(FILE *file)
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

	//declare arrays to hold points and lines
	iterator = head;
	point points[size];
	line lines[size - 1];

	//construct points
	for(i = 0; i < size; i++)
	{
		p.x = iterator -> x;
		p.y = iterator -> y;
		
		points[i] = p;
		iterator = iterator -> next;
	}

	//sort the array of points based on x co-ordinates
	qsort(points, size, sizeof(point), pointCompare);

	//construct and store lines
	for(i = 0; i < size - 1; i++)
	{
		t.x = points[i];
		t.y = points[i + 1];
		t.z = sqrt((points[i].x - points[i + 1].x)*(points[i].x - points[i + 1].x) + (points[i].y - points[i + 1].y)*(points[i].y - points[i + 1].y));

		lines[i] = t;
	}

	//output
	printf("Total line segments = %d\n\n", size);

	for(i = 0; i < size - 1; i++)
	{
		totalLength = totalLength + lines[i].z;
		printf("Segment[%d]: (%0.2f, %0.2f) --> (%0.2f, %0.2f);\tlength = %0.2f\n", i + 1,  lines[i].x.x, lines[i].x.y, lines[i].y.x, lines[i].y.y, lines[i].z);
	} 

	printf("\nTotal tour length = %0.2f\n", totalLength);
}
