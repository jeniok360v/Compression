#include <bits/stdc++.h>



using namespace std;

string decode(vector<int> seq) 
{ 
	string out = "";
	unordered_map<int, string> dict; 
	for (int i = 0; i <= 255; i++) 
	{ 
		string str = ""; 
		str += char(i); 
		dict[i] = str; 
	} 
	int pk = seq[0], k; 
	string s = dict[pk]; 
	string c = ""; 
	c += s[0]; 
	out += s;
	int count = 256; 
	for (int i=0;i<seq.size()-1;i++) 
	{ 
		k = seq[i+1]; 
		if (dict.find(k) == dict.end()) 
		{ 
			s = dict[pk]; 
			s = s+c; 
		} 
		else 
		{ 
			s = dict[k]; 
		} 
		out += s;
		c = ""; 
		c += s[0]; 
		dict[count] = dict[pk] + c; 
		count++; 
		pk = k; 
	} 
	return out;
}