/**
	Project - File System Scanner
	Copyright (c) 2015 Poturaev A.S.
	e-mail: a.s.poturaev@gmail.com
*/

#include "stdafx.h"
#include "ScannerFactory.h"
#include "Exception.h"

namespace FileSystemScanner { namespace Core {

	
	namespace Details {
		extern IScannerPtr_t _Factory_BoyerMooreScanner(size_t poolSize);
		extern IScannerPtr_t _Factory_BoyerMooreHorsepoolScanner(size_t poolSize);
		extern IScannerPtr_t _Factory_KnutMorrisPrattScanner(size_t poolSize);
		extern IScannerPtr_t _Factory_StdSearchScanner(size_t poolSize);
	} /// end namespace Details

	namespace {
		typedef std::lock_guard<std::mutex> const _Lock;
	} /// end unnamed namespace 

	ScannerFactory::ScannerFactory()
	{
		_Lock _(m_Access);

		m_Store["boyer_moore"] = &Details::_Factory_BoyerMooreScanner;
		m_Store["boyer_moore_horsepool"] = &Details::_Factory_BoyerMooreHorsepoolScanner;
		m_Store["knut_morris_pratt"] = &Details::_Factory_KnutMorrisPrattScanner;
		m_Store["std_search"] = &Details::_Factory_StdSearchScanner;
	}

	size_t ScannerFactory::GetCount() const 
	{
		_Lock _(m_Access);
		return m_Store.size();
	}
	
	ScannerFactory::ScannerNames_t ScannerFactory::GetRegistredScannerNames() const
	{
		_Lock _(m_Access);

		ScannerNames_t result;
		result.reserve(m_Store.size());

		for (auto const& node : m_Store)
			result.push_back(node.first);

		return result;
	}

	void ScannerFactory::RegisterScanner(std::string const& name, FactoryMathod_t const& factory)
	{
		if (name.empty() || !factory)
			ThrowWarning("Call FileSystemScanner::Core::ScannerFactory::RegisterScanner is failed. Reason: Bad params - empty scanner name of empty factory method");

		_Lock _(m_Access);

		m_Store[name] = factory;
	}

	void ScannerFactory::UnRegisterScanner(std::string const& name)
	{
		_Lock _(m_Access);
		m_Store.erase(name);
	}

	IScannerPtr_t ScannerFactory::CreateScanner(std::string const& name, size_t poolSize) const
	{
		_Lock _(m_Access);

		auto const found = m_Store.find(name);
		if (found != m_Store.end())
			return found->second(poolSize);

		return nullptr;
	}

}} /// end namespace FileSystemScanner::Core
