/**
	Project - File System Scanner
	Copyright (c) 2015 Poturaev A.S.
	e-mail: a.s.poturaev@gmail.com
*/

#include "stdafx.h"
#include "SignatureStoreParser.h"
#include "SignatureStoreGrammar.h"

namespace FileSystemScanner { namespace Core { namespace Details {

	namespace {
		bool _Call(RawConstByteData_t first, RawConstByteData_t last, SignatureStoreStorage_t& sigStore, bool needCheckLastParserPosition)
		{
			bool const parseResult = boost::spirit::qi::phrase_parse(first, last, SignatureStoreGrammar(), boost::spirit::qi::ascii::space, sigStore);
			return parseResult && (needCheckLastParserPosition ? first == last : true);
		}
	} /// end unnamed namespace

	bool SignatureStoreParser::Call(InputByteRange_t const& inputRange, SignatureStoreStorage_t& sigStore, bool needCheckLastParserPosition) {
		return _Call(inputRange.begin(), inputRange.end(), sigStore, needCheckLastParserPosition);
	}

}}} /// end namespace FileSystemScanner::Core::Details
