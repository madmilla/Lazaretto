/*
## Author : Daan Joling 1617085 
*/

#include "stopwatch.h"
#include <string.h>

stopwatch::stopwatch()
{
	unsigned int start = clock();
}

stopwatch::~stopwatch(){}

string stopwatch::printTimePast(){
	string time = msclr::interop::marshal_as< string >((clock() - start) / (double)CLOCKS_PER_SEC/10  + "sec past");
	return time;
}
