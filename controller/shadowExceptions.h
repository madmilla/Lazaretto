#ifndef shadowExceptions_H
#define shadowExceptions_H

#include <string>
#include <iostream>
#include "shadow_lighting.h"
	// File: shadowExceptions.h
	// @Author Lars Veenendaal 1633223
	// 0.1 - Skeleton setup

class ShadowExceptions {
private:
	std::string m_strError;
	ShadowExceptions() {}; // not meant to be called
public:
	ShadowExceptions(std::string strError) : m_strError(strError)
	{
		if (strError == "SHADOW"){

			std::cout << "SHADOW" << std::endl;
		}
		if (strError == "OVEREXPOSED"){
			std::cout << "OVEREXPOSED" << std::endl;
		}
		if (strError == "NOTHING"){
			std::cout << "NOTHING" << std::endl;
		}
	}

	std::string GetError() { return m_strError; }
};

#endif