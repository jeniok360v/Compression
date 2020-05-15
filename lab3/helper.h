#ifndef HELPER_H
#define HELPER_H
#include <string>
#include <bits/stdc++.h>
typedef enum 
{
	fibonacci = 0,
	gamma = 1,
	delta = 2,
	omega = 3
}compressionType;

std::string int2bin_str(int a);

std::string beggining_encode(std::string str, compressionType encoding);
std::string beggining_decode(std::string str);
compressionType compType(std::string str);

#endif




