/**
	Project - File System Scanner
	Copyright (c) 2015 Poturaev A.S.
	e-mail: a.s.poturaev@gmail.com
*/

#include "stdafx.h"
#include "SignatureStoreFactory.h"
#include "SignatureStoreParser.h"
#include "MappedFileReadOnly.h"

#include <boost/filesystem/operations.hpp>

namespace FileSystemScanner { namespace Core {

	SignatureStorePtr_t SignatureStoreFactory::Create(InputByteRange_t const& inputRange, bool needCheckLastParserPosition)
	{
		try {
			return _Create(inputRange, needCheckLastParserPosition);
		} catch (...) {
			return nullptr;
		}
	}

	SignatureStorePtr_t SignatureStoreFactory::Create(boost::filesystem::path const& filePath, bool needCheckLastParserPosition)
	{
		try
		{
			assert(!filePath.empty());
			if (!filePath.empty() && boost::filesystem::exists(filePath) && !boost::filesystem::is_empty(filePath) && boost::filesystem::is_regular_file(filePath))
			{
				Details::MappedFileReadOnly const mappedFileReadOnly(filePath);
				return _Create(mappedFileReadOnly.GetRange(), needCheckLastParserPosition);
			}

			return nullptr;
		}
		catch (...) {
			return nullptr;
		}
	}

	SignatureStorePtr_t SignatureStoreFactory::_Create(InputByteRange_t const& inputRange, bool needCheckLastParserPosition)
	{
		Details::SignatureStoreStorage_t storage;
		if (Details::SignatureStoreParser::Call(inputRange, storage, needCheckLastParserPosition))
			return SignatureStorePtr_t(new SignatureStore(std::move(storage)));

		return nullptr;
	}

}} /// end namespace FileSystemScanner::Core
