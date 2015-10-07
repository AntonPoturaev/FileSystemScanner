/**
	Project - File System Scanner
	Copyright (c) 2015 Poturaev A.S.
	e-mail: a.s.poturaev@gmail.com
*/

#include "stdafx.h"
#include "Signature.h"

namespace FileSystemScanner { namespace Core {

	bool Signature::Equal(Signature const& other) const {
		return value == other.value;
	}

	bool operator == (Signature const& l, Signature const& r) {
		return l.Equal(r);
	}

}} /// !end namespace FileSystemScanner::Core

namespace boost {
	size_t hash_value(FileSystemScanner::Core::Signature const& sig) {
		return hash_value(sig.value);
	}
} /// end namespace boost
