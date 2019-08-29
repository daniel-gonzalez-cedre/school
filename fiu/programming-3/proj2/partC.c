#include <stdio.h>
#include <string.h>

typedef struct
{
	float score;
	char name[256];
} player;

//main function
void partC(FILE *file)
{
	player bestDef;
	player bestOff;
	float tempDefScore;
	float tempOffScore;
	int flag1 = 1;
	int flag2 = 1;
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


	//read and store input from file, calculate best defensive and offensive players
	while(fscanf(file, "%d %s %f %f %f %f %f %d %d %d", &_id, _name, &_PPG, &_APG, &_RPG, &_SPG, &_MPG, &_vote1, &_vote2, &_vote3) != EOF)
	{
		//current scores being read
		tempDefScore = (_RPG * 5 + _SPG * 3) / _MPG;
		tempOffScore = (_PPG + _APG * 2 + _RPG / 2) / _MPG;

		if(flag1)
		{
			flag1 = 0;
			bestDef.score = tempDefScore;
			strcpy(bestDef.name, _name);
			continue;
		}

		if(flag2)
		{
			flag2 = 0;
			bestOff.score = tempOffScore;
			strcpy(bestOff.name, _name);
			continue;
		}

		if(tempDefScore > bestDef.score)
		{
			bestDef.score = tempDefScore;
			strcpy(bestDef.name, _name);
		}

		if(tempOffScore > bestOff.score)
		{
			bestOff.score = tempOffScore;
			strcpy(bestOff.name, _name);
		}
	}

	//output
	printf("The best defense player is %s, with the defense value %f\n", bestDef.name, bestDef.score);
	printf("The best offense player is %s, with the offense value %f\n", bestOff.name, bestOff.score);
}
