#include <iostream>
#include <ctime>
#include <msclr/marshal_cppstd.h>
#include <string.h>
// File: stopwatch.h
// @Author Lars Veenendaal 1633223
// @Daan Joling 1617085
// 0.1 - Skeleton setup

using namespace std;

class stopwatch{
private:
	
public:
	unsigned int start;
	void reset_the_clock();
	stopwatch() : start(clock()){};
	~stopwatch();
	string printTimePast();
};
