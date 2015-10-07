/**
	Project - File System Scanner
	Copyright (c) 2015 Poturaev A.S.
	e-mail: a.s.poturaev@gmail.com
*/

#include "stdafx.h"
#include "MappedFileReadOnly.h"

namespace FileSystemScanner { namespace Core { namespace Details {

	MappedFileReadOnly::MappedFileReadOnly(boost::filesystem::path const& filePath)
		: MappedFileBase<>(filePath.string(), boost::interprocess::read_only)
	{
	}

	MappedFileReadOnly::MappedFileReadOnly(std::string const& filePath)
		: MappedFileBase<>(filePath, boost::interprocess::read_only)
	{
	}

}}} /// end namespace FileSystemScanner::Core::Details
