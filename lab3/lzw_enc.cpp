#include <iostream>
#include "head.h"
#include <bitset>
#include <string>

typedef unsigned char uchar;

using namespace std;

int main(int argc, char *argv[])
{
	FILE* input;
	compressionType compType;
	if(argc == 2)
	{
		input = fopen(argv[1], "rb");
		compType = omega;	
	}	
	else if(argc == 3)
	{
		input = fopen(argv[1], "rb");
		compType = (compressionType)strtol(argv[2], NULL, 10);
	}
	else 
	{
		cout << "Niepoprawna liczba argumentow!" << endl;
		return 0;
	}

	uchar buffer = 0;
	string input_str = "";
	int n;
	while((n = fread(&buffer, 1, 1, input)) != 0)
	{
		input_str += buffer;
	}
	fclose(input);
	
	vector<int> seq;
	seq = encode(input_str);
	
	string for_encoding = "";
	if     (compType == 0)
	{
		for(int i=0;i<seq.size();i++)
		{
			for_encoding += fib_encode(seq.at(i));
		}	

	}
	else if(compType == 1)
	{
		for(int i=0;i<seq.size();i++)
		{
			for_encoding += gamma_encode(seq.at(i));
		}	
	}
	else if(compType == 2)
	{
		for(int i=0;i<seq.size();i++)
		{
			for_encoding += delta_encode(seq.at(i));
		}	
	}
	else if(compType == 3)
	{
		for(int i=0;i<seq.size();i++)
		{
			for_encoding += omega_encode(seq.at(i));
		}	
	}
	else 
	{
		cout << "Niepoprawny typ kodowania" << endl;
		cout << "0 - Fibonacci" << endl;
		cout << "1 - Eliasa gamma" << endl;
		cout << "2 - Eliasa delta" << endl;
		cout << "3 - Eliasa omega" << endl;
		return 0;
	}	
	for_encoding = beggining_encode(for_encoding, compType);
	
	FILE* output;
	output = fopen("archive.bin", "wb"); 
	if (output == NULL) 
	{ 
		printf("Cannot open file \n"); 
		exit(0); 
	}
	
	int length = for_encoding.length()/8;
	for(int i=0;i<length;i++)
	{
		char c = (int)stoi(for_encoding.substr(i*8, 8), 0, 2);
		fwrite(&c, sizeof(char), 1, output);
	}
	fclose(output);
}	
