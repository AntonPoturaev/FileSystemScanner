/**
	Project - File System Scanner
	Copyright (c) 2015 Poturaev A.S.
	e-mail: a.s.poturaev@gmail.com
*/

#include "stdafx.h"
#include "IScanner.h"

#include <boost/algorithm/searching/knuth_morris_pratt.hpp>

namespace FileSystemScanner { namespace Core { namespace Details {

	class KnutMorrisPrattScanner
		: public IScanner
	{
	public:
		KnutMorrisPrattScanner(size_t poolSize);

	protected:
		virtual FindAlgorithm_t _GetFindAlgorithmInstance() const override;
	};

	KnutMorrisPrattScanner::KnutMorrisPrattScanner(size_t poolSize)
		: IScanner(poolSize)
	{
	}

	IScanner::FindAlgorithm_t KnutMorrisPrattScanner::_GetFindAlgorithmInstance() const
	{
		return [](InputByteRange_t const& input, ByteString_t const& pattern) {
			return boost::algorithm::knuth_morris_pratt_search(input.begin(), input.end(), pattern.begin(), pattern.end()) != input.end();
		};
	}

	IScannerPtr_t _Factory_KnutMorrisPrattScanner(size_t poolSize) {
		return IScannerPtr_t(new KnutMorrisPrattScanner(poolSize));
	}

}}} /// end namespace FileSystemScanner::Core::Details
