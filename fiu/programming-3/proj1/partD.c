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

//structure modeling a rectangle
typedef struct
{
	point x;
	point y;
	float area;
} rectangle;

//compares rectangles based on their areas
int rectangleCompare(const void *a, const void *b)
{
	return (*((rectangle *)(a))).area - ((*(rectangle *)(b))).area;
}

void rectangleAreas(FILE *file)
{
	int i;
	int flag = 1;
	int size = 0;
	node *head = NULL;
	node *iterator;
	node *temp;
	point p;
	rectangle r;

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

	//declare an array to hold the rectangles constructed from the points
	iterator = head;
	rectangle rectangles[size - 1];

	//construct points, construct and store rectangles
	for(i = 0; i < size / 2; i++)
	{
		p.x = iterator -> x;
		p.y = iterator -> y;
		r.x = p;

		p.x = iterator -> next -> x;
		p.y = iterator -> next -> y;
		r.y = p;

		r.area = fabsf(r.x.x - r.y.x) * fabsf(r.x.y - r.y.y);

		rectangles[i] = r;
		iterator = iterator -> next;
		iterator = iterator -> next;
	}

	//sort the rectangles based on areas
	qsort(rectangles, size / 2, sizeof(rectangle), rectangleCompare);

	//output
	printf("Total line segments = %d\n\n", size);

	for(i = 0; i < size / 2; i++)
	{
		printf("Rectangle[%d]: ((%0.2f, %0.2f), (%0.2f, %0.2f));\tarea = %0.2f\n", i + 1,  rectangles[i].x.x, rectangles[i].x.y, rectangles[i].y.x, rectangles[i].y.y, rectangles[i].area);
	}
}
