#pragma once
class Extensions
{
public:

	//template function to calculate percentage with different arithmetic types
	template< typename T, typename N>
	static int getPercentage(T part, N total){
		return (int)(std::round((double)part / (double)total * 100));
	}

	//template function to get value from percentage with different arithmetic types
	template< typename T>
	static int getValueFromPercentage(T part, int percentage){
		return (int)(std::round((double)(part / 100.0 * percentage)));
	}

	//function to calculate value from -1 to 1 from percentage
	static double getWeightFromPercentage(int percentage){
		// 2 / 100 = 0.02
		return (0.02 * percentage) - 1;
	}
};

