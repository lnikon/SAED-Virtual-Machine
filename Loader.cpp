#include "Loader.h"

void CLoader::work(CRam& ram, QDataStream& in)
{
	if (!checkSignature(in))
	{
		throw "wrong signature";
	}

	int version = getInt(in);
	int sectionCount = getInt(in);

	QVector<SHeaderTable> sections;

	for (int i(0); i < sectionCount; ++i)
	{
		ESctionType type = static_cast<ESctionType>(getInt(in));
		int offset = getInt(in);
		int size = getInt(in) - m_sSignature.size() - 8 - sectionCount * 12; // 8 -> version, sectionCount, 12 -> type, offset, size
		sections.push_back(SHeaderTable(type, offset, size));
	}

	string fileBody;
	qint8 c;
	while (!in.atEnd())
	{
		in.operator>>(c);
		fileBody.push_back(c);
	}

	unsigned int currentRamIndex = 0;

	for (auto it : sections)
	{
		if (it.type == ESctionType::Code || it.type == ESctionType::Data)
		{
			if (it.type == ESctionType::Code)
			{
				ram.setIP(currentRamIndex);
			}
			for (int i(0); i < it.size; ++i)
			{
				ram[currentRamIndex++] = fileBody[it.offset + i];
			}
		}
	}
}

bool CLoader::checkSignature(QDataStream& in)
{
	QString fileSignature;;
	qint8 c;
	for (int i(0); i < m_sSignature.size(); ++i)
	{
		in.operator>>(c);
		fileSignature += c;
	}
	return (m_sSignature == fileSignature);
}

int CLoader::getInt(QDataStream& in)
{
	int version = 0;
	qint8 c;
	for (int i(0); i < 4; ++i)
	{
		in.operator>>(c);
		version <<= 8;
		version += static_cast<int> (c);
		cout << i << ": " << version << endl;
	}
	return version;
}