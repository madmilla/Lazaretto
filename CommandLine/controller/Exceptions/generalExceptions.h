#ifndef generalExceptions_H
#define generalExceptions_H

#include <string>
#include <iostream>

	// File: generalExceptions.h
	// @Author Lars Veenendaal 1633223
	// 0.1 - Skeleton setup

class GeneralExceptions{
private:
	std::string m_strError;
	GeneralExceptions() {}; // not meant to be called
public:
	GeneralExceptions(std::string strError) : m_strError(strError)
	{
		// Still pending instructions for how to handle errors.
		if (strError == "IMAGE_NOT_FOUND"){
			std::cout << "IMAGE_NOT_FOUND" << std::endl;
		}
		if (strError == "IMAGE_FILETYPE_NOT_ALLOWED"){
			std::cout << "IMAGE_FILETYPE_NOT_ALLOWED" << std::endl;
		}
		if (strError == "IMAGE_RESOLUTION_TOO_SMALL"){
			std::cout << "IMAGE_RESOLUTION_TOO_SMALL" << std::endl;
		}
	}

	std::string GetError() { return m_strError; }
};

#endif