/**
	Project - File System Scanner
	Copyright (c) 2015 Poturaev A.S.
	e-mail: a.s.poturaev@gmail.com
*/

#include "stdafx.h"
#include "IScanner.h"

#include <boost/algorithm/searching/boyer_moore.hpp>

namespace FileSystemScanner { namespace Core { namespace Details {

	class BoyerMooreScanner
		: public IScanner
	{
	public:
		BoyerMooreScanner(size_t poolSize);

	protected:
		virtual FindAlgorithm_t _GetFindAlgorithmInstance() const override;
	};

	BoyerMooreScanner::BoyerMooreScanner(size_t poolSize)
		: IScanner(poolSize)
	{
	}

	IScanner::FindAlgorithm_t BoyerMooreScanner::_GetFindAlgorithmInstance() const
	{
		return [](InputByteRange_t const& input, ByteString_t const& pattern) {
			return boost::algorithm::boyer_moore_search(input.begin(), input.end(), pattern.begin(), pattern.end()) != input.end();
		};
	}

	IScannerPtr_t _Factory_BoyerMooreScanner(size_t poolSize) {
		return IScannerPtr_t(new BoyerMooreScanner(poolSize));
	}

}}} /// end namespace FileSystemScanner::Core::Details
