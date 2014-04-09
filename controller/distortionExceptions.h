#ifndef distortExceptions_H
#define distortExceptions_H

#include <string>
#include <iostream>

	// File: distortionExceptions.h
	// @Author Lars Veenendaal 1633223
	// 0.1 - Skeleton setup

class DistortExceptions{
private:
	std::string m_strError;
	DistortExceptions() {}; // not meant to be called
public:
	DistortExceptions(std::string strError) : m_strError(strError)
	{
		// None yet.
	}

	std::string GetError() { return m_strError; }
};

#endif