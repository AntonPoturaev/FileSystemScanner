/**
	Project - File System Scanner
	Copyright (c) 2015 Poturaev A.S.
	e-mail: a.s.poturaev@gmail.com
*/

#include "stdafx.h"
#include "IScanner.h"

#include <boost/algorithm/searching/boyer_moore_horspool.hpp>

namespace FileSystemScanner { namespace Core { namespace Details {

	class BoyerMooreHorsepoolScanner
		: public IScanner
	{
	public:
		BoyerMooreHorsepoolScanner(size_t poolSize);

	protected:
		virtual FindAlgorithm_t _GetFindAlgorithmInstance() const override;
	};

	BoyerMooreHorsepoolScanner::BoyerMooreHorsepoolScanner(size_t poolSize)
		: IScanner(poolSize)
	{
	}

	IScanner::FindAlgorithm_t BoyerMooreHorsepoolScanner::_GetFindAlgorithmInstance() const
	{
		return [](InputByteRange_t const& input, ByteString_t const& pattern) {
			return boost::algorithm::boyer_moore_horspool_search(input.begin(), input.end(), pattern.begin(), pattern.end()) != input.end();
		};
	}

	IScannerPtr_t _Factory_BoyerMooreHorsepoolScanner(size_t poolSize) {
		return IScannerPtr_t(new BoyerMooreHorsepoolScanner(poolSize));
	}

}}} /// end namespace FileSystemScanner::Core::Details

