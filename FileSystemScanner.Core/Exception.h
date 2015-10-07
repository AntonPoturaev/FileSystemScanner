/**
	Project - File System Scanner
	Copyright (c) 2015 Poturaev A.S.
	e-mail: a.s.poturaev@gmail.com
*/

#pragma once

#if !defined(FILESYSTEMS_SCANNER_CORE_EXCEPTION_H)
#	define FILESYSTEMS_SCANNER_CORE_EXCEPTION_H

#include <stdexcept>

namespace FileSystemScanner { namespace Core {

	struct Exception
		: public std::runtime_error
	{
	public:
		enum class State
		{
			kEScritical
			, kESwarning
			/// etc...
		};

	public:
		Exception(std::string const& message, State state = State::kEScritical);

		State GetState() const;

	protected:
		State m_State;
	};

	void ThrowException(std::string const& message);
	void ThrowWarning(std::string const& message);

}} /// end namespace FileSystemScanner::Core

#endif /// !FILESYSTEMS_SCANNER_CORE_EXCEPTION_H
