/**
	Project - File System Scanner
	Copyright (c) 2015 Poturaev A.S.
	e-mail: a.s.poturaev@gmail.com
*/

#pragma once

#if !defined(FILESYSTEMS_SCANNER_CORE_HEXEDECIMAL_STRING_GRAMMAR_H)
#	define FILESYSTEMS_SCANNER_CORE_HEXEDECIMAL_STRING_GRAMMAR_H

#include "Bytes.h"

#include <boost/spirit/include/qi.hpp>

namespace FileSystemScanner { namespace Core { namespace Details {

	class HexadecimalStringGrammar
		: public boost::spirit::qi::grammar<RawConstByteData_t, ByteString_t()>
	{
		typedef boost::spirit::qi::rule<iterator_type, Byte_t()> HexDigitRule_t;
		typedef boost::spirit::qi::uint_parser<Byte_t, 16, 1, 1> Hex1DigitParser_t;

	public:
		HexadecimalStringGrammar();

	private:
		HexDigitRule_t const m_Hex1Digit;
		HexDigitRule_t m_HexDigit;
		start_type m_Start;
	};

}}} /// end namespace FileSystemScanner::Core::Details

#endif /// !FILESYSTEMS_SCANNER_CORE_HEXEDECIMAL_STRING_GRAMMAR_H
