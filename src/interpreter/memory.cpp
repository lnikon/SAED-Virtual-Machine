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

// ================================

void CMemory::resize(uint32 newSize)
{
	m_aMemory.resize(newSize);
}
