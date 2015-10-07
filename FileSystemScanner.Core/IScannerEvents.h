/**
	Project - File System Scanner
	Copyright (c) 2015 Poturaev A.S.
	e-mail: a.s.poturaev@gmail.com
*/

#pragma once

#if !defined(FILESYSTEMS_SCANNER_CORE_ISCANNER_EVENTS_H)
#	define FILESYSTEMS_SCANNER_CORE_ISCANNER_EVENTS_H

#include "Bytes.h"
#include "Exception.h"

#include <boost/filesystem/path.hpp>
#include <boost/signals2.hpp>
#include <boost/variant.hpp>

namespace FileSystemScanner { namespace Core {

	struct IScannerEvents
	{
	public:
		typedef boost::signals2::signal<void()> OnInitializationStartSignal_t;
		typedef boost::signals2::signal<void()> OnInitializationEndSignal_t;
		typedef boost::signals2::signal<void(std::string message)> OnInitializationStepCompleteSignal_t;

		typedef boost::signals2::signal<void(size_t filesCount)> OnFilesCountReceivedSignal_t;
		typedef boost::signals2::signal<void(std::string reason, Exception::State state)> OnErrorSignal_t;

		typedef boost::signals2::signal<void()> OnScanProcessStartSignal_t;
		typedef boost::signals2::signal<void()> OnScanProcessEndSignal_t;

		typedef boost::signals2::signal<void()> OnScanProcessFileHasBeenViewedSignal_t;

		typedef boost::variant<
			boost::filesystem::path /// infected file path
			, std::string /// infected data range id
		> InfectedInfo_t;
		typedef boost::signals2::signal<void(InfectedInfo_t, ByteString_t)> OnScanProcessSignatureDetectedSignal_t;

	public:
		virtual boost::signals2::connection AttachOnInitializationStartSignal(OnInitializationStartSignal_t::slot_type&& slot) = 0;
		virtual boost::signals2::connection AttachOnInitializationEndSignal(OnInitializationEndSignal_t::slot_type&& slot) = 0;
		virtual boost::signals2::connection AttachOnInitializationStepCompleteSignal(OnInitializationStepCompleteSignal_t::slot_type&& slot) = 0;
		virtual boost::signals2::connection AttachOnFilesCountReceivedSignal(OnFilesCountReceivedSignal_t::slot_type&& slot) = 0;
		virtual boost::signals2::connection AttachOnErrorSignal(OnErrorSignal_t::slot_type&& slot) = 0;
		virtual boost::signals2::connection AttachOnScanProcessStartSignal(OnScanProcessStartSignal_t::slot_type&& slot) = 0;
		virtual boost::signals2::connection AttachOnScanProcessEndSignal(OnScanProcessEndSignal_t::slot_type&& slot) = 0;
		virtual boost::signals2::connection AttachOnScanProcessFileHasBeenViewedSignal(OnScanProcessFileHasBeenViewedSignal_t::slot_type&& slot) = 0;
		virtual boost::signals2::connection AttachOnScanProcessSignatureDetectedSignal(OnScanProcessSignatureDetectedSignal_t::slot_type&& slot) = 0;
	};

}} /// end namespace FileSystemScanner::Core

#endif /// !FILESYSTEMS_SCANNER_CORE_ISCANNER_EVENTS_H