#include "FileData.h"

FileData * FileData::_FileData = NULL;

FileData::FileData() { }
FileData::~FileData() { }

void FileData::Initialize(const std::string & FilePath) {
	_FilePath = FilePath;

	_FileName = FilePath.substr(0, FilePath.find_last_of('.'));

	if (_FileName.find('/') != std::string::npos)
		_FileName = _FileName.substr(_FileName.find_last_of('/') + 1);
	else if (_FileName.find('\\') != std::string::npos)
		_FileName = _FileName.substr(_FileName.find_last_of('\\') + 1);

	_FileExtension = FilePath.substr(FilePath.find_last_of('.'));
}

FileData * FileData::GetInstance() {
	if (_FileData == NULL)
		_FileData = new FileData();
	return _FileData;
}