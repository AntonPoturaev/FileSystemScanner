/**
	Project - File System Scanner
	Copyright (c) 2015 Poturaev A.S.
	e-mail: a.s.poturaev@gmail.com
*/

#pragma once

#if !defined(FILESYSTEMS_SCANNER_CORE_BYTES_H)
#	define FILESYSTEMS_SCANNER_CORE_BYTES_H

#include <string>
#include <boost/range/iterator_range_core.hpp>

namespace FileSystemScanner {

	typedef unsigned char Byte_t;
	typedef Byte_t const* ByteConstPtr_t;
	typedef ByteConstPtr_t RawConstByteData_t;
	typedef std::basic_string<Byte_t> ByteString_t;

	namespace Core {
		typedef boost::iterator_range<ByteConstPtr_t> InputByteRange_t;
	} /// end namespace Core

} /// end namespace FileSystemScanner

#endif /// !FILESYSTEMS_SCANNER_CORE_BYTES_H
