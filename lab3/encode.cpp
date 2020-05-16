#include <bits/stdc++.h>

using namespace std;

vector<int> encode(string str)
{
	unordered_map<string, int> dict;
	for (int i=0;i<256;i++)
	{ 
		string s = ""; 
		s += char(i);
		dict[s] = i; 
	} 
	
	string c = "", s = ""; 
	c += str[0]; 
	int code = 256; 
	vector<int> out; 
	for (int i=0;i<str.length();i++) 
	{ 
		if (i != str.length()-1) 
			s += str[i+1]; 
		if (dict.find(c+s) != dict.end())
		{ 
			c += s; 
		} 
		else 
		{
			out.push_back(dict[c]); 
			dict[c+s] = code; 
			code++; 
			c = s; 
		} 
		s = ""; 
	}
	out.push_back(dict[c]); 
	return out;
}