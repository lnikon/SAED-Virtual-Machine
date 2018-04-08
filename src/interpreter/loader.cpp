#include "loader.h"
#include <QByteArray.h>

CLoader::SInfo CLoader::load(CMemoryPtr memory, CReaderWriter& reader, uint32 stackSize)
{
	SHeader header = reader.readHeader();
	QByteArray code = reader.readCodeSection(header);
	QByteArray data = reader.readDataSection(header);
	memory->resize(stackSize + code.size() + data.size());

	SInfo info;
	info.dataIndex = 0;
	info.dataSize = data.size();
	info.codeIndex = data.size();
	info.codeSize = data.size() + code.size();
	info.stackSize = stackSize;
	info.stackIndex = stackSize + code.size() + data.size() - 1; // last element of memmory

	uint32 index = 0;
	// write data
	for (index; index < data.size(); ++index)
	{
		memory->operator[](index) = data[index];
	}

	// write code
	for (index; index < info.codeIndex + info.codeSize; ++index)
	{
		memory->operator[](index) = code[index - info.codeIndex];
	}

	return info;
}
