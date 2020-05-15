#ifndef FIB_H
#define FIB_H
#include <string>
#include <bits/stdc++.h>

int encode_fib_count(int x);
void fib_fill(int length, int arr[]);
void fib(int amount, int arr[]);

std::string fib_encode(int x);
std::vector<int> fib_decode(int amount, std::string str);

#endif
