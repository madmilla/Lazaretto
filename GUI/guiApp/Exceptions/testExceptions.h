#ifndef testExceptions_H
#define testExceptions_H

#include <string>
#include <iostream>

	// File: testExceptions.h
	// @Author Lars Veenendaal 1633223
	// 0.1 - Skeleton setup

	// Used for testing purposes
	// Primarily on how to handle scenarios/exceptions.

class testExceptions{
private:
	std::string m_strError;
	testExceptions() {}; // not meant to be called
public:
	testExceptions(std::string strError) : m_strError(strError)
	{
		// None yet.
	}

	std::string GetError() { return m_strError; }
};

#endif