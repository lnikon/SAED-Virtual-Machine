#include "memory.h"

CMemory::CMemory(uint32 ms)
{
	if (ms > 0)
	{
		m_aMemory.resize(ms);
	}
}

void CMemory::SetStackSize(uint32 nStackSize)
{
	m_nStackSize = nStackSize;
}

uint32 CMemory::GetStackSize()
{
	return m_nStackSize;
}

uint32 CMemory::GetMemorySize()
{
	return m_aMemory.size();
}

uint8& CMemory::operator[](uint32 ind)
{
	return m_aMemory[ind];
}

const uint8& CMemory::operator[](uint32 ind) const
{
	return m_aMemory[ind];
}

template<typename T>
T& CMemory::at(uint32 ind)
{
	return reinterpret_cast<T&>(m_aMemory[ind]);
}

template<typename T>
inline constexpr T& CMemory::at(uint32 ind) const
{
	return reinterpret_cast<constexpr T&>(m_aMemory[ind]);
}
