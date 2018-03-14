#ifndef MEMORY_H
#define MEMORY_H

#include <memory>

#include <QVector>

#include "../compiler/instructions.h"

class CMemory
{
public:
	enum
	{
		DefaultSize = 0x00010000,
		MaxSize = 0x01000000,

		DefaultStackSize = 0x00001000,
		MinStackSize = 0x00000100,
		MaxStackSize = 0x00100000
	};

public:
	CMemory(uint32 ms = 0);

	~CMemory() = default;
	CMemory(CMemory const&) = delete;
	CMemory(CMemory&&) = delete;
	void operator=(CMemory const&) = delete;
	void operator=(CMemory&&) = delete;

public:
	void SetStackSize(uint32 nStackSize);
	uint32 GetStackSize();

	uint32 GetMemorySize();

public:
	template <typename T>
	T& at(uint32 ind);

	template <typename T>
	constexpr T& at(uint32 ind) const;

	uint8& operator[](uint32 ind);
	const uint8& operator[](uint32) const;

private:
	uint32 m_nStackSize = DefaultStackSize;
	QVector<uint8> m_aMemory;

};

using CMemoryPtr = std::shared_ptr<CMemory>;


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

#endif // !MEMORY_H