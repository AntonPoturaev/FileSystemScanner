/**
	Project - File System Scanner
	Copyright (c) 2015 Poturaev A.S.
	e-mail: a.s.poturaev@gmail.com
*/

#pragma once

#if !defined(FILESYSTEMS_SCANNER_CORE_MAPPED_FILE_BASE_H)
#	define FILESYSTEMS_SCANNER_CORE_MAPPED_FILE_BASE_H

#include "Bytes.h"

#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>

namespace FileSystemScanner { namespace Core { namespace Details {

	template <typename DataConstPointerT = RawConstByteData_t, typename DataRangeT = boost::iterator_range<DataConstPointerT>>
	class MappedFileBase
	{
	public:
		typedef DataConstPointerT DataConstPointer_t;
		typedef DataRangeT DataRange_t;

	public:
		DataConstPointer_t GetData() const {
			return static_cast<DataConstPointer_t>(m_Region.get_address());
		}

		size_t GetDataSize() const {
			return m_Region.get_size();
		}

		DataRange_t GetRange() const
		{
			ByteConstPtr_t const data(GetData());
			return boost::make_iterator_range(data, data + GetDataSize());
		}

	protected:
		MappedFileBase(std::string const& filePath, boost::interprocess::mode_t mode)
			: m_Mapping(filePath.c_str(), mode)
			, m_Region(m_Mapping, mode)
		{
		}

	protected:
		boost::interprocess::file_mapping const m_Mapping;
		boost::interprocess::mapped_region const m_Region;
	};

}}} /// end namespace FileSystemScanner::Core::Details

#endif /// !FILESYSTEMS_SCANNER_CORE_MAPPED_FILE_BASE_H