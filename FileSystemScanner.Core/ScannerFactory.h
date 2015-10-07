/**
	Project - File System Scanner
	Copyright (c) 2015 Poturaev A.S.
	e-mail: a.s.poturaev@gmail.com
*/

#pragma once

#if !defined(FILESYSTEMS_SCANNER_CORE_SCANNER_FACTORY_H)
#	define FILESYSTEMS_SCANNER_CORE_SCANNER_FACTORY_H

#include "IScanner.h"

#include <mutex>

#include <boost/unordered_map.hpp>

namespace FileSystemScanner { namespace Core {

	class ScannerFactory
	{
	public:
		typedef std::vector<std::string> ScannerNames_t;
		typedef std::function<IScannerPtr_t(size_t poolSize)> FactoryMathod_t;

	private:
		typedef boost::unordered_map<std::string, FactoryMathod_t> Store_t;

	public:
		ScannerFactory();

		size_t GetCount() const;
		ScannerNames_t GetRegistredScannerNames() const;
		
		void RegisterScanner(std::string const& name, FactoryMathod_t const& factory);
		void UnRegisterScanner(std::string const& name);

		IScannerPtr_t CreateScanner(std::string const& name, size_t poolSize) const;

	private:
		Store_t m_Store;
		std::mutex mutable m_Access;
	};

}} /// end namespace FileSystemScanner::Core

#endif /// !FILESYSTEMS_SCANNER_CORE_SCANNER_FACTORY_H
