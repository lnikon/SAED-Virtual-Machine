#include "parser.h"

void CParser::work(CReaderWriter* writer, QVector<SDataToken> dataTokens, QVector<SCodeToken> codeTokens,
				   QVector<QString> dataTable, QString filename)
{
	m_dataTokens = dataTokens;
	m_codeTokens = codeTokens;
	m_dataTable = dataTable;

	QByteArray dataSection = writeDataSection();						//OK
	QByteArray codeSection = writeCodeSection();						//OK
	QByteArray dataTableSection = writeDataTableSection();				//OK

//	testDataSection(dataSection);										//OK
//	testCodeSection(codeSection);										//OK
//	testDataTableSection(dataTableSection);								//OK

	writer->addSection(dataSection, ESectionType::Data);
	writer->addSection(codeSection, ESectionType::Code);
	writer->addSection(dataTableSection, ESectionType::DataTable);
	writer->write(filename);

}

QByteArray CParser::writeCodeSection()
{

	qDebug() << "writeCodeSection\n\n";
	QByteArray out;
	int offset = 0;			//size of codeSection

	QHash<QString, int>::Iterator i;

	qDebug() << "nameGrammer";
	for (i = m_nameGrammar.begin(); i != m_nameGrammar.end(); ++i)
	{
		qDebug() << i.key() << " : " << i.value();
	}
	qDebug() << "end of nameGrammar\n\n";


	qDebug() << "\n\ndataTable";
	for (int i = 0; i < m_dataTable.size(); ++i)
	{
		qDebug() << i << " = " << m_dataTable[i];
	}
	qDebug() << "end of dataTable\n\n";


	for (int i = 0; i < m_codeTokens.size(); i++)
	{
		qDebug() << "m_codeTokens[i].opcode.opcode = " << m_codeTokens[i].opcode.opcode;
		out.append(m_codeTokens[i].opcode.opcode);
		offset += sizeof m_codeTokens[i].opcode.opcode;
		qDebug() << "offset = " << offset;

		for (int j = 0; j < m_codeTokens[i].argValue.size(); j++)
		{
			if ((j == 0 && m_codeTokens[i].opcode.arg1Type == static_cast<uint16>(EArgumentType::Data)) ||
				(j == 1 && m_codeTokens[i].opcode.arg2Type == static_cast<uint16>(EArgumentType::Data)) ||
				(j == 2 && m_codeTokens[i].opcode.arg3Type == static_cast<uint16>(EArgumentType::Data)))
			{
				int indexInDataTable = m_codeTokens[i].argValue[j];
				qDebug() << "indexInDataTable = " << indexInDataTable;
				QString identifierName = m_dataTable[indexInDataTable];
				qDebug() << "identifierName = " << identifierName;
				int indexInSymbolTable = m_nameGrammar[identifierName];
				out.append(indexInSymbolTable);
				qDebug() << " indexInSymbolTable = " << indexInSymbolTable;
				offset += sizeof indexInSymbolTable;
				qDebug() << "\t\t\t offset = " << offset;
			}
			else
			{
				out.append(m_codeTokens[i].argValue[j]);
				qDebug() << " m_codeTokens[i].argValue[j] = " << m_codeTokens[i].argValue[j];
				offset += sizeof m_codeTokens[i].argValue[j];
				qDebug() << "\t\t\t offset = " << offset;
			}
		}
		qDebug() << "out.size() = " << out.size();
	}
	qDebug() << "size of codeSection" << out.size();
	qDebug() << "end of writeCodeSection\n\n";
	return out;
}
void CParser::testCodeSection(QByteArray& codeSection)
{
	qDebug() << "testCodeSection Start\n\n";
	QByteArray in = codeSection;

	for (int pos = 0; pos < in.size(); ++pos)
	{
		qDebug() << pos << static_cast<int>(in[pos]);
	}
	qDebug() << "\n\nend of testCodeSection";
}
QByteArray CParser::writeDataSection()
{
	qDebug() << "writeDataSection\n\n";

	QByteArray out;
	int offset = 0;		//size of dataSection
	uint16 zero = 0;
	int remainder = 0;
	int typeToSize = 0;
	int currOffset = 0;
	//	int prevOffset = 0;

	for (int i = 0; i < m_dataTokens.size(); ++i)
	{
		//		qDebug() << "\n\n\ni = " << i << "\n\n\n";
		int dataType = static_cast<int>(m_dataTokens[i].type);
		//		qDebug() << "dataType = " << dataType;
		typeToSize = static_cast<int> (pow(2, dataType));
		//		qDebug() << "typeToSize = " << typeToSize;

		if (currOffset % typeToSize != 0)
		{
			int remainder = typeToSize - (currOffset % typeToSize);
			//			qDebug() << " remainder = " << remainder;
			while (remainder != 0)
			{
				out.append(zero);
				//				qDebug() << "zero	" << zero;		///////
				remainder--;
				//				qDebug() << "remainder--" << remainder;
				++currOffset;
			}
		}
		m_nameGrammar[m_dataTokens[i].identifierName] = currOffset;
		//		qDebug() << m_dataTokens[i].identifierName << " = " << m_nameGrammar[m_dataTokens[i].identifierName];
		out.append(m_dataTokens[i].value);
		//		qDebug() << "m_dataTokens[i].value = " << m_dataTokens[i].value;
		currOffset += typeToSize;
		//		qDebug() << "currOffset = " << currOffset;
		//		qDebug() << "SIZE = " << out.size();
	}
	//	qDebug() << out.size(); ///////////

	qDebug() << "size of dataSection" << out.size();
	qDebug() << "\n\nend of writeDataSection\n\n";
	return out;
}
void CParser::testDataSection(QByteArray& dataSection)
{
	qDebug() << "testDataSection Start\n\n";
	QByteArray in = dataSection;

	for (int pos = 0; pos < in.size(); ++pos)
	{
		qDebug() << pos << static_cast<int>(in[pos]);
	}

	qDebug() << "\n\nend of testDataSection";
}
QByteArray CParser::writeDataTableSection()
{
	qDebug() << "writeDataTableSection\n\n";
	QByteArray out;
	int offset = 0;
	for (int i = 0; i < m_dataTokens.size(); i++)
	{
		int dataType = static_cast<int>(m_dataTokens[i].type);
		out.append(dataType);
		qDebug() << "m_dataTokens[i].type = " << dataType;

		QByteArray sizeofidname = m_dataTokens[i].identifierName.toUtf8();
		qDebug() << "bytearray sizeofidname.size() = " << sizeofidname.size();

		out.append(sizeofidname.size());
		out.append(sizeofidname);

		//	out.append(m_dataTokens[i].identifierName);
		qDebug() << "sizeof m_dataTokens[i].identifierName = " << sizeof m_dataTokens[i].identifierName;
		qDebug() << "m_dataTokens[i].identifierName = " << m_dataTokens[i].identifierName;
		//		out.append(m_dataTokens[i].value);
		//		qDebug() << "m_dataTokens[i].value = " << m_dataTokens[i].value;
		out.append(m_dataTokens[i].line);
		qDebug() << "m_dataTokens[i].line = " << m_dataTokens[i].line;
		//offset += sizeof(int) + m_dataTokens[i].identifierName.size() +
		//	/*dataType +*/ sizeof(int);
		qDebug() << "offset = " << offset;
	}
	qDebug() << "size of dataTableSection" << out.size();
	qDebug() << "end of writeDatatableSection\n\n";
	return out;
}
void CParser::testDataTableSection(QByteArray& dataTableSection)
{
	qDebug() << "testDataTableSection Start\n\n";

	QByteArray in = dataTableSection;

	for (int pos = 0; pos < in.size(); )
	{
		int nDataType = static_cast<int>(in[pos]);
		qDebug() << "nDataType = " << nDataType;
		++pos;
		int nIdNameSize = static_cast<int>(in[pos]);
		qDebug() << "IdentifierNameSize = " << nIdNameSize;
		++pos;
		QString strIdName = 0;
		for (int j = 0; j < nIdNameSize; ++j)
		{
			strIdName += static_cast<QChar>(in[pos]);
			++pos;
		}
		qDebug() << "IdentifierName = " << strIdName;
		int nLine = static_cast<int>(in[pos]);
		qDebug() << "line = " << nLine;
		++pos;
	}

	qDebug() << "\n\nend of testDataTableSection";
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

