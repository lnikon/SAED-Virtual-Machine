#include "disparser.h"

void CDisParser::work(CReaderWriter* reader, QByteArray buffer)
{
	m_reader = reader;
	m_buffer = buffer;
	getHeader();
}

void CDisParser::getHeader()
{
	QByteArray headerBuffer;
	headerBuffer = m_buffer.left(128);
	QDataStream headerStream(&headerBuffer, QIODevice::ReadWrite);
	headerStream >> m_SHeader.sSignature;
	headerStream >> m_SHeader.nVersion;
	headerStream >> m_SHeader.recordCount;

	int eType;
	int32 offset;
	int32 size;
	for (int i = 0; i < m_reader -> getHeaderSize(); /*++i*/)
	{
		headerStream >> eType;
		headerStream >> offset;
		headerStream >> size;
		m_SHeader.recordTable.push_back(SHeaderTable(static_cast<ESectionType>(eType), offset, size));
		i += sizeof eType + sizeof offset + sizeof size;
	}
}

QVector<SDataToken> CDisParser::getDataTokens()
{
	int offset = m_SHeader.recordTable[static_cast<int>(ESectionType::DataTable)].offset;
	int dataTableSize = m_SHeader.recordTable[static_cast<int>(ESectionType::DataTable)].size;
	QByteArray dataTableBuffer = m_buffer.mid(offset, dataTableSize);
	QDataStream dataTableStream(&dataTableBuffer, QIODevice::ReadWrite);

	int32 dataType;
	QString idName;
	QByteArray value;
	int32 line;

	for (int i = 0; i < dataTableSize;)
	{
		dataTableStream >> dataType;
		dataTableStream >> idName;
		dataTableStream >> value;
		dataTableStream >> line;
		m_SDataTokens.push_back(SDataToken(static_cast<EType>(dataType), idName, value, line));
		i += sizeof dataType + sizeof idName + sizeof value + sizeof line;
	}

	return m_SDataTokens;
}

QHash<QString, int32> CDisParser::getDataNames()
{
	int offset = 0;
	int remainder = 0;

	for (int i = 0; i < m_SDataTokens.size(); ++i)
	{
		int dataType = static_cast<int>(m_SDataTokens[i].type);
		int typeToSize = static_cast<int>(pow(2,dataType));
		remainder = offset % typeToSize;
		while (remainder != 0)
		{
			++offset;
			--remainder;
		}
		m_DataNames[m_SDataTokens[i].identifierName] = offset;
		offset += pow(2, dataType);
	}
	return m_DataNames;
}

QVector<SCodeToken> CDisParser::getCodeTokens()
{
	int offset = m_SHeader.recordTable[static_cast<int>(ESectionType::Code)].offset;
	int codeSize = m_SHeader.recordTable[static_cast<int>(ESectionType::Code)].size;
	QByteArray codeBuffer = m_buffer.mid(offset, codeSize);
	QDataStream codeStream(&codeBuffer, QIODevice::ReadWrite);

	UOpcode op;
	QVarLengthArray<uint32, 3> args;
//	QVarLengthArray<int> args(3);
//	QVarLengthArray<int, 3> args;
	//	int ch;

	uint32 arg;

	for (int i = 0; i < codeSize;)
	{
		codeStream >> op.opcode;
//		codeStream >> ch;		//ays depqum ashxatum e
		//codeStream >> args[0];
		//codeStream >> args[1];
		//codeStream >> args[2];
		codeStream >> arg;
		args.push_back(arg);
		codeStream >> arg;
		args.push_back(arg);
		codeStream >> arg;
		args.push_back(arg);

		m_SCodeTokens.push_back(SCodeToken(op, args));
	}

	return m_SCodeTokens;
}





