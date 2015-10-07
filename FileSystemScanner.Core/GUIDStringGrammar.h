/**
	Project - File System Scanner
	Copyright (c) 2015 Poturaev A.S.
	e-mail: a.s.poturaev@gmail.com
*/

#pragma once

#if !defined(FILESYSTEMS_SCANNER_CORE_GUID_STRING_GRAMMAR_H)
#	define FILESYSTEMS_SCANNER_CORE_GUID_STRING_GRAMMAR_H

#include "Bytes.h"

#include <boost/spirit/include/qi.hpp>

namespace FileSystemScanner { namespace Core { namespace Details {

	class GUIDStringGrammar
		: public boost::spirit::qi::grammar<RawConstByteData_t, ByteString_t()>
	{
		typedef boost::spirit::qi::rule<iterator_type, Byte_t()> DigitRule_t;

	public:
		GUIDStringGrammar();

	private:
		start_type m_Start;
		DigitRule_t const m_HexDigit;
	};

}}} /// end namespace FileSystemScanner::Core::Details

#endif /// !FILESYSTEMS_SCANNER_CORE_GUID_STRING_GRAMMAR_H
