/**
	Project - File System Scanner
	Copyright (c) 2015 Poturaev A.S.
	e-mail: a.s.poturaev@gmail.com
*/

#pragma once

#if !defined(FILESYSTEMS_SCANNER_CORE_ISCANNER_H)
#	define FILESYSTEMS_SCANNER_CORE_ISCANNER_H

#include "IScannerFwd.h"
#include "IScanerProtocol.h"
#include "IScannerEvents.h"

#include <functional>

namespace FileSystemScanner { namespace Core {

	class IScanner
		: public IScanerProtocol
		, public IScannerEvents
	{
		struct _Impl;

	protected:
		typedef std::function<bool(InputByteRange_t const& input, ByteString_t const& pattern)> FindAlgorithm_t;
		
	public:
		virtual ~IScanner();

		virtual boost::signals2::connection AttachOnInitializationStartSignal(OnInitializationStartSignal_t::slot_type&& slot) override;
		virtual boost::signals2::connection AttachOnInitializationEndSignal(OnInitializationEndSignal_t::slot_type&& slot) override;
		virtual boost::signals2::connection AttachOnInitializationStepCompleteSignal(OnInitializationStepCompleteSignal_t::slot_type&& slot) override;
		virtual boost::signals2::connection AttachOnFilesCountReceivedSignal(OnFilesCountReceivedSignal_t::slot_type&& slot) override;
		virtual boost::signals2::connection AttachOnErrorSignal(OnErrorSignal_t::slot_type&& slot) override;
		virtual boost::signals2::connection AttachOnScanProcessStartSignal(OnScanProcessStartSignal_t::slot_type&& slot) override;
		virtual boost::signals2::connection AttachOnScanProcessEndSignal(OnScanProcessEndSignal_t::slot_type&& slot) override;
		virtual boost::signals2::connection AttachOnScanProcessFileHasBeenViewedSignal(OnScanProcessFileHasBeenViewedSignal_t::slot_type&& slot) override;
		virtual boost::signals2::connection AttachOnScanProcessSignatureDetectedSignal(OnScanProcessSignatureDetectedSignal_t::slot_type&& slot) override;

		virtual void ScanAsync(boost::filesystem::path const& signatureStorePath, InputPathStorePtr_t const& pathStore) override;
		virtual void ScanAsync(boost::filesystem::path const& signatureStorePath, ByteDataRangeStorePtr_t const& dataRangesStore) override;
		virtual void AbortScan() override;

		virtual bool IsFree() const override;

		static size_t _DefaultPoolSize();

	protected:
		IScanner(size_t poolSize = _DefaultPoolSize());
		void _CheckFree() const;
		virtual FindAlgorithm_t _GetFindAlgorithmInstance() const = 0;
				
	private:
		std::shared_ptr<_Impl> m_Impl;
	};

}} /// end namespace FileSystemScanner::Core

#endif /// !FILESYSTEMS_SCANNER_CORE_ISCANNER_H
