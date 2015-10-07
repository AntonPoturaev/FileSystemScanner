/**
	Project - File System Scanner
	Copyright (c) 2015 Poturaev A.S.
	e-mail: a.s.poturaev@gmail.com
*/

#include "stdafx.h"
#include "SignatureStore.h"

namespace FileSystemScanner { namespace Core {

	SignatureStore::SignatureStore(Details::SignatureStoreStorage_t&& storage)
		: Details::SignatureStoreStorage_t(std::forward<Details::SignatureStoreStorage_t>(storage))
	{
	}

}} /// end namespace FileSystemScanner::Core
