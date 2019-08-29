// Daniel Gonzalez, FIU Mathematics & Computer Science BSc
// Fall 2015

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static unsigned char S0[4][4] = {{1, 0, 3, 2}, {3, 2, 1, 0}, {0, 2, 1, 3}, {3, 1, 3, 2}};
static unsigned char S1[4][4] = {{0, 1, 2, 3}, {2, 0, 1, 3}, {3, 0, 1, 0}, {2, 1, 0, 3}};

unsigned char gen_subkey(unsigned char init_key[2], unsigned char subkey, int flag)
{
	//temp_key = {[7], [5], [8], [3], [6] || [0], [9], [1], [2], [4]}

	//temp_key = {[5], [8], [3], [6], [7] || [9], [1], [2], [4], [0]};
	//p8 = {[9], [3], [1], [6], [2], [7], [0], [4]}
	//subkey1

	//temp_key = {[8], [3], [6], [7], [5] || [1], [2], [4], [0], [9]};
	//p8 = {[1], [6], [2], [7], [4], [5], [9], [0]}
	//subkey2

	//temp_key = {[3], [6], [7], [5], [8] || [2], [4], [0], [9], [1]};
	//p8 = {[2], [7], [4], [5], [0], [8], [1], [9]}
	//subkey2

	if(flag == 1)
	{
		subkey = subkey | (((init_key[0] >> 4) & 1) << 0);
		subkey = subkey | (((init_key[0] >> 0) & 1) << 1);
		subkey = subkey | (((init_key[0] >> 7) & 1) << 2);
		subkey = subkey | (((init_key[0] >> 2) & 1) << 3);
		subkey = subkey | (((init_key[0] >> 6) & 1) << 4);
		subkey = subkey | (((init_key[0] >> 1) & 1) << 5);
		subkey = subkey | (((init_key[0] >> 3) & 1) << 6);
		subkey = subkey | (((init_key[1] >> 1) & 1) << 7);//9
	} else if (flag == 2) {
		subkey = subkey | (((init_key[1] >> 1) & 1) << 0);//9
		subkey = subkey | (((init_key[0] >> 1) & 1) << 1);
		subkey = subkey | (((init_key[1] >> 0) & 1) << 2);//8
		subkey = subkey | (((init_key[0] >> 0) & 1) << 3);
		subkey = subkey | (((init_key[0] >> 5) & 1) << 4);
		subkey = subkey | (((init_key[0] >> 4) & 1) << 5);
		subkey = subkey | (((init_key[0] >> 7) & 1) << 6);
		subkey = subkey | (((init_key[0] >> 2) & 1) << 7);
	}

	return subkey;
}

unsigned char initial_permutation(unsigned char block)
{
	unsigned char temp = block;

	block = 0;
	block = block | (((temp >> 1) & 1) << 0);
	block = block | (((temp >> 3) & 1) << 1);
	block = block | (((temp >> 0) & 1) << 2);
	block = block | (((temp >> 4) & 1) << 3);
	block = block | (((temp >> 7) & 1) << 4);
	block = block | (((temp >> 5) & 1) << 5);
	block = block | (((temp >> 2) & 1) << 6);
	block = block | (((temp >> 6) & 1) << 7);

	return block;
}

unsigned char inverse_permutation(unsigned char block)
{
	unsigned char temp = block;

	block = 0;
	block = block | (((temp >> 2) & 1) << 0);
	block = block | (((temp >> 0) & 1) << 1);
	block = block | (((temp >> 6) & 1) << 2);
	block = block | (((temp >> 1) & 1) << 3);
	block = block | (((temp >> 3) & 1) << 4);
	block = block | (((temp >> 5) & 1) << 5);
	block = block | (((temp >> 7) & 1) << 6);
	block = block | (((temp >> 4) & 1) << 7);

	return block;
}

unsigned char SW(unsigned char block)
{
	unsigned char temp = block;

	block = 0;
	block = block | (((temp >> 4) & 1) << 0);
	block = block | (((temp >> 5) & 1) << 1);
	block = block | (((temp >> 6) & 1) << 2);
	block = block | (((temp >> 7) & 1) << 3);
	block = block | (((temp >> 0) & 1) << 4);
	block = block | (((temp >> 1) & 1) << 5);
	block = block | (((temp >> 2) & 1) << 6);
	block = block | (((temp >> 3) & 1) << 7);

	return block;
}

unsigned char fK(unsigned char subkey, unsigned char block)
{
	//unsigned char e_p[8] = {block[4], block[7], block[6], block[5], block[6], block[5], block[4], block[7]};
	unsigned char entry0, entry1;
	unsigned char matrix_result = 0;
	unsigned char e_p = 0;

	//expand and permute the right-most 4 bits of the block
	e_p = e_p | (((block >> 3) & 1) << 0);
	e_p = e_p | (((block >> 0) & 1) << 1);
	e_p = e_p | (((block >> 1) & 1) << 2);
	e_p = e_p | (((block >> 2) & 1) << 3);
	e_p = e_p | (((block >> 1) & 1) << 4);
	e_p = e_p | (((block >> 2) & 1) << 5);
	e_p = e_p | (((block >> 3) & 1) << 6);
	e_p = e_p | (((block >> 0) & 1) << 7);

	//XOR with the subkey
	e_p = e_p ^ subkey;

	//compute the entries in the matrices
	entry0 = S0[(((e_p >> 7) & 1) << 1) | ((e_p >> 4) & 1)][(((e_p >> 6) & 1) << 1) | ((e_p >> 5) & 1)];
	entry1 = S1[(((e_p >> 3) & 1) << 1) | ((e_p >> 0) & 1)][(((e_p >> 2) & 1) << 1) | ((e_p >> 1) & 1)];
	//block = block | ((((entry0 >> 1) & 1) ^ ((block >> 4) & 1)) << 4);

	//permute the matrix using P4
	matrix_result = matrix_result | (((entry0 >> 1) & 1) << 4);
	matrix_result = matrix_result | (((entry1 >> 1) & 1) << 5);
	matrix_result = matrix_result | (((entry1 >> 0) & 1) << 6);
	matrix_result = matrix_result | (((entry0 >> 0) & 1) << 7);

	//XOR the result with the left-most 4 bits of the block (the right-most 4 bits of matrix_result are 0)
	block = block ^ matrix_result;

	return block;
}

void encryption(unsigned char subkey_one, unsigned char subkey_two, unsigned char init_vector, char* s_filename, char* r_filename)
{
	FILE* s_file;
	FILE* r_file;
	unsigned char buffer[1];

	if((s_file = fopen(s_filename, "rb")) == NULL)
	{
		printf("ERROR: could not open source file!\n");
		return;
	}

	if((r_file = fopen(r_filename, "wb")) == NULL)
	{
		printf("ERROR: could not create destination file!\n");
		return;
	}

	while(fread(buffer, sizeof(char), 1, s_file))
	{
		unsigned char block = buffer[0];

		//cypher block chaining (encryption): XOR block with vector
		block = block ^ init_vector;

		//encrypting the block
		block = inverse_permutation(fK(subkey_two, SW(fK(subkey_one, initial_permutation(block)))));

		//cypher block chaining: updating the vector
		init_vector = block;

		//write encrypted block to file
		buffer[0] = block;
		fwrite(buffer, sizeof(char), 1, r_file);
	}

	fclose(s_file);
	fclose(r_file);
}

void decryption(unsigned char subkey_one, unsigned char subkey_two, unsigned char init_vector, char* s_filename, char* r_filename)
{
	FILE* s_file;
	FILE* r_file;
	unsigned char buffer[1];

	if((s_file = fopen(s_filename, "rb")) == NULL)
	{
		printf("ERROR: could not open source file!\n");
		return;
	}

	if((r_file = fopen(r_filename, "wb")) == NULL)
	{
		printf("ERROR: could not create destination file!\n");
		return;
	}

	while(fread(buffer, sizeof(char), 1, s_file))
	{
		unsigned char block = buffer[0];

		//encrypting the block
		block = inverse_permutation(fK(subkey_one, SW(fK(subkey_two, initial_permutation(block)))));

		//cypher block chaining (decryption): XOR block with vector
		block = block ^ init_vector;

		//cypher block chaining: updating the vector
		init_vector = buffer[0];

		//write decrypted block to file
		buffer[0] = block;
		fwrite(buffer, sizeof(char), 1, r_file);
	}

	fclose(s_file);
	fclose(r_file);
}

int main(int argc, char* argv[])
{
	int decode_flag, n;
	char* s_filename;
	char* r_filename;
	unsigned char init_key[2];
	unsigned char init_vector = 0;
	//unsigned char subkey_one = 0;
	//unsigned char subkey_two = 0;

	//checking arguments
	if(argc < 5)
	{
		printf("ERROR: not enough arguments!\n");
		printf("For encryption: ./mycipher <init_key> <init_vector> <s_filename> <r_filename>\n");
		printf("For decryption: ./mycipher -d <init_key> <init_vector> <s_filename> <r_filename>\n");
		return -1;
	} else if(argc == 5) {
		decode_flag = 0;
		n = 1;
	} else if(strlen(argv[1]) != 2 || argv[1][0] != '-' || argv[1][1] != 'd') {
		printf("ERROR: unrecognized input \"%s\"!\n", argv[1]);
		printf("For encryption: ./mycipher <init_key> <init_vector> <s_filename> <r_filename>\n");
		printf("For decryption: ./mycipher -d <init_key> <init_vector> <s_filename> <r_filename>\n");
		return -1;
	} else {
		decode_flag = 1;
		n = 2;
	}

	init_key[0] = 0;
	init_key[1] = 0;

	//set init_key
	for(int i = 0; i < 8; i++)
	{
		if(argv[n][9 - i] == '1')
		{
			init_key[0] = init_key[0] | (1 << i);
		} else if(argv[n][9 - i] == '0')
		{
			continue;
		} else {
			printf("ERROR: init_key was not a binary string!\n");
			return -1;
		}
	}

	//still setting init_key
	for(int i = 8; i < 10; i++)
	{
		if(argv[n][9 - i] == '1')
		{
			init_key[1] = init_key[1] | (1 << (i - 8));
		} else if(argv[n][9 - i] == '0')
		{
			continue;
		} else {
			printf("ERROR: init_key was not a binary string!\n");
			return -1;
		}
	}

	n = n + 1;

	//set init_vector
	for(int i = 0; i < 8; i++)
	{
		if(argv[n][7 - i] == '1')
		{
			init_vector = init_vector | (1 << i);
		} else if(argv[n][7 - i] == '0')
		{
			continue;
		} else {
			printf("ERROR: init_vector was not a binary string!\n");
			return -1;
		}
	}

	n = n + 1;
	s_filename = argv[n];
	n = n + 1;
	r_filename = argv[n];

	//generate the subkeys and either encrypt or decrypt the file
	if(decode_flag)
	{
		decryption(gen_subkey(init_key, 0, 1), gen_subkey(init_key, 0, 2), init_vector, s_filename, r_filename);
		printf("Succesfully decrypted file %s to %s!\n", s_filename, r_filename);
	} else {
		encryption(gen_subkey(init_key, 0, 1), gen_subkey(init_key, 0, 2), init_vector, s_filename, r_filename);
		printf("Succesfully encrypted file %s to %s!\n", s_filename, r_filename);
	}

	return 0;
}
