/**
	Project - File System Scanner
	Copyright (c) 2015 Poturaev A.S.
	e-mail: a.s.poturaev@gmail.com
*/

#pragma once

#if !defined(FILESYSTEMS_SCANNER_CORE_SIGNATURE_H)
#	define FILESYSTEMS_SCANNER_CORE_SIGNATURE_H

#include "Bytes.h"

namespace FileSystemScanner { namespace Core {

	struct Signature
	{
	public:
		bool Equal(Signature const& other) const;

	public:
		ByteString_t value;
		ByteString_t guid;
	};

	bool operator == (Signature const& l, Signature const& r);

}} /// end namespace FileSystemScanner::Core

#include <boost/functional/hash.hpp>

namespace boost {
	size_t hash_value(FileSystemScanner::Core::Signature const& sig);
} /// end namespace boost

#endif /// !FILESYSTEMS_SCANNER_CORE_SIGNATURE_H
