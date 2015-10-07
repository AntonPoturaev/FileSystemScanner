/**
	Project - File System Scanner
	Copyright (c) 2015 Poturaev A.S.
	e-mail: a.s.poturaev@gmail.com
*/

#pragma once

#if !defined(FILESYSTEMS_SCANNER_CORE_MAPPED_FILE_READONLY_H)
#	define FILESYSTEMS_SCANNER_CORE_MAPPED_FILE_READONLY_H

#include "MappedFileBase.h"

#include <boost/filesystem/path.hpp>

namespace FileSystemScanner { namespace Core { namespace Details {

	class MappedFileReadOnly
		: public MappedFileBase<>
	{
	public:
		MappedFileReadOnly(boost::filesystem::path const& filePath);
		MappedFileReadOnly(std::string const& filePath);
	};

}}} /// end namespace FileSystemScanner::Core::Details

#endif /// !FILESYSTEMS_SCANNER_CORE_MAPPED_FILE_READONLY_H