
#include "tinnet/includes/memory/ScopedStorage.h"

#include <cstdint>
#include <cstdlib>
#include <utility>

namespace tinnet::memory {
	ScopedStorage::ScopedStorage() : pOrigin{nullptr}, pAligned{nullptr} {}

	ScopedStorage::ScopedStorage(std::size_t nSize)
	{
		this->pOrigin  = std::malloc(nSize + 32);
		this->pAligned = reinterpret_cast<void *>(
			(reinterpret_cast<std::uint64_t>(this->pOrigin) + 31) & ~31);	 // 32byte alignment.
	}

	ScopedStorage::ScopedStorage(ScopedStorage &&sRhs) noexcept : ScopedStorage()
	{
		using std::swap;

		swap(this->pOrigin, sRhs.pOrigin);
		swap(this->pAligned, sRhs.pAligned);
	}

	ScopedStorage::~ScopedStorage() noexcept
	{
		if (this->pOrigin) std::free(this->pOrigin);
	}

	ScopedStorage &ScopedStorage::operator=(ScopedStorage &&sRhs)
	{
		if (&sRhs == this) return *this;

		this->~ScopedStorage();

		this->pOrigin  = sRhs.pOrigin;
		this->pAligned = sRhs.pAligned;
		sRhs.pOrigin   = nullptr;
		sRhs.pAligned  = nullptr;

		return *this;
	}
}	 // namespace tinnet::memory