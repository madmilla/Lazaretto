#ifndef localizationExceptions_H
#define localizationExceptions_H

#include <string>
#include <iostream>

	// File: localizationExceptions.h
	// @Author Lars Veenendaal 1633223
	// 0.1 - Skeleton setup

class LocalizationExceptions{
private:
	std::string m_strError;
	LocalizationExceptions() {}; // not meant to be called
public:
	LocalizationExceptions(std::string strError) : m_strError(strError)
	{
		// None yet.
	}

	std::string GetError() { return m_strError; }
};

#endif