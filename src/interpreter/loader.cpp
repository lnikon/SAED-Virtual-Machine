#include "loader.h"

uint32 CLoader::load(const QString& filePath, CMemory& memory)
{
	CRW reader;
	reader.read(filePath);
	QByteArray code = reader.getSection(CRW::ESectionType::Code);
	QByteArray data = reader.getSection(CRW::ESectionType::Data);

	if (code.size() + data.size() >= memory.getSize())
	{
		throw "error. memory has not enough size";
	}

	uint32 index = 0;

	for (uint32 i = 0; i < data.size(); ++i)
	{
		memory[index++] = data[i];
	}

	for (uint32 i = 0; i < code.size(); ++i)
	{
		memory[index++] = code[i];
	}

	return data.size();
}
