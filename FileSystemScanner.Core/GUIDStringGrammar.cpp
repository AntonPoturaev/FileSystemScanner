/**
	Project - File System Scanner
	Copyright (c) 2015 Poturaev A.S.
	e-mail: a.s.poturaev@gmail.com
*/

#include "stdafx.h"
#include "GUIDStringGrammar.h"

namespace FileSystemScanner { namespace Core { namespace Details {

	using boost::spirit::qi::char_;

	GUIDStringGrammar::GUIDStringGrammar()
		: base_type(m_Start)
		, m_HexDigit(char_("0-9a-fA-F"))
	{
		m_Start = char_('{')
			>> m_HexDigit >> m_HexDigit >> m_HexDigit >> m_HexDigit >> m_HexDigit >> m_HexDigit >> m_HexDigit >> m_HexDigit
			>> char_('-') >> m_HexDigit >> m_HexDigit >> m_HexDigit >> m_HexDigit
			>> char_('-') >> m_HexDigit >> m_HexDigit >> m_HexDigit >> m_HexDigit
			>> char_('-') >> m_HexDigit >> m_HexDigit >> m_HexDigit >> m_HexDigit
			>> char_('-') >> m_HexDigit >> m_HexDigit >> m_HexDigit >> m_HexDigit >> m_HexDigit >> m_HexDigit >> m_HexDigit >> m_HexDigit >> m_HexDigit >> m_HexDigit >> m_HexDigit >> m_HexDigit
			>> char_('}')
		;
	}

}}} /// end namespace FileSystemScanner::Core::Details
