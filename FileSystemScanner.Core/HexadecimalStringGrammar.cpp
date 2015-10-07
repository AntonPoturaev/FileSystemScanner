/**
	Project - File System Scanner
	Copyright (c) 2015 Poturaev A.S.
	e-mail: a.s.poturaev@gmail.com
*/

#include "stdafx.h"
#include "HexadecimalStringGrammar.h"

#include <boost/spirit/include/phoenix.hpp>

namespace FileSystemScanner { namespace Core { namespace Details {

	HexadecimalStringGrammar::HexadecimalStringGrammar()
		: base_type(m_Start)
		, m_Hex1Digit(Hex1DigitParser_t())
	{
		using boost::phoenix::at;
		using boost::spirit::qi::_1;
		using boost::spirit::qi::_val;
		using boost::spirit::qi::repeat;

		m_HexDigit = repeat(2)[m_Hex1Digit][_val = at(_1, 0) << 4 | at(_1, 1)] | m_Hex1Digit[_val = _1 << 4];

		m_Start = +m_HexDigit;
	}

}}} /// end namespace FileSystemScanner::Core::Details
