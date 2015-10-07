/**
	Project - File System Scanner
	Copyright (c) 2015 Poturaev A.S.
	e-mail: a.s.poturaev@gmail.com
*/

#include "stdafx.h"
#include "IScanner.h"

namespace FileSystemScanner { namespace Core { namespace Details {
	
	class StdSearchScanner
		: public IScanner
	{
	public:
		StdSearchScanner(size_t poolSize);

	protected:
		virtual FindAlgorithm_t _GetFindAlgorithmInstance() const override;
	};

	StdSearchScanner::StdSearchScanner(size_t poolSize)
		: IScanner(poolSize)
	{
	}

	IScanner::FindAlgorithm_t StdSearchScanner::_GetFindAlgorithmInstance() const
	{
		return [](InputByteRange_t const& input, ByteString_t const& pattern) {
			return std::search(input.begin(), input.end(), pattern.begin(), pattern.end()) != input.end();
		};
	}

	IScannerPtr_t _Factory_StdSearchScanner(size_t poolSize) {
		return IScannerPtr_t(new StdSearchScanner(poolSize));
	}

}}} /// end namespace FileSystemScanner::Core::Details
