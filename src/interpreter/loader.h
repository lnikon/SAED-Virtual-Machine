#ifndef LOADER_H
#define LOADER_H

#include <QString>
#include <QByteArray>

#include "memory.h"
#include "../compiler/readerwriter.h"
#include "../compiler/instructions.h"

class CLoader
{
public:
	struct SInfo
	{
		uint32 dataIndex;
		uint32 dataSize;

		uint32 codeIndex;
		uint32 codeSize;

		uint32 stackIndex;
		uint32 stackSize;
	};
public:
	SInfo load(CMemoryPtr memory, CReaderWriter& reader, uint32 stackSize);
};

#endif // LOADER_H
