/**
	Project - File System Scanner
	Copyright (c) 2015 Poturaev A.S.
	e-mail: a.s.poturaev@gmail.com
*/

#include "stdafx.h"
#include "SignatureStoreGrammar.h"

#include <boost/fusion/adapted/struct.hpp>
#include <boost/spirit/include/qi_eol.hpp>
#include <boost/spirit/include/qi_eoi.hpp>

BOOST_FUSION_ADAPT_STRUCT(FileSystemScanner::Core::Signature, (FileSystemScanner::ByteString_t, value) (FileSystemScanner::ByteString_t, guid));

namespace FileSystemScanner { namespace Core { namespace Details {

	SignatureStoreGrammar::SignatureStoreGrammar()
		: base_type(m_Start)
	{
		using boost::spirit::qi::eol;
		using boost::spirit::qi::eoi;

		m_Start = +(m_Signature >> '.' >> m_GUID >> eol) >> -eoi;
	}

}}} /// end namespace FileSystemScanner::Core::Details
