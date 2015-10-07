/**
	Project - File System Scanner
	Copyright (c) 2015 Poturaev A.S.
	e-mail: a.s.poturaev@gmail.com
*/

#pragma once

#include <Bytes.h>

#include <boost/spirit/include/qi.hpp>

namespace {

	using namespace FileSystemScanner;
	using namespace FileSystemScanner::Core;

	template <typename Iterator, typename Grammar, typename Attribute>
	bool _Call_phrase_parse_with_attr(Iterator first, Iterator last, Grammar const& grammar, Attribute& attribute, bool fullMatch = true) {
		return  (boost::spirit::qi::phrase_parse(first, last, grammar, boost::spirit::qi::ascii::space, attribute) && (!fullMatch || (first == last)));
	}

	template<typename Ptr>
	ByteConstPtr_t ToByteConstPtr(Ptr ptr) {
		return reinterpret_cast<ByteConstPtr_t>(ptr);
	}

	template<typename Grammar, typename Attribute>
	bool TestGrammar(std::string const& input, Grammar const& grammar, Attribute& attribute, bool fullMatch = true) {
		return _Call_phrase_parse_with_attr(ToByteConstPtr(input.data()), ToByteConstPtr(input.data() + input.size()), grammar, attribute, fullMatch);
	}

} /// end unnamed namespace

#define BOOST_TEST_MODULE FFSCUT_SignatureParserUnitTests
#include <boost/test/included/unit_test.hpp>

#include <HexadecimalStringGrammar.h>

using namespace FileSystemScanner::Core::Details;

BOOST_AUTO_TEST_CASE(HexStringGrammar_test)
{
	HexadecimalStringGrammar const grammar;
	std::string pattern("");
	ByteString_t attribute;

	BOOST_TEST((TestGrammar(pattern, grammar, attribute) == false && attribute.empty()), L"Empty input string test");

	pattern = " /";
	BOOST_TEST(TestGrammar(pattern, grammar, attribute) == false, L"Incorrect input string test");

	pattern = "e"; attribute.clear();
	BOOST_TEST((TestGrammar(pattern, grammar, attribute) && attribute.size() == 1 && attribute[0] == 0xe0), L"One digit input string test");

	pattern = "ea"; attribute.clear();
	BOOST_TEST((TestGrammar(pattern, grammar, attribute) && attribute.size() == 1 && attribute[0] == 0xea), L"Two digit input string test");

	pattern = "eaf"; attribute.clear();
	BOOST_TEST((TestGrammar(pattern, grammar, attribute, false) && attribute.size() == 2 && attribute[0] == 0xea && attribute[1] == 0xf0), L"Three digit input string test");
}

#include <GUIDStringGrammar.h>

namespace {

	bool _GuidStr_Test(std::string const& pattern, bool needCmp = true) 
	{
		GUIDStringGrammar const grammar;
		ByteString_t attribute;
		bool const result = TestGrammar(pattern, grammar, attribute);
		std::string const view(attribute.begin(), attribute.end());
		if (needCmp)
		{
			bool const compareResult = pattern == view;
			return compareResult;
		}

		return result;
	}

} /// end unnamed namespace

BOOST_AUTO_TEST_CASE(GUIDStringGrammar_test)
{
	BOOST_TEST(_GuidStr_Test("", false) == false, "Empty string test");
	BOOST_TEST(_GuidStr_Test("{5c34b10f-3f6d-4bbb-b9ec-2faa1ee07660}"), "Correct test");
	BOOST_TEST(_GuidStr_Test("{5c34b10f-3f6d-4Yfb-b9ec-2faa1ee07660}") == false, "Incorrect test");
}

#include <SignatureStoreGrammar.h>

BOOST_AUTO_TEST_CASE(SigStoreGrammar_test)
{
	S
}

//#include <SignatureStoreParser.h>

