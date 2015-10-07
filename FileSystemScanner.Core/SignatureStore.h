/**
	Project - File System Scanner
	Copyright (c) 2015 Poturaev A.S.
	e-mail: a.s.poturaev@gmail.com
*/

#pragma once

#if !defined(FILESYSTEMS_SCANNER_CORE_SIGNATURE_STORE_H)
#	define FILESYSTEMS_SCANNER_CORE_SIGNATURE_STORE_H

#include "Signature.h"

#include <memory>

#include <boost/unordered_set.hpp>

namespace FileSystemScanner { namespace Core {

	namespace Details {
		typedef boost::unordered_set<Signature> SignatureStoreStorage_t;
	} /// end namespace Details

	class SignatureStoreFactory;

	class SignatureStore
		: public Details::SignatureStoreStorage_t
	{
		friend class SignatureStoreFactory;

	private:
		SignatureStore(Details::SignatureStoreStorage_t&& storage);
	};

	typedef std::shared_ptr<SignatureStore> SignatureStorePtr_t;

}} /// end namespace FileSystemScanner::Core

#endif /// !FILESYSTEMS_SCANNER_CORE_SIGNATURE_STORE_H
