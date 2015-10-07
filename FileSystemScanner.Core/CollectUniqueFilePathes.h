/**
	Project - File System Scanner
	Copyright (c) 2015 Poturaev A.S.
	e-mail: a.s.poturaev@gmail.com
*/

#pragma once

#if !defined(FILESYSTEMS_SCANNER_CORE_COLLECT_UNIQUEFILE_PATHES_H)
#	define FILESYSTEMS_SCANNER_CORE_COLLECT_UNIQUEFILE_PATHES_H

#include "IScanerProtocol.h"

#include <boost/unordered_set.hpp>

namespace FileSystemScanner { namespace Core { namespace Details {

	typedef boost::unordered_set<boost::filesystem::path> UniquePathStore_t;

	struct CollectUniqueFilePathes
	{
		static UniquePathStore_t Call(IScanerProtocol::InputPathStore_t const& pathStore);
	};

}}} /// end namespace FileSystemScanner::Core::Details

#endif /// !FILESYSTEMS_SCANNER_CORE_COLLECT_UNIQUEFILE_PATHES_H