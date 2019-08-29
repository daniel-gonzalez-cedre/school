#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct
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
} player;

//declared globally due to size
static player players[1000000];

//compare function for PPG sorting
int cmpPPG(const void *a, const void *b)
{
	if((*((player *) b)).PPG - (*((player *) a)).PPG > 0)
		return 1;
	else
		return -1;
}

//compare function for APG sorting
int cmpAPG(const void *a, const void *b)
{
	if((*((player *) b)).APG - (*((player *) a)).APG > 0)
		return 1;
	else
		return -1;
}

//compare function for RPG sorting
int cmpRPG(const void *a, const void *b)
{
	if((*((player *) b)).RPG - (*((player *) a)).RPG > 0)
		return 1;
	else
		return -1;
}

//compare function for SPG sorting
int cmpSPG(const void *a, const void *b)
{
	if((*((player *) b)).SPG - (*((player *) a)).SPG > 0)
		return 1;
	else
		return -1;
}

//main function
void partB(FILE *file, char *choice)
{
	int i = 0;
	int j;
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

	//read and store input from file
	while(fscanf(file, "%d %s %f %f %f %f %f %d %d %d", &_id, _name, &_PPG, &_APG, &_RPG, &_SPG, &_MPG, &_vote1, &_vote2, &_vote3) != EOF)
	{
		players[i].id = _id;
		strcpy(players[i].name, _name);
		players[i].PPG = _PPG;
		players[i].APG = _APG;
		players[i].RPG = _RPG;
		players[i].SPG = _SPG;
		players[i].MPG = _MPG;
		players[i].vote1 = _vote1;
		players[i].vote2 = _vote2;
		players[i].vote3 = _vote3;

		i = i + 1;
	}

	//output sorted PPG list
	if(!strcmp(choice, "PPG"))
	{
		qsort(players, i, sizeof(player), cmpPPG);

		for(j = 0; j < i; j++)
			printf("%d %s %0.1f\n", players[j].id, players[j].name, players[j].PPG);

		return;
	}

	//output sorted APG list
	if(!strcmp(choice, "APG"))
	{
		qsort(players, i, sizeof(player), cmpAPG);

		for(j = 0; j < i; j++)
			printf("%d %s %0.1f\n", players[j].id, players[j].name, players[j].APG);

		return;
	}

	//output sorted RPG list
	if(!strcmp(choice, "RPG"))
	{
		qsort(players, i, sizeof(player), cmpRPG);

		for(j = 0; j < i; j++)
			printf("%d %s %0.1f\n", players[j].id, players[j].name, players[j].RPG);

		return;
	}

	//output sorted SPG list
	if(!strcmp(choice, "SPG"))
	{
		qsort(players, i, sizeof(player), cmpSPG);

		for(j = 0; j < i; j++)
			printf("%d %s %0.1f\n", players[j].id, players[j].name, players[j].SPG);

		return;
	}

	printf("Incorrect parameter. Choose either PPG, APG, RPG, or SPG.\n");
}
