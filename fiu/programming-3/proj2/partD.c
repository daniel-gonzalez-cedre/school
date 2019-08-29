#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

//Vote structure to save votes
typedef struct
{
	int vote1;
	int vote2;
	int vote3;
} vote;

//Node structure for linked list
struct Node
{
	int id;
	int score;
	char name[256];
	struct Node *next;
};

typedef struct Node node;

//Linked structure list of nodes
struct List
{
	node *head;
	node *itr;
};

typedef struct List list;

//allocated globally due to size
static vote votes[1000000];
static node *result[1000000];
static list players[1000000];
static int flag[1000000];

void partD(FILE *file)
{
	int i = 0;
	int j;
	node MVP;
	node *ptr;
	int hashed;
	int hashed1;
	int hashed2;
	int hashed3;
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

	MVP.score = -1;

	//read input, create inked lists, and count votes
	while(fscanf(file, "%d %s %f %f %f %f %f %d %d %d", &_id, _name, &_PPG, &_APG, &_RPG, &_SPG, &_MPG, &_vote1, &_vote2, &_vote3) != EOF)
	{
		ptr = malloc(sizeof(node));
		hashed = hashID(_id);

		ptr -> id = _id;
		ptr -> score = 0;
		strcpy(ptr -> name, _name);
		
		if(_id == _vote1)
			votes[i].vote1 = -1;
		else
			votes[i].vote1 = _vote1;

		if(_id == _vote2 || _vote1 == _vote2)
			votes[i].vote2 = -1;
		else
			votes[i].vote2 = _vote2;

		if(_id == _vote3 || _vote1 == _vote3 || _vote2 == _vote3)
			votes[i].vote3 = -1;
		else
			votes[i].vote3 = _vote3;

		if(!flag[hashed])
		{
			flag[hashed] = 1;
			players[hashed].head = ptr;
			players[hashed].itr = players[hashed].head;
		} else {
			players[hashed].itr -> next = ptr;
			players[hashed].itr = players[hashed].itr -> next;
		}

		i = i + 1;
	}

	//analyze votes and assign scores
	for(j = 0; j < i; j++)
	{
		_vote1 = votes[j].vote1;
		_vote2 = votes[j].vote2;
		_vote3 = votes[j].vote3;

		//calculate score for vote 1
		if(_vote1 != -1)
		{
			hashed1 = hashID(_vote1);
			ptr = players[hashed1].head;

			while(ptr != NULL)
			{
				if(ptr -> id == _vote1)
					ptr -> score = ptr -> score + 3;

				if(ptr -> score > MVP.score)
				{
					MVP.id = ptr -> id;
					MVP.score = ptr -> score;
					strcpy(MVP.name, ptr -> name);
				}
		
				ptr = ptr -> next;
			}
		}

		//calculate score for vote 2
		if(_vote2 != -1)
		{
			hashed2 = hashID(_vote2);
			ptr = players[hashed2].head;

			while(ptr != NULL)
			{
				if(ptr -> id == _vote2)
					ptr -> score = ptr -> score + 2;

				if(ptr -> score > MVP.score)
				{
					MVP.id = ptr -> id;
					MVP.score = ptr -> score;
					strcpy(MVP.name, ptr -> name);
				}
		
				ptr = ptr -> next;
			}
		}

		//calculate score for vote3
		if(_vote3 != -1)
		{
			hashed3 = hashID(_vote3);
			ptr = players[hashed3].head;

			while(ptr != NULL)
			{
				if(ptr -> id == _vote3)
					ptr -> score = ptr -> score + 1;

				if(ptr -> score > MVP.score)
				{
					MVP.id = ptr -> id;
					MVP.score = ptr -> score;
					strcpy(MVP.name, ptr -> name);
				}
		
				ptr = ptr -> next;
			}
		}
	}

	//output
	printf("The MVP is %s with %d point(s).\n", MVP.name, MVP.id);
}
