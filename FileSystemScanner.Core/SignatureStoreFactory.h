/**
	Project - File System Scanner
	Copyright (c) 2015 Poturaev A.S.
	e-mail: a.s.poturaev@gmail.com
*/

#pragma once

#if !defined(FILESYSTEMS_SCANNER_CORE_SIGNATURE_FACTORY_H)
#	define FILESYSTEMS_SCANNER_CORE_SIGNATURE_FACTORY_H

#include "SignatureStore.h"

#include <boost/filesystem/path.hpp>

namespace FileSystemScanner { namespace Core {

	class SignatureStoreFactory
	{
	public:
		static SignatureStorePtr_t Create(InputByteRange_t const& inputRange, bool needCheckLastParserPosition = true);
		static SignatureStorePtr_t Create(boost::filesystem::path const& filePath, bool needCheckLastParserPosition = true);

	private:
		static SignatureStorePtr_t _Create(InputByteRange_t const& inputRange, bool needCheckLastParserPosition);
	};

}} /// end namespace FileSystemScanner::Core

#endif /// !FILESYSTEMS_SCANNER_CORE_SIGNATURE_FACTORY_H
