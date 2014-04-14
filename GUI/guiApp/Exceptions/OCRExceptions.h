#ifndef OCRExceptions_H
#define OCRExceptions_H

#include <string>
#include <iostream>

	// File: OCRExceptions.h
	// @Author Lars Veenendaal 1633223
	// 0.1 - Skeleton setup

class OCRExceptions{
private:
	std::string m_strError;
	OCRExceptions() {}; // not meant to be called
public:
	OCRExceptions(std::string strError) : m_strError(strError)
	{
		// None yet.
	}

	std::string GetError() { return m_strError; }
};

#endif