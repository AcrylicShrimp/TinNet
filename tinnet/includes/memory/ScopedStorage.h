
#ifndef _TINNET_MEMORY_SCOPEDSTORAGE_H

#define _TINNET_MEMORY_SCOPEDSTORAGE_H

#include <cstddef>

namespace tinnet::memory {
	class ScopedStorage final {
	private:
		void *pOrigin;
		void *pAligned;

	public:
		ScopedStorage();
		ScopedStorage(std::size_t nSize);
		ScopedStorage(ScopedStorage &&sRhs) noexcept;
		~ScopedStorage() noexcept;

	public:
		ScopedStorage &operator=(ScopedStorage &&sRhs);

	public:
		inline void *origin() const noexcept
		{
			return this->pOrigin;
		}
		template<class T>
		inline T *origin() const noexcept
		{
			return reinterpret_cast<T *>(this->pOrigin);
		}
		inline void *aligned() const noexcept
		{
			return this->pAligned;
		}
		template<class T>
		inline T *aligned() const noexcept
		{
			return reinterpret_cast<T *>(this->pAligned);
		}

	public:
		// TODO: Provide swap support here.
	};
}	 // namespace tinnet::memory

#endif