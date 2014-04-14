#include <iostream>
#include <ctime>
// File: stopwatch.h
// @Author Lars Veenendaal 1633223
// 0.1 - Skeleton setup

using namespace std;

class Stopwatch{
private:
	unsigned int start;
public:
	Stopwatch() : start(clock()){};
	void printTimePast(){
		cout << (clock() - start) / (double)CLOCKS_PER_SEC << " seconds past." << endl;
	}
};