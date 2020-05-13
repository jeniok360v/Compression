#include <iostream>
#include "head.h"

using namespace std;

int main()
{
	string str = "";
	for(int i=1;i<14;i++)
	{
		str += fib_seq(i);
	}
	int ar[13]={};
	decode_fib_str(13, str, ar);
	for(int i=0;i<13;i++)
	{
		cout << ar[i] << endl;
	}


}