#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

//Node structure for linked list
struct Node
{
	int id;
	char name[256];
	float PPG;
	float APG;
	float RPG;
	float SPG;
	float MPG;
	int vote1;
	int vote2;
	int vote3;
	struct Node *next;
};

typedef struct Node node;

//Linked structure list of nodes
struct List
{
	int size;
	node *head;
	node *itr;
};

typedef struct List list;

//allocated globally due to size
static node *result[1000000];
static list players[1000000];
static int flag[1000000];

//main function
void partA(FILE *file, char *request)
{
	int i;
	int j = 0;
	node *ptr;
	int hashed;
	int _id;
	char _name[256];
	float _PPG;
	float _APG;
	float _RPG;
	float _SPG;
	float _MPG;
	int _vote1;
	int _vote2;
	int _vote3;

	//read and create linked lists to store input from file at hashed entries
	while(fscanf(file, "%d %s %f %f %f %f %f %d %d %d", &_id, _name, &_PPG, &_APG, &_RPG, &_SPG, &_MPG, &_vote1, &_vote2, &_vote3) != EOF)
	{
		ptr = malloc(sizeof(node));
		hashed = hashName(_name);

		ptr -> id = _id;
		strcpy(ptr -> name, _name);
		ptr -> PPG = _PPG;
		ptr -> APG = _APG;
		ptr -> RPG = _RPG;
		ptr -> SPG = _SPG;
		ptr -> MPG = _MPG;
		ptr -> vote1 = _vote1;
		ptr -> vote2 = _vote2;
		ptr -> vote3 = _vote3;

		//allocate memory to the players array if necessary
		if(!flag[hashed])
		{
			flag[hashed] = 1;
			players[hashed].size = 1;
			players[hashed].head = ptr;
			players[hashed].itr = players[hashed].head;
		} else {
			players[hashed].size = players[hashed].size + 1;
			players[hashed].itr -> next = ptr;
			players[hashed].itr = players[hashed].itr -> next;
		}
	}

	hashed = hashName(request);
	ptr = players[hashed].head;

	//filter the players in the hashed address who have the same name as requested
	while(ptr != NULL)
	{
		if(!strcmp(ptr -> name, request))
		{
			result[j] = ptr;
			j = j + 1;
		}

		ptr = ptr -> next;
	}

	//output
	printf("There are %d player(s) with the name %s.\n", j, request);

	if(j == 0)
		return;
	
	for(i = 0; i < j; i++)
	{
		printf("The statistics of %s (ID: %d) are: \n", result[i] -> name, result[i] -> id);
		printf("%0.1f point(s) per game.\n", result[i] -> PPG);
		printf("%0.1f assist(s) per game.\n", result[i] -> APG);
		printf("%0.1f rebound(s) per game.\n", result[i] -> RPG);
		printf("%0.1f steal(s) per game.\n", result[i] -> SPG);
		printf("%s plays %0.1f minute(s) per game\n\n", result[i] -> name, result[i] -> MPG);
	}
}
