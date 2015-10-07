/**
	Project - File System Scanner
	Copyright (c) 2015 Poturaev A.S.
	e-mail: a.s.poturaev@gmail.com
*/
#include "stdafx.h"
#include "Exception.h"

namespace FileSystemScanner { namespace Core {

	Exception::Exception(std::string const& message, State state)
		: std::runtime_error(message)
		, m_State(state)
	{
	}

	Exception::State Exception::GetState() const {
		return m_State;
	}

	void ThrowException(std::string const& message) {
		throw Exception(message, Exception::State::kEScritical);
	}

	void ThrowWarning(std::string const& message) {
		throw Exception(message, Exception::State::kESwarning);
	}

}} /// end namespace FileSystemScanner::Core