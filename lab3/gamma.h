#ifndef GAMMA_H
#define GAMMA_H
#include <string>

std::string int2bin_str(int a);
std::string gamma_encode(int n);
void gamma_decode(int length, std::string str, int arr[]);

#endif
