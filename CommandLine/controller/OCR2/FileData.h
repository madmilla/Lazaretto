#pragma once
#include <string>

// Temporary class, wont be used in final application

class FileData {
public:
	void Initialize(const std::string & FilePath);

	std::string GetFilePath() { return _FilePath; }
	std::string GetFileName() { return _FileName; }
	std::string GetFileExtension() { return _FileExtension; }

	static FileData * GetInstance();

private:
	FileData();
	~FileData();

	static FileData * _FileData;

	std::string _FilePath;
	std::string _FileName;
	std::string _FileExtension;
};

