#define OS_Windows 1 // lazy define
#if defined(OS_Windows)
	#include <Windows.h>
#endif
#if defined(OS_Posix)
	#include <pthread.h>
#endif

namespace Sys {

#if defined(OS_Windows)
	class CriticalSection::Impl {
	private:
		CRITICAL_SECTION sgMemCrit;
	public:
		Impl()  { }
		~Impl() { }
	public:
		void Create(void) {
			InitializeCriticalSection(&sgMemCrit);
		}
		void Destroy(void) {
			DeleteCriticalSection(&sgMemCrit);
		}
		void Lock() {
			EnterCriticalSection(&sgMemCrit);
		}
		void Unlock() {
			LeaveCriticalSection(&sgMemCrit);
		}
	};
#endif
#if defined(OS_Posix)
	class CriticalSection::Impl {
	private:
		pthread_mutex_t sgMemCrit;
	public:
		Impl()  { }
		~Impl() { }
	public:
		void Create(void) {
			pthread_mutex_init(&sgMemCrit);
		}
		void Destroy(void) {
			pthread_mutex_destroy(&sgMemCrit);
		}
		void Lock() {
			pthread_mutex_lock(&sgMemCrit);
		}
		void Unlock() {
			pthread_mutex_unlock(&sgMemCrit);
		}
};
#endif

	CriticalSection::CriticalSection(void) : m_pImpl(new CriticalSection::Impl()) { }
	CriticalSection::~CriticalSection(void) { }
	void CriticalSection::Create(void) { m_pImpl->Create(); }
	void CriticalSection::Destroy(void) { m_pImpl->Destroy(); }
	void CriticalSection::Enter(void) { m_pImpl->Lock(); }
	void CriticalSection::Leave(void) { m_pImpl->Unlock(); }

}
