/**
	Project - File System Scanner
	Copyright (c) 2015 Poturaev A.S.
	e-mail: a.s.poturaev@gmail.com
*/

#include "stdafx.h"
#include "CollectUniqueFilePathes.h"

#include <boost/filesystem/operations.hpp>

namespace FileSystemScanner { namespace Core { namespace Details {

	UniquePathStore_t CollectUniqueFilePathes::Call(InputPathStore_t const& pathStore)
	{
		assert(!pathStore.empty());

		UniquePathStore_t uniquePathStore;

		for (auto const& path : pathStore)
		{
			assert(!path.empty());
			if (!path.empty() && boost::filesystem::exists(path) && !boost::filesystem::is_empty(path))
			{
				if (boost::filesystem::is_directory(path))
				{
					for (boost::filesystem::recursive_directory_iterator rdi(path); rdi != boost::filesystem::recursive_directory_iterator(); ++rdi)
					{
						auto const& currentPath = rdi->path();
						if (boost::filesystem::is_regular_file(currentPath))
							uniquePathStore.insert(currentPath);
					}
				}
				else if (boost::filesystem::is_regular_file(path))
				{
					uniquePathStore.insert(path);
				}
				else
				{
					assert(!"unknown logic (((");
				}
			}
		}

		return uniquePathStore;
	}

}}} /// end namespace FileSystemScanner::Core::Details
