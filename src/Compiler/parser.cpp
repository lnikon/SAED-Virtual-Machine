#include "parser.h"

CParser::CParser(QVector<SDataToken> dataTokens, QVector<SCodeToken> codeTokens) :
m_dataTokens(dataTokens), m_codeTokens(codeTokens)
{
}
void CParser::work(CReaderWriter* writer, QString filename)
{
//	CReaderWriter* writer = new CReaderWriter;

//	writer->addSection(writeHeader(writer->getSignature(), writer -> getVersion()), filename);
	writer->addSection(writeDataSection());
	writer->addSection(writeCodeSection());
	writer->addSection(writeDataTableSection());
	writer->addSection(writeCodeTableSection());
	writer->write(filename);
}
//
//QByteArray CParser::writeHeader(QString signature, int32 version)
//{
//	SHeader header = createHeader(signature, version);
//	QByteArray out;
//
//	out.append(header.signature);
//	out.append(header.version);
//	out.append(header.recordCount);
//
//	for (int i = 0; i < header.recordCount; ++i)
//	{
//		out.append(static_cast<int>(header.recordTable[i].type));
//		out.append(header.recordTable[i].offset);
//		out.append(header.recordTable[i].size);
//	}
//	return out;
//}
//SHeader CParser::createHeader(QString signature, int32 version)
//{
//	QString signature = signature;
//	int version = version;
//	int offset = sizeof signature + sizeof(int);
//
//	SHeader header(signature, version);
//
//	if (!m_dataTokens.isEmpty())
//	{
//		SHeaderTable headerTable(ESectionType::Data, offset, m_dataTokens.size());
//		header.recordTable.push_back(headerTable);
//		offset += writeDataSection().size();
//	}
//
//	{
//		SHeaderTable headerTable(ESectionType::Code, offset, m_codeTokens.size());
//		header.recordTable.push_back(headerTable);
//		offset += writeCodeSection().size();
//	}
//
//	if (!m_dataTokens.isEmpty())
//	{
//		SHeaderTable headerTable(ESectionType::DataTable, offset, m_dataTokens.size());
//		header.recordTable.push_back(headerTable);
//		offset += writeDataTableSection().size();
//	}
//
//	/*
//	{
//	SHeaderTable headerTable(ESectionType::CodeTable, offset, m_dataTokens.size());
//	header.arrayTable.push_back(headerTable);
//	offset += writeCodeTableSection(m_out);
//	}
//
//	*/
//	header.recordCount = header.recordTable.size();
//	header.size = offset;
//	return header;
//}

QByteArray CParser::writeCodeSection()
{
	QByteArray out;
	int offset = 0;			//size of codeSection
	for (int i = 0; i < m_codeTokens.size(); i++)
	{
		out.append(m_codeTokens[i].opcode.opcode);
		offset += sizeof m_codeTokens[i].opcode.opcode;
		for (int j = 0; j < m_codeTokens[i].argValue.size(); j++)
		{
			out.append(m_codeTokens[i].argValue[j]);
			offset += sizeof m_codeTokens[i].argValue[j];
		}
	}
	return out;
}

QByteArray CParser::writeDataSection()
{
	QByteArray out;
	int offset = 0;		//size of dataSection
	uint8 zero = 0;
	int remainder = 0;
	for (int i = 0; i < m_dataTokens.size(); i++)
	{
		m_nameGrammar[m_dataTokens[i].identifierName] = offset;
		int dataType = static_cast<int>(m_dataTokens[i].type);
		if (dataType)
		{
			int typeToSize = static_cast<int> (pow(2, dataType));
			remainder = offset % typeToSize;
			offset += typeToSize - remainder;
		}
		else

		{
			remainder = 0;
		}
		while (remainder != 0)
		{
			out.append(zero);
			remainder--;
		}
		out.append(m_dataTokens[i].value);
		offset += pow(2, dataType);
	}
	return out;
}
QByteArray CParser::writeDataTableSection()
{
	QByteArray out;
	int offset = 0;
	for (int i = 0; i < m_dataTokens.size(); i++)
	{
		int dataType = static_cast<int>(m_dataTokens[i].type);
		out.append(dataType);
		out.append(m_dataTokens[i].identifierName);
		out.append(m_dataTokens[i].value);
		out.append(m_dataTokens[i].line);
		offset += sizeof(int) + m_dataTokens[i].identifierName.size() +
			/*dataType +*/ sizeof(int);
	}
	return out;
}
QByteArray CParser::writeCodeTableSection()
{
	QByteArray out;
	int offset = 0;
	/*for (int i = 0; i < m_codeTokens.size(); i++)
	{
	out << m_codeTokens[i].opcode.opcode;

	}*/
//	return offset;
	return out;
}

