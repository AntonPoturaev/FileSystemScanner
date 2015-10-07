/**
	Project - File System Scanner
	Copyright (c) 2015 Poturaev A.S.
	e-mail: a.s.poturaev@gmail.com
*/

#include "stdafx.h"
#include "IScanner.h"
#include "CollectUniqueFilePathes.h"
#include "MappedFileReadOnly.h"
#include "SignatureStoreFactory.h"

#include <atomic>
#include <cassert>

#include <boost/optional.hpp>
#include <boost/threadpool.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/variant.hpp>

namespace FileSystemScanner { namespace Core {

	struct IScanner::_Impl
		: public std::enable_shared_from_this<_Impl>
	{
	public:
		typedef boost::optional<ByteString_t> OptionalSignatureGUID_t;
		typedef std::weak_ptr<_Impl> SelfWeakPtr_t;
		typedef boost::iterator_range<Details::SignatureStoreStorage_t::const_iterator> SignatureRange_t;
		typedef std::function<FindAlgorithm_t()> FindAlgorithmGetter_t;
		typedef std::shared_ptr<Details::UniquePathStore_t> UniquePathStorePtr_t;
		typedef boost::variant<UniquePathStorePtr_t, ByteDataRangeStorePtr_t> DataForCheck_t;
		typedef ByteDataRangeStore_t::value_type ByteDataRangeNode_t;
		
		class _Data4CheckScheduler
			: public boost::static_visitor<void>
		{
		public:
			_Data4CheckScheduler(_Impl& self)
				: m_Self(self)
			{
			}

			void operator()(UniquePathStorePtr_t const& ups) const
			{
				assert(ups && "Bad data!");

				size_t taskIndex = 0;
				for (auto const& current : *ups)
					if (!m_Self._ScheduleTaskByPath(current, taskIndex++))
						m_Self._OnErrorSignal();
			}

			void operator()(ByteDataRangeStorePtr_t const& bdrs) const
			{
				assert(bdrs && "Bad data!");
				size_t taskIndex = 0;
				for (auto const& current : *bdrs)
					if (!m_Self._ScheduleTaskByDataRange(current, taskIndex++))
						m_Self._OnErrorSignal();
			}

		private:
			_Impl& m_Self;
		};

		struct _Data4CheckGetSize
			: public boost::static_visitor<size_t>
		{
			size_t operator()(UniquePathStorePtr_t const& ups) const
			{
				assert(ups && "Bad data!");
				return ups->size();
			}

			size_t operator()(ByteDataRangeStorePtr_t const& bdrs) const
			{
				assert(bdrs && "Bad data!");
				return bdrs->size();
			}
		};

	public:
		_Impl(FindAlgorithmGetter_t&& findAlgorithmGetter, size_t poolSize)
			: m_FindAlgorithmGetter(std::forward<FindAlgorithmGetter_t>(findAlgorithmGetter))
			, m_Pool(poolSize)
			, m_Wait4Abort(false)
		{
			assert(m_FindAlgorithmGetter && "Bad data!");
		}

		~_Impl() {
			_AbortScan();
		}

		void _AbortScan()
		{
			m_Wait4Abort.store(true);
			m_Pool.wait();
			m_Wait4Abort.store(false);
		}

		bool _Prepare(boost::filesystem::path signatureStorePath, InputPathStorePtr_t const& pathStore)
		{
			m_OnInitializationStartSignal();

			if (_LoadSignatureStore(signatureStorePath))
			{
				m_OnInitializationStepCompleteSignal("_LoadSignatureStore");

				if (auto ups = _CollectFiles(pathStore))
				{
					m_DataForCheck = ups;
					m_OnInitializationStepCompleteSignal("_CollectFiles");
					return true;
				}
			}

			return false;
		}

		bool _Prepare(boost::filesystem::path signatureStorePath, ByteDataRangeStorePtr_t const& dataRangesStore)
		{
			m_OnInitializationStartSignal();

			if (_LoadSignatureStore(signatureStorePath))
			{
				m_OnInitializationStepCompleteSignal("_LoadSignatureStore");

				if (dataRangesStore && !dataRangesStore->empty())
				{
					m_OnFilesCountReceivedSignal(dataRangesStore->size());
					
					m_DataForCheck = dataRangesStore;

					m_OnInitializationStepCompleteSignal("ByteDataRangeStore");

					return true;
				}
			}

			return false;
		}

		bool _LoadSignatureStore(boost::filesystem::path const& signatureStorePath)
		{
			try {
				m_SignatureStore = SignatureStoreFactory::Create(signatureStorePath);
			}
			catch (Exception const&)
			{
				_OnErrorSignal();
				return false;
			}
			catch (boost::filesystem::filesystem_error const&)
			{
				_OnErrorSignal();
				return false;
			}
			catch (std::exception const&)
			{
				_OnErrorSignal();
				return false;
			}
			catch (...)
			{
				_OnErrorSignal();
				return false;
			}

			if (!m_SignatureStore || m_SignatureStore->empty())
			{
				_OnErrorSignal();
				return false;
			}

			return true;
		}

		UniquePathStorePtr_t _CollectFiles(InputPathStorePtr_t const& pathStore) const
		{
			if (pathStore)
			{
				_OnErrorSignal();
				return nullptr;
			}

			UniquePathStorePtr_t result;
			try {
				result.reset(new Details::UniquePathStore_t(Details::CollectUniqueFilePathes::Call(*pathStore)));
			}
			catch (Exception const&)
			{
				_OnErrorSignal();
				return nullptr;
			}
			catch (boost::filesystem::filesystem_error const&)
			{
				_OnErrorSignal();
				return nullptr;
			}
			catch (std::exception const&)
			{
				_OnErrorSignal();
				return nullptr;
			}
			catch (...)
			{
				_OnErrorSignal();
				return nullptr;
			}

			if (!result || result->empty())
			{
				_OnErrorSignal();
				return nullptr;
			}

			m_OnFilesCountReceivedSignal(result->size());

			return result;
		}

		void _EntryByPathStore(boost::filesystem::path signatureStorePath, InputPathStorePtr_t pathStore)
		{
			if (_Prepare(signatureStorePath, pathStore))
			{
				m_OnInitializationEndSignal();

				if (!m_Pool.schedule(std::bind(&_Impl::_Routine, this)))
					_OnErrorSignal();
			}
			else
				_OnErrorSignal();
		}

		void _EntryByDataRangesStore(boost::filesystem::path signatureStorePath, ByteDataRangeStorePtr_t const& dataRangesStore)
		{
			if (_Prepare(signatureStorePath, dataRangesStore))
			{
				m_OnInitializationEndSignal();

				if (!m_Pool.schedule(std::bind(&_Impl::_Routine, this)))
					_OnErrorSignal();
			}
			else
				_OnErrorSignal();
		}

		void _Routine()
		{
			m_OnScanProcessStartSignal();
			boost::apply_visitor(_Data4CheckScheduler(*this), m_DataForCheck);
		}

		bool _ScheduleTaskByDataRange(ByteDataRangeNode_t const& rangeNode, size_t taskIndex) {
			return m_Pool.schedule([=]() { _TaskByDataRange(SelfWeakPtr_t(shared_from_this()), rangeNode, taskIndex); });
		}

		static void _TaskByDataRange(SelfWeakPtr_t selfWeak, ByteDataRangeNode_t const& rangeNode, size_t taskIndex)
		{
			if (auto const self = selfWeak.lock())
				self->_DoTaskByDataRange(rangeNode, taskIndex);
		}

		void _DoTaskByDataRange(ByteDataRangeNode_t const& rangeNode, size_t taskIndex) const
		{
			if (m_Wait4Abort.load())
				return;

			if (auto const found = _Find(rangeNode.second, boost::make_iterator_range(*m_SignatureStore)))
			{
				m_OnScanProcessSignatureDetectedSignal(rangeNode.first, *found);
				m_OnScanProcessFileHasBeenViewedSignal();
			}

			if (taskIndex == boost::apply_visitor(_Data4CheckGetSize(), m_DataForCheck))
				m_OnScanProcessEndSignal();
		}

		bool _ScheduleTaskByPath(boost::filesystem::path const& path, size_t taskIndex) {
			return m_Pool.schedule([=]() { _TaskByPath(SelfWeakPtr_t(shared_from_this()), path, taskIndex); });
		}

		static void _TaskByPath(SelfWeakPtr_t selfWeak, boost::filesystem::path const& path, size_t taskIndex)
		{
			if (auto const self = selfWeak.lock())
				self->_DoTaskByPath(path, taskIndex);
		}

		void _DoTaskByPath(boost::filesystem::path const& path, size_t taskIndex) const
		{
			if (m_Wait4Abort.load())
				return;

			Details::MappedFileReadOnly const file(path);

			if (m_Wait4Abort.load())
				return;

			if (auto const found = _Find(file.GetRange(), boost::make_iterator_range(*m_SignatureStore)))
			{
				m_OnScanProcessSignatureDetectedSignal(path, *found);
				m_OnScanProcessFileHasBeenViewedSignal();
			}

			if (taskIndex == boost::apply_visitor(_Data4CheckGetSize(), m_DataForCheck))
				m_OnScanProcessEndSignal();
		}

		OptionalSignatureGUID_t _Find(InputByteRange_t const& input, SignatureRange_t const& sigRange) const
		{
			OptionalSignatureGUID_t result;

			if (auto const finder = m_FindAlgorithmGetter())
			{
				for (auto const& currentSignature : sigRange)
				{
					if (m_Wait4Abort.load())
						break;

					if (finder(input, currentSignature.value))
					{
						result = currentSignature.guid;
						break;
					}
				}
			}
			else
				_OnErrorSignal();

			return result;
		}

		void _OnErrorSignal(std::string&& message = "", Exception::State state = Exception::State::kEScritical) const {
			m_OnErrorSignal(std::forward<std::string>(message), state);
		}

	public:
		FindAlgorithmGetter_t const m_FindAlgorithmGetter;
		boost::threadpool::pool m_Pool;
		std::atomic<bool> m_Wait4Abort;

		OnInitializationStartSignal_t m_OnInitializationStartSignal;
		OnInitializationEndSignal_t m_OnInitializationEndSignal;
		OnInitializationStepCompleteSignal_t m_OnInitializationStepCompleteSignal;
		OnFilesCountReceivedSignal_t m_OnFilesCountReceivedSignal;
		OnErrorSignal_t m_OnErrorSignal;
		OnScanProcessStartSignal_t m_OnScanProcessStartSignal;
		OnScanProcessEndSignal_t m_OnScanProcessEndSignal;
		OnScanProcessFileHasBeenViewedSignal_t m_OnScanProcessFileHasBeenViewedSignal;
		OnScanProcessSignatureDetectedSignal_t m_OnScanProcessSignatureDetectedSignal;

		SignatureStorePtr_t m_SignatureStore;
		DataForCheck_t m_DataForCheck;
	};

	IScanner::~IScanner() {}

	boost::signals2::connection IScanner::AttachOnInitializationStartSignal(OnInitializationStartSignal_t::slot_type&& slot) {
		return m_Impl->m_OnInitializationStartSignal.connect(std::forward<OnInitializationStartSignal_t::slot_type>(slot));
	}

	boost::signals2::connection IScanner::AttachOnInitializationEndSignal(OnInitializationEndSignal_t::slot_type&& slot) {
		return m_Impl->m_OnInitializationEndSignal.connect(std::forward<OnInitializationEndSignal_t::slot_type>(slot));
	}

	boost::signals2::connection IScanner::AttachOnInitializationStepCompleteSignal(OnInitializationStepCompleteSignal_t::slot_type&& slot) {
		return m_Impl->m_OnInitializationStepCompleteSignal.connect(std::forward<OnInitializationStepCompleteSignal_t::slot_type>(slot));
	}

	boost::signals2::connection IScanner::AttachOnFilesCountReceivedSignal(OnFilesCountReceivedSignal_t::slot_type&& slot) {
		return m_Impl->m_OnFilesCountReceivedSignal.connect(std::forward<OnFilesCountReceivedSignal_t::slot_type>(slot));
	}

	boost::signals2::connection IScanner::AttachOnErrorSignal(OnErrorSignal_t::slot_type&& slot) {
		return m_Impl->m_OnErrorSignal.connect(std::forward<OnErrorSignal_t::slot_type>(slot));
	}

	boost::signals2::connection IScanner::AttachOnScanProcessStartSignal(OnScanProcessStartSignal_t::slot_type&& slot) {
		return m_Impl->m_OnScanProcessStartSignal.connect(std::forward<OnScanProcessStartSignal_t::slot_type>(slot));
	}

	boost::signals2::connection IScanner::AttachOnScanProcessEndSignal(OnScanProcessEndSignal_t::slot_type&& slot) {
		return m_Impl->m_OnScanProcessEndSignal.connect(std::forward<OnScanProcessEndSignal_t::slot_type>(slot));
	}

	boost::signals2::connection IScanner::AttachOnScanProcessFileHasBeenViewedSignal(OnScanProcessFileHasBeenViewedSignal_t::slot_type&& slot) {
		return m_Impl->m_OnScanProcessFileHasBeenViewedSignal.connect(std::forward<OnScanProcessFileHasBeenViewedSignal_t::slot_type>(slot));
	}

	boost::signals2::connection IScanner::AttachOnScanProcessSignatureDetectedSignal(OnScanProcessSignatureDetectedSignal_t::slot_type&& slot) {
		return m_Impl->m_OnScanProcessSignatureDetectedSignal.connect(std::forward<OnScanProcessSignatureDetectedSignal_t::slot_type>(slot));
	}

	void IScanner::ScanAsync(boost::filesystem::path const& signatureStorePath, InputPathStorePtr_t const& pathStore) 
	{
		_CheckFree();
		m_Impl->m_Pool.schedule(std::bind(&_Impl::_EntryByPathStore, m_Impl, signatureStorePath, pathStore));
	}

	void IScanner::ScanAsync(boost::filesystem::path const& signatureStorePath, ByteDataRangeStorePtr_t const& dataRangesStore)
	{
		_CheckFree();
		m_Impl->m_Pool.schedule(std::bind(&_Impl::_EntryByDataRangesStore, m_Impl, signatureStorePath, dataRangesStore));
	}

	void IScanner::AbortScan() {
		m_Impl->_AbortScan();
	}

	bool IScanner::IsFree() const {
		return m_Impl->m_Pool.empty();
	}

	size_t IScanner::_DefaultPoolSize() {
		return boost::thread::hardware_concurrency() * 2;
	}

	IScanner::IScanner(size_t poolSize)
		: m_Impl(new _Impl(std::bind(&IScanner::_GetFindAlgorithmInstance, this), poolSize))
	{
	}

	void IScanner::_CheckFree() const
	{
		if (!IsFree())
			ThrowException("File system scanner is busy!");
	}

}} /// end namespace FileSystemScanner::Core
