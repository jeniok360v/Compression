#include <string>
#include <iostream>
#include <bitset>
#include <math.h>

#define SIZE 256

using namespace std;

typedef unsigned long long int ullint;

typedef enum 
{
	fibonac = 0,
	gamm = 1,
	delt = 2,
	omeg = 3
}compressionType;

string int2bin_str(int n)
{
	string str;
    while(n!=0) 
	{
		str=(n%2==0 ?"0":"1")+str; 
		n/=2;
	}
    return str;
}

string beggining_encode(string str, compressionType encoding)
{
	int k = str.length() % 8;
	k = 8-k;
	k = k%8;
	
	// pierwsze 3 bity do zapisu przesuniecia
	string zeros_amount = bitset<3>(k).to_string();
	// nastepne 5 to typ kodowania
	string type = bitset<5>((int)encoding).to_string();
	
	string zeros = "";
	for(int i=0;i<k;i++)
	{
		zeros = "0"+zeros;
	}
	
	//cout << zeros_amount+type+zeros << endl;
	str = zeros_amount+type+zeros + str;
	return str;
}


string beggining_decode(string str)
{
	int k = stoi(str.substr(0, 3), 0, 2);
	str.erase(0, k+8);
	return str;
}

compressionType compType(string str)
{
	return (compressionType)stoi(str.substr(3, 5), 0, 2);
}

float calculate_entr(int ilosc[SIZE], ullint amount)	//amount to liczba bajtow
{
	float entropy=0;
	if(amount>0)
	{
		for (int i=0; i<SIZE;i++)
		{
			if(ilosc[i]>0)
			{
				entropy += ilosc[i]*(log2(ilosc[i]));
			}
		}
		entropy= -entropy/(float)amount;
		entropy+=log2((float)amount);
	}
	return entropy;
}



























