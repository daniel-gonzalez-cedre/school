//hashing function for use in assignment
int hashName(char *string)
{
	int i = 0;
	int value = 0;

	while(*(string + i) != '\0')
	{
		value = value + *(string + i) - 64;
		i = i + 1;
	}
	
	return value % 1000000;
}

int hashID(int id)
{
	return id % 1000000;
}
