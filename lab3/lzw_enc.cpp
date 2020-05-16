#include <iostream>
#include "head.h"
#include <bitset>
#include <string>

#define SIZE 256

typedef unsigned char uchar;
typedef unsigned long long int ullint;

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

	int before[SIZE] = {};
	uchar buffer = 0;
	string input_str = "";
	int n;
	while((n = fread(&buffer, 1, 1, input)) != 0)
	{
		before[(int)buffer]++; 
		input_str += buffer;
	}
	fclose(input);
	
	vector<int> seq;
	seq = encode(input_str);
	
	string for_encoding = "";
	if     (compType == 0)
	{
		cout << "Kodowanie Fibonacci" << endl;
		for(int i=0;i<seq.size();i++)
		{
			for_encoding += fib_encode(seq.at(i));
		}	

	}
	else if(compType == 1)
	{
		cout << "Kodowanie Eliasa Gamma" << endl;
		for(int i=0;i<seq.size();i++)
		{
			for_encoding += gamma_encode(seq.at(i));
		}	
	}
	else if(compType == 2)
	{
		cout << "Kodowanie Eliasa Delta" << endl;
		for(int i=0;i<seq.size();i++)
		{
			for_encoding += delta_encode(seq.at(i));
		}	
	}
	else if(compType == 3)
	{
		cout << "Kodowanie Eliasa Omega" << endl;
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
	
	int after[SIZE]={};
	int length = for_encoding.length()/8;
	for(int i=0;i<length;i++)
	{
		uchar c = (int)stoi(for_encoding.substr(i*8, 8), 0, 2);
		fwrite(&c, sizeof(uchar), 1, output);
		after[(int)c]++;
	}
	fclose(output);
	
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
	
	int len = input_str.length();
	cout << "Liczba bajtow na wejsciu: "	<< len										<< endl;
	cout << "Liczba bajtow na wyjsciu: "	<< length 									<< endl;
	cout << "Stopien kompresji: " 			<< (float)len/(float)length 				<< endl;
	cout << "Entropia przed kodowaniem: "	<< calculate_entr(before, (ullint)len)		<< endl;
	cout << "Entropia po kodowaniu: "		<< calculate_entr(after, (ullint)length)	<< endl;
	
}	
