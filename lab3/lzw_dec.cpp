#include <iostream>
#include "head.h"
#include <bitset>
#include <string>

typedef unsigned char uchar;

using namespace std;

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		cout << "Prosze podac nazwe pliku wyjsciowego!\n" << endl;
		return 0;
	}	
	FILE* output;
	output = fopen(argv[1], "wb");	
	
	FILE* archive;
	archive = fopen("archive.bin", "rb"); 	
	if (archive == NULL) 
	{ 
		cout << "Cannot open file" << endl; 
		return 0; 
	}
	
	string in_str = "";
	uchar buffer = 0;
	int n;
	while((n = fread(&buffer, 1, 1, archive)) != 0)
	{  
		for(int i=0;i<8;i++)
		{
			in_str += ((buffer & (1 << (7-i))) ? '1' : '0');
		}
	}
	fclose(archive);
	
	compressionType compT = compType(in_str);
	in_str = beggining_decode(in_str);
	
	vector<int> vec;
	if		((int)compT == 0)
	{
		cout << "Kodowanie Fibonacci" << endl;
		vec = fib_decode(0, in_str);
	}
	else if	((int)compT == 1)
	{
		cout << "Kodowanie Eliasa Gamma" << endl;
		vec = gamma_decode(in_str);
	}
	else if	((int)compT == 2)
	{
		cout << "Kodowanie Eliasa Delta" << endl;
		vec = my_delta_decode(in_str);
	}
	else if	((int)compT == 3)
	{
		cout << "Kodowanie Eliasa Omega" << endl;
		vec = omega_decode(in_str);
	}	
	else
	{
		cout << "Nieznany typ kodowania" << endl;
		fclose(output);
		return 0;
	}
	string out_str = decode(vec);
	
	int length = out_str.length();
	for(int i=0;i<length;i++)
	{
		char c = out_str.at(i);
		fwrite(&c, sizeof(char), 1, output);
	}
	fclose(output);
}	
























