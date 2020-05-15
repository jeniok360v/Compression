#include <string>
#include <iostream>
#include <bitset>

using namespace std;

typedef enum 
{
	fibonacci = 0,
	gamma = 1,
	delta = 2,
	omega = 3
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





























