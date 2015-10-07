/**
	Project - File System Scanner
	Copyright (c) 2015 Poturaev A.S.
	e-mail: a.s.poturaev@gmail.com
*/

#pragma once

#if !defined(FILESYSTEMS_SCANNER_CORE_SIGNATURE_STORE_GRAMMAR_H)
#	define FILESYSTEMS_SCANNER_CORE_SIGNATURE_STORE_GRAMMAR_H

#include "SignatureStore.h"
#include "HexadecimalStringGrammar.h"
#include "GUIDStringGrammar.h"

namespace FileSystemScanner { namespace Core { namespace Details {

	class SignatureStoreGrammar
		: public boost::spirit::qi::grammar<RawConstByteData_t, SignatureStoreStorage_t()>
	{
	public:
		SignatureStoreGrammar();

	private:
		GUIDStringGrammar const m_GUID;
		HexadecimalStringGrammar const m_Signature;
		start_type m_Start;
	};

}}} /// end namespace FileSystemScanner::Core::Details

#endif /// !FILESYSTEMS_SCANNER_CORE_SIGNATURE_STORE_GRAMMAR_H
