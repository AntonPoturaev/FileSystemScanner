/**
	Project - File System Scanner
	Copyright (c) 2015 Poturaev A.S.
	e-mail: a.s.poturaev@gmail.com
*/

#pragma once

#if !defined(FILESYSTEMS_SCANNER_CORE_ISCANNER_FWD_H)
#	define FILESYSTEMS_SCANNER_CORE_ISCANNER_FWD_H

#include <memory>

namespace FileSystemScanner { namespace Core {

	class IScanner;
	typedef std::shared_ptr<IScanner> IScannerPtr_t;

}} /// end namespace FileSystemScanner::Core

#endif /// !FILESYSTEMS_SCANNER_CORE_ISCANNER_FWD_H