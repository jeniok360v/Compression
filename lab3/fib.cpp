#include <iostream>
#include <string>
#include <bits/stdc++.h>

using namespace std;

void fib(int amount, int arr[]);
int encode_fib_count(int x);
string fib_encode(int x);
void fib_fill(int length, int arr[]);
void fib_decode(int amount, string str, int arr[]);

void fib(int amount, int arr[])
{
	int a=1;
	int b=1;
	int temp;
	for(int i=0;i<amount;i++)
	{
		temp = a;
		a = b;
		b = temp+b;
		arr[i] = a;
	}
}


int encode_fib_count(int x)
{
	int a=1;
	int b=1;
	int temp;
	int counter=0;
	while(b<=x)
	{
		temp = a;
		a = b;
		b = temp+b;
		counter++;
	}
	return counter;
}

string fib_encode(int x)
{
	int length = encode_fib_count(x);
	int fib_num[length];
	fib_fill(length, fib_num);
	string str = "";
	int temp = x;
	
	for(int i=length-1;i>=0;i--)
	{
		if(temp>=fib_num[i])
		{
			str = "1"+str;
			temp -= fib_num[i];
		}
		else
		{
			str = "0"+str;
		}
	}
	return str+"1";
}

void fib_fill(int length, int arr[])
{
	int a=1;
	int b=1;
	int temp;
	for(int i=0;i<length;i++)
	{
		temp = a;
		a = b;
		b = temp+b;
		arr[i]=a;
	}
}

vector<int> fib_decode(int amount, string str)
{
	vector<int> arr;
	int counter = 0;
	string temp[amount] = {};
	
	int max=0;
	for(int i=0;i<amount;i++)
	{
		int size=0;
		while(str.at(counter)!='1' || str.at(counter+1)!='1')
		{
			size++;
			temp[i] = temp[i]+str.at(counter);
			counter++;
		}
		temp[i] += str.at(counter);
		counter+=2;	
		if(size+1>max)
		{
			max = size+1;
		}
	}
	int fibs[max];
	fib(max, fibs);	
	for(int i=0;i<amount;i++)
	{
		arr.push_back(0);
		for(int j=0;j<(int)temp[i].size();j++)
		{
			if(temp[i].at(j)=='1')
				arr.at(i) += fibs[j];
			//arr[i] += fibs[j];
		}
	}
	return arr;
}

































