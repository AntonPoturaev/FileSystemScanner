/**
	Project - File System Scanner
	Copyright (c) 2015 Poturaev A.S.
	e-mail: a.s.poturaev@gmail.com
*/

#pragma once

#if !defined(FILESYSTEMS_SCANNER_CORE_SIGNATURE_STORE_PARSER_H)
#	define FILESYSTEMS_SCANNER_CORE_SIGNATURE_STORE_PARSER_H

#include "SignatureStore.h"

namespace FileSystemScanner { namespace Core { namespace Details {

	struct SignatureStoreParser
	{
		static bool Call(InputByteRange_t const& inputRange, SignatureStoreStorage_t& sigStore, bool needCheckLastParserPosition = true);
	};

}}} /// end namespace FileSystemScanner::Core::Details

#endif /// !FILESYSTEMS_SCANNER_CORE_SIGNATURE_STORE_PARSER_H
