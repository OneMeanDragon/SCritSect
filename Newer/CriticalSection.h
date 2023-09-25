#if !defined(_CRITICALSECTION_HEADER)
#define _CRITICALSECTION_HEADER
#pragma once

namespace Sys {

	class CriticalSection {
	private:
		class Impl;
		std::unique_ptr<Impl> m_pImpl;
	public:
		CriticalSection(void);
		~CriticalSection(void);
	public:
		void Create(void);
		void Destroy(void);
		void Enter(void);
		void Leave(void);
	};

}

#endif
