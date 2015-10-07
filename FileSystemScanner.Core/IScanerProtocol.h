/**
	Project - File System Scanner
	Copyright (c) 2015 Poturaev A.S.
	e-mail: a.s.poturaev@gmail.com
*/

#pragma once

#if !defined(FILESYSTEMS_SCANNER_CORE_ISCANNER_PROTOCOL_H)
#	define FILESYSTEMS_SCANNER_CORE_ISCANNER_PROTOCOL_H

#include "Bytes.h"

#include <boost/filesystem/path.hpp>
#include <boost/unordered_map.hpp>

namespace FileSystemScanner { namespace Core {
	
	struct IScanerProtocol
	{
	public:
		typedef std::vector<boost::filesystem::path> InputPathStore_t;
		typedef std::shared_ptr<InputPathStore_t> InputPathStorePtr_t;

		typedef boost::iterator_range<ByteConstPtr_t> ByteDataRange_t;
		typedef boost::unordered_map<
			std::string /// name (id) for data range
			, ByteDataRange_t /// data range
		> ByteDataRangeStore_t;
		typedef std::shared_ptr<ByteDataRangeStore_t> ByteDataRangeStorePtr_t;

	public:
		virtual void ScanAsync(boost::filesystem::path const& signatureStorePath, InputPathStorePtr_t const& pathStore) = 0;
		virtual void ScanAsync(boost::filesystem::path const& signatureStorePath, ByteDataRangeStorePtr_t const& dataRangesStore) = 0;
		virtual void AbortScan() = 0;
		virtual bool IsFree() const = 0;
	};

}} /// end namespace FileSystemScanner::Core

#endif /// !FILESYSTEMS_SCANNER_CORE_ISCANNER_PROTOCOL_H